import serial
ser = serial.Serial(
    port='/dev/ttyUSB2', # for windows use COM1
    baudrate=57600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)
f = open('1sec.txt','a')

while 1:
    a = ser.readline()
    if(a.startswith("radio_rx")):
        if(int(a[10]) == 0):
            nodeId = str(a[11])
            data = str(a[12]) + str(a[13])
        elif int(a[10]) != 0:
            nodeId = str(a[10])
            data = str(a[11])
        print("nodeId : " + nodeId + " data : " + data)         # check which port was really used
        f.write(nodeId + ',' + data + '\n')
    if(a.startswith("radio_err")):
        f.write('0,0\n')

