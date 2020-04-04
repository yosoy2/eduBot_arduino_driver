import serial, time

print("---START---")
arduino = serial.Serial("/dev/ttyACM1", 250000)
time.sleep(2)
#rawString = arduino.readline()
#print(rawString)
arduino.write(b'0')
arduino.close()
