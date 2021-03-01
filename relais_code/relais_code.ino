/*
  Menu with voice and rotary encoder
  http://www.electronoobs.com/eng_arduino_tut22.php
  http://www.youtube.com/c/ELECTRONOOBS
 */
 
#include <LiquidCrystal.h>
#define buzzer 13        //Buzzer Pin
#define relais1 A1
#define relais2 7


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);





//Variables for the menu encoder
int counter = 0; 
int page=1;
int time1=0;
int time2=0;
int Ready=1;
int submenu=0;
int last_counter = 0; 
bool clk_State;
bool Last_State; 
bool dt_State;  
int pushed = 0;

//The pin for the push button
#define push 10
//Vectors for musical note and arrow

uint8_t arrow[8] = {0x0, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};

void setup() {
  pinMode (push,INPUT);       //Define the pin as input
  pinMode (relais1,OUTPUT);
  pinMode (relais2,OUTPUT);
  pinMode (buzzer,OUTPUT);
  
    lcd.begin (16,2);                  //Init the LCD
            //Activate backlight

  lcd.createChar(1, arrow);   //Create the arrow symbol
  lcd.home();                 //Home the LCD
  
  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan                                                 
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 trigger an interrupt on state change. 
  PCMSK0 |= (1 << PCINT1);  //Set pin D9 trigger an interrupt on state change.  
  DDRB &= B11111100;        //8, 9 as input for the encoder clock and data pins

  Last_State =   (PINB & B00000001); //pin 8 state (clock pin)? 
  
  
 //Print the first page menu.

  lcd.setCursor(0,0);
  lcd.write(1);  
  lcd.print("activate relais");
  lcd.setCursor(0,1);  
  lcd.print(" Set time 1");
  digitalWrite(relais1,HIGH);
  digitalWrite(relais2,HIGH);
  tintin();
}
//Void for the DFplayer to play sounds
void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();  
  while ((millis() - start) < msWait)
  {
    // calling mp3.loop() periodically allows for notifications to be handled without interrupts
    delay(1);
    }
  }

















