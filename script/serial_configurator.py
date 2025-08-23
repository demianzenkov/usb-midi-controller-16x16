# Script for connecting to device via Serial Port and send an image as a byte array
import serial
import time
# Establish a serial connection with the device
ser = serial.Serial('/dev/cu.usbmodem3695347034303', 576000)
# Iterate over the chunks
for i in range(0, 16):
    
    # message = '/set/value/' + str(i) + '/32' + '\n'
    # ser.write(message.encode())
    # time.sleep(0.00005)
    
    # message = '/set/color/bg/' + str(i) + '/ff0000' + '\n'
    # ser.write(message.encode())
    # time.sleep(0.00005)
    
    # message = '/set/color/border/' + str(i) + '/ff0000' + '\n'
    # ser.write(message.encode())
    # time.sleep(0.00005)
    
    # message = '/set/color/text/' + str(i) + '/00ff00' + '\n'
    # ser.write(message.encode())
    # time.sleep(0.00005)
    
    message = '/set/color/bar/' + str(i) + '/ff0000' + '\n'
    ser.write(message.encode())
    time.sleep(0.00005)
    
ser.close()

print('parameters sent')


