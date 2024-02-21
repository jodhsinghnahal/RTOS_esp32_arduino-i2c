import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(1)
ser.reset_input_buffer()
print("SERIAL OK")

while True:
    if ser.in_waiting > 0:
        time.sleep(0.05)
        line = ser.readline()
        print(line)
