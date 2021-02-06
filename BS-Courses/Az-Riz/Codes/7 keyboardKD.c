/*
   Written by :ozhan(ojan) KD for AVR-XMEGA evaluation board
   Chip: ATmega128A
   Fusebit setting : XTAL = 16MHz
   3x4 Keyboard is defined as follow:

   1   2   3   4
   5   6   7   8
   9   0   -  blank

  Pressing any key displays keyboard code on 7segments from left to right and
  one LED turns on by any key hit.
*/

#include  <mega128.h>
#include "KEY7SEG_0.h"

extern volatile unsigned char DIGITS[6];
extern volatile unsigned char dot_points;
extern volatile unsigned char LEDS;

void increaseTime();
void updateKDVariables();
 int go=1;
 int blink=0;    
int h,m,s;
int lastChangeMode;
void main()
{
 unsigned char key_code=nokey_code;
 unsigned char old_key_code=nokey_code;
 unsigned char i=0,j=0;     
 int currentPos=-1; // -1:none 0:H 1:M 2:S
 init_7seg();
 h=23;
 m=59;
 s=55;
updateKDVariables();
LEDS=0x04;
 dot_points=0x00;
 #asm("sei")   

 while(1)
 {
   increaseTime();
  
  for(j=0;j<10;j++)
  {              
    if(blink==0)
    {                
    updateKDVariables();  
    if(currentPos!=-1)
    {   
    lastChangeMode++;
      DIGITS[5-currentPos*2]=11; 
      DIGITS[5-currentPos*2-1]=11;        
    }
      else
         lastChangeMode=0;
      
    }
    else
    {   
     updateKDVariables();
    }
    blink++;
    blink%=2;
    
    if(lastChangeMode==10)// end modify mode
    {
    lastChangeMode=0;     
    currentPos=-1; 
     dot_points=0x00;
    }   
  
   delay_ms(100);
  key_code=get_key();
  if (key_code!= old_key_code)
  {
   old_key_code=key_code;
   if (key_code!=nokey_code)
   {          
    if(key_code==11) 
    {
       // ++  
       lastChangeMode=0; 
       switch(currentPos)
       {
       case 0:
        h++;
        if(h==24)
            h=0;
        break;
       case 1:
        m++;
        if(m==60)
            m=0;
        break; 
       case 2:
        s++;
        if(s==60)
            s=0;
        break;
       }
    }                   
    else if(key_code==10) 
    {
       // --  
       lastChangeMode=0; 
          switch(currentPos)
       {
       case 0:
        h--;
        if(h==-1)
            h=23;
        break;
       case 1:
        m--;
        if(m==-1)
            m=59;
        break; 
       case 2:
        s--;
        if(s==-1)
            s=59;
        break;
       }
    } 
    else if(key_code==8) 
    {
       // -->      
       lastChangeMode=0; 
       if(currentPos==-1)
        currentPos=0;
       currentPos++;
        if(currentPos>2)
        currentPos=0;
       LEDS=0x04;
       dot_points=0x20;
       for(i=0;i<currentPos*2;i++)
           dot_points= dot_points>>1;
       dot_points += (dot_points/2);
          
    }
     else if(key_code==7) 
    {
       // <--         
       lastChangeMode=0;    
       if(currentPos==-1)
        currentPos=0;
       currentPos--;
       if(currentPos<0)
        currentPos=2;
       LEDS=0x04;       
        dot_points=0x20;
       for(i=0;i<currentPos*2;i++)
           dot_points= dot_points>>1; 
       dot_points += (dot_points/2);
    } 
    else if(key_code==0) 
    {
       go=1;
    }
     else if(key_code==9) 
    {
       go=0; 
    }
    else if(key_code==1) 
    {
       h=m=s=0;
    } 
   }
  } 
  }
  
 }
}

void increaseTime()
{
    if(go==0)
        return;  
    s++;
    if(s==60)
    {
        s=0;
        m++;
        if(m==60)
        {
        m=0;
        h++;
        if(h==24)
        {
            h=0;
            
        }
        }
    }
}

void updateKDVariables()
{

 DIGITS[5]=h/10; DIGITS[4]=h%10; DIGITS[3]=m/10;
 DIGITS[2]=m%10; DIGITS[1]=s/10; DIGITS[0]=s%10;
 }