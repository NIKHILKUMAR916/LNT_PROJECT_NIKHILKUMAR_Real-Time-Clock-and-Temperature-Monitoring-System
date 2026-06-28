#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

RTC_DS1307 rtc;

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (1);
  }

  if (!rtc.begin()) {
    Serial.println("RTC not found");
    while (1);
  }

  // Uncomment once to set RTC
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  sensors.begin();
  display.setTextColor(SSD1306_WHITE);
}
void loop() {

  static float temp = 22.0;
  static bool alert = false;

  DateTime now = rtc.now();

  // Increase temperature
  temp += 0.5;

  if(temp >= 35.0)
    alert = true;

  // Reset after 45°C
  if(temp > 45.0){
    temp = 22.0;
    alert = false;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // Time
  display.setCursor(0,0);

  if(now.hour()<10) display.print("0");
  display.print(now.hour());
  display.print(":");

  if(now.minute()<10) display.print("0");
  display.print(now.minute());
  display.print(":");

  if(now.second()<10) display.print("0");
  display.println(now.second());

  // Temperature
  display.setCursor(0,14);
  display.print("Temp: ");
  display.print(temp,1);
  display.print(" C");

  // Progress Bar
  display.drawRect(0,30,120,10,SSD1306_WHITE);

  int width = map((int)(temp*10),220,450,0,118);

  display.fillRect(1,31,width,8,SSD1306_WHITE);

  if(!alert){

    display.setCursor(0,46);
    display.print("Status: Heating...");

  }
  else{

    static bool blink=false;

    blink=!blink;

    if(blink){

      display.setCursor(0,46);
      display.print("!!! ALERT !!!");

    }

    display.setCursor(0,56);
    display.print("HIGH TEMP");

  }

  display.display();

  Serial.print("Temperature = ");
  Serial.println(temp);

  delay(1000);
}