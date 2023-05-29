//Interfacing LCD with ARM7-LPC2148 (4-Bit Mode)
//
#include <lpc214x.h>       //Header File to include LPC214x libraries
#include <stdint.h>        //Header File for using integer type with specified widths
#include <stdlib.h>        //Header File for include standard library
#include <stdio.h>         //Header File for include standard input output library
#include <string.h>
 
# define EN 0x00020000
# define RS 0x00010000  
# define DP 0X00C30000
 
void delay_ms(uint16_t j)  // Function for making delay in milliseconds
{
    uint16_t x,i;
for(i=0;i<j;i++)
{
    for(x=0; x<6000; x++);    // Forloop to generate 1 millisecond delay with Cclk = 60MHz
}
}
 
void LCD_COMMAND(char command)     //Function to send hex commands
{
IO1PIN = ( (IO1PIN & DP) | ((command & 0xF0)<<14) ); //Send upper nibble of command
IO1SET = EN; //Making Enable HIGH
IO1CLR = RS; //Making RS & RW LOW
delay_ms(5);
IO1CLR = EN; //Makeing Enable LOW
delay_ms(5);
IO1PIN = ( (IO1PIN & DP) | ((command & 0x0F)<<18) ); //Send Lower nibble of command
IO1SET = EN;  //ENABLE HIGH
IO1CLR = RS;  //RS & RW LOW
delay_ms(5);
IO1CLR = EN;  //ENABLE LOW
delay_ms(5);
}
 
void LCD_INITILIZE(void)          //Function to get ready the LCD
{
IO1DIR = 0x003F0000;
delay_ms(20);

LCD_COMMAND(0x02);  // Initialize lcd in 4-bit mode of operation
LCD_COMMAND(0x28);  // 2 lines (16X2)

LCD_COMMAND(0x0C);   // Display on cursor off
LCD_COMMAND(0x06);  // Auto increment cursor
LCD_COMMAND(0x01);   // Display clear
LCD_COMMAND(0x80);  // First line first position
}
 
void LCD_DISPLAY (char* msg)         //Function to print the characters sent one by one
{
uint8_t i=0;
while(msg[i]!=0)
{
IO1PIN = ( (IO1PIN & DP) | ((msg[i] & 0xF0)<<14) ); //Sends Upper nibble
  //RS HIGH & ENABLE HIGH to print data
IO1SET = EN;
IO1SET = RS;
delay_ms(2);
IO1CLR = EN; // EN = 0, RS and RW unchanged(i.e. RS = 1)
delay_ms(5);
IO1PIN = ( (IO1PIN & DP) | ((msg[i] & 0x0F)<<18) ); //Sends Lower nibble
IO1SET = EN;
IO1SET = RS;
delay_ms(2);
IO1CLR = EN;
delay_ms(5);
i++;
}
}

//------------------------------------------------------


void LCD_DISPLAY1(int c,char *msg)
{
int l=0;
int i=0;
int j=0;
int uhex = 0x80;
int lhex = 0xc0;
  while (msg[j]!=0)
{
      l++;
      j++;
   }

if(c == 0)
{
i=0;
uhex = 0x80;
while(l>0)
{
LCD_COMMAND(uhex);
IO1PIN = ( (IO1PIN & DP) | ((msg[i] & 0xF0)<<14) ); //Sends Upper nibble
//RS HIGH & ENABLE HIGH to print data
IO1SET = EN;
IO1SET = RS;
delay_ms(2);
IO1CLR = EN; // EN = 0, RS and RW unchanged(i.e. RS = 1)
delay_ms(5);
IO1PIN = ( (IO1PIN & DP) | ((msg[i] & 0x0F)<<18) ); //Sends Lower nibble
IO1SET = EN;
IO1SET = RS;
delay_ms(2);
IO1CLR = EN;
delay_ms(5);
i++;
uhex++;
l--;

}

}
else
{
i=0;
lhex = 0xC0;
while(l>0)
{
LCD_COMMAND(lhex);
IO1PIN = ( (IO1PIN & DP) | ((msg[i] & 0xF0)<<14) ); //Sends Upper nibble
//RS HIGH & ENABLE HIGH to print data
IO1SET = EN;
IO1SET = RS;
delay_ms(2);
IO1CLR = EN; // EN = 0, RS and RW unchanged(i.e. RS = 1)
delay_ms(5);
IO1PIN = ( (IO1PIN & DP) | ((msg[i] & 0x0F)<<18) ); //Sends Lower nibble
IO1SET = EN;
IO1SET = RS;
delay_ms(2);
IO1CLR = EN;
delay_ms(5);
i++;
lhex++;
l--;
}
}
}

//------------------------------------------------------
 
int main(void)
{
int i,rem,num,len;
int x = 0;
char p[4];
while(1)
{
LCD_INITILIZE();                  //Function call INITILIZE
LCD_DISPLAY("    YASWANTH    ");  //Function call DISPLAY with String arguments (put your message here)
LCD_COMMAND(0xC0);                //Function call SEND with Hex command as argument
delay_ms(100);                    //Function call delay with delay time as argument
LCD_DISPLAY("    KAKATIYA    ");  //Function call DISPLAY with our message (Puts your message here)
LCD_COMMAND(0xCC); //Function call SEND with Hex command as argument

//--------------
LCD_COMMAND(0x01);
LCD_DISPLAY1(0,"      panguluri");
LCD_DISPLAY1(0,"       yaswanth");

p[0] ='1';
p[1] ='2';
p[2] ='3';
p[3] ='4';
len = 4;
num = x;
x++;
for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        p[len - (i + 1)] = rem + '0';
    }
    p[len] = '\0';
LCD_DISPLAY1(1,p);

}
//-------------------
return 0;
}
