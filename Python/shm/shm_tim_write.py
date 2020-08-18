import paho.mqtt.client as mqtt
import base64
import json
import csv
import datetime

counter = 0

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+ str(rc))
    client.subscribe("application/2/device/0004a30b0020096f/rx")

def on_message(client, userdata, msg):
    #print(msg.topic + " " + str(msg.payload))
    my_json = msg.payload.decode('utf8').replace("'", '"')
    d = json.loads(my_json)
    print("###############")
    datetime_object = datetime.datetime.now()
    rxInfo = d['rxInfo'][0]
    rxInfo_time = ""
    if 'time' in rxInfo:
        rxInfo_time = rxInfo['time']
    else:
        rxInfo_time = ""
    print(rxInfo)
    txInfo = d['txInfo']
    print(txInfo)
    row = [d['devEUI'], rxInfo_time, rxInfo['rssi'], rxInfo['loRaSNR'], str(rxInfo['location']), txInfo['frequency'], txInfo['dr'], d['fCnt'], d['fPort'], base64.b64decode(str(d['data'])).decode('utf-8'), str(datetime_object), "pitslab"]
    head = ['devEUI    ','time      ', 'rssi      ', 'loraSNR   ', 'location  ', 'freq      ', 'dr        ', 'fCnt      ', 'fPort     ', 'data      ', 'timestamp  ', 'location  ']
    for i in range(len(head)):
        print("i ", i, " :: ", head[i], " :: ", row[i])
    global counter
    print("counter", counter)
    counter +=1
    print(" end **********")
    with open('shm_tim_home.csv', 'a') as csvFile:
        writer = csv.writer(csvFile)
        writer.writerow(row)
    csvFile.close()

client = mqtt.Client(client_id="loc_write", clean_session=True, userdata=None)

client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.0.111", 1883, 60)
#client.connect("192.168.0.120", 1883, 60)

client.loop_forever()
