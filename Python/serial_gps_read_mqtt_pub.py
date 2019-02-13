import serial
import paho.mqtt.client as mqtt
import time
import json
import requests

ser = serial.Serial(
    port='/dev/ttyUSB0',  # for windows use COM1
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)


def on_connect(client, userdata, rc):
    print("Connected with result code "+str(rc))
    # client.subscribe("#")


def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set('loraroot', 'root')
# linux : ip addr show
client.connect("192.168.1.102", 1883, 60)
client.loop_start()

while 1:
    # radio_tx 9730 0F0 11021195 0F0 76937967 0F0 1
    #a = ser.readline()
    a = "radio_rx 97300F0110419950F0769389670F01"
    print(a)
    if(a.startswith("radio_rx")):
        ary = a.split('0F0')
        dist = ary[0].replace("radio_rx", "")
        client.publish("loramote/1", "lat : " + ary[1] + " lng : " +
                       ary[2] + " node : " + ary[3] + " d" + dist, qos=0, retain=False)
    time.sleep(5)
