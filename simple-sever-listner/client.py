
import socket
import time
import sys


message = sys.argv[1]
sockobj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sockobj.connect(('127.0.0.1',8003 ))
i = 0
while i<3:
    sockobj.send((message+" messageid="+str(i)).encode())
    time.sleep(3)
    i +=1

sockobj.close()