
//Libraries used: To be added manually on the Arduino IDE!
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


//WiFi credentials: 2.4GHz networks only!
//Avoid long SSIDs and passwords, and use preferably only letters and numbers
 #define SSID "INTRODUCE_YOUR_SSID_HERE"
 #define PASSWORD "INTRODUCE_YOUR_PASSWORD_HERE"


//MQTT credentials from relayr's Developer Dashboard
//Any other MQTT broker can be used, as long as this format is updated
 #define DEVICE_ID "INTRODUCE_YOUR_DEVICE_ID_HERE"
 #define MQTT_USER "INTRODUCE_YOUR_MQTT_USER_HERE"
 #define MQTT_PASSWORD "INTRODUCE_YOUR_MQTT_PASSWORD_HERE"
 #define MQTT_CLIENTID "INTRODUCE_YOUR_MQTT_CLIENT_HERE"
 #define MQTT_TOPIC "INTRODUCE_YOUR_MQTT_TOPIC_HERE"
 #define MQTT_SERVER "mqtt.relayr.io"


//This creates the WiFi client and the pub-sub client instance
WiFiClient espClient;
PubSubClient client(espClient);


//Variable definitions
int i, noise;
long sum, average;


//Function prototypes
void setup_wifi();
void mqtt_connect();
void publish();


//Setup function
void setup()
{

  //Initializing the serial port
  Serial.begin(9600);

  //Initializing the WiFi and connecting to the MQTT broker
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  mqtt_connect();
}




//------------------------------------------------------------------------------------//
// This function connects to the WiFi network, and prints the current IP address      //
//------------------------------------------------------------------------------------//

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}




//------------------------------------------------------------------------------------//
// This function establishes the connection with the MQTT server                      //
//------------------------------------------------------------------------------------//

void mqtt_connect()
{
  Serial.println("");
  Serial.println("Connecting to MQTT server...");
  
  if (client.connect(MQTT_CLIENTID, MQTT_USER, MQTT_PASSWORD))
  {
    Serial.println("Connection successful!");
  }

  else
  {
      Serial.println("Connection failed! Check your credentials or the WiFi network");
      //This reports the error code
      Serial.println("rc = ");
      Serial.print(client.state());
      //And it tries again in 5 seconds
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
  }
}




//------------------------------------------------------------------------------------//
// This is the MAIN LOOP, it's repeated until the end of time! :)                     //
//------------------------------------------------------------------------------------//

void loop()
{
  //This is to calculate average noise values (taking 10000 samples each time)
  sum = 0;
  average = 0;

  for(i=0; i<10000; i++){
    sum += analogRead(A0);
  }

  average = sum/i;

  //Uncomment for debugging
  //Serial.println(average);
  
  //If we're connected, we can send data...
  if (client.connected())
  {
    client.loop();
        
    noise = average;
    publish();    
  }

  //If the connection is lost, then reconnect...
  else
  {
    Serial.println("Retrying...");
    mqtt_connect();
  }      

  //This function prevents the device from crashing
  //since it allows the ESP8266 background functions to be executed
  //(WiFi, TCP/IP stack, etc.)
  yield();
}




//------------------------------------------------------------------------------------//
// Publish function: What we want to send to the cloud                                //
//------------------------------------------------------------------------------------//

void publish()
{    
  //MQTT_MAX_PACKET_SIZE is defined in "PubSubClient.h", it's 128 bytes by default
  //A modified version with 512 bytes it's available here:
  //https://github.com/uberdriven/pubsubclient
  StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> pubJsonBuffer;
  //Create our JsonArray
  JsonArray& root = pubJsonBuffer.createArray();

//-------------------------------------------------
  //JSON object including noise values
  JsonObject& leaf1 = root.createNestedObject();
  leaf1["meaning"] = "noise";
  leaf1["value"] = noise;
//-------------------------------------------------
  
  char message_buff[MQTT_MAX_PACKET_SIZE];
  root.printTo(message_buff, sizeof(message_buff));
  client.publish("/v1/"DEVICE_ID"/data", message_buff);
  Serial.println("Publishing " + String(message_buff));
}




