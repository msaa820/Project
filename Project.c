#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/*if the magnet is low  the magnet is turn on
  if the magnet is HIGH the magnet is turn off  */

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define magnet 10
#define led 13
#define sensor 11

int sensorr = 0, count = 0;

int reprint1 = 1 ;
int reprint2 = 1 ;
int reprint3 = 1 ;


unsigned long btime1 = 0, etime1 = 0;
unsigned long btime2 = 0, etime2 = 0;
unsigned long btime3 = 0, etime3 = 0;

int distance1 = 0 , distance2 =0,  distance3 =0 ;  // distance in cm

float time1 = 0 , time2 = 0 , time3 = 0;   // time in ms from millis()

float a1 = 0, a2 = 0, a3 = 0,avg = 0; // the acceleration

bool check = 0, num = 0; // thank message to detector

void setup()
{
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    lcd.setCursor(0, 0);
    lcd.print("     Tech Titans     ");
    lcd.setCursor(0, 1);
    lcd.print("       Welcome       ");

    pinMode(magnet, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(sensor, INPUT);
    digitalWrite(magnet , HIGH);
}

void loop()
{
    char key = keypad.getKey();

    if(key)
    {
      Serial.println(key);
      if(key == 'B'){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");
            lcd.setCursor(0, 1);
            lcd.print("D =");
            lcd.setCursor(9, 1);
            lcd.print("T =");
            digitalWrite(magnet , LOW);
            delay(10);
            digitalWrite(led ,   HIGH);


            count=1;
        }

    }

            
    while (count == 1)
    {
        char key = keypad.getKey();
        lcd.setCursor(0, count);
        lcd.print("D =");
        lcd.setCursor(9, count);
        lcd.print("T =");
        if (key == 'B')
        {
            b();
        }
        else if (key >= '0' && key <= '9')
        {
            distance1 = distance1 * 10 + (key - '0'); // in cm
            lcd.setCursor(4, 1);
            lcd.print(distance1);
            if(reprint1 == 1) {
            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");
            lcd.setCursor(0, count);
            lcd.print("D =");
            lcd.setCursor(9, count);
            lcd.print("T =          ");
            reprint1 = 0 ; 
            }
        }
        else if (key == '*' && distance1 != 0)
            {
            digitalWrite(magnet, HIGH);
            delay(10);

            btime1 = millis();

            // Wait for the ball to arrive at the sensor
            while (digitalRead(sensor))
            {
                // This loop will wait until the sensor reads LOW (ball arrives)
                // Adding a delay to avoid blocking the loop for too long
                delay(10);
            }

            // Ball has arrived, record the end time
            etime1 = millis();
            time1 = (etime1 - btime1); // millesconds
            //time1 = time1 + 10 ;
            a1 = 1000000 * 2 * (distance1) / (time1 * time1);
            a1 = abs(a1);
            
            

            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");
            lcd.setCursor(0, 1);
            lcd.print("D =");
            lcd.setCursor(9, 1);
            lcd.print("T =          ");
            lcd.setCursor(4, 1);
            lcd.print(distance1);
            lcd.setCursor(13, 1);
            lcd.print(time1);
            lcd.setCursor(0, 1);
            lcd.print("D =");
             



           
            
        }
        else if (key == 'C' && distance1 != 0)
        {
          distance1 = 0 ;
          lcd.setCursor(0, 1);
          lcd.print("D =    ");
        }
         else if(key == '#')
           
             {
              lcd.setCursor(0, 0);
              lcd.print("Distance   Time ");
              lcd.setCursor(0, count);
              lcd.print("D =     ");
              lcd.setCursor(9, count);
              lcd.print("T =        ");
              distance1 = 0 ;
              a1 = 0;
              btime1 =0 ;
              etime1 = 0;
              time1 = 0;
              digitalWrite(magnet , LOW);
              

             }
             else if((key == 'A') &&  (distance1 != 0 ))
             {
              digitalWrite(magnet, LOW);
              delay(10);
              count = 2;
             }
        
    }

    while (count == 2)
    {   
        char key = keypad.getKey();
        lcd.setCursor(0, 1);
        lcd.print("D =");
        lcd.setCursor(0, count);
        lcd.print("D =");
        lcd.setCursor(9, count);
        lcd.print("T =");

        if (key == 'B')
        {
            b();
        }
        else if (key >= '0' && key <= '9')
        {

            distance2 = distance2 * 10 + (key - '0'); // in cm
            lcd.setCursor(0, 1);
            lcd.print("D =");

          
            lcd.setCursor(4, 2);
            lcd.print(distance2);

            if(reprint2 == 1){
            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");
            lcd.setCursor(0, 1);
            lcd.print("D =");
            reprint2 = 0;
            }

        }
        else if (key == '*' && distance2 != 0)
        {  
            lcd.setCursor(0, 1);
            lcd.print("D =");       
            digitalWrite(magnet, HIGH);
            delay(10);

            btime2 = millis();

            // Wait for the ball to arrive at the sensor
            while (digitalRead(sensor))
            {
                // This loop will wait until the sensor reads LOW (ball arrives)
                // Adding a delay to avoid blocking the loop for too long
                delay(10);
            }

            // Ball has arrived, record the end time
            etime2 = millis();
            time2 = (etime2 - btime2); // millesconds
            //time2 = time2 + 30; 
            //distance = distance ;//  centimeters cm

           // Serial.println("Time: " + String(time2) + " seconds\n");
           // Serial.println("Distance: " + String(distance2) + " units\n");

            a2 = 1000000 * 2 * (distance2) / (time2 * time2);
            a2 = abs(a2);
            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");

            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");
          
            lcd.setCursor(13, 2);
            lcd.print(time2);
            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");

        } else if (key == 'C' && distance2 != 0){
           distance2 =0 ;
           
            lcd.setCursor(0, 2);
            lcd.print("D =    ");
           }
           else if((key == '#') && (distance2 != 0) )
           
             {
              lcd.setCursor(0, 0);
              lcd.print("Distance   Time ");
              lcd.setCursor(0, count);
              lcd.setCursor(9, count);
              lcd.print("T =          ");
              distance2 = 0 ;
              a2 = 0;
              btime2 =0 ;
              etime2 = 0;
              time2 = 0;
              lcd.print("D =     ");
              digitalWrite(magnet , LOW);
              

             }
             else if((key == 'A') )
             {
               digitalWrite(magnet, LOW);
               delay(10);
               count = 3;
               lcd.setCursor(0, 3);
               lcd.print("D =");
               lcd.setCursor(9, 3);
               lcd.print("T =");
               lcd.setCursor(0, 0);
               lcd.print("Distance   Time ");
             }

        
    }

    while (count == 3)
    {
        
        char key = keypad.getKey();
       

        if (key == 'B')
        {
            b();
        }
        else if (key >= '0' && key <= '9')
        {
            lcd.setCursor(0, 0);
            lcd.print("Distance   Time ");
            distance3 = distance3 * 10 + (key - '0'); // in cm
            lcd.setCursor(4, 3);
            lcd.print(distance3);

           if(reprint3 == 1)
           {
            lcd.setCursor(0, 2);
            lcd.print("D =");
            lcd.setCursor(0, count);
            lcd.print("D =");
            lcd.setCursor(9, count);
            lcd.print("T =");
            lcd.setCursor(0, 1);
            lcd.print("D =");
            lcd.setCursor(0, 2);
            lcd.print("D =") ;  
            reprint3  = 0 ;         
          
           }
        }
        else if (key == '*' && distance3 != 0)
        { 
          digitalWrite(magnet, HIGH);
          delay(10);
          btime3 = millis();
             
           


            

            // Wait for the ball to arrive at the sensor
            while (digitalRead(sensor))
            {
                // This loop will wait until the sensor reads LOW (ball arrives)
                // Adding a delay to avoid blocking the loop for too long
                delay(10);
            }

            // Ball has arrived, record the end time
            etime3 = millis();
            time3 = (etime3 - btime3); // millesconds
            //time3 = time3 + 30 ;
           

            a3 = 1000000 * 2 * (distance3) / (time3 * time3);
            a3 = abs(a3);
            Serial.print("t3 = ");
            Serial.println(time3);
            Serial.print("distance3 = ");
            Serial.println(distance3);
            Serial.print("a3 = ");
            Serial.println(a3);
            Serial.print("\n\n\n");
            
            lcd.setCursor(13, 3);
            lcd.print(time3);


           

           

        }
        else if (key == 'C' && distance3 != 0)
        {
            lcd.setCursor(0, 3);
            lcd.print("D =    ");
          
        }
        else if(key == '#')
           
             {
              lcd.setCursor(0, 0);
              lcd.print("Distance   Time ");
              lcd.setCursor(0, count);
              lcd.print("D =      ");
              lcd.setCursor(9, count);
              lcd.print("T =          ");
              distance3 = 0 ;
              a3 = 0;
              btime3 =0 ;
              etime3 = 0;
              time3 = 0;
              digitalWrite(magnet , LOW);
              

             }
             else if((key == 'A'))
             {

               lcd.clear();
               lcd.clear();            
               avg =  a1 + a2 +  a3 ;
               avg = avg /300;
               lcd.clear();
               lcd.clear(); 
               lcd.setCursor(0, 0);
               lcd.print("Osman ElKinani ");
               lcd.setCursor(0, 1);
               lcd.print("The acceleration = ");
               lcd.setCursor(5, 2);
               lcd.print(avg);
               Serial.print("avg = ");
               Serial.println(avg);
               lcd.setCursor(11, 2);
               lcd.print("m/s^2");
             

             }
    }
    
}