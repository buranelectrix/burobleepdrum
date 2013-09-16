unsigned long recordoffsettimer,offsetamount,taptempof;
int potX;

void loop() {
  bouncertap.update ( );
  bouncer1.update ( );
  bouncer2.update ( );
  bouncer4.update ( );
  bouncer3.update ( );
  LEDS();
  BUTTONS();
  RECORD();

  if (noise_mode==0)
  {
    pot1=((analogRead(0))>>1)+2;
    pot2=((analogRead(1))>>2)+32; 
  }
  if (noise_mode==1)
  {
    if (shift_latch==0)
    {
      pot1=((analogRead(0))>>1)+1;
      pot2=((analogRead(1))>>2)+1;
    }
    if (shift_latch==1)
    {
      pot3=(analogRead(0))<<4; ////////////////MAKE ME BETTERERER  
      pot4=analogRead(1)<<2;
    }
  }

  
  ////////////////////////////
  // trigger input
  
  trigger_in_read=digitalRead(16);
  
  if (trigger_in_read==1 && prev_trigger_in_read==0)
  {
    trigger_input=1;
    if (ext_sync_mode == 1)
    {
      fake_taptempo = (micros() - fake_prevtap) >> 2;
      fake_prevtap = micros();
    }
  }
  else
  {
    trigger_input=0;
  }

  prev_trigger_in_read=trigger_in_read;
  
  
  //////////////////////////////////////
  // trigger out
  
  eigth=loopstep%4;

  if(eigth==0)
  {
    digitalWrite(12, HIGH);
  }
  else
  {
    digitalWrite(12, LOW);
  }
  
  
  if (ext_sync_mode == 1)
  {
    taptempof=fake_taptempo;
    recordoffsettimer=micros()-fake_prev ;
    offsetamount=taptempof-(taptempof>>2 );
    if ((recordoffsettimer)>(offsetamount))
    {
      loopstepf=loopstep+1;
      loopstepf%=32;
    }
  }
  else
  {
    taptempof=taptempo;
    recordoffsettimer=micros()-prev ;
    offsetamount=taptempof-(taptempof>>2 );
    if ((recordoffsettimer)>(offsetamount))
    {
      loopstepf=loopstep+1;
      loopstepf%=32;
    }
  }



  if (play==1)
  {
    if (onetime==1)
    {
      taptempo=4000000;
      onetime=0;
    }
    else
    {
      prevloopstep=loopstep;
      preva=eigth;

      if (recordmode==1)
      {
        if (ext_sync_mode == 1)
        {
          if (trigger_input == 1)
          {
            fake_prev = micros();
            loopstep++;
            loopstep%=32;
            fake_trig_cnt = 0;
          }
          else
          if (((micros() - fake_prev) > (fake_taptempo)) && (fake_trig_cnt < 3))
          {
            fake_prev = micros();
            loopstep++;
            loopstep%=32;
            fake_trig_cnt ++;
          }
        }
        
        else if (micros() - prev > (taptempof) ) 
        {
          prev = micros();    
          loopstep++;
          loopstep%=32;
        }
      }
    }

    B4_loop_trigger=B4_sequence[loopstep+banko];
    B1_loop_trigger=B1_sequence[loopstep+banko];
    B2_loop_trigger=B2_sequence[loopstep+banko];
    B3_loop_trigger=B3_sequence[loopstep+banko];
  }

  if (play==0)
  {
    loopstep=0;
    prev==0;
    B4_loop_trigger=0;
    B1_loop_trigger=0;
    B2_loop_trigger=0;
    B3_loop_trigger=0;

   // ext_sync_mode = 0;
  }


  if (loopstep!=prevloopstep && B3_loop_trigger==1)
  {
    B3_seq_trigger=1;
  }
  else 
  {
    B3_seq_trigger=0;
  }

  if (loopstep!=prevloopstep && B2_loop_trigger==1)
  {
    B2_seq_trigger=1;
  }
  else 
  {
    B2_seq_trigger=0;
  }

  if (loopstep!=prevloopstep && B4_loop_trigger==1)
  {
    B4_seq_trigger=1;
  }
  else 
  {
    B4_seq_trigger=0;
  }

  if (loopstep!=prevloopstep && B1_loop_trigger==1)
  {
    B1_seq_trigger=1;
  }
  else 
  {
    B1_seq_trigger=0;
  }

  if (B3_trigger==1 || B3_seq_trigger==1)
  {
    index3=0;
    accumulator3=0;
    B3_latch=1;
  }

  if (B4_trigger==1 || B4_seq_trigger==1)
  {
    index4=0;
    accumulator4=0;
    B4_latch=1;
  }
  
  if (B1_trigger==1)
  {
    index=0;
    accumulator=0;
    B1_latch=1;
  }

  if (B1_seq_trigger==1)
  {
    index_freq_1=0;
    accu_freq_1=0;
    B1_seq_latch=1;
  }
  
  if (B2_seq_trigger==1)
  {
    index_freq_2=0;
    accu_freq_2=0;
    B2_seq_latch=1;
  }

  if (B2_trigger==1)
  {
    index2=0;
    accumulator2=0;
    B2_latch=1;
  }


  //////////////////////////////////////////////////////////////// T A P
/*
  if (shift==1)
  {
      if (bouncertap.fallingEdge())
      {
        t++;
        t%=2;
        tapbank[t]=((micros())-prevtap)>>2;
        taptempo=((tapbank[0]+tapbank[1])>>1);
        prevtap=micros();
      }
  }
*/

  if (bouncertap.fallingEdge())
  {
    if (shift == 1) // shift nestisknut
    {
      t++;
      t%=2;
      tapbank[t]=((micros())-prevtap)>>2;
      taptempo=((tapbank[0]+tapbank[1])>>1);
      prevtap=micros();
    }
    else
    {
      ext_sync_mode ++;
      ext_sync_mode %= 2;
    }
  }
  
/*  if (ext_sync_mode == 1)
  {
    taptempo = (micros() - prevtap) >> 2;
    prevtap = micros();
  }
  */
}


