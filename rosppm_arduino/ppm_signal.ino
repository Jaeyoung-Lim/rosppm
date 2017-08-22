void set_ppm(){
    //Channel 1 to Channel 4 receives command values for control
    //minimum 650 max 1700
    
    for(int i=0; i<number_of_outputs; i++){
    pulses[i] = (int) cmd_val[i]*512.0+1175.0; //Encode stick inputs into pulse values
    }
    
}

void read_ppm(){
    // Read RX values
  for (int i = 1; i < 7; i++){                                        //for each of the 6 channels:
     in_pulses[i] = pulseIn(ppmin_PIN, HIGH, 20000);                            //read the receiver signal
     
     if (in_pulses[i] == 0) {in_pulses[i] = buff_pulses[i];} else {buff_pulses[i] = in_pulses[i];}    //if the signal is good then use it, else use the previous signal
     
     read_fval[i] = (float) in_pulses[i];
     read_val[i] = (read_fval[i]-1175.0)/512.0;
     //constrain (in_pulses[i], 0, 511);                                       //make sure that the value stays within the disired boundries
  }
 }
