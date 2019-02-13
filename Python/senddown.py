import base64
import random
import json


def sendDownLink(data):
    print(data)
    a, b = data.split(',')
    print(b)
    if int(b) < 10:
        dlNode = 'application/1/node/0004A30B00200D67/tx'
        # data = base64.b64encode(dataArray[1])
        randomNumber = random.randint(1, 101)
        send = '{"reference":"1234nivu","confirmed" : true, "dlPort": 10, "data": 1}'
        #this.unsafePublish(dlNode, json.loads((send)))
        jsondata = json.load(send)
        print(str(jsondata.data))


sendDownLink('Waterlevel,6')
