import paho.mqtt.client as mqtt
import base64
import json
import csv
import datetime

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+ str(rc))
    client.subscribe("application/1/device/+/rx")

def on_message(client, userdata, msg):
    #print(msg.topic + " " + str(msg.payload))
    d = json.loads(msg.payload)
    print("###############")
    print(d['devEUI'])
    print(d['rxInfo'][0]['rssi'])
    datetime_object = datetime.datetime.now()
    row = [d['devEUI'], d['rxInfo'][0]['rssi'], d['rxInfo'][0]['loRaSNR'], d['txInfo']['frequency'], d['txInfo']['dr'], d['fCnt'], d['fPort'], d['data'], str(datetime_object)]
    for val in row:
        print(val)
    with open('lorawan_data.csv', 'a') as csvFile:
        writer = csv.writer(csvFile)
        writer.writerow(row)
    csvFile.close()
    #print("device : " + base64.b64decode(d['deviceName']))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.0.117", 1883, 60)

client.loop_forever()
