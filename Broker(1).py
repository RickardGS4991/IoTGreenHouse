import paho.mqtt.client as mqtt
from urllib import parse, request
import time
import math
import requests

//Se ejecuta cada vez que el clinete se conecta o se reconecta al broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("/ITESM/PUEBLA/accelerationx")
    client.subscribe("/ITESM/PUEBLA/accelerationy")
    client.subscribe("/ITESM/PUEBLA/accelerationz")
    client.subscribe("/ITESM/PUEBLA/rotationx")
    client.subscribe("/ITESM/PUEBLA/rotationy")
    client.subscribe("/ITESM/PUEBLA/rotationz")

//Esta función sirve para procesar mensajes que se publican en un tópico suscrito
def on_message(client, userdata, msg):
    if msg.topic == "/ITESM/PUEBLA/accelerationx":
        str0 = str(msg.payload)
        str1=str0[3:7]
        global val1
        val1=float(str1)
        print("Received message: " + msg.topic + "  "  + str1 + "C"  )

    if msg.topic == "/ITESM/PUEBLA/accelerationy":
        str2 = str(msg.payload)
        str3=str2[3:7]
        global val2
        val2=float(str3)
        print("Received message: " + msg.topic + "  "  + str3 + "C"  )

    if msg.topic == "/ITESM/PUEBLA/accelerationz":
        str4 = str(msg.payload)
        str5=str4[3:7]
        global val3
        val3=float(str5)
        print("Received message: " + msg.topic + "  "  + str5 + "C"  )

    if msg.topic == "/ITESM/PUEBLA/rotationx":
        str6 = str(msg.payload)
        str7=str6[3:7]
        global val4
        val4=float(str7)
        print("Received message: " + msg.topic + "  "  + str7 + "%" )

    if msg.topic == "/ITESM/PUEBLA/rotationy":
        str8 = str(msg.payload)
        str9=str8[3:7]
        global val5
        val5=float(str9)
        print("Received message: " + msg.topic + "  "  + str9 + "%" )

    if msg.topic == "/ITESM/PUEBLA/rotationz":
        str10 = str(msg.payload)
        str11=str10[3:7]
        global val6
        val6=float(str11)
        print("Received message: " + msg.topic + "  "  + str11 + "%" )

mqttc=mqtt.Client()
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.connect("localhost",1883,60)
mqttc.loop_start()
