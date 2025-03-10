
import * as React from 'react';
import ModalTemplate from './ModalTemplate'
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import { DateTimePicker } from '@mui/x-date-pickers';
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import MenuItem from '@mui/material/MenuItem';
import FormControl from '@mui/material/FormControl';
import Select, { SelectChangeEvent } from '@mui/material/Select';
import InputLabel from '@mui/material/InputLabel';
import Button from '@mui/material/Button';
import SendIcon from '@mui/icons-material/Send';
import Checkbox from '@mui/material/Checkbox';
import Stack from '@mui/material/Stack';



const base_url = `${import.meta.env.VITE_API_URL}`

export default function ScheduleOpModal() {

    const [doSendNow, setDoSendNow] = React.useState<boolean>(false);
    const [dateIsValid, setDateIsValid] = React.useState<boolean>(false);
    const [isValidOpSelected, setIsValidOpSelected] = React.useState<boolean>(false);
    const [scheduleDate, setScheduleDate] = React.useState<Date>();
    const [operation, setOperation] = React.useState<boolean>();


    async function testAPI() {
        console.log(`Hitting ${base_url}/test_pub...`);
    
        try {
          const response = await fetch(base_url + '/test_pub', {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json'
            },
          });
          if (!response.ok) {
            const errorData = await response.json();
            throw new Error(errorData.message || "Something went wrong");
          }
    
          console.log("Successfully hit!");
          // const data = await response.json();
          // setResult(data.message);
        } catch (error) {
          console.error('Error fetching sensor data:', error);
        }
    }

    const handleSendNowClicked = (event: React.ChangeEvent<HTMLInputElement>) => {
        setDoSendNow(event.target.checked);
    };

    const handleDateTimeChosen = (value: TValue, context: FieldChangeHandlerContext) => {
        if (value != null) {
            var d = value["$d"];
            if (context.validationError == null) {
                setScheduleDate(d);
                setDateIsValid(true);
            } else {
                setDateIsValid(false);
            }
        }
    }

    const handleOperationChosen = (event: SelectChangeEvent, child?: object) => {
        var choice = event.target.value;
        if (choice != null) {
            setOperation(choice == 1);
            setIsValidOpSelected(true);
        } else {
            setIsValidOpSelected(false);
        }
        console.log(isValidOpSelected);
    }

    return (
        <LocalizationProvider dateAdapter={AdapterDayjs}>
            <ModalTemplate label="Schedule Bulk Operation">

                <Stack spacing={2}>
                    <h3>Choose Date/Time:</h3>
                    
                    <DateTimePicker 
                        disablePast
                        disabled={doSendNow}
                        onAccept={handleDateTimeChosen}
                        />

                    <Box sx={{ minWidth: 120 }}>
                        <h3>Send Now</h3>
                        <Checkbox
                            color="primary"
                            // indeterminate={numSelected > 0 && numSelected < rowCount}
                            // checked={rowCount > 0 && numSelected === rowCount}
                            onChange={handleSendNowClicked}
                            inputProps={{
                            'aria-label': 'schedule-now',
                            }}
                        />
                    </Box>
                    

                    <h3>Choose Operation:</h3>
                    
                    <FormControl fullWidth>
                        <InputLabel id="operation-select-label">Operation</InputLabel>
                        <Select
                            labelId="operation-select-label"
                            id="operation-select"
                            label="Operation"
                            defaultValue={-1}
                            onChange={handleOperationChosen}
                            >
                            <MenuItem value={0}>Up</MenuItem>
                            <MenuItem value={1}>Down</MenuItem>
                        </Select>
                    </FormControl>

                    

                    <Button
                        variant="contained"
                        startIcon={<SendIcon/>}
                        disabled = {!((dateIsValid || doSendNow) && isValidOpSelected)}
                        onClick = {
                            () => {
                                testAPI();
                                
                            }
                        }>
                            Send
                    </Button>
                </Stack>
            </ModalTemplate>
        </LocalizationProvider>
    )
}