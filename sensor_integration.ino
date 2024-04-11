#include <ThingSpeak.h>  //To connect our thingspeak channel with the esp8266 through this code.
#include <ESP8266WiFi.h>  // To connect the esp with internet
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

//---------------------Enter wifi credentials -----------------//
const char* ssid     = "KITCampus";    //Name of your wifi network
const char* password = "student@kit";  // Wifi password

//---------------------Channel Details--------------------//
unsigned long Channel_ID = 1703407; // Channel ID
const char *WriteAPIKey = "1187E3TSBFW42HCT"; // Your write API Key
WiFiClient  client;

//---------------------Sensor Details--------------------//
#define DHTPIN 2              //D4 pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define sensorPin A0          //connect the sensor to analog pin of esp8266
#define motorPin D8
#define BMP_SDA 4
#define BMP_SCL 5
Adafruit_BMP280 bmp;

//---------------------Calibration values--------------------//
/* Change these values based on your calibration values */
int soilWet = 65;        // Define max value we consider soil 'wet'   
int soilDry = 35;        // Define min value we consider soil 'dry'

float Humidity = 0.0 ;
float Temperature = 0.0 ;
float Pressure = 0.0;
float Altitude = 0.0;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, HIGH);
  Serial.begin(9600); 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Irrigation" );
  lcd.setCursor(0,1);
  lcd.print("     System" );
  WiFi.begin(ssid, password);  // Connecting esp to wifi
  while (WiFi.status() != WL_CONNECTED)  //This loop will work untill esp connects to the wifi
  {   
  delay(500);
  Serial.print(".");
  }
  ThingSpeak.begin(client);       //The client here is esp8266 
  delay(1000);
  lcd.clear();
  bmp.begin(0x76);
}

void loop() {
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  Pressure = bmp.readPressure() / 100.0;
  Altitude = bmp.readAltitude(101325);

  Serial.print("Humidity : ");
  Serial.println(Humidity);
  Serial.print("Temperature :");
  Serial.println(Temperature);
  Serial.print("Pressure : ");
  Serial.println(Pressure);
  Serial.print("Altitude : ");
  Serial.println(Altitude);

  int moisture = analogRead(sensorPin);    //Read the analog values
   moisture = map(moisture, 0, 1024, 100, 0);
  Serial.print("Soil moisture: ");  //Print the analog values
  Serial.println(moisture);

  if ((millis() - delayStart) >= 15000) {
    ThingSpeak.writeField(Channel_ID,1,Humidity, WriteAPIKey);
    ThingSpeak.writeField(Channel_ID,2,Temperature, WriteAPIKey);
    ThingSpeak.writeField(Channel_ID,3,Pressure, WriteAPIKey);
    ThingSpeak.writeField(Channel_ID,4,Altitude, WriteAPIKey);
    ThingSpeak.writeField(Channel_ID,5,moisture, WriteAPIKey);

    lcd.setCursor(0,0);
    lcd.print("Humidity : ");
    lcd.print(Humidity);
    lcd.setCursor(0,1);
    lcd.print("Moisture : ");
    lcd.print(moisture);

    // Determine status of our soil using the values already defined for wet and dry soil
    if (moisture > soilWet) 
    {
      Serial.println("Status: Soil is too wet");
      digitalWrite(motorPin, HIGH);
    } 
    else if (moisture <= soilWet && moisture > soilDry) 
    {
      Serial.println("Status: Soil moisture is perfect");
      digitalWrite(motorPin, HIGH); 
    } 
    else 
    {
      Serial.println("Status: Soil is too dry - time to water!");
      digitalWrite(motorPin, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Watering...");
      delay(5000);
      digitalWrite(motorPin, HIGH);
      lcd.clear();
    }
    delayStart = millis();
  }
  delay(500);
  Serial.println();
}