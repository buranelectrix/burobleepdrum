void RECORD() {

  playbutton = digitalRead(7);
  if (playbutton != pplaybutton && playbutton == LOW && shift==1){
    //loopstep=31;
    play++;  
    play%=2;
  }
  else{
  }
  pplaybutton = playbutton;


  recordbutton=digitalRead(8);
  if (recordbutton == LOW && recordbutton!=precordbutton) {
    //    loopstep=31;
    record++;
    record%=2;
    play=1;
  } 

  else{
  }

  if (play==0){
    record=0;
  }


  ////////////////////////////////////////////////////////////////////erase 

  precordbutton=recordbutton;
  if (shift==LOW && recordbutton == LOW){

   
 eef++;
    if (eef>=84){
       erase=1;
    play=1;
    record=0;
    if (bouncer1.read()==0){ 
      B1_sequence[ef+banko]=0;
    }
    if (bouncer2.read()==0){ 
      B2_sequence[ef+banko]=0;
    }
    if (bouncer4.read()==0){ 
      B4_sequence[ef+banko]=0;
    }
    if (bouncer3.read()==0){ 
      B3_sequence[ef+banko]=0;
    }
    ef++;
      if (ef==32){
        ef=0;
        eef=0;
      }

  }
  }

  if (playbutton==LOW && recordbutton == LOW){
    eee++;
    if (eee>=84){
      erase=1;
      play=1;
      record=0;
      B1_sequence[ee+banko]=0;
      B2_sequence[ee+banko]=0;
      B4_sequence[ee+banko]=0;
      B3_sequence[ee+banko]=0;
      ee++;
      if (ee==32){
        ee=0;
        eee=0;
      }
    }

  }
  else {
    erase=0;
  }



  if (record==1)
  {

    if (B1_trigger==1){
      B1_sequence[loopstepf+banko]=1;
	 B1_freq_sequence[loopstepf+banko]=pot1;

    }

    if (B2_trigger==1){
      B2_sequence[loopstepf+banko]=1;
      B2_freq_sequence[loopstepf+banko]=(pot2);
    }

    if (B4_trigger==1){
      B4_sequence[loopstepf+banko]=1;
    }

    if (B3_trigger==1){
      B3_sequence[loopstepf+banko]=1;
    }

  }

}



