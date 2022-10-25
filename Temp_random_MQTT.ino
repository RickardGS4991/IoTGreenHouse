//Liberías
#include <WiFi.h>
#include <PubSubClient.h>
#include <esp_wpa2.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// WiFi network Home
const char* ssid = "";
const char* password = "";

//declaramos a nuestro sensor con una varaible
Adafruit_MPU6050 mpu;

// IP Broker
const char* mqtt_broker = "";
const char* clientID = "Sensor_TEMP";

// MQTT Broker
WiFiClient ESP32_;
PubSubClient client(mqtt_broker, 1883, ESP32_);

//Función para conectarse al wifi
void setup_wifi() {
  delay(50);
  // Connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  Serial.print(".");
  }
  if (client.connect(clientID)) {
    Serial.println("");
    Serial.println("Connected to Broker!");
  }
  else {
    Serial.println("Connected to Broker failed...");
  }
  Serial.println("");
  Serial.println("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect_Broker() {
  if (client.connect(clientID)) {
    Serial.println("Reconnected to Broker!");
  }
  else {
    Serial.println("Reconnected to Broker failed...");
  }
    delay(3000);
}

void setup() {
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
 //Obtiene los parametros del giroscopio
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  setup_wifi();
}



void loop() {
    //declaramos nuestras variables para obtener la aceleración y la rotación
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    if (!client.connect(clientID)) {
      reconnect_Broker();
    }
    //Aceleración en X
    float ax = a.acceleration.x;
    static char accelerationx[7];
    dtostrf(ax, 6, 2, accelerationx);
    //Aceleración en Y
    float ay = a.acceleration.y;
    static char accelerationy[7];
    dtostrf(ay, 6, 2, accelerationy);
    //Aceleración en Z
    float az = a.acceleration.z;
    static char accelerationz[7];
    dtostrf(az, 6, 2, accelerationz);

    //Rotación en X
    float rx = g.gyro.x;
    static char girox[7];
    dtostrf(rx, 6, 2, girox);
    //Rotación en Y
    float ry = g.gyro.y;
    static char giroy[7];
    dtostrf(ry, 6, 2, giroy);
    //Rotación en Z
    float rz = g.gyro.z;
    static char giroz[7];
    dtostrf(rz, 6, 2, giroz);

    //Con estas líneas, podemos obtener los valores obtenidos en nuestro giroscopio, mandados a la ESP32 y mandamos a nuestro sistema mediante mosquitto
    client.publish("/ITESM/PUEBLA/accelerationx", accelerationx);
    client.publish("/ITESM/PUEBLA/accelerationy", accelerationy);
    client.publish("/ITESM/PUEBLA/accelerationz", accelerationz);

    
    client.publish("/ITESM/PUEBLA/rotationx", girox);
    client.publish("/ITESM/PUEBLA/rotationy", giroy);
    client.publish("/ITESM/PUEBLA/rotationz", giroz);

    Serial.print("Aceleración en x: ");
    Serial.print(accelerationx);
    Serial.print(" %\t");
    Serial.println("");
    Serial.print("Aceleración en y: ");
    Serial.print(accelerationy);
    Serial.print(" %\t");
    Serial.println("");
    Serial.print("Aceleración en z: ");
    Serial.print(accelerationz);
    Serial.print(" %\t");
    Serial.println("");
    delay(1000);

    Serial.print("Rotación en x: ");
    Serial.print(girox);
    Serial.print(" %\t");
    Serial.println("");
    Serial.print("Rotación en y: ");
    Serial.print(giroy);
    Serial.print(" %\t");
    Serial.println("");
    Serial.print("Rotación en z: ");
    Serial.print(giroz);
    Serial.print(" %\t");
    Serial.println("");
    delay(1000);

}
