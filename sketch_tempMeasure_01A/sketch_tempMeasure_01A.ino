#include <math.h>
#include <stdlib.h>
//Schematic:                                      modified 4.K by forex2
// [Ground] ---- [10k-Resister] -------|------- [Thermistor] ---- [+5v]
//                                     |
//                                Analog Pin 0

double Thermistor(int RawADC) {
// Inputs ADC Value from Thermistor and outputs Temperature in Celsius
//  requires: include <math.h>
// Utilizes the Steinhart-Hart Thermistor Equation:
//    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  long Resistance;  double Temp;  // Dual-Purpose variable to save space.
  Resistance=((10240000/RawADC) - 10000);  //   Calculation is actually: Resistance = (1024 * BalanceResistor/ADC) - BalanceResistor
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate it 4 times later. // "Temp" means "Temporary" on this line.
  Temp = 1 / (0.0012954816 + (0.00023539242 * Temp) + (0.00000011285038 * Temp * Temp * Temp));   // Now it means both "Temporary" and "Temperature"
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius                                         // Now it only means "Temperature"
  // Uncomment this line for the function to return Fahrenheit instead.
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert to Fahrenheit
  return Temp;  // Return the Temperature
}

void printDouble(double val, byte precision) {
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimal places
  // example: printDouble(3.1415, 2); // prints 3.14 (two decimal places)
  Serial.print (int(val));  //prints the int part
  if( precision > 0) {
    Serial.print("."); // print the decimal point
    unsigned long frac, mult = 1;
    byte padding = precision -1;
    while(precision--) mult *=10;
    if(val >= 0) frac = (val - int(val)) * mult; else frac = (int(val) - val) * mult;
    unsigned long frac1 = frac;
    while(frac1 /= 10) padding--;
    while(padding--) Serial.print("0");
    Serial.print(frac,DEC) ;
   }
 }
 

#define ThermistorPIN 0   // Analog Pin 0
#define LEDPIN 13

void setup() {
  Serial.begin(9600); //doesn't work for me with anything but 9600?
  pinMode(LEDPIN, OUTPUT);
 }

  
double temp;
int recordNumber = 0;
char buffer[8];
int received;
void loop() {
  temp=Thermistor(analogRead(ThermistorPIN));  // read ADC and convert it to Celsius
  //Serial.print("Celsius: ");
  printDouble(temp,2);     // display Celsius
  Serial.println(" ");  // End of Line
  digitalWrite(LEDPIN, HIGH);
  delay(1000);
  digitalWrite(LEDPIN, LOW);
  delay(29000); 
}

