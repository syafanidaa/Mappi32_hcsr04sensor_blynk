#define BLYNK_TEMPLATE_ID "XXXXXXXXXXX" //ID Template
#define BLYNK_DEVICE_NAME "XXXXX" // Nama Device
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXXXXXXX" // Token dari Blynk
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>  // Token dari Blynk

#define triggerPin  26 // set Trigger ke pin 26/IO26
#define echoPin     25 // set Echo ke pin 25/IO25
#define pinLED  5

char auth[] = BLYNK_AUTH_TOKEN;


char ssid[] = "XXXXXX";   // Nama Hotspot / WiFi
char pass[] = "XXXXXXXX"; // Password WiFi



long duration;
int jarak;

BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}


void setup()
{
  // Debug console
  pinMode(triggerPin, OUTPUT);  // Set triggerPin sbg Output
  pinMode(echoPin, INPUT);   // Set echoPin sbg Input
  pinMode (pinLED, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(triggerPin, LOW);   //Set triggerPin low
  delayMicroseconds(2);       // delay 2 micro second

  digitalWrite(triggerPin, HIGH);  // Set triggerPin high
  delayMicroseconds(10);      // triggerPin high selama 10 micro seconds
  digitalWrite(triggerPin, LOW);   // triggerPinPin low

  duration = pulseIn(echoPin, HIGH);   //Pembacaan Echo pin dan durasi
  jarak = duration * 0.034 / 2;   ///Menghitung jarak yg sebenarnya

  Serial.println("jarak :"); //Output jarak pada serial monitor
  Serial.print(jarak);
  Serial.println(" cm");
  delay(250);

  if (jarak <= 10  )  // jika jarak yg didapatkan kurang dari atau sama dengan 10 cm maka lampu akan berkedip 
  {
    digitalWrite (pinLED, HIGH);
    delay(250);
    digitalWrite (pinLED, LOW);
    delay(250);
    digitalWrite (pinLED, HIGH);
    delay(250);
    digitalWrite (pinLED, LOW);
    delay(250);
    digitalWrite (pinLED, HIGH);
    delay(1000);
    digitalWrite (pinLED, LOW);
    delay(250);
    digitalWrite (pinLED, HIGH);
    delay(250);
    digitalWrite (pinLED, LOW);
    delay(250);
    digitalWrite (pinLED, HIGH);
    delay(250);
    digitalWrite (pinLED, LOW);
    delay(250);
    digitalWrite (pinLED, HIGH);
    delay(1000);
    digitalWrite (pinLED, LOW);
    delay(250);
  

  }
  else {
    digitalWrite (pinLED, LOW);
    delay(250);
  }

  Blynk.virtualWrite(V0, jarak);
  delay(1000);



}
