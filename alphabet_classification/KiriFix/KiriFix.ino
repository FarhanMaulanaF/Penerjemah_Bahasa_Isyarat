// Include the necessary libraries
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <movingAvg.h>
#include <WiFi.h>
#include <PubSubClient.h>

Adafruit_MPU6050 mpu;

// Define the pins for the flex sensors
const int flexSensor1Pin = 33; // D13
const int flexSensor2Pin = 32; // D12
const int flexSensor3Pin = 35; // D14
const int flexSensor4Pin = 39; // D27
const int flexSensor5Pin = 34; // D26 

// use 10 data points for the moving average
movingAvg mAvgFlex1(10);
movingAvg mAvgFlex2(10); 
movingAvg mAvgFlex3(10); 
movingAvg mAvgFlex4(10); 
movingAvg mAvgFlex5(10);
movingAvg mAvgAccX(10);
movingAvg mAvgAccY(10);
movingAvg mAvgAccZ(10);

// WiFi
const char *ssid = "Hotspot"; // Enter your WiFi name
const char *password = "minimum1234";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.43.34";
const char *topic = "/sarung/kiri";
const char *mqtt_username = "A-13";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Set the flex sensor pins as INPUT
  pinMode(flexSensor1Pin, INPUT);
  pinMode(flexSensor2Pin, INPUT);
  pinMode(flexSensor3Pin, INPUT);
  pinMode(flexSensor4Pin, INPUT);
  pinMode(flexSensor5Pin, INPUT);

  // Moving Average
  mAvgFlex1.begin();
  mAvgFlex2.begin();
  mAvgFlex3.begin();
  mAvgFlex4.begin();
  mAvgFlex5.begin();
  mAvgAccX.begin();
  mAvgAccY.begin();
  mAvgAccZ.begin();
  
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");


  
  // connecting to an MQTT broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Public EMQX MQTT broker connected");
      } else {
          Serial.print("Failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }

  
}

void callback(char *topic, byte *payload, unsigned int length) {
  // Handle incoming MQTT messages here
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g,&temp);

  long flexSensor1Sum = 0;
  long flexSensor2Sum = 0;
  long flexSensor3Sum = 0;
  long flexSensor4Sum = 0;
  long flexSensor5Sum = 0;
  float AccXSum = 0;
  float AccYSum = 0;
  float AccZSum = 0;

  int count = 0;
  unsigned long startTime = millis();
  while (millis() - startTime < 750) {
    // Read the analog values from the flex sensors
    int flexSensor1Value = analogRead(flexSensor1Pin);
    int flexSensor2Value = analogRead(flexSensor2Pin);
    int flexSensor3Value = analogRead(flexSensor3Pin);
    int flexSensor4Value = analogRead(flexSensor4Pin);
    int flexSensor5Value = analogRead(flexSensor5Pin);
    float AccXVal = a.acceleration.x;
    float AccYVal = a.acceleration.y;
    float AccZVal = a.acceleration.z;

    int FlexAvg1 = mAvgFlex1.reading(flexSensor1Value);
    int FlexAvg2 = mAvgFlex2.reading(flexSensor2Value);
    int FlexAvg3 = mAvgFlex3.reading(flexSensor3Value);
    int FlexAvg4 = mAvgFlex4.reading(flexSensor4Value);
    int FlexAvg5 = mAvgFlex5.reading(flexSensor5Value);
    float AccXAvg = mAvgAccX.reading(AccXVal);
    float AccYAvg = mAvgAccY.reading(AccYVal);
    float AccZAvg = mAvgAccZ.reading(AccZVal);


    // Add the values to the sums
    flexSensor1Sum += FlexAvg1;
    flexSensor2Sum += FlexAvg2;
    flexSensor3Sum += FlexAvg3;
    flexSensor4Sum += FlexAvg4;
    flexSensor5Sum += FlexAvg5;
    AccXSum += AccXAvg;
    AccYSum += AccYAvg;
    AccZSum += AccZAvg;

    // Increment the count
    count++;

    // Add a delay to prevent too rapid readings
    delay(10); // Adjust the delay time as needed
  }

  int Flex1 = flexSensor1Sum / count;
  int Flex2 = flexSensor2Sum / count;
  int Flex3 = flexSensor3Sum / count;
  int Flex4 = flexSensor4Sum / count;
  int Flex5 = flexSensor5Sum / count;
  float AccX = AccXSum / count;
  float AccY = AccYSum / count;
  float AccZ = AccZSum / count;

  char charToOutput = '-'; // Default value if no condition is met
  if (
        Flex1 > 2500 &&
        Flex2 > 2400 && 
        Flex3 < 2100 &&
        Flex4 < 2450 &&
        Flex5 < 2450 && 
        //AccX < 7 &&
        AccY > -1) {
      charToOutput = 'A';
    } else if(
        Flex1 > 2500 &&
        Flex2 > 2500 && 
        Flex3 < 2100 &&
        Flex4 < 2450 &&
        Flex5 < 2450 &&
        //AccX > 5.2 && 
        AccY < -1 &&
        AccZ < 7) {
      charToOutput = 'W';
    } else if (
        Flex1 < 2400 &&
        Flex2 > 2250 &&
        Flex3 < 2050 && 
        Flex4 < 2350 && 
        Flex5 < 2300 &&
        AccX > 7) {
      charToOutput = 'I';
    } else if (
        Flex1 < 2400 &&
        Flex2 > 2250 &&
        Flex3 < 2050 && 
        Flex4 < 2250 && 
        Flex5 < 2300 &&
        AccX < 7) {
      charToOutput = 'X';
    } else if (
        Flex1 > 2300 && Flex1 < 2650 &&
        Flex2 > 2050 && Flex2 < 2400 &&
        Flex3 < 2050 &&
        Flex4 < 2250 &&
        Flex5 < 2300) {
      charToOutput = 'S';
    } else if (
        Flex1 < 2600 &&
        Flex2 < 2250 &&
        Flex3 > 2350 && 
        Flex4 > 2450 && 
        Flex5 > 2450) {
      charToOutput = 'Q';
    } else if (
        Flex1 < 2450 &&
        Flex2 < 2000 &&
        Flex3 < 2100 && 
        Flex4 < 2300 && 
        Flex5 < 2350) {
      charToOutput = 'G'; 
    } else if (
        Flex1 > 2300 &&
        Flex2 > 2300 &&
        Flex3 > 2200 && 
        Flex4 > 2300 && 
        Flex5 > 2300 &&
        AccX > 3) {
      charToOutput = 'M'; 
    } else if (
        Flex1 > 2300 &&
        Flex2 > 2350 &&
        Flex3 > 2350 && 
        Flex4 > 2300 && 
        Flex5 > 2350 &&
        AccX < -5) {
      charToOutput = '0'; 
    }
   
  // Output the selected character
  Serial.print(charToOutput);
  Serial.print(" ");
  // Print the sensor values to the Serial Monitor
  Serial.print(Flex1);
  Serial.print(" ");
  Serial.print(Flex2);
  Serial.print(" ");
  Serial.print(Flex3);
  Serial.print(" ");
  Serial.print(Flex4);
  Serial.print(" ");
  Serial.print(Flex5);
  Serial.print(" ");
  Serial.print(AccX);
  Serial.print(" ");
  Serial.print(AccY);
  Serial.print(" ");
  Serial.println(AccZ);
  //Serial.println(" ");
  //Serial.print(g.gyro.x);
  //Serial.print(" ");
  //Serial.print(g.gyro.y);

  String payload = String(charToOutput); // + "," + String(Flex1) + "," + String(Flex2) + "," + String(Flex3) + "," + String(Flex4) + "," + String(Flex5) + "," + String(AccX) + "," + String(AccY) + "," + String(AccZ);
  client.publish(topic, payload.c_str());

  // Wait before publishing again (adjust this delay as needed)
  delay(0);

  // Handle MQTT messages
  client.loop();
}
