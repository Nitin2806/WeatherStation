#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Servo.h>
#include <ArduinoJson.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define ESP_RX 9
#define ESP_TX 8
#define GPS_RX 4
#define GPS_TX 3
#define SERVO_PIN 6
#define WIFI_AP "Nitin's PC"
#define WIFI_PASSWORD "Nitin123"
#define MSG_BUFFER_SIZE  (100)

static const int rainSensorMin = 0;
static const int rainSensorMax = 1024;
char msg[MSG_BUFFER_SIZE];
char temp[7];
char hum[7];
float t;
float h;


WiFiEspClient espClient;
PubSubClient mqttClient(espClient);
IPAddress broker(192,168,43,235);
Servo myservo;

SoftwareSerial ESP8266(ESP_RX, ESP_TX);
DHT dht(DHTPIN, DHTTYPE);

int angle = 0;
int status = WL_IDLE_STATUS;
char *ID = "uno";
char *TOPIC = "uno/weatherStats";

int AT_cmd_time;
boolean AT_cmd_result = false;


void setup() {
  Serial.begin(9600);
  initWiFi();
  dht.begin();
  mqttClient.setServer("192.168.137.1",1883);
  Serial.println("GPS, DHT11, and, Raindrop detector started.");
  pinMode(6, INPUT);
}

void loop() {
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(WIFI_AP);
      // Connect to WPA/WPA2 network
      status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      delay(500);
    }
    Serial.println("Connected to AP");
  }
  if(!mqttClient.connected()){
    reconnect_mqtt();
  }
  delay(3000);
 h = dht.readHumidity();
 t = dht.readTemperature();
  int rainReading = analogRead(A0);
  int range = map(rainReading, rainSensorMin, rainSensorMax, 0, 2);
  
  //For Door(Servo Motor)
  if(rainReading<100){
   myservo.attach(SERVO_PIN);
   myservo.write(0);
   Serial.println("Door Closed");
   delay(2000);
   myservo.detach();
  }
  if(myservo.read()==0 & rainReading>700){
   myservo.attach(SERVO_PIN);
   myservo.write(120);
   Serial.println("Door Open");
   delay(2000);
   myservo.detach();
  }
  if(!isnan(t) || !isnan(h))
  {
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr,200);
     Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(TOPIC);

    if (mqttClient.publish(TOPIC, jsonStr) == true) {
      Serial.println("Success sending message");
      }        
    else {
      Serial.println("Error sending message");
    }
}
  mqttClient.loop();


  #1
/*  dtostrf(t,4,2,temp);
  dtostrf(h,4,2,hum);
  strcat(temp,";");
  strcat(temp,hum);
  mqttClient.publish(TOPIC,temp); */
}

  

void initWiFi(){                              
  ESP8266.begin(9600);
  WiFi.init(&ESP8266);
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true) {
      
    }
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID:");
    Serial.println(WIFI_AP);
    //Connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  }
}

void reconnect_mqtt(){
  while(!mqttClient.connected()){
    Serial.println("Attempting MQTT Connection");
    if(mqttClient.connect("uno")){
      Serial.println("MQTT connection established.");
      Serial.print("Publishing to: ");
      Serial.println(TOPIC);
    }
    else{
      Serial.println(" Try again in 5 seconds");
      delay(5000);
    }
  }
}
String buildJson() {
  String data = "{";
  data+="\n";
  data+= "\"d\": {";
  data+="\n";
  data+="\"Name\": \"Arduino DHT11\",";
  
  data+="\n";
  data+="\"temperature (C)\": ";
  data+=(int)t;
  data+= ",";
  data+="\n";
  data+="\"humidity\": ";
  data+=(int)h;
  data+="\n";
  data+="}";
  data+="\n";
  data+="}";
  return data;
  
}


/* #1
if (!isnan(h) || !isnan(t))
    Serial.print("Temparture: " + String(t) + "°C | " + " Humidity: " + String(h) + " | ");
  else {
    Serial.println("Failed to obtain temparature and humidity data");
  }
  switch (range) {
    case 0:
      Serial.print("Rain Warning : 1");
      break;
    case 1:
      Serial.print("Rain Warning : 0");
      break;
  }
  Serial.println(" | Lat: 22.716191217468406 Lon: 72.44229199663788");
*/
