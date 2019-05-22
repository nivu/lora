import paho.mqtt.client as mqtt
import base64
import json
import csv
import datetime


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+ str(rc))
    client.subscribe("application/1/device/0004a30b001febcf/rx")

def on_message(client, userdata, msg):
    #print(msg.topic + " " + str(msg.payload))
    d = json.loads(msg.payload)
    print("###############")
    datetime_object = datetime.datetime.now()
    row = [d['devEUI'], d['rxInfo'][0]['rssi'], d['rxInfo'][0]['loRaSNR'], d['txInfo']['frequency'], d['txInfo']['dr'], d['fCnt'], d['fPort'], base64.b64decode(str(d['data'])).decode('utf-8'), str(datetime_object), "appartment"]
    head = ['devEUI    ', 'rssi      ', 'loraSNR   ', 'freq      ', 'dr        ', 'fCnt      ', 'fPort     ', 'data      ', 'datetime  ', 'location  ']
    for i in range(9):
        print(head[i], " :: ", row[i])
    print(" ")
    with open('loc_data_23_04_cp.csv', 'a') as csvFile:
        writer = csv.writer(csvFile)
        writer.writerow(row)
    csvFile.close()

client = mqtt.Client(client_id="loc_write", clean_session=True, userdata=None)

client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.42.158", 1883, 60)
#client.connect("192.168.0.120", 1883, 60)

client.loop_forever()
