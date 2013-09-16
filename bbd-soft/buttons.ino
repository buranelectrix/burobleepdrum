
void BUTTONS() 
{
  shift=digitalRead(3);

  if (shift==0 && prevshift==1)
  {
    shift_latch++;
    shift_latch%=2;
  }
  prevshift=shift;
  
  
  ///////////////////////////////////////////////////sequence select

  if (shift==0&&recordbutton==1)
  {
    prevpot2=pot2;
    if (bouncer1.read()==0 ){ //red
      banko=63;
      bankpr=4;
      bankpg=0;
      bankpb=0;
    }
    if (bouncer4.read()==0){  //yellow
      banko=31;
      bankpr=4;
      bankpg=4;
      bankpb=0;
    }
    if (bouncer2.read()==0 || banko==0){   //blue
      banko=0;
       bankpr=0;
      bankpg=0;
      bankpb=8;
    }
    if (bouncer3.read()==0){//green
      banko=95;
      bankpr=0;
      bankpg=3;
      bankpb=0;
    }
    
    if ((shift == 0) && (digitalRead(7) == 0)) 
    {
      revbutton = 1;
    }
    else
    {
      revbutton = 0;
    }
    
    if (revbutton==1 && prevrevbutton==0)
    {
        playmode++;
        playmode%=2;
    }

    prevrevbutton=revbutton;
  }

/*
    if (bouncertap.read()==LOW)
    {
       play=1;
       ratepot=(analogRead(14))<<4;
       taptempo=ratepot<<4;
    }
*/    
    
 

  if (shift==1)
  {
    if (bouncer1.fallingEdge())
    {
      B1_trigger=1;  
    }
    else
    {
      B1_trigger=0;
    }

    if (bouncer4.fallingEdge())
    {
      B4_trigger=1; 
    }
    else
    {
      B4_trigger=0;
    }

    if (bouncer2.fallingEdge())
    {
      B2_trigger=1; 
    }
    else
    {
      B2_trigger=0;
    }

    if (bouncer3.fallingEdge())
    {
      B3_trigger=1; 
    }
    else
    {
      B3_trigger=0;
    }
  }
}

