import serial
import time
import base64
import binascii

ser = serial.Serial(
    port='COM23', # for windows use COM1
    baudrate=57600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

def lora_ser_cmd(cmd):
    print(cmd)
    cmdrn = cmd + "\r\n"
    ser.write(str.encode(cmdrn))
    print(ser.readline())
    print()

channelId = 0
while 1:
    chStatus = ""
    if(channelId < 6):
        chStatus = ("mac set ch status %d %s" % (channelId, 'on'))
    else:
        chStatus = ("mac set ch status %d %s" % (channelId, 'off'))
    lora_ser_cmd(chStatus)
    channelId += 1
    time.sleep(2)