void loop() { 
  digitalWrite(relais1,HIGH);
  digitalWrite(relais2,HIGH);
  
  if((last_counter > counter) || (last_counter < counter)  || pushed) //Only print on the LCD when a step is detected or the button is pushed.
  {
    Ready=1;

    //First page of the menu
    if(submenu == 0)
    {  
      if(0 <= counter && counter < 5)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("activate relais");
        lcd.setCursor(0,1);  
        lcd.print("Set time l");
        page=1;
        if(pushed)
        {
         
          pushed=0;
        }
      }
    
      if(5 < counter && counter < 10)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" activate relais");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("Set time1 ");
        page=2;
        if(pushed)
        {
         
          pushed=0;
        }     
      }
      
      if(10 < counter && counter < 15)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("Set time2");

        page=3;
        if(pushed)
        {
         
          pushed=0;
        }       
      }
    
      
  }//submenu = 0;













    //Second page of the menu
    if(submenu == 1)
      {  
        if(0 <= counter && counter < 5)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.write(1);  
          lcd.print("relais 1");
          lcd.setCursor(0,1);  
          lcd.print("relais 2");
          page=1;
          pushed=0;    
        }
      
        if(5 < counter && counter < 10)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("relais 1");
          lcd.setCursor(0,1);
          lcd.write(1);    
          lcd.print("relais 2");
          page=2;
          pushed=0;      
        }
      
        if(10 < counter && counter < 15)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.write(1);  
          lcd.print("both");
          lcd.setCursor(0,1);  
          lcd.print(" Back");
          page=3;
          pushed=0;      
        }
      
        if(15 < counter && counter < 20)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" both");
          lcd.setCursor(0,1);
          lcd.write(1);   
          lcd.print("Back");
          page=4;
          pushed=0;        
        }
      }//submenu = 1;




    //Third page of the menu
    if(submenu == 2)
    {  
      if(0 <= counter && counter < 5)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("1 minuts");
        lcd.setCursor(0,1);  
        lcd.print("2 minuts");
        page=1;
        pushed=0;    
      }
    
      if(5 < counter && counter < 10)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("3 minuts");
        page=2;
        pushed=0;      
      }
    
      if(10 < counter && counter < 15)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("3 minuts");
        lcd.setCursor(0,1);  
        lcd.print("4 minuts");
        page=3;
        pushed=0;      
      }
    
      if(15 < counter && counter < 20)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("3 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("4 minuts");
        page=4;
        pushed=0;        
      }

      //
       if(20 <= counter && counter < 25)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("5 minuts");
        lcd.setCursor(0,1);  
        lcd.print("6 minuts");
        page=5;
        pushed=0;    
      }
    
      if(25 < counter && counter < 30)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("5 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("6 minuts");
        page=6;
        pushed=0;      
      }
    
      if(30 < counter && counter < 35)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("7 minuts");
        lcd.setCursor(0,1);  
        lcd.print("8 minuts");
        page=7;
        pushed=0;      
      }
    
      if(35 < counter && counter < 40)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("7 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("8 minuts");
        page=8;
        pushed=0;        
      }
      //
             if(40 <= counter && counter < 45)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("9 minuts");
        lcd.setCursor(0,1);  
        lcd.print("10 minuts");
        page=9;
        pushed=0;    
      }
    
      if(45 < counter && counter < 50)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("9 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("10 minuts");
        page=10;
        pushed=0;      
      }
    
      if(50 < counter && counter < 55)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("11 minuts");
        lcd.setCursor(0,1);  
        lcd.print("12 minuts");
        page=11;
        pushed=0;      
      }
    
      if(55 < counter && counter < 60)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("11 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("12 minuts");
        page=12;
        pushed=0;        
      }
      //
                   if(60 <= counter && counter < 65)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("13 minuts");
        lcd.setCursor(0,1);  
        lcd.print("14 minuts");
        page=13;
        pushed=0;    
      }
    
      if(65 < counter && counter < 70)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("13 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("14 minuts");
        page=14;
        pushed=0;      
      }
    
      if(70 < counter && counter < 75)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("15 minuts");
        lcd.setCursor(0,1);  
        lcd.print("16 minuts");
        page=15;
        pushed=0;      
      }
    
      if(75 < counter && counter < 80)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("15 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("16 minuts");
        page=16;
        pushed=0;        
      }
      //
                   if(80 <= counter && counter < 85)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("17 minuts");
        lcd.setCursor(0,1);  
        lcd.print("18 minuts");
        page=17;
        pushed=0;    
      }
    
      if(85 < counter && counter < 90)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("17 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("18 minuts");
        page=18;
        pushed=0;      
      }
    
      if(90 < counter && counter < 95)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("19 minuts");
        lcd.setCursor(0,1);  
        lcd.print("20 minuts");
        page=19;
        pushed=0;      
      }
    
      if(95 < counter && counter < 100)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("19 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("20 minuts");
        page=20;
        pushed=0;        
      }
      //
                   if(100 <= counter && counter < 105)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("21 minuts");
        lcd.setCursor(0,1);  
        lcd.print("22 minuts");
        page=21;
        pushed=0;    
      }
    
      if(105 < counter && counter < 110)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("21 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("22 minuts");
        page=22;
        pushed=0;      
      }
    
      if(110 < counter && counter < 115)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("23 minuts");
        lcd.setCursor(0,1);  
        lcd.print("24 minuts");
        page=23;
        pushed=0;      
      }
    
      if(115 < counter && counter < 120)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("23 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("24 minuts");
        page=24;
        pushed=0;        
      }
      //
                   if(120 <= counter && counter < 125)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("25 minuts");
        lcd.setCursor(0,1);  
        lcd.print("26 minuts");
        page=25;
        pushed=0;    
      }
    
      if(125 < counter && counter < 130)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("25 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("26 minuts");
        page=26;
        pushed=0;      
      }
    
      if(130 < counter && counter < 135)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("27 minuts");
        lcd.setCursor(0,1);  
        lcd.print("28 minuts");
        page=27;
        pushed=0;      
      }
    
      if(135 < counter && counter < 140)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("27 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("28 minuts");
        page=28;
        pushed=0;        
      }
      //
                   if(140 <= counter && counter < 145)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("29 minuts");
        lcd.setCursor(0,1);  
        lcd.print("30 minuts");
        page=29;
        pushed=0;    
      }
    
      if(145 < counter && counter < 150)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("29 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("30 minuts");
        page=30;
        pushed=0;      
      }
    
      if(150 < counter && counter < 155)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("1 hour");
        lcd.setCursor(0,1);  
        lcd.print("2 hours");
        page=31;
        pushed=0;      
      }
    
      if(155 < counter && counter < 160)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 hour");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("2 hours");
        page=32;
        pushed=0;        
      }
      //
    }//submenu = 2;

    
