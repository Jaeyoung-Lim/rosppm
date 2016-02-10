void set_ppm(){
    //Channel 1 to Channel 4 receives command values for control
    //minimum 650 max 1700
    for(int i=0; i<number_of_outputs; i++){
    pulses[0] = (int) cmd_val[0]*512.0+1175.0;
    }
    
}
