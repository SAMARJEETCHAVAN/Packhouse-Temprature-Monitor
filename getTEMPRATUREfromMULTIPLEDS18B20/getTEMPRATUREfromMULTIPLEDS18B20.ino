#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
int lcdColumns = 20;
int lcdRows = 4;


// Data wire is plugged TO GPIO 4
#define ONE_WIRE_BUS 27

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup(){
  // start serial port
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Wire.setClock(10000);
  // Start up the library
  sensors.begin();
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Reading");
  lcd.setCursor(0, 1);
  lcd.print("SENSORS");
  lcd.setCursor(0, 2);
  lcd.print("PLEASE");
  lcd.setCursor(0, 3);
  lcd.print("WAIT");
  delay(1000);
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Locating devices");
  lcd.setCursor(0, 1);
  lcd.print("Found");
  lcd.setCursor(0, 2);
  lcd.print(String(numberOfDevices));
  lcd.setCursor(0, 3);
  lcd.print("devices");
  delay(1000);

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      String deviceaddr = printAddress(tempDeviceAddress);
       
      Serial.println();
      
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("found dewvice");
  lcd.setCursor(0, 1);
  lcd.print(String(i));
  lcd.setCursor(0, 2);
  lcd.print(deviceaddr);
  lcd.setCursor(0, 3);
  lcd.print("devices");
  delay(1000);
    } else {
      String deviceaddr = printAddress(tempDeviceAddress);
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
      
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("found ghost @");
  lcd.setCursor(0, 1);
  lcd.print("could not detect ");
  lcd.setCursor(0, 2);
  lcd.print(deviceaddr);
  lcd.setCursor(0, 3);
  lcd.print("address");
  delay(1000);
    }
  }
}

void loop(){ 
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      // Output the device ID
      Serial.print("Temperature for device: ");
      Serial.println(i,DEC);
      // Print the data
      float tempC = sensors.getTempC(tempDeviceAddress);
      Serial.print("Temp C: ");
      Serial.print(tempC);
      Serial.print(" Temp F: ");
      Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
      
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temperature for");
  lcd.setCursor(0, 1);
  lcd.print(String(i));
  lcd.setCursor(0, 2);
  lcd.print(String(tempC));
  lcd.setCursor(0, 3);
  lcd.print("ok");
  delay(10000);
    }
  }
  delay(5000);
}