if(submenu == 3)
    {  
      if(0 <= counter && counter < 5)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("1 minuts");
        lcd.setCursor(0,1);  
        lcd.print("2 minuts");
        page=1;
        pushed=0;    
      }
    
      if(5 < counter && counter < 10)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("3 minuts");
        page=2;
        pushed=0;      
      }
    
      if(10 < counter && counter < 15)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("3 minuts");
        lcd.setCursor(0,1);  
        lcd.print("4 minuts");
        page=3;
        pushed=0;      
      }
    
      if(15 < counter && counter < 20)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("3 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("4 minuts");
        page=4;
        pushed=0;        
      }

      //
       if(20 <= counter && counter < 25)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("5 minuts");
        lcd.setCursor(0,1);  
        lcd.print("6 minuts");
        page=5;
        pushed=0;    
      }
    
      if(25 < counter && counter < 30)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("5 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("6 minuts");
        page=6;
        pushed=0;      
      }
    
      if(30 < counter && counter < 35)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("7 minuts");
        lcd.setCursor(0,1);  
        lcd.print("8 minuts");
        page=7;
        pushed=0;      
      }
    
      if(35 < counter && counter < 40)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("7 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("8 minuts");
        page=8;
        pushed=0;        
      }
            //
             if(40 <= counter && counter < 45)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("9 minuts");
        lcd.setCursor(0,1);  
        lcd.print("10 minuts");
        page=9;
        pushed=0;    
      }
    
      if(45 < counter && counter < 50)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("9 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("10 minuts");
        page=10;
        pushed=0;      
      }
    
      if(50 < counter && counter < 55)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("11 minuts");
        lcd.setCursor(0,1);  
        lcd.print("12 minuts");
        page=11;
        pushed=0;      
      }
    
      if(55 < counter && counter < 60)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("11 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("12 minuts");
        page=12;
        pushed=0;        
      }
      //
                   if(60 <= counter && counter < 65)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("13 minuts");
        lcd.setCursor(0,1);  
        lcd.print("14 minuts");
        page=13;
        pushed=0;    
      }
    
      if(65 < counter && counter < 70)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("13 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("14 minuts");
        page=14;
        pushed=0;      
      }
    
      if(70 < counter && counter < 75)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("15 minuts");
        lcd.setCursor(0,1);  
        lcd.print("16 minuts");
        page=15;
        pushed=0;      
      }
    
      if(75 < counter && counter < 80)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("15 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("16 minuts");
        page=16;
        pushed=0;        
      }
      //
                   if(80 <= counter && counter < 85)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("17 minuts");
        lcd.setCursor(0,1);  
        lcd.print("18 minuts");
        page=17;
        pushed=0;    
      }
    
      if(85 < counter && counter < 90)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("17 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("18 minuts");
        page=18;
        pushed=0;      
      }
    
      if(90 < counter && counter < 95)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("19 minuts");
        lcd.setCursor(0,1);  
        lcd.print("20 minuts");
        page=19;
        pushed=0;      
      }
    
      if(95 < counter && counter < 100)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("19 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("20 minuts");
        page=20;
        pushed=0;        
      }
      //
                   if(100 <= counter && counter < 105)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("21 minuts");
        lcd.setCursor(0,1);  
        lcd.print("22 minuts");
        page=21;
        pushed=0;    
      }
    
      if(105 < counter && counter < 110)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("21 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("22 minuts");
        page=22;
        pushed=0;      
      }
    
      if(110 < counter && counter < 115)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("23 minuts");
        lcd.setCursor(0,1);  
        lcd.print("24 minuts");
        page=23;
        pushed=0;      
      }
    
      if(115 < counter && counter < 120)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("23 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("24 minuts");
        page=24;
        pushed=0;        
      }
      //
                   if(120 <= counter && counter < 125)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("25 minuts");
        lcd.setCursor(0,1);  
        lcd.print("26 minuts");
        page=25;
        pushed=0;    
      }
    
      if(125 < counter && counter < 130)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("25 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("26 minuts");
        page=26;
        pushed=0;      
      }
    
      if(130 < counter && counter < 135)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("27 minuts");
        lcd.setCursor(0,1);  
        lcd.print("28 minuts");
        page=27;
        pushed=0;      
      }
    
      if(135 < counter && counter < 140)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("27 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("28 minuts");
        page=28;
        pushed=0;        
      }
      //
                   if(140 <= counter && counter < 145)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("29 minuts");
        lcd.setCursor(0,1);  
        lcd.print("30 minuts");
        page=29;
        pushed=0;    
      }
    
      if(145 < counter && counter < 150)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("29 minuts");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("30 minuts");
        page=30;
        pushed=0;      
      }
    
      if(150 < counter && counter < 155)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1);  
        lcd.print("1 hour");
        lcd.setCursor(0,1);  
        lcd.print("2 hours");
        page=31;
        pushed=0;      
      }
    
      if(155 < counter && counter < 160)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 hour");
        lcd.setCursor(0,1);
        lcd.write(1);   
        lcd.print("2 hours");
        page=32;
        pushed=0;        
      }
    }//submenu = 2;







 
  
  
    

  
  }//end of the MENU prints on the LCD


  last_counter = counter; //Save the value of the last state



