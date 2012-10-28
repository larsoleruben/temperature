#! /usr/bin/python
#*************************************************************************************************************
#l.christoffersen@rubenc.dk disclaimer bla bla bla don't use for control of neuclar reactors
#*************************************************************************************************************
import serial
from cosm import Cosm
FEED = "68554"
API_KEY = 'Din Cosm n√∏g√le her'

cosm = Cosm( FEED, API_KEY )

ser = serial.Serial('/dev/ttyACM0', 9600)

def is_number_ok( nval ):
	try:
		if( float(nval) < 50 and float(nval) > -50 ):
			return True
		else:
			return False
	except ValueError:
		return False

while 1:
	a = ser.readline().rstrip()
	if( is_number_ok(a) ):
		#print a
		info = [
			("10", a )
		]
		try:
			cosm.put( info )
		except Exception, ex:
			print "Error", str(ex)

#fin
