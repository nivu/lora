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

def lora_ser(cmd):
    print(cmd)
    cmdrn = cmd + "\r\n"
    ser.write(str.encode(cmdrn)) 
    print(ser.readline())
    while ser.in_waiting:
        print(ser.readline())
    print()

lora_ser("sys reset")
time.sleep(2)
lora_ser("mac join abp")
time.sleep(2)

# Ref : https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html
channelId = 3

# mac set ch freq 3 867100000
chFreq = ("mac set ch freq %d %d" % (channelId, 867100000))
# lora_ser(chFreq)

# 10% duty cycle => (100/10)-1 = 9
# mac set ch dcycle 3 9
chDtCyl = ("mac set ch dcycle %d %d" % (channelId, 9))
# lora_ser(chDtCyl)
# time.sleep(2)

# mac set ch drrange 3 0 5
chDrRange = ("mac ser ch drrange %d %d %d" % (channelId, 0, 5))
# lora_ser(chDrRange)
# time.sleep(2)

# mac set ch status 3 on
chStatus = ("mac set ch status %d %s" % (channelId, 'on'))
# lora_ser(chStatus)
# time.sleep(3)

fPort = 1
while 1:
    tx = ("mac tx cnf %d %s" % (fPort, str(fPort).encode().hex()))
    lora_ser(tx)
    fPort += 1
    time.sleep(3)


