
#include <mega64.h>
#include <delay.h>

int keyDown=0;
int readKeys();
//unsigned char scan();
void show();
char getCode(int num);
int number[6];
int counter;
int curNumber; //just read number
//unsigned char curNumber;
//int dir;
unsigned char key;
void main (void)
{
    DDRA = 0b00000111; //row output so we can make them 1 later
    PORTA = 0xFF ; //make inputs 'pull up'. so default value is 1 when CPU read inputs
    PORTA.0 = 1;
    PORTA.1 = 1;
    PORTA.2 = 1;
    // to read we make one outut 0, then check id any input is 0 ( because of key push which cause connection
    
    DDRD = 0xFF;
    DDRC = 0xFF; 
    // Tutorial 
    PORTC=0x04; // C.0=1 => LED RUN || C.1-6=1 => Which 7Seg RUN     
    //  PORTD=XXX;   Which LED's || Value of selected 7Seg
      
    for( counter=0; counter<6;counter++)
        number[counter]=-1;    
    //cur7Seg=0;
  
    while(1)
    {          
       delay_ms(2); 
       curNumber = -100;
       curNumber = readKeys() ;     
       //curNumber = scan();
       
       if(curNumber!=-100)
       {
            for( counter=0; counter<=5;counter++)
               number[counter]=number[counter+1];    
            number[5]=curNumber;    
       }          
     
 //   for( counter=0; counter<250;counter++)
  //  {
       // delay_ms(5);      
         show();    
  //  }
       
      /* if( readKeys() == 5 )
          PORTD=0x06;
       else
          PORTD=0x3f;*/  
    }
   
}

void show()
{
    PORTC = (PORTC<<1);
    if(PORTC==0x00)
        PORTC=0x02;
    if(PORTC==0x2)
        PORTD=getCode(number[0]);
    else if(PORTC==0x4)
        PORTD=getCode(number[1]);
    else if(PORTC==0x8)
        PORTD=getCode(number[2]);
    else if(PORTC==0x10)
        PORTD=getCode(number[3]); 
    else if(PORTC==0x20)
        PORTD=getCode(number[4]);
    else if(PORTC==0x40)
        PORTD=getCode(number[5]);
}

int getPushedCol()
{
    if( PINA.3==0)
        return 1;
    if( PINA.4==0)
        return 2;
    if( PINA.5==0)
        return 3;
    if( PINA.6==0)
        return 4;
    return -1;
}

int readKeys()
{
    int row=0, col=0, result=0; 
      PORTA.0 = 1;    
  PORTA.1 = 1;
    PORTA.2 = 1;   
   if( result==0)   
   { 
        PORTA.0 = 0;    
      PORTA.1 = 1;
        PORTA.2 = 1; //Row3 
      result= getPushedCol();
      if(result==-1)  
        result=0;
      else
      {
        result = 8 + result ;
      }   
   } 
   if( result==0)   
   { 
              PORTA.0 = 1;    
      PORTA.1 = 0;
        PORTA.2 = 1; //Row2 
      result= getPushedCol();
      if(result==-1)  
        result=0;
      else
        result = 4 + result ;   
   }
   if( result==0)   
   { 
              PORTA.0 = 1;    
      PORTA.1 = 1;
        PORTA.2 = 0; //Row1  
      result= getPushedCol();
      if(result==-1)  
        result=0;
      else
        result = result ;   
   }                                                                                                            PORTA.0 = 0x00;    

 
    
    if(result==0 )
    {      
        keyDown=-100;
        return -100;
    }           
       
    //result--;
    if(result==10)
        result=0;    
    else if(result==11)
        result=-2; 
    else if(result>=12)
        result=-1;
    if(keyDown==result)
        return -100;
    
    keyDown=result;
    return result;
}

char getCode(int num)
{

    switch(num)
    {         
    case -1:
       return 0x00;
       break;  
    case -2:
        return  0x40; 
        break;
    case 0:
        return 0x3F;
        break; 
    case 1:
        return 0x06;
        break;
    case 2:
        return 0x5B;
        break;
    case 3:
        return 0x4F;
        break;
    case 4:
        return 0x66;
        break;
    case 5:
        return 0x6D;
        break;
    case 6:
        return 0x7D;
        break;
    case 7:
        return 0x07;
        break;
    case 8:
        return 0x7F;
        break;
    case 9:
        return 0x6F;
        break;
    }
}









