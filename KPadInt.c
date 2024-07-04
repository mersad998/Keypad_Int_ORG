
#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <sleep.h>

// Declare your global variables here
flash char key_refresh[4]={0xFE, 0xFD, 0xFB, 0xF7};
//      flash int key_number [4][4]={'7', '8', '9', '-3',
//                                   '4', '5', '6', '-4',
//                                   '1', '2', '3', '-5',
//                                 '-1', '0', '-2', '-6'};   

flash char key_number [4][4]={'7', '8', '9', '/',
                              '4', '5', '6', '*',
                              '1', '2', '3', '-',
                              'C', '0', '=', '+'};   
eeprom int password1 = -1 ;
eeprom int password2 = -1 ;
eeprom int password3 = -1 ;
eeprom int password4 = -1 ;
int position = -1 ;     
eeprom int isPassword = -1 ;

int pass1 = -1 ;
int pass2 = -1 ;
int pass3 = -1 ;
int pass4 = -1 ;


// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void){

 char  row, column, temp;
  
       for (row=0; row<4; row++)
        {  
             PORTD =  key_refresh[row]; 
             
         temp = PIND;
         temp = temp & 0xF0; 
             
         if (temp != 0xF0)
         {
             if (PIND.4 == 0)
                column=0;      
             if (PIND.5 == 0)
                column=1;      
             if (PIND.6 == 0)
                column=2;      
             if (PIND.7 == 0)
                column=3;
                
             if (key_number[row][column] == 'C') {
              lcd_clear();
              isPassword = -1 ;
              password1 = -1 ;   
              password2 = -1 ;
              password3 = -1 ;
              password4 = -1 ;
              lcd_putsf ("Please choose a new password"); 
              position = 1 ;             
              } 
              
              else  
              {   
                    if (isPassword == -1 && position == 1) {  
                 lcd_clear();
                 lcd_putchar(key_number[row][column]); 
                 password1 = key_number[row][column] ;
                 position = 2 ; 
                 
                      } 
                 
                 else if (isPassword == -1 && position == 2) {  
                 lcd_putchar(key_number[row][column]); 
                 password2 = key_number[row][column] ;
                 position = 3 ;
             }else if (isPassword == -1 && position == 3) {  
                 lcd_putchar(key_number[row][column]); 
                 password3 = key_number[row][column] ;
                 position = 4  ;
             }else if (isPassword == -1 && position == 4) {
                 password4 = key_number[row][column] ; 
                 lcd_clear();  
                 lcd_putsf ("Password Seted Successfully");                 
                 isPassword = 1 ; 
                 position = 1 ;                 
                 delay_ms(2000) ;
                 lcd_clear();  
                 lcd_putsf ("Please insert your password");   
                 
             }else if (isPassword == 1 && position == 1) {
                 lcd_clear();  
                 lcd_putchar(key_number[row][column]); 
                 pass1 = key_number[row][column] ;
                 position = 2 ; 
             }else if (isPassword == 1 && position == 2) {
                 lcd_putchar(key_number[row][column]); 
                 pass2 = key_number[row][column] ;
                 position = 3 ; 
             }else if (isPassword == 1 && position == 3) {
                 lcd_putchar(key_number[row][column]); 
                 pass3 = key_number[row][column] ;
                 position = 4 ; 
             }else if (isPassword == 1 && position == 4) {
                 lcd_putchar(key_number[row][column]); 
                 pass4 = key_number[row][column] ;
                 position = 5 ;  
             }
             
              if (key_number[row][column] == '='){              
                if (password1 == pass1) {
                   if (password2 == pass2){
                     if (password3 == pass3){
                       if(password4 == pass4){                          
                         lcd_clear();  
                         lcd_putsf ("ok");
                         delay_ms(1500);
                         lcd_clear();  
                         lcd_putsf ("Please insert your password");             
                         position = 1 ;
                         
                         if (PORTB.0 == 0){
                         PORTB.0 = 1;}
                         else if (PORTB.0 == 1){
                         PORTB.0 = 0;}                                       
                         }else if(password4 != pass4){
                         lcd_clear();  
                         lcd_putsf ("Password wrong !!!");
                         delay_ms(1500);
                         lcd_clear();  
                         lcd_putsf ("Please insert your password");             
                         position = 1 ;} 
                       }else if(password3 != pass3){
                         lcd_clear();  
                         lcd_putsf ("Password wrong !!!");
                         delay_ms(1500);
                         lcd_clear();  
                         lcd_putsf ("Please insert your password");             
                         position = 1 ;}
                     }else if(password2 != pass2){
                         lcd_clear();  
                         lcd_putsf ("Password wrong !!!");
                         delay_ms(1500);
                         lcd_clear();  
                         lcd_putsf ("Please insert your password");             
                         position = 1 ;}
                }else if(password1 != pass1){
                         lcd_clear();  
                         lcd_putsf ("Password wrong !!!");
                         delay_ms(1500);
                         lcd_clear();  
                         lcd_putsf ("Please insert your password");             
                         position = 1 ;}              
                            
              }
               
                 
//                 if (key_number[row][column] == '+'){
//                 lcd_clear();  
//                 lcd_putchar(password1);
//                 lcd_putchar(password2);
//                 lcd_putchar(password3);
//                 lcd_putchar(password4);
//                 }
                 
                 
                   
             }
              
              
          //       else if ( isPassword == -1 && position == -1 ) {
        //         lcd_putsf ("Please choose a new password");  
      //           position = 1 ;    
    //         } if (isPassword == -1 && position == 1) {  
//                 lcd_clear();
//                 lcd_putchar(key_number[row][column]); 
 //                password1 = key_number[row][column] ;
  //               position = 2 ;      }
//             }else if (isPassword == -1 && position == 2) {  
//                 lcd_putchar(key_number[row][column]); 
//                 password2 = key_number[row][column] ;
//                 position = 3 ;
//             }else if (isPassword == -1 && position == 3) {  
//                 lcd_putchar(key_number[row][column]); 
//                 password3 = key_number[row][column] ;
//                 position = 4  ;
//             }else if (isPassword == -1 && position == 4) {
//                 password4 = key_number[row][column] ; 
//                 lcd_clear();  
//                 lcd_putsf ("Password Seted Successfully");                 
//                 isPassword = 1 ; 
//                 position = 1 ;
//             }else if (isPassword == 1 && position == 1  ) {
//                 lcd_clear();  
//                 lcd_putsf ("yessssss");
//             }

         }     
         
                 
   
   }
   PORTD = 0xF0;
   
   }


   
      
void main(void){
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (1<<PORTB1) | (0<<PORTB0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);


// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
GICR|=(0<<INT1) | (0<<INT0) | (1<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (0<<INTF0) | (1<<INTF2);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1){

  idle();
 //Ba dastoore idele() CPU be halate Sleep rafte va faghat
 // ba interrupt az khab bidar migardad. Gozashtane in dastoor
 // baes migardad dar tavane masrafi sarfejooyi shode va micro bihoode dagh nagardad. 
} 
      

}
