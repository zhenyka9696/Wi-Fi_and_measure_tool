#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2); 
#define analog_amperage A1
#define analog_voltage A0
float seconds=0.00028;
uint32_t timer_s;
uint32_t timer;
uint32_t mm;
uint32_t hh;
uint32_t globh=3600000000;
int mVperAmp = 100; // use 185 for 5A Module, 100 for 20A Module, 66 for 30A Module
int RawValue= 0;
int Volts=0;
int ACSoffset = 2500; 
float VoltageLoc = 0.0;
float Amps = 0.0;
float Voltage_0=0.0;
float C=0.0;
float input_volt = 0.0;
float temp=0.0;
float r1=5700.0; //значение R1, здесь вы можете установить своё значение
float r2=631.0; //значение R2, здесь вы можете установить своё значение
void setup() 
{
Serial.begin(115200);
lcd.init();
lcd.backlight();
lcd.clear();
lcd.setCursor(8,1);
lcd.print("00:00");
}

void loop() {
int analogvalue = analogRead(analog_voltage);
temp = (analogvalue * 5.0) / 1024.0; // Формула для преобразования аналогового сигнала в напряжения
input_volt = (temp / (r2/(r1+r2)))*1.06; // Формула коррекции напряжения с учётом делителя
RawValue = analogRead(analog_amperage);
VoltageLoc = (RawValue / 1024.0) * 5000;
Amps = (((VoltageLoc - ACSoffset) / mVperAmp)*1.05);

if((millis()-timer_s>=1000)&&Amps>=0.01)
{timer_s=millis();
seconds=seconds+0.00028;}

C=Amps*seconds;

if(millis()-mm>=60000)
{mm=millis();
lcd.clear();
lcd.setCursor(9,1);
lcd.print(':');
lcd.print(millis()/60000)/*/60000)*/;}

if(millis()-hh>=globh)
{hh=millis();
lcd.clear();
lcd.setCursor(7,1);
lcd.print(millis()/globh)/*/3600000000)*/;}

if(millis()-timer>=2000)
{timer=millis();
lcd.setCursor(0,0);
lcd.print("C=");
//lcd.setCursor(2,0);
lcd.print(C,3);
//lcd.setCursor(5,0);
lcd.print("I=");
lcd.print(Amps,3);
lcd.setCursor(0,1);
lcd.print("V=");
lcd.print(input_volt,2);
//lcd.setCursor(10,0);

/*Serial.print("time is   ");
Serial.print(seconds);
Serial.print("\t Amps = "); 
Serial.print(Amps,8);
Serial.print("\t Ёмкость = ");
Serial.println(C,8);}*/
}
}