// function to print a device address
String printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
      return(String(deviceAddress[i], HEX));
  }
}
/*
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define ONE_WIRE_BUS 27
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress sensor1 = { 0x28, 0xCD, 0x73, 0x99, 0x5C, 0x20, 0x01, 0xB6 };
DeviceAddress sensor2 = { 0x28, 0xF2, 0xC8, 0x06, 0x64, 0x20, 0x01, 0xB3 };
DeviceAddress sensor3 = { 0x28, 0x6A, 0x16, 0xF5, 0x4F, 0x20, 0x01, 0xF3 };
DeviceAddress sensor4 = { 0x28, 0xC1, 0x77, 0xE8, 0x4F, 0x20, 0x01, 0x2E };
DeviceAddress sensor5 = { 0x28, 0xB3, 0x43, 0xFC, 0x4E, 0x20, 0x01, 0xDE };
DeviceAddress sensor8 = { 0x28, 0x7E, 0xEF, 0xE6, 0x5D, 0x20, 0x01, 0x94 };
DeviceAddress sensor9 = { 0x28, 0xC3, 0xB0, 0xF0, 0x5D, 0x20, 0x01, 0x12 };
DeviceAddress sensor10 = { 0x28, 0xC5, 0x45, 0xDC, 0xF5, 0x20, 0x01, 0xB6 };
DeviceAddress sensor11 = { 0x28, 0x25, 0xDD, 0x3, 0x50, 0x20, 0x01, 0x9D };
DeviceAddress sensor13 = { 0x28, 0xAC, 0xF8, 0xDC, 0x5D, 0x20, 0x01, 0x40 };

const char* serverName = "https://www.feweather.com/post-packhouse-data.php";
String apiKeyValue = "tPmAT5Ab3j7F9";
String siteLocation = "MIRAJ";
String room1 = "SMALL PRE-COOL";
String room2 = "BIG PRE-COOL";
String room3 = "COLD STORAGE";
String room4 = "HOLDING ROOM";
String room5 = "PACKHOUSE 1";
String room8 = "PACKHOUSE 2";
String room9 = "PACKHOUSE 3";
String room10 = "LOADING DOCK";
String room11 = "EXTERNAL";
String room13 = "Racking Room";
String room12 = "Room 12";
String room6 = "Room 6";
String room7 = "Room 7";
String timedate = "00:00:00";
String formattedTime = "00:00:00";//timeClient.getFormattedTime();
int monthDay = 0;//ptm->tm_mday;
int currentMonth = 0;//ptm->tm_mon+1;
int currentYear = 0;//ptm->tm_year+1900;
int lcdColumns = 20;
int lcdRows = 4;


const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIF2DCCA8CgAwIBAgIQTKr5yttjb+Af907YWwOGnTANBgkqhkiG9w0BAQwFADCB\n" \
"hTELMAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4G\n" \
"A1UEBxMHU2FsZm9yZDEaMBgGA1UEChMRQ09NT0RPIENBIExpbWl0ZWQxKzApBgNV\n" \
"BAMTIkNPTU9ETyBSU0EgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMTAwMTE5\n" \
"MDAwMDAwWhcNMzgwMTE4MjM1OTU5WjCBhTELMAkGA1UEBhMCR0IxGzAZBgNVBAgT\n" \
"EkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UEChMR\n" \
"Q09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMTIkNPTU9ETyBSU0EgQ2VydGlmaWNh\n" \
"dGlvbiBBdXRob3JpdHkwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCR\n" \
"6FSS0gpWsawNJN3Fz0RndJkrN6N9I3AAcbxT38T6KhKPS38QVr2fcHK3YX/JSw8X\n" \
"pz3jsARh7v8Rl8f0hj4K+j5c+ZPmNHrZFGvnnLOFoIJ6dq9xkNfs/Q36nGz637CC\n" \
"9BR++b7Epi9Pf5l/tfxnQ3K9DADWietrLNPtj5gcFKt+5eNu/Nio5JIk2kNrYrhV\n" \
"/erBvGy2i/MOjZrkm2xpmfh4SDBF1a3hDTxFYPwyllEnvGfDyi62a+pGx8cgoLEf\n" \
"Zd5ICLqkTqnyg0Y3hOvozIFIQ2dOciqbXL1MGyiKXCJ7tKuY2e7gUYPDCUZObT6Z\n" \
"+pUX2nwzV0E8jVHtC7ZcryxjGt9XyD+86V3Em69FmeKjWiS0uqlWPc9vqv9JWL7w\n" \
"qP/0uK3pN/u6uPQLOvnoQ0IeidiEyxPx2bvhiWC4jChWrBQdnArncevPDt09qZah\n" \
"SL0896+1DSJMwBGB7FY79tOi4lu3sgQiUpWAk2nojkxl8ZEDLXB0AuqLZxUpaVIC\n" \
"u9ffUGpVRr+goyhhf3DQw6KqLCGqR84onAZFdr+CGCe01a60y1Dma/RMhnEw6abf\n" \
"Fobg2P9A3fvQQoh/ozM6LlweQRGBY84YcWsr7KaKtzFcOmpH4MN5WdYgGq/yapiq\n" \
"crxXStJLnbsQ/LBMQeXtHT1eKJ2czL+zUdqnR+WEUwIDAQABo0IwQDAdBgNVHQ4E\n" \
"FgQUu69+Aj36pvE8hI6t7jiY7NkyMtQwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB\n" \
"/wQFMAMBAf8wDQYJKoZIhvcNAQEMBQADggIBAArx1UaEt65Ru2yyTUEUAJNMnMvl\n" \
"wFTPoCWOAvn9sKIN9SCYPBMtrFaisNZ+EZLpLrqeLppysb0ZRGxhNaKatBYSaVqM\n" \
"4dc+pBroLwP0rmEdEBsqpIt6xf4FpuHA1sj+nq6PK7o9mfjYcwlYRm6mnPTXJ9OV\n" \
"2jeDchzTc+CiR5kDOF3VSXkAKRzH7JsgHAckaVd4sjn8OoSgtZx8jb8uk2Intzna\n" \
"FxiuvTwJaP+EmzzV1gsD41eeFPfR60/IvYcjt7ZJQ3mFXLrrkguhxuhoqEwWsRqZ\n" \
"CuhTLJK7oQkYdQxlqHvLI7cawiiFwxv/0Cti76R7CZGYZ4wUAc1oBmpjIXUDgIiK\n" \
"boHGhfKppC3n9KUkEEeDys30jXlYsQab5xoq2Z0B15R97QNKyvDb6KkBPvVWmcke\n" \
"jkk9u+UJueBPSZI9FoJAzMxZxuY67RIuaTxslbH9qh17f4a+Hg4yRvv7E491f0yL\n" \
"S0Zj/gA0QHDBw7mh3aZw4gSzQbzpgJHqZJx64SIDqZxubw5lT2yHh17zbqD5daWb\n" \
"QOhTsiedSrnAdyGN/4fy3ryM7xfft0kL0fJuMAsaDk527RH89elWsn2/x20Kk4yl\n" \
"0MC2Hb46TpSi125sC8KKfPog88Tk5c0NqMuRkrF8hey1FGlmDoLnzc7ILaZRfyHB\n" \
"NVOFBkpdn627G190\n" \
"-----END CERTIFICATE-----\n";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
void setup(void){
  Serial.begin(115200);
  sensors.begin();
  lcd.init();
  lcd.backlight();
  Wire.setClock(10000);
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Reading");
  lcd.setCursor(0, 1);
  lcd.print("SENSORS");
  lcd.setCursor(0, 2);
  lcd.print("PLEASE");
  lcd.setCursor(0, 3);
  lcd.print("WAIT");
  delay(1000);
}

void loop(void){ 
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
  Serial.print("Sensor 11(*C): ");
  String t11 = String(sensors.getTempC(sensor11));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room11);
  lcd.setCursor(0, 1);
  lcd.print(String(t11));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room1));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 1(*C): ");
  String t1 = String(sensors.getTempC(sensor1));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room1);
  lcd.setCursor(0, 1);
  lcd.print(String(t1));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room2));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 2(*C): ");
  String t2 = String(sensors.getTempC(sensor2));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room2);
  lcd.setCursor(0, 1);
  lcd.print(String(t2));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room3));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 3(*C): ");
  String t3 = String(sensors.getTempC(sensor3));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room3);
  lcd.setCursor(0, 1);
  lcd.print(String(t3));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room4));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 4(*C): ");
  String t4 = String(sensors.getTempC(sensor4));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room4);
  lcd.setCursor(0, 1);
  lcd.print(String(t4));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room5));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 5(*C): ");
  String t5 = String(sensors.getTempC(sensor5));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room5);
  lcd.setCursor(0, 1);
  lcd.print(String(t5));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room8));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 8(*C): ");
  String t8 = String(sensors.getTempC(sensor8));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room8);
  lcd.setCursor(0, 1);
  lcd.print(String(t8));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room9));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 9(*C): ");
  String t9 = String(sensors.getTempC(sensor9));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room9);
  lcd.setCursor(0, 1);
  lcd.print(String(t9));
  lcd.setCursor(0, 2);
  lcd.print("Reading SENSOR @");
  lcd.setCursor(0, 3);
  lcd.print(String(room10));
  delay(10000);
  Serial.println("DONE");
  Serial.print("Sensor 10(*C): ");
  String t10 = String(sensors.getTempC(sensor10));
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp@"+room10);
  lcd.setCursor(0, 1);
  lcd.print(String(t10));
  lcd.setCursor(0, 2);
  lcd.print("End of all");
  lcd.setCursor(0, 3);
  lcd.print("sensors");
  delay(10000);
  String t6 = "404";
  String t7 = "404";
  String t12 = "404";
  String t13 = "404";
  String h1 = "404";
  String h2 = "404";
  String h3 = "404";
  String h4 = "404";
  String h5 = "404";
  String h6 = "404";
  String h7 = "404";
  String h8 = "404";
  String h9 = "404";
  String h10 = "404";
  String h11 = "404";
  String h12 = "404";
  String h13 = "404";
  
}
*/
