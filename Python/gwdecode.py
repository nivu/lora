import paho.mqtt.client as mqtt
import base64
import json
import csv
import datetime
from pprint import pprint


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+ str(rc))
    client.subscribe("gateway/+/rx")

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))
    # d = json.loads(msg.payload)
    # datetime_object = datetime.datetime.now()
    # pprint(d.json())
    # for val in row:
    #     print(val)
    # with open('lorawan_data.csv', 'a') as csvFile:
    #     writer = csv.writer(csvFile)
    #     writer.writerow(row)
    # csvFile.close()
    #print("device : " + base64.b64decode(d['deviceName']))

client = mqtt.Client(client_id="gwrx", clean_session=True, userdata=None)

client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.43.158", 1883, 60)
#client.connect("192.168.0.120", 1883, 60)

client.loop_forever()
