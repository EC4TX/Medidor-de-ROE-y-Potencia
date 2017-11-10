// Medidor de ROE y Potencia con Arduino by EC4TX @2012
// www.ec4tx.com

// The circuit:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
// * LCD R/W pin to ground
// * 10K resistor:
// * ends to +5V and ground
//* wiper to LCD VO pin (pin 3)
// * DIR to analog pin A0
// * REF to analog pin A1
// * LED ALARM to digital pin 13
 
 */
// PINS

int directPin = A0;    // select the input pin for the DIRECT signal
float directValue = 0;   // variable to store the value coming from the DIRECT
int reflePin = A1;     // select the input pin for REFLE signal
float refleValue = 0;    // variable to store the value coming from the REFLE
int led = 13;  // select the pin for the LED ALARM 
float swrValue = 0;
float Powerdirect = 0;
float Powerdirectcuadra = 0;
float PowerdirectOK = 0 ;


// int Potencia = 0;
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  // declare the ledPin as an OUTPUT:
  pinMode(led, OUTPUT);  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16,2);
  // Print a message to the LCD.
  lcd.print(" SWR EC4TX V1.0 ");
  lcd.setCursor(0,1); 
  lcd.print("INICIALIZANDO !!");
  // delay :
  delay(5000);
  lcd.clear();
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}
void loop() 
{

//  lcd.clear();
  // read the analog DIRECT in value:
  directValue = (analogRead(directPin)*5.00/1024.00);
  // read the analog REFLE in value:
  //delay(5);
  refleValue = (analogRead(reflePin)*5.00/1024.00); 
  //delay(5);
   // Calculo SWR (1+raiz(REF/RIR))/(1-raiz(REF/DIR))
 swrValue = (1+sqrt(refleValue/directValue))/(1-sqrt(refleValue/directValue));
   // NO******swrValue = ((directValue+refleValue)/(directValue+refleValue))******;

  // Calculo Potencia
  //Potencia = (Vout+0.5)^2/100);
  Powerdirect = (directValue+0.500);
  //al cuadrado
  Powerdirectcuadra = (Powerdirect*Powerdirect);
  PowerdirectOK = (Powerdirectcuadra/100);
  lcd.clear();
  //Clasificamos según el SWR leido
  if (swrValue > 2.5)
    {
    lcd.print(" RE:");
    lcd.print(refleValue);
    lcd.print(" DI:");
    lcd.print(directValue);
    lcd.setCursor(0,1);
    lcd.print("SWR:");
    lcd.print(swrValue); 
    lcd.print(" HIGH!!");
    digitalWrite(led, HIGH);
    }
    else if (swrValue > 2.0 && (swrValue < 2.5))
    {
    digitalWrite(led, HIGH);
    delay(10);
    digitalWrite(led, LOW);
    lcd.print(" RE:");
    lcd.print(refleValue);
    lcd.print(" DI:");
    lcd.print(directValue);
    lcd.setCursor(0,1);
    lcd.print("SWR:");
    lcd.print(swrValue); 
    lcd.print (" HIGH ");
    }
    else if (swrValue >= 1.0 && (swrValue < 2.0))
    {
    lcd.print(" RE:");
    lcd.print(refleValue);
    lcd.print(" DI:");
    lcd.print(directValue);
    lcd.setCursor(0,1);
    lcd.print("SWR:");
    lcd.print(swrValue); 
    lcd.print(" PW:");
    lcd.print(PowerdirectOK);
    digitalWrite(led, LOW);
    }
    else if (swrValue < 1.0)
    {
    lcd.print(" RE:");
    lcd.print(refleValue);
    lcd.print(" DI:");
    lcd.print(directValue);
    lcd.setCursor(0,1);
    lcd.print("SWR:");
    lcd.print("ERR"); 
    lcd.print(" PW:");
    lcd.print(PowerdirectOK);
    digitalWrite(led, LOW);
    }
    else
    delay(150);
    
  // print the results to the serial monitor:
  Serial.print(" DIRECTA = " );                       
  Serial.println(directValue,DEC);      
  Serial.print(" REFLEJADA = ");      
  Serial.print(refleValue,DEC);
  Serial.print(" SWR = 1:" );
  Serial.print(swrValue);
  Serial.print(" POWER = " );
  Serial.print(PowerdirectOK,DEC);
  ;

  // wait 250 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(350);                       
}

