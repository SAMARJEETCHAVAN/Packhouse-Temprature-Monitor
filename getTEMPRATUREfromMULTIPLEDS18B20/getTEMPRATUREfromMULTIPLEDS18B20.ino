#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#define ONE_WIRE_BUS 27
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int lcdColumns = 20;
int lcdRows = 4;
int numberOfDevices;
DeviceAddress tempDeviceAddress; 
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

const char *ssid     = "FENET";
const char *password = "12345678";
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


  String t1 = "404.00";
  String t2 = "404.00";
  String t3 = "404.00";
  String t4 = "404.00";
  String t5 = "404.00";
  String t6 = "404.00";
  String t7 = "404.00";
  String t8 = "404.00";
  String t9 = "404.00";
  String t10 = "404.00";
  String t11 = "404.00";
  String t12 = "404.00";
  String t13 = "404.00";
  String h1 = "404.00";
  String h2 = "404.00";
  String h3 = "404.00";
  String h4 = "404.00";
  String h5 = "404.00";
  String h6 = "404.00";
  String h7 = "404.00";
  String h8 = "404.00";
  String h9 = "404.00";
  String h10 = "404.00";
  String h11 = "404.00";
  String h12 = "404.00";
  String h13 = "404.00";
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

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org");


void setup(){
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Wire.setClock(10000);
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
  }

