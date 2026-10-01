import serial
import time

BAUDRATE = 115200
port='/dev/ttyUSB0'

limit_open=200
limit_close=10

debug=False

if not debug:
    ser = serial.Serial(port=port,baudrate=BAUDRATE,timeout=2)
    time.sleep(2)

    ser.write(b'm')
    status=ser.readline().decode().strip()
    ser.close()
else:
    status='5 250'

#print(status)

dist=status.split()

#if 'E' in status:
#    raise ValueError(f'Wrong value from sensor: "{status}"')

status=''

if dist[0]=='E':
    status+='error'
else:
    left=float(dist[0])

    if left>limit_open: status+='opened'
    elif left<limit_close: status+='closed'
    else: status+='error'

status+=' '

if dist[1]=='E':
    status+='error'
else:
    right=float(dist[1])

    if right>limit_open: status+='opened'
    elif right<limit_close: status+='closed'
    else: status+='error'

print(status)


