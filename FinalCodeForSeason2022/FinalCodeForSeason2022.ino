#include "DHT.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#define DHTPIN1 32
#define DHTPIN2 33
#define DHTPIN3 25
#define DHTPIN4 26
#define DHTPIN5 27
#define DHTPIN6 14
#define DHTPIN7 12
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
DHT dht011(16, DHT22);
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
  lcd.setCursor(0, 0);
  lcd.print("PLEASE");
  lcd.setCursor(0, 1);
  lcd.print("WAIT WHILE");
  lcd.setCursor(0, 2);
  lcd.print("READING");
  lcd.setCursor(0, 3);
  lcd.print("DATA");
  delay(2000);
}
void loop() {
  int boottime = int(millis());
  ///////////////////////////////////////////////////////////
  dht011.begin();
  delay(10000);
  float t11 = dht011.readTemperature();
  //delay(10000);
  float h11 = dht011.readHumidity();
  if (isnan(h11)) {
    Serial.println(("Failed to read from DHT sensor11!"));
    h11 = 404;
  }
  if (isnan(t11)) {
    Serial.println(("Failed to read from DHT sensor11!"));
    t11 = 404;
  }
  float h11ic = dht011.computeHeatIndex(t11, h11, false);
  Serial.println("Temprature IN "+room11);
  Serial.println(t11);
  Serial.println("Humidity IN "+room11);
  Serial.println(h11);
  Serial.println("Feels Like="+String(h11ic)+"'C IN "+room11);
  ///////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////
  dht1.begin();
  delay(10000);
  float h1 = dht1.readHumidity();
  delay(10000);
  float t1 = dht1.readTemperature();
  if (isnan(h1)) {
    Serial.println(("Failed to read from DHT sensor1!"));
    h1 = 404;
  }
  if (isnan(t1)) {
    Serial.println(("Failed to read from DHT sensor1!"));
    t1 = 404;
  }
  float h1ic = dht1.computeHeatIndex(t1, h1, false);
  Serial.println("Temprature IN "+room1);
  Serial.println(t1);
  Serial.println("Humidity IN "+room1);
  Serial.println(h1);
  Serial.println("Feels Like="+String(h1ic)+"'C IN "+room1);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht2.begin();
  delay(10000);
  float h2 = dht2.readHumidity();
  delay(10000);
  float t2 = dht2.readTemperature();
  if (isnan(h2)) {
    Serial.println(("Failed to read from DHT sensor2!"));
    h2 = 404;
  }
  if (isnan(t2)) {
    Serial.println(("Failed to read from DHT sensor2!"));
    t2 = 404;
  }
  float h2ic = dht2.computeHeatIndex(t2, h2, false);
  Serial.println("Temprature IN "+room2);
  Serial.println(t2);
  Serial.println("Humidity IN "+room2);
  Serial.println(h2);
  Serial.println("Feels Like="+String(h2ic)+"'C IN "+room2);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht3.begin();
  delay(10000);
  float h3 = dht3.readHumidity();
  delay(10000);
  float t3 = dht3.readTemperature();
  if (isnan(h3)) {
    Serial.println(("Failed to read from DHT sensor3!"));
    h3 = 404;
  }
  if (isnan(t3)) {
    Serial.println(("Failed to read from DHT sensor3!"));
    t3 = 404;
  }
  float h3ic = dht3.computeHeatIndex(t3, h3, false);
  Serial.println("Temprature IN "+room3);
  Serial.println(t3);
  Serial.println("Humidity IN "+room3);
  Serial.println(h3);
  Serial.println("Feels Like="+String(h3ic)+"'C IN "+room3);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht4.begin();
  delay(10000);
  float h4 = dht4.readHumidity();
  delay(10000);
  float t4 = dht4.readTemperature();
  if (isnan(h4)) {
    Serial.println(("Failed to read from DHT sensor4!"));
    h4 = 404;
  }
  if (isnan(t4)) {
    Serial.println(("Failed to read from DHT sensor4!"));
    t4 = 404;
  }
  float h4ic = dht4.computeHeatIndex(t4, h4, false);
  Serial.println("Temprature IN "+room4);
  Serial.println(t4);
  Serial.println("Humidity IN "+room4);
  Serial.println(h4);
  Serial.println("Feels Like="+String(h4ic)+"'C IN "+room4);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht5.begin();
  delay(10000);
  float h5 = dht5.readHumidity();
  delay(10000);
  float t5 = dht5.readTemperature();
  if (isnan(h5)) {
    Serial.println(("Failed to read from DHT sensor5!"));
    h5 = 404;
  }
  if (isnan(t5)) {
    Serial.println(("Failed to read from DHT sensor5!"));
    t5 = 404;
  }
  float h5ic = dht5.computeHeatIndex(t5, h5, false);
  Serial.println("Temprature IN "+room5);
  Serial.println(t5);
  Serial.println("Humidity IN "+room5);
  Serial.println(h5);
  Serial.println("Feels Like="+String(h5ic)+"'C IN "+room5);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht8.begin();
  delay(10000);
  float h8 = dht8.readHumidity();
  delay(10000);
  float t8 = dht8.readTemperature();
  if (isnan(h8)) {
    Serial.println(("Failed to read from DHT sensor8!"));
    h8 = 404;
  }
  if (isnan(t8)) {
    Serial.println(("Failed to read from DHT sensor8!"));
    t8 = 404;
  }
  float h8ic = dht8.computeHeatIndex(t8, h8, false);
  Serial.println("Temprature IN "+room8);
  Serial.println(t8);
  Serial.println("Humidity IN "+room8);
  Serial.println(h8);
  Serial.println("Feels Like="+String(h8ic)+"'C IN "+room8);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht9.begin();
  delay(10000);
  float h9 = dht9.readHumidity();
  delay(10000);
  float t9 = dht9.readTemperature();
  if (isnan(h9)) {
    Serial.println(("Failed to read from DHT sensor9!"));
    h9 = 404;
  }
  if (isnan(t9)) {
    Serial.println(("Failed to read from DHT sensor9!"));
    t9 = 404;
  }
  float h9ic = dht9.computeHeatIndex(t9, h9, false);
  Serial.println("Temprature IN "+room9);
  Serial.println(t9);
  Serial.println("Humidity IN "+room9);
  Serial.println(h9);
  Serial.println("Feels Like="+String(h9ic)+"'C IN "+room9);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht10.begin();
  delay(10000);
  float h10 = dht10.readHumidity();
  delay(10000);
  float t10 = dht10.readTemperature();
  if (isnan(h10)) {
    Serial.println(("Failed to read from DHT sensor10!"));
    h10 = 404;
  }
  if (isnan(t10)) {
    Serial.println(("Failed to read from DHT sensor10!"));
    t10 = 404;
  }
  float h10ic = dht10.computeHeatIndex(t10, h10, false);
  Serial.println("Temprature IN "+room10);
  Serial.println(t10);
  Serial.println("Humidity IN "+room10);
  Serial.println(h10);
  Serial.println("Feels Like="+String(h10ic)+"'C IN "+room10);
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  dht13.begin();
  delay(10000);
  float h13 = dht13.readHumidity();
  delay(10000);
  float t13 = dht13.readTemperature();
  if (isnan(h13)) {
    Serial.println(("Failed to read from DHT sensor13!"));
    h13 = 404;
  }
  if (isnan(t13)) {
    Serial.println(("Failed to read from DHT sensor13!"));
    t13 = 404;
  }
  float h13ic = dht13.computeHeatIndex(t13, h13, false);
  Serial.println("Temprature IN "+room13);
  Serial.println(t13);
  Serial.println("Humidity IN "+room13);
  Serial.println(h13);
  Serial.println("Feels Like="+String(h13ic)+"'C IN "+room13);
  ///////////////////////////////////////////////////////////

  
  ///////////////////////////////////////////////////////////
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(1000);
    }
   timeClient.begin();
   timeClient.setTimeOffset(19800);
  
  //if(WiFi.status()== WL_CONNECTED){
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
    float h12 = 404;
    float t12 = 404;
    float h6 = 404;
    float t6 = 404;
    float h7 = 404;
    float t7 = 404;
    String httpRequestData = "api_key=tPmAT5Ab3j7F9&timedate="+timedate+"&siteLocation="+siteLocation+"&T1="+t1+"&H1="+h1+"&T2="+t2+"&H2="+h2+"&T3="+t3+"&H3="+h3+"&T4="+t4+"&H4="+h4+"&T5="+t5+"&H5="+h5+"&T6="+t6+"&H6="+h6+"&T7="+t7+"&H7="+h7+"&T8="+t8+"&H8="+h8+"&T9="+t9+"&H9="+h9+"&T10="+t10+"&H10="+h10+"&T11="+t11+"&H11="+h11+"&T12="+t12+"&H12="+h12+"&T13="+t13+"&H13="+h13+"&MAC="+String(WiFi.macAddress());
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
  WiFi.disconnect();
  while((boottime-int(millis()))<600000){
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
  lcd.print("Humidity="+String(h2)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h2ic)+"'C");
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
  lcd.print("Humidity="+String(h3)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h3ic)+"'C");
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
  lcd.print("Humidity="+String(h4)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h4ic)+"'C");
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
  lcd.print("Humidity="+String(h5)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h5ic)+"'C");
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
  lcd.print("Humidity="+String(h8)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h8ic)+"'C");
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
  lcd.print("Humidity="+String(h9)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h9ic)+"'C");
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
  lcd.print("Humidity="+String(h10)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h10ic)+"'C");
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
  lcd.print("Humidity="+String(h11)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h11ic)+"'C");
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
  lcd.print("Humidity="+String(h13)+"%");
  lcd.setCursor(0, 3);
  lcd.print("Feels Like="+String(h13ic)+"'C");
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
  }
  ESP.restart();
}
