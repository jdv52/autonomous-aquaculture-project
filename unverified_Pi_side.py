import paho.mqtt.client as mqtt
import serial
import time
import json

MQTT_BROKER = "172.29.112.170" 
MQTT_PORT = 1883
LORA_PORT = 'COM7' #change if hooked directly to serial rather than via the USB-to-UART adapter
BAUD_RATE = 9600
PACKET_SIZE = 100 #fine tune latter
MAX_PACKETS = 10 #possibly increase; size doesn't really matter on the Pi side
BUFFER_SIZE = 260 #LoRa constraint
ACK_TIMEOUT = 20 #possibly increase; possibly scrap
RETRY_LIMIT = 10 #possibly increase; possibly scrap

total_packets = -1
received_packets = ["" for _ in range(MAX_PACKETS)]
mqtt_task_list = []

lora = serial.Serial(LORA_PORT, BAUD_RATE, timeout=1)

address_lookup = {}

def add_address(id, address):
    """Add an ID-address pair to the lookup table."""
    address_lookup[id] = address

def get_address(id):
    """Fetch the address based on the given ID."""
    return address_lookup.get(id, None)


def send_command(command):
    lora.write((command + "\r\n").encode('utf-8'))
    time.sleep(0.1)
    lora.flushInput()

def configure_lora():
    send_command("AT+IPR=9600")
    send_command("AT+CRFOP=22")
    send_command("AT+NETWORKID=6")
    send_command("AT+BAND=915000000")
    send_command("AT+PARAMETER=9,7,1,12")
    send_command("AT+ADDRESS=1")
    print("LoRa module configured.")

configure_lora()

def send_fragmented_message(message, address):
    global total_packets
    header_size = len(f"{0},{0},")
    fragment_size = PACKET_SIZE - header_size
    
    total_packets = (len(message) + fragment_size - 1) // fragment_size
    
    for i in range(total_packets):
        fragment = message[i * fragment_size: (i + 1) * fragment_size]
        packet_header = f"{i},{total_packets},"
        packet = packet_header + fragment
        command = f"AT+SEND={address},{len(packet)},{packet}"
        
        retries = 0
        while retries < RETRY_LIMIT:
            print(f"Sending: {packet}")
            send_command(command)
            if wait_for_ack(i):
                break
            retries += 1
        else:
            print(f"Failed to receive ACK for packet {i}")

def wait_for_ack(expected_id):
    start_time = time.time()
    buffer = ""
    while time.time() - start_time < ACK_TIMEOUT:
        if lora.in_waiting:
            char = lora.read().decode("utf-8")
            if char == '\n':
                print(f"Received buffer: {buffer.strip()}")
                
                if "ACK:" in buffer:
                    ack_id = int(buffer.split("ACK:")[1].split(",")[0].strip())
                    if ack_id == expected_id:
                        print(f"Received ACK for packet {expected_id}")
                        return True
                buffer = ""
            else:
                buffer += char
    return False

def on_message(client, userdata, msg):
    message = msg.payload.decode("utf-8")
    #print(f"Received MQTT message: {message}")
    topic_parts = msg.topic.split("/")
    address=get_address(topic_parts[1])
    if address:
            mqtt_task_list.append((message, address))
            #print(f"Appended task with address {address}")

def process_received_data(received):
    global total_packets
    print(f"Processing: {received}")
    if not received.startswith("+RCV="):
        return
    parts = received.split(",")
    if len(parts) < 6:
        return
    try:
        address = parts[0].split('=')[-1]
        packet_id = int(parts[2])
        total_packets = int(parts[3])
        message_data = ",".join(parts[4:]).rsplit(",", 2)[0]
        received_packets[packet_id] = message_data
        print(f"Storing Packet {packet_id + 1} of {total_packets}: {message_data}")
        ack_message = f"ACK:{packet_id}"
        print("sending ack")
        send_command(f"AT+SEND={address},{len(ack_message)},{ack_message}")
        if all_packets_received():
            reconstruct_message()
    except ValueError:
        print("Error parsing received data")

def all_packets_received():
    if total_packets == -1:
        return False
    return all(received_packets[i] for i in range(total_packets))

def reconstruct_message():
    global total_packets, received_packets
    print("Reassembling message...")
    full_message = "".join(received_packets[:total_packets])
    print(f"Final Reconstructed Message: {full_message}")
    received_packets = ["" for _ in range(MAX_PACKETS)]
    total_packets = -1
    #Use the reconstructed JSON to find out what topic the message needs to be publised to.
    try:
        data = json.loads(full_message)
        if (len(data) == 2):
            #print(data.get("farm_id", "Key not found")) 
            #print(data.get("LoRa_address", "Key not found"))
            add_address(data.get("farm_id"),data.get("LoRa_address"))
    except json.JSONDecodeError as e:
        print(f"JSON decoding failed: {e}")
    #print(get_address(data.get("farm_id")))

mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, "logan")
mqtt_client.on_connect = lambda client, userdata, flags, rc, properties: client.subscribe("farm/+/cage")
mqtt_client.on_message = on_message
mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
mqtt_client.loop_start()

buffer = ""
while True:
    if (mqtt_task_list):
        message, address = mqtt_task_list[0]
        send_fragmented_message(message, address)
        mqtt_task_list.remove(mqtt_task_list[0])
    else:
        if lora.in_waiting:
            char = lora.read().decode("utf-8")
            if char == '\n':
                process_received_data(buffer.strip())
                buffer = ""
            else:
                buffer += char
