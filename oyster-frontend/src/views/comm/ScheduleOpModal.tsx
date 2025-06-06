import * as React from "react";
import ModalTemplate from "./ModalTemplate";
import Typography from "@mui/material/Typography";
import Box from "@mui/material/Box";
import { DateTimePicker } from "@mui/x-date-pickers";
import { AdapterDayjs } from "@mui/x-date-pickers/AdapterDayjs";
import { LocalizationProvider } from "@mui/x-date-pickers/LocalizationProvider";
import MenuItem from "@mui/material/MenuItem";
import FormControl from "@mui/material/FormControl";
import Select, { SelectChangeEvent } from "@mui/material/Select";
import InputLabel from "@mui/material/InputLabel";
import Button from "@mui/material/Button";
import SendIcon from "@mui/icons-material/Send";
import Checkbox from "@mui/material/Checkbox";
import Stack from "@mui/material/Stack";
import Chip from "@mui/material/Chip";
import { styled } from "@mui/material/styles";
import DeviceData from "./DeviceDataInterface";
import TextField from "@mui/material/TextField";
import { Dayjs } from "dayjs";

const base_url = `${import.meta.env.VITE_API_URL}`;

interface ScheduleModalProps {
  closeFn: any;
  devices: DeviceData[];
}

const ListItem = styled("li")(({ theme }) => ({
  margin: theme.spacing(0.5),
}));

export default function ScheduleOpModal(props: ScheduleModalProps) {
  const [doSendNow, setDoSendNow] = React.useState<boolean>(false);
  const [dateIsValid, setDateIsValid] = React.useState<boolean>(false);
  const [isValidOpSelected, setIsValidOpSelected] =
    React.useState<boolean>(false);
  const [scheduleDate, setScheduleDate] = React.useState<Date>();
  const [operation, setOperation] = React.useState<string>();
  const [duration, setDuration] = React.useState<number>();

  const [devices, setDevices] = React.useState<readonly DeviceData[]>(
    props.devices
  );

  function formatDate(date: Date) {
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, "0"); // Months are 0-indexed
    const day = String(date.getDate()).padStart(2, "0");
    const hours = String(date.getHours()).padStart(2, "0");
    const minutes = String(date.getMinutes()).padStart(2, "0");
    const seconds = String(date.getSeconds()).padStart(2, "0");

    return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
  }

  const handleDelete = (chipToDelete: DeviceData) => () => {
    setDevices((chips) =>
      chips.filter((chip) => chip._id !== chipToDelete._id)
    );
  };

  async function handleConfirm() {
    const ids = devices.map((device: DeviceData) => {
      return device._id;
    });

    try {
      const response = await fetch(base_url + "/farm/cage/addActiveSchedule", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          farm_ids: ids,
          schedule: [
            {
              dates: [
                doSendNow ? formatDate(new Date()) : formatDate(scheduleDate!),
              ],
              command: operation,
              duration: duration,
              status: "pending",
            },
          ],
        }),
      });
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }
    } catch (error) {
      console.error("Error sending command:", error);
    }

    props.closeFn();
  }

  const handleSendNowClicked = (event: React.ChangeEvent<HTMLInputElement>) => {
    setDoSendNow(event.target.checked);
  };

  const handleDateTimeChosen = (
    value: Dayjs | null,
    context: { validationError: string | null }
  ) => {
    if (value != null) {
      var d = value.toDate();
      if (context.validationError == null) {
        setScheduleDate(d);
        setDateIsValid(true);
      } else {
        setDateIsValid(false);
      }
    }
  };

  const handleOperationChosen = (
    event: SelectChangeEvent,
    _child?: React.ReactNode
  ) => {
    var choice = event.target.value;
    if (choice != null) {
      setOperation(choice);
      setIsValidOpSelected(true);
    } else {
      setIsValidOpSelected(false);
    }
    console.log(isValidOpSelected);
  };

  const handleDuration = (
    event: React.ChangeEvent<HTMLInputElement>,
    _child?: object
  ) => {
    setDuration(parseInt(event.target.value));
  };

  return (
    <LocalizationProvider dateAdapter={AdapterDayjs}>
      <ModalTemplate label="Schedule Bulk Operation">
        <Stack spacing={2}>
          <Typography>Selected Devices:</Typography>

          <Box
            sx={{
              display: "flex",
              justifyContent: "center",
              flexWrap: "wrap",
              listStyle: "none",
              p: 0.5,
              m: 0,
            }}
            component="ul"
          >
            {devices.map((data: DeviceData, idx: number) => {
              return (
                <ListItem key={idx}>
                  <Chip label={data._id} onDelete={handleDelete(data)} />
                </ListItem>
              );
            })}
          </Box>

          <Typography>Choose Date/Time: </Typography>

          <DateTimePicker
            disablePast
            disabled={doSendNow}
            onAccept={handleDateTimeChosen}
          />

          <Box sx={{ minWidth: 500 }}>
            <Typography>Send Now: </Typography>
            <Checkbox
              color="primary"
              onChange={handleSendNowClicked}
              inputProps={{
                "aria-label": "schedule-now",
              }}
            />
          </Box>

          <Box>
            <Typography>Set Duration: </Typography>
            <TextField
              id="outlined-basic"
              label="Duration (in minutes)"
              variant="outlined"
              type="number"
              sx={{ width: "100%", marginTop: 2 }}
              onChange={handleDuration}
            />
          </Box>

          <Typography>Choose Operation: </Typography>

          <FormControl fullWidth>
            <InputLabel id="operation-select-label">Operation</InputLabel>
            <Select
              labelId="operation-select-label"
              id="operation-select"
              label="Operation"
              defaultValue={""}
              onChange={handleOperationChosen}
            >
              <MenuItem value={1}>Up</MenuItem>
              <MenuItem value={0}>Down</MenuItem>
            </Select>
          </FormControl>

          <Button
            variant="contained"
            startIcon={<SendIcon />}
            disabled={
              !((dateIsValid || doSendNow) && isValidOpSelected && duration)
            }
            onClick={handleConfirm}
          >
            Send
          </Button>
        </Stack>
      </ModalTemplate>
    </LocalizationProvider>
  );
}
