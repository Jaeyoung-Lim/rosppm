void ppm_command(){
    //Channel 1 to Channel 4 receives command values for control
    pulses[0] = map(cmd_val[0], 0, 1023, 650, 1700); // Copy Pulse values
    pulses[1] = map(cmd_val[1], 0, 1023, 650, 1700); //Map Pulse values
    pulses[2] = map(cmd_val[2], 0, 1023, 650, 1700); // Copy Pulse values
    pulses[3] = map(cmd_val[3], 0, 1023, 650, 1700); // Copy Pulse values
    
}
