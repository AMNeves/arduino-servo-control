import serial
import time

arduinoData = serial.Serial('com4', 9600)
switch = True

def send90():
    arduinoData.write(b'a190\n')


def send0():
    arduinoData.write(b'a000\n')


time.sleep(5)

while True:
    if switch:
        send90()
        switch = False
    else:
        send0()
        switch = True
    time.sleep(1)




print("done")