#include "DHT.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>


#define DHTPIN1 32//26
#define DHTPIN2 33//27
#define DHTPIN3 25//32
#define DHTPIN4 26//33
#define DHTPIN5 27//14
#define DHTPIN6 14//12
#define DHTPIN7 12//25
#define DHTPIN8 15
#define DHTPIN9 02
#define DHTPIN10 04
#define DHTPIN11 16
#define DHTPIN12 17
#define DHTPIN13 05

#define DHTTYPE1 DHT22
#define DHTTYPE2 DHT22
#define DHTTYPE3 DHT22
#define DHTTYPE4 DHT22
#define DHTTYPE5 DHT22
#define DHTTYPE6 DHT22
#define DHTTYPE7 DHT22
#define DHTTYPE8 DHT22
#define DHTTYPE9 DHT22
#define DHTTYPE10 DHT22
#define DHTTYPE11 DHT22
#define DHTTYPE12 DHT22
#define DHTTYPE13 DHT22

DHT dht1(DHTPIN1, DHTTYPE1);
DHT dht2(DHTPIN2, DHTTYPE2);
DHT dht3(DHTPIN3, DHTTYPE3);
DHT dht4(DHTPIN4, DHTTYPE4);
DHT dht5(DHTPIN5, DHTTYPE5);
DHT dht6(DHTPIN6, DHTTYPE6);
DHT dht7(DHTPIN7, DHTTYPE7);
DHT dht8(DHTPIN8, DHTTYPE8);
DHT dht9(DHTPIN9, DHTTYPE9);
DHT dht10(DHTPIN10, DHTTYPE10);
DHT dht11(DHTPIN11, DHTTYPE11);
DHT dht12(DHTPIN12, DHTTYPE12);
DHT dht13(DHTPIN13, DHTTYPE13);

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
int lcdColumns = 20;
int lcdRows = 4;


const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n"\
"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\n"\
"-----END CERTIFICATE-----\n";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org");
void setup() {
  Serial.begin(115200);
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
}

void loop() {
  
  dht1.begin();
  delay(5000);
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  if (isnan(h1) || isnan(t1)) {
    Serial.println(F("Failed to read from DHT sensor1!"));
    h1 = t1 = 404;
  }
  float h1ic = dht1.computeHeatIndex(t1, h1, false);
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Room="+room1);
  lcd.setCursor(0, 1);
  lcd.print("Temperature="+String(t1)+"'C");
  lcd.setCursor(0, 2);
  lcd.print("Humidity="+String(h1)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h1ic)+"'C");
  delay(5000);
  Serial.println("Temprature 1");
  Serial.println(t1);
  Serial.println("Humidity 1");
  Serial.println(h1);
  ///////////////////////////////////////////////////////////
  
  dht2.begin();
  delay(5000);
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  if (isnan(h2) || isnan(t2)) {
    Serial.println(F("Failed to read from DHT sensor2!"));
    h2 = t2 = 404;
  }
  float h2ic = dht2.computeHeatIndex(t2, h2, false);
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
  lcd.print("Humidity="+String(h2)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h2ic)+"'C");
  delay(5000);
  Serial.println("Temprature 2");
  Serial.println(t2);
  Serial.println("Humidity 2");
  Serial.println(h2);
  ///////////////////////////////////////////////////////////
  dht3.begin();
  delay(5000);
  float h3 = dht3.readHumidity();
  float t3 = dht3.readTemperature();
  if (isnan(h3) || isnan(t3)) {
    Serial.println(F("Failed to read from DHT sensor3!"));
    h3 = t3 = 404;
    //return;
  }
  float h3ic = dht3.computeHeatIndex(t3, h3, false);
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
  lcd.print("Humidity="+String(h3)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h3ic)+"'C");
  delay(5000);
  Serial.println("Temprature 3");
  Serial.println(t3);
  Serial.println("Humidity 3");
  Serial.println(h3);
  ///////////////////////////////////////////////////////////
  dht4.begin();
  delay(5000);
  float h4 = dht4.readHumidity();
  float t4 = dht4.readTemperature();
  if (isnan(h4) || isnan(t4)) {
    Serial.println(F("Failed to read from DHT sensor4!"));
    h4 = t4 = 404;
    //return;
  }
  float h4ic = dht4.computeHeatIndex(t4, h4, false);
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
  lcd.print("Humidity="+String(h4)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h4ic)+"'C");
  delay(5000);
  Serial.println("Temprature 4");
  Serial.println(t4);
  Serial.println("Humidity 4");
  Serial.println(h4);
  ///////////////////////////////////////////////////////////
  dht5.begin();
  delay(5000);
  float h5 = dht5.readHumidity();
  float t5 = dht5.readTemperature();
  if (isnan(h5) || isnan(t5)) {
    Serial.println(F("Failed to read from DHT sensor5!"));
    h5 = t5 = 404;
    //return;
  }
  float h5ic = dht5.computeHeatIndex(t5, h5, false);
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
  lcd.print("Humidity="+String(h5)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h5ic)+"'C");
  delay(5000);
  Serial.println("Temprature 5");
  Serial.println(t5);
  Serial.println("Humidity 5");
  Serial.println(h5);
  ///////////////////////////////////////////////////////////
  dht6.begin();
  delay(5000);
  float h6 = dht6.readHumidity();
  float t6 = dht6.readTemperature();
  if (isnan(h6) || isnan(t6)) {
    Serial.println(F("Failed to read from DHT sensor6!"));
    h6 = t6 = 404;
    //return;
  }
  Serial.println("Temprature 6");
  Serial.println(t6);
  Serial.println("Humidity 6");
  Serial.println(h6);
  ///////////////////////////////////////////////////////////
  dht7.begin();
  delay(5000);
  float h7 = dht7.readHumidity();
  float t7 = dht7.readTemperature();
  if (isnan(h7) || isnan(t7)) {
    Serial.println(F("Failed to read from DHT sensor7!"));
    h7 = t7 = 404;
    //return;
  }
  Serial.println("Temprature 7");
  Serial.println(t7);
  Serial.println("Humidity 7");
  Serial.println(h7);
  ///////////////////////////////////////////////////////////
  dht8.begin();
  delay(5000);
  float h8 = dht8.readHumidity();
  float t8 = dht8.readTemperature();
  if (isnan(h8) || isnan(t8)) {
    Serial.println(F("Failed to read from DHT sensor8!"));
    h8 = t8 = 404;
    //return;
  }
  float h8ic = dht8.computeHeatIndex(t8, h8, false);
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
  lcd.print("Humidity="+String(h8)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h8ic)+"'C");
  delay(5000);
  Serial.println("Temprature 8");
  Serial.println(t8);
  Serial.println("Humidity 8");
  Serial.println(h8);
  ///////////////////////////////////////////////////////////
  dht9.begin();
  delay(5000);
  float h9 = dht9.readHumidity();
  float t9 = dht9.readTemperature();
  if (isnan(h9) || isnan(t9)) {
    Serial.println(F("Failed to read from DHT sensor9!"));
    h9 = t9 = 404;
    //return;
  }
  float h9ic = dht9.computeHeatIndex(t9, h9, false);
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
  lcd.print("Humidity="+String(h9)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h9ic)+"'C");
  delay(5000);
  Serial.println("Temprature 9");
  Serial.println(t9);
  Serial.println("Humidity 9");
  Serial.println(h9);
  ///////////////////////////////////////////////////////////
  dht10.begin();
  delay(5000);
  float h10 = dht10.readHumidity();
  float t10 = dht10.readTemperature();
  if (isnan(h10) || isnan(t10)) {
    Serial.println(F("Failed to read from DHT sensor10!"));
    h10 = t10 = 404;
    //return;
  }
  float h10ic = dht10.computeHeatIndex(t10, h10, false);
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
  lcd.print("Humidity="+String(h10)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h10ic)+"'C");
  delay(5000);
  Serial.println("Temprature 10");
  Serial.println(t10);
  Serial.println("Humidity 10");
  Serial.println(h10);
  ///////////////////////////////////////////////////////////
  dht11.begin();
  delay(5000);
  float h11 = dht11.readHumidity();
  float t11 = dht11.readTemperature();
  if (isnan(h11) || isnan(t11)) {
    Serial.println(F("Failed to read from DHT sensor11!"));
    h11 = t11 = 404;
    //return;
  }
  float h11ic = dht11.computeHeatIndex(t11, h11, false);
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
  lcd.print("Humidity="+String(h11)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h11ic)+"'C");
  delay(5000);
  Serial.println("Temprature 11");
  Serial.println(t11);
  Serial.println("Humidity 11");
  Serial.println(h11);
  ///////////////////////////////////////////////////////////
  dht12.begin();
  delay(5000);
  float h12 = dht12.readHumidity();
  float t12 = dht12.readTemperature();
  if (isnan(h12) || isnan(t12)) {
    Serial.println(F("Failed to read from DHT sensor12!"));
    h12 = t12 = 404;
    //return;
  }

  Serial.println("Temprature 12");
  Serial.println(t12);
  Serial.println("Humidity 12");
  Serial.println(h12);
  ///////////////////////////////////////////////////////////
  dht13.begin();
  delay(5000);
  float h13 = dht13.readHumidity();
  float t13 = dht13.readTemperature();
  if (isnan(h13) || isnan(t13)) {
    Serial.println(F("Failed to read from DHT sensor13!"));
    h13 = t13 = 404;
    //return;
  }
  float h13ic = dht13.computeHeatIndex(t13, h13, false);
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
  lcd.print("Humidity="+String(h13)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h13ic)+"'C");
  delay(5000);
  Serial.println("Temprature 13");
  Serial.println(t13);
  Serial.println("Humidity 13");
  Serial.println(h13);
  
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
    }
  timeClient.begin();
  timeClient.setTimeOffset(19800);
  if(WiFi.status()== WL_CONNECTED){
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
    String httpRequestData = "api_key=tPmAT5Ab3j7F9&timedate="+timedate+"&siteLocation="+siteLocation+"&T1="+t1+"&H1="+h1+"&T2="+t2+"&H2="+h2+"&T3="+t3+"&H3="+h3+"&T4="+t4+"&H4="+h4+"&T5="+t5+"&H5="+h5+"&T6="+t6+"&H6="+h6+"&T7="+t7+"&H7="+h7+"&T8="+t8+"&H8="+h8+"&T9="+t9+"&H9="+h9+"&T10="+t10+"&H10="+h10+"&T11="+t11+"&H11="+h11+"&T12="+t12+"&H12="+h12+"&T13="+t13+"&H13="+h13+"&MAC=C4:4F:33:7A:90:55";//+String(WiFi.macAddress());
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
    }
    http.end();
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    delay(1000);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 0);
    lcd.print("WIFI DOWN");
    lcd.setCursor(0, 1);
    lcd.print("PLEASE VERIFY");
    lcd.setCursor(0, 2);
    lcd.print("WHETHER FENET WIFI");
    lcd.setCursor(0, 3);
    lcd.print("IS ON");
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    delay(1000); 
    }
  }
  WiFi.disconnect();
  for(int s=0;s<=5;s++){
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
  lcd.print("Humidity="+String(h1)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h1ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h2)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h2ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h3)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h3ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h4)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h4ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h5)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h5ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h8)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h8ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h9)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h9ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h10)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h10ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h11)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h11ic)+"'C");
  delay(5000);
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
  lcd.print("Humidity="+String(h13)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h13ic)+"'C");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(1000);
  }
  ESP.restart();
}
