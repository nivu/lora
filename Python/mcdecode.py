import paho.mqtt.client as mqtt
import base64
import json
import csv
import datetime


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+ str(rc))
    client.subscribe("application/2/device/+/rx")

def on_message(client, userdata, msg):
    #print(msg.topic + " " + str(msg.payload))
    d = json.loads(msg.payload)
    print("###############")
    datetime_object = datetime.datetime.now()
    row = [d['devEUI'], d['rxInfo'][0]['rssi'], d['rxInfo'][0]['loRaSNR'], d['txInfo']['frequency'], d['txInfo']['dr'], d['fCnt'], d['fPort'], base64.b64decode(str(d['data'])).decode('utf-8'), str(datetime_object)]
    head = ['devEUI    ', 'rssi      ', 'loraSNR   ', 'freq      ', 'dr        ', 'fCnt      ', 'fPort     ', 'data      ', 'datetime  ']
    for i in range(9):
        print(head[i], " :: ", row[i])
    print(" ")
    with open('app2_data.csv', 'a') as csvFile:
        writer = csv.writer(csvFile)
        writer.writerow(row)
    csvFile.close()

client = mqtt.Client(client_id="mcdecode", clean_session=True, userdata=None)

client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.43.158", 1883, 60)
#client.connect("192.168.0.120", 1883, 60)

client.loop_forever()