void loop(){
    int boottime = int(millis());

   t1 = "404.00";
   t2 = "404.00";
   t3 = "404.00";
   t4 = "404.00";
   t5 = "404.00";
   t6 = "404.00";
   t7 = "404.00";
   t8 = "404.00";
   t9 = "404.00";
   t10 = "404.00";
   t11 = "404.00";
   t12 = "404.00";
   t13 = "404.00";
   h1 = "404.00";
   h2 = "404.00";
   h3 = "404.00";
   h4 = "404.00";
   h5 = "404.00";
   h6 = "404.00";
   h7 = "404.00";
   h8 = "404.00";
   h9 = "404.00";
   h10 = "404.00";
   h11 = "404.00";
   h12 = "404.00";
   h13 = "404.00"; 
  numberOfDevices = sensors.getDeviceCount();
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
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      String deviceaddr = printAddress(tempDeviceAddress);   
      Serial.println();
      
  /*lcd.setCursor(0, 0);
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
  delay(1000);*/
    } else {
      String deviceaddr = printAddress(tempDeviceAddress);
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
      
  /*lcd.setCursor(0, 0);
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
  delay(1000);*/
    }
  }

  
  sensors.requestTemperatures(); // Send the command to get temperatures
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Temperature for device: ");
      Serial.println(i,DEC);
      String deviceaddr = printAddress(tempDeviceAddress);   
      float tempC = sensors.getTempC(tempDeviceAddress);
      Serial.println(tempC);
      Serial.println(deviceaddr);
      if(String(deviceaddr)=="28b343fc4e201de"){
        t5=String(tempC);}
      else if(String(deviceaddr)=="287eefe65d20194"){
        t8=String(tempC);
        }
      else if(String(deviceaddr)=="28c3b0f05d20112"){
        t9=String(tempC);
        }
      else if(String(deviceaddr)=="2825dd3502019d"){
        t11=String(tempC);
        }
      else if(String(deviceaddr)=="28c545dc5d201b6"){
        t10=String(tempC);
        }
      
      else if(String(deviceaddr)=="28cd73995c201c5"){
        t1=String(tempC);
        }
      else if(String(deviceaddr)=="286a16f54f201f3"){
        t3=String(tempC);
        }
      else if(String(deviceaddr)=="28acf8dc5d20140"){
        t13=String(tempC);
        }
      else if(String(deviceaddr)=="28C177E84F2012E"){
        t4=String(tempC);
        }
      else if(String(deviceaddr)=="28f2c8664201b3"){
        t2=String(tempC);
        }
    }
  }
  WiFi.begin(ssid, password);
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
  lcd.print("PLEASE WAIT");
  lcd.setCursor(0, 1);
  lcd.print("WHILE");
  lcd.setCursor(0, 2);
  lcd.print("TRYING TO");
  lcd.setCursor(0, 3);
  lcd.print("CONNECT 2 FENET");
  delay(1000);
  int timeout = millis();
  while(WiFi.status()!= WL_CONNECTED) {
      Serial.println(".");
      Serial.println((millis()-timeout));
      if((millis()-timeout)>=120000){
        
          Serial.println("WIFI CONNECTION FAILED");
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
          lcd.print("WIFI");
          lcd.setCursor(0, 1);
          lcd.print("CONNECTION");
          lcd.setCursor(0, 2);
          lcd.print("FAILED");
          lcd.setCursor(0, 3);
          lcd.print("WILL REBOOT");
          delay(60000);
          ESP.restart();
          }
  }
  timeClient.begin();
  timeClient.setTimeOffset(19800);
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  monthDay = ptm->tm_mday;
  currentMonth = ptm->tm_mon+1;
  currentYear = ptm->tm_year+1900;
  timedate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay)+ " "+formattedTime;
  WiFiClient client;
  HTTPClient http;
  http.begin(serverName, root_ca);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "api_key=tPmAT5Ab3j7F9&timedate="+String(timedate)+"&siteLocation="+siteLocation+"&T1="+String(t1)+"&H1="+String(h1)+"&T2="+String(t2)+"&H2="+String(h2)+"&T3="+String(t3)+"&H3="+String(h3)+"&T4="+String(t4)+"&H4="+String(h4)+"&T5="+String(t5)+"&H5="+String(h5)+"&T6="+String(t6)+"&H6="+String(h6)+"&T7="+String(t7)+"&H7="+String(h7)+"&T8="+String(t8)+"&H8="+String(h8)+"&T9="+String(t9)+"&H9="+String(h9)+"&T10="+String(t10)+"&H10="+String(h10)+"&T11="+String(t11)+"&H11="+String(h11)+"&T12="+String(t12)+"&H12="+String(h12)+"&T13="+String(t13)+"&H13="+String(h13)+"&MAC="+String(WiFi.macAddress());
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
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
      lcd.print("HTTPcode:"+String(httpResponseCode));
      lcd.setCursor(0, 1);
      lcd.print(timedate);
      if(httpResponseCode==200){
      lcd.setCursor(0, 2);
      lcd.print("Upload was ");
      lcd.setCursor(0, 3);
      lcd.print("Sucessful");
      delay(60000);}
      else{
          lcd.setCursor(0, 2);
          lcd.print("Upload was ");
          lcd.setCursor(0, 3);
          lcd.print("Unsucessful");
          delay(60000);
          ESP.restart();
  http.end();
  WiFi.disconnect();
  }
  }
  while((int(millis())-boottime)<600000){
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
  lcd.print("HTTPcode:"+String(httpResponseCode));
  lcd.setCursor(0, 1);
  lcd.print(timedate);
  if(httpResponseCode==200){
  lcd.setCursor(0, 2);
  lcd.print("Upload was ");
  lcd.setCursor(0, 3);
  lcd.print("Sucessful");
  }
  delay(10000);
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
  lcd.print("Room="+room1);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t1)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room2);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t2)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room3);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t3)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room4);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t4)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room5);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t5)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room8);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t8)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room9);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t9)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room10);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t10)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room11);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t11)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
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
  lcd.print("Room="+room13);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t13)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Above reading @");
  lcd.setCursor(0, 3);
  lcd.print(String(timedate));
  delay(10000);
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(10000);
    }
  delay(5000);
}

// function to print a device address
String printAddress(DeviceAddress deviceAddress) {
  String devadd = "";
  for (uint8_t i = 0; i < 8; i++){
    
    if (deviceAddress[i] < 16) Serial.print("0");
      //Serial.print(deviceAddress[i], HEX);
      devadd = devadd + String(deviceAddress[i], HEX);
  }
  
      return(devadd);
}
//THIS THE CODE
