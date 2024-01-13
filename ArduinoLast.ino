#include <Servo.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
const int pinServo = D2;
const int pinPhotoresistor = A0;
const int seuilMontee = 85;
const int seuilDescente = 2000;
const int resistanceFixe = 10000;
const int angleMontee = 50;
const int angleDescente = 140;
const int angleNeutre = 100;
const int angleCalibrageMontee = 135;
const int angleCalibrageDescente = 90;
int state = 0;

Servo monServo;

const char *ssid = "iPhone";
const char *password = "123azert";
const char *mqttServer = "test.mosquitto.org"; // Replace with your MQTT broker address
const int mqttPort = 1883;
const char *mqttUsername = ""; 
const char *mqttPassword = ""; 
const char *mqttClientId = "esp8266-client";
const char *mqttTopic = "MOTORSERVO";

WiFiClient espClient;
PubSubClient client(espClient);
//
void publishToMQTT(const char *message)
{
    // Publish data to MQTT topic
    char topic[50];
    snprintf(topic, sizeof(topic), "%s", mqttTopic);
    client.publish(topic, message);
}
// function to reconnect to mqtt broker
void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.println("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(mqttClientId, mqttUsername, mqttPassword))
        {
            Serial.println("Connected to MQTT broker");
            // Subscribe to the topic after reconnection
            client.subscribe(mqttTopic);
        }
        else
        {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup()
{
    monServo.attach(pinServo);
    Serial.begin(9600);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Connect to MQTT broker
    client.setServer(mqttServer, mqttPort);
    while (!client.connected())
    {
        if (client.connect(mqttClientId, mqttUsername, mqttPassword))
        {
            Serial.println("Connected to MQTT broker");
        }
        else
        {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying...");
            delay(1000);
        }
    }
}

void loop()
{
    int valeurLumiere = analogRead(pinPhotoresistor);
    float resistancePhotoresistor = (resistanceFixe * (1023.0 - valeurLumiere)) / valeurLumiere;

    Serial.print("Resistance de la photoresistance : ");
    Serial.println(resistancePhotoresistor);
    delay(10000);
    if (resistancePhotoresistor < seuilMontee)
    {
        monServo.write(angleMontee);
        state = 1;
        publishToMQTT("montee");
    }
    else if (resistancePhotoresistor > seuilMontee && resistancePhotoresistor < seuilDescente && state == 1)
    {
        monServo.write(angleCalibrageMontee);
        state = 0;
        publishToMQTT("calibrage_montee");
        publishToMQTT(String(angleCalibrageMontee).c_str() );
    }
    else if (resistancePhotoresistor > seuilMontee && resistancePhotoresistor < seuilDescente && state == 0)
    {
        monServo.write(angleNeutre);
        state = 0;
        publishToMQTT("neutre");
         publishToMQTT(String(angleNeutre).c_str() );
    }
    else if (resistancePhotoresistor > seuilDescente)
    {
        monServo.write(angleDescente);
        state = 2;
       
        publishToMQTT("descente="  );
        publishToMQTT(String(angleDescente).c_str() );

    }
    else if (resistancePhotoresistor > seuilMontee && resistancePhotoresistor < seuilDescente && state == 2)
    {
        monServo.write(angleNeutre);
        state = 0;
        publishToMQTT("calibrage_descente");
    }

    delay(500);
    // Maintain MQTT connection
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}
