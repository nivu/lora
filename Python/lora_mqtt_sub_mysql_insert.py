import mysql.connector
import paho.mqtt.client as mqtt
import time
import json
import requests

# mydb = mysql.connector.connect(
#    host="localhost",
#    user="root",
#    passwd="",
#    database="lora"
# )


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("application/1/device/+/rx")


def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    d = json.loads(msg.payload)


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# linux : ip addr show
client.connect("192.168.0.113", 1883, 60)
client.loop_forever()

#mycursor = mydb.cursor()

#sql = "INSERT INTO test (node_id) VALUES (1)"
# mycursor.execute(sql)

# mydb.commit()

#print(mycursor.rowcount, "record inserted.")
