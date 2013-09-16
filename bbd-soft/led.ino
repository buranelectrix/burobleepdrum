void LEDS() 
{
   
  
    analogWrite(6,255-(bout>>1)); 
    analogWrite(9,255-(gout>>1)); 
    analogWrite(5,255-(rout>>1));
  
    
  if (noise_mode==1)
  {    
    rout=r;
    gout=g;
    bout=b;
    if (shift_latch==1)
    {
      if (record==0 && play==0 )
      {
        r+=sample>>3;
        b+=4;
      }
    }
    if (shift_latch==0)
    {
      if (record==0 && play==0 )
      {
        g+=sample>>3;
        b+=2;
      }
    }
  }
  else
  {
  }

  preveigth=eigth;

  if (erase==1)
  {
    e=16;
  }
  if (erase==0)
  {
    e=0;
  }

  if (g>1)
  { 
    g--;
  }
  if(g<=1)
  { 
    g=0;
  }

  if (r>1)
  { 
    r--;
  }
  if(r<=1)
  { 
    r=0;
  }

  if (b>1)
  { 
    b--;
  }
  if(b<=1)
  { 
    b=0;
  }

  if (noise_mode==0)
  {
    if (record==0 && play==0 )
    {
      rout=16;
      gout=16;
      bout=16;
      
      if ((ext_sync_mode == 1) && (digitalRead(16) == 0))
      {
        rout=8;
        gout=8;
        bout=8;
      }
    }
  }

  if (play==1 && record ==0)
  {
    bout=b;
    rout=r;
    gout=g;

    ///////////////////////////////////////////////////CHANGE TO ONLY += WHEN LOOPSTEP != PREVLOOPSTEP

    if (loopstep==0 && prevloopstep==1 )
    {
      r=64;
      g=64;
      b=64;
    }
    else if (loopstep%4 ==0 && prevloopstep%4!=0 )
    {
      r+=64;
      g+=64;
      b+=64;
    }
    else 
    {
      b=bankpb;
      r=bankpr;
      g=bankpg;
    }
  }

  if (play==1 && record==1 )
  {
    bout=b;
    rout=r;
    gout=g;

    if( loopstep==0 )
    {
      r=32;
      g=16;
      b=6;
    }
    else  if( loopstep==16 )
    {
      r=32;
      g=0;
      b=0;
    }
    else if( loopstep==4 || loopstep==8 || loopstep==12   || loopstep==20 || loopstep==24 || loopstep==28)
    {
      r=48;
      g=0;
      b=0;
    }
    else 
    {
      b=bankpb;
      r=bankpr;
      g=bankpg;
    }
  }
}






