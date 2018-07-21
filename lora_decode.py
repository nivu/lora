import paho.mqtt.client as mqtt
import base64
import random
import json


def stringToBase64(s):
    return base64.b64encode(s.encode('utf-8'))


def sendDownLink(data):
    print(data)
    a, b = data.split(',')
    val = b[0: len(b)-1]
    print(val)
    if int(val) < 10:
        dlNode = 'application/1/node/0004A30B00200D67/tx'
        # data = base64.b64encode(dataArray[1])
        randomNumber = random.randint(1, 101)
        senddata = {}
        senddata['reference'] = '1234nivu' + str(randomNumber)
        senddata['confirmed'] = True
        senddata['fPort'] = randomNumber
        senddata['data'] = base64.b64encode('1')
        # str(stringToBase64(str(1)))
        # 'MQ=='

        json_data = json.dumps(senddata)
        status = client.publish(dlNode, json_data)
        print(status)
        # print(str(jsondata.data))


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("application/1/device/0004a30b001f9f3c/rx")


def on_message(client, userdata, msg):
    print(msg.topic)
    d = json.loads(msg.payload)
    # print(d)
    ded = str(base64.b64decode(str(d['data'])))
    print(ded)
    sendDownLink(str(ded))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.1.104", 1883, 60)

client.loop_forever()
