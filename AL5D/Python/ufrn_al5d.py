#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jun 20 15:24:07 2018


@author: jean
"""
import time
import serial
import os

## $ sudo apt-get install python-serial

SERIAL_PORT='/dev/ttyS0' #Serial
BAUD_RATE='115200'       #Set Baud rates to 115200
TIMEOUT='1'              #Timeout after opening
PARITY='N'               # No parity
STOPBITS='1'             
BYTESIZE='8'
XONXOFF = False
RTSCTS = False

#estabelece serial ttyS0

os.system('sudo chmod 777 /dev/ttyS0')
os.system('sudo rm /dev/ttyS0')  
os.system('sudo ln -s /dev/ttyUSB0 /dev/ttyS0')      

#configura porta
#serial_port = serial.Serial('/dev/ttyS0',115200)
serial_port = serial.Serial(SERIAL_PORT, 
int(BAUD_RATE), 
timeout=int(TIMEOUT), 
bytesize=int(BYTESIZE), 
stopbits=int(STOPBITS), 
parity=PARITY,
xonxoff = XONXOFF,
rtscts= RTSCTS)


#abre porta
if not serial_port.is_open:
    serial_port.open()

print ('\nObtendo informacoes sobre a comunicacao serial\n')
 # Alem das opcoes rtscts=BOOL, xonxoff=BOOL, e dsrdtr=BOOL
time.sleep(1.8) # Entre 1.5s a 2s

#testa porta
print ('\nStatus Porta: %s ' % (serial_port.isOpen()))
print ('Device conectado: %s ' % (serial_port.name))
print ('Dump da configuracao:\n %s ' % (serial_port))
print('\n###############################################\n')
print('HOME POSITION... \n')
time.sleep(1.5) # Entre 1.5s a 2s
serial_port.write('#0P1500#1P1500#2P1500#3P1500#4P1500T1500\r')
time.sleep(1.5)
serial_port.write('#0P1000T200\r')
      
#fecha porta      
serial_port.close() 