//Now we detect when we push the button
if(digitalRead(push)==0)
  {
     if(submenu == 1)
    {    
       if(page==1)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("  relais 1 on ");
        lcd.setCursor(0,1);  
        lcd.print("Wait:");
        lcd.print(time1);
        lcd.print(" Minuts");
        digitalWrite(relais1,LOW);
        delay((time1*60000));
        digitalWrite(relais1,HIGH);
        delay(1000);
        tintin();
       }
    
       if(page==2)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("   relais 2 on");
        lcd.setCursor(0,1);  
        lcd.print("Wait:");
        lcd.print(time2);
        lcd.print(" Minuts");
        digitalWrite(relais2,LOW);
        delay((time2*60000));
        digitalWrite(relais2,HIGH);
        delay(1000);
        tintin();
       }
    
       if(page==3)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("relais 2,1 on");
        lcd.setCursor(0,1);  
        lcd.print("      not configured yet       ");
        tintin();
        delay(1000);
       }
    
       if(page==4)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Going back...  ");
        lcd.setCursor(0,1);  
        lcd.print("      Wait      ");
        delay(500);
       }
    }//end of submenu 1






    if(submenu == 2)
    {    
       if(page==1)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 minut set ");delay(1000); time1=1;

       }
    
       if(page==2)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 minut set");delay(1000);time1=2;

       }
    
       if(page==3)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("3 minut set");delay(1000);time1=3;

       }
    
       if(page==4)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("4 minut set");delay(1000);time1=4;

       }
       //
       if(page==5)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("5 minut set ");delay(1000);time1=5;

       }
    
       if(page==6)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("6 minut set");delay(1000);time1=6;

       }
    
       if(page==7)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("7 minut set");delay(1000);time1=7;

       }
    
       if(page==8)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("8 minut set");delay(1000);time1=8;

       }
       //
       if(page==9)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("9 minut set ");delay(1000); time1=9;

       }
    
       if(page==10)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("10 minut set");delay(1000);time1=10;

       }
    
       if(page==11)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("11 minut set");delay(1000);time1=11;

       }
    
       if(page==12)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("12 minut set");delay(1000);time1=12;

       }
       //
              if(page==13)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("13 minut set ");delay(1000); time1=13;

       }
    
       if(page==14)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("14 minut set");delay(1000);time1=14;

       }
    
       if(page==15)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("15 minut set");delay(1000);time1=15;

       }
    
       if(page==16)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("16 minut set");delay(1000);time1=16;

       }
     
       if(page==17)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("17 minut set ");delay(1000);time1=17;

       }
    
       if(page==18)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("18 minut set");delay(1000);time1=18;

       }
    
       if(page==19)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("19 minut set");delay(1000);time1=19;

       }
    
       if(page==20)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("20 minut set");delay(1000);time1=20;

       }
       //
       if(page==21)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("21 minut set ");delay(1000); time1=21;

       }
    
       if(page==22)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("22 minut set");delay(1000);time1=22;

       }
    
       if(page==23)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("23 minut set");delay(1000);time1=23;

       }
    
       if(page==24)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("24 minut set");delay(1000);time1=24;

       }
       //
              if(page==25)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("25 minut set");delay(1000);time1=25;

       }
    
       if(page==26)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("26 minut set");delay(1000);time1=26;

       }
       //
              if(page==27)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("27 minut set ");delay(1000); time1=27;

       }
    
       if(page==28)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("28 minut set");delay(1000);time1=28;

       }
    
       if(page==29)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("29 minut set");delay(1000);time1=29;

       }
    
       if(page==30)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("30 minut set");delay(1000);time1=30;

       }
     
       if(page==31)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 hours set ");delay(1000);time1=60;

       }
    
       if(page==32)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 hours set");delay(1000);time1=120;

       }
    
       
    }//end of submenu 1





    if(submenu == 3)
    {    
             if(page==1)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 minut set ");delay(1000); time2=1;

       }
    
       if(page==2)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 minut set");delay(1000);time2=2;

       }
    
       if(page==3)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("3 minut set");delay(1000);time2=3;

       }
    
       if(page==4)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("4 minut set");delay(1000);time2=4;

       }
       //
       if(page==5)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("5 minut set ");delay(1000);time2=5;

       }
    
       if(page==6)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("6 minut set");delay(1000);time2=6;

       }
    
       if(page==7)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("7 minut set");delay(1000);time2=7;

       }
    
       if(page==8)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("8 minut set");delay(1000);time2=8;

       }
       //
       if(page==9)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("9 minut set ");delay(1000); time2=9;

       }
    
       if(page==10)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("10 minut set");delay(1000);time2=10;

       }
    
       if(page==11)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("11 minut set");delay(1000);time2=11;

       }
    
       if(page==12)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("12 minut set");delay(1000);time2=12;

       }
       //
              if(page==13)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("13 minut set ");delay(1000); time2=13;

       }
    
       if(page==14)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("14 minut set");delay(1000);time2=14;

       }
    
       if(page==15)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("15 minut set");delay(1000);time2=15;

       }
    
       if(page==16)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("16 minut set");delay(1000);time2=16;

       }
     
       if(page==17)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("17 minut set ");delay(1000);time2=17;

       }
    
       if(page==18)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("18 minut set");delay(1000);time2=18;

       }
    
       if(page==19)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("19 minut set");delay(1000);time2=19;

       }
    
       if(page==20)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("20 minut set");delay(1000);time2=20;

       }
       //
       if(page==21)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("21 minut set ");delay(1000); time2=21;

       }
    
       if(page==22)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("22 minut set");delay(1000);time2=22;

       }
    
       if(page==23)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("23 minut set");delay(1000);time2=23;

       }
    
       if(page==24)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("24 minut set");delay(1000);time2=24;

       }
       //
              if(page==25)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("25 minut set");delay(1000);time2=25;

       }
    
       if(page==26)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("26 minut set");delay(1000);time2=26;

       }
       //
              if(page==27)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("27 minut set ");delay(1000); time2=27;

       }
    
       if(page==28)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("28 minut set");delay(1000);time2=28;

       }
    
       if(page==29)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("29 minut set");delay(1000);time2=29;

       }
    
       if(page==30)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("30 minut set");delay(1000);time2=30;

       }
     
       if(page==31)
       {
        submenu=0;
        counter=1;
        pushed=0;
        Ready=0;
     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 hours set ");delay(1000);time2=60;

       }
    
       if(page==32)
       {
        submenu=0;
        counter=0;
        pushed=0;
        Ready=0;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 hours set");delay(1000);time2=120;

       }
    }//end of submenu 1

