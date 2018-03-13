import serial
import time
ser = serial.Serial(
    port='/dev/ttyUSB0', # for windows use COM1
    baudrate=57600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

while 1:
    ser.write('sys reset\r\n') 
    a = ser.readline()
    print(a)
    time.sleep(1)