if(submenu == 0 && Ready==1)
    {    
       if(page==1)
       {
        submenu=1;
        counter=0;
        pushed=1;

        delay(500);
        
        
       }
    
       if(page==2)
       {
        submenu=2;
        counter=0;

        pushed=1;delay(500);
       }
    
       if(page==3)
       {
        submenu=3;
        counter=0;

        pushed=1;delay(500);
       }
    
       if(page==4)
       {
        submenu=4;
        counter=0;

        pushed=1;delay(500);
       }
    }//end of submenu 0

    
  }





  




  //Add limit for the counter. Each line of the menu has 5 points. Since my menu has 4 lines the maximum counter will be from 0 to 20
  //If you add more lines for the menu, increase this value
  if(counter > 160)
  {
    counter=160;
  }
  if(counter < 0)
  {
    counter=0;
  }
}//end void






void tintin(){
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
    digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
    digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
    digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
    digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
    digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
    digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
}







//Interruption vector

ISR(PCINT0_vect){
  
  clk_State =   (PINB & B00000001); //pin 8 state, clock pin? 
  dt_State  =   (PINB & B00000010); 
  if (clk_State != Last_State){     
     // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (dt_State != clk_State) { 
       counter ++;
     }
     else {
       counter --;
     } 
   } 
   Last_State = clk_State; // Updates the previous state of the data with the current state
  
}
