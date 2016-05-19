#!/usr/bin/python
#==============================================================================
#title           :akeru.py
#description     :Swiss kniffe for Foquinha Raspberry shield.
#author          :Sn00tlab
#license         :CC BY-NC-SA 4.0
#date            :20161505
#version         :1.0
#usage           :python akeru.py
#notes           :
#==============================================================================

import serial
import sys, getopt

### FUNCTIONS ###

# Usages
def usages():
	print 'Usage: akeru.py [COMMANDS(S)] (You can use many commands)'
	print 'Commands list:'
	print '\t -q,--quiet \t\t Quiet mode.'
	print '\t -D,--device \t\t Serial device (default=/dev/ttyAMA0).'
	print '\t -m,--message=msg \t Send a message.'
	print '\t -v,--supply-voltage \t Return supply voltage.'
	print '\t -t,--temperature \t Return temperature.'
	print '\t -i,--identity \t\t Return modem ID.'
	print '\t -H,--hardware-version \t Return hardware version.'
	print '\t -S,--software-version \t Return software version.'
	print '\t -h,--help \t\t This help.'
	print 'Examples:'
	print '\tReturn supply voltage, temperature et software version with :'
	print '\t\t./akeru.py -v -t -S'
	print '\tSend an message (max 12 bytes) in hexa :'
	print '\t\t./akeru.py -m "65 66 68" '

def my_print(string) :
	if not quiet :
		print(format(string))

# Low level
def transfert(send, true, false) :
	# Add suffix
	send += "\r"
	true += "\r\n"
	false += "\r\n"
	# Send data
	serialFd.write(send);
	# Wait response
	data = ''
	first = 1
	while true not in data and false not in data :
		c = serialFd.read(1)
		if c == '' :
			return '';
		elif first == 1 :	# remove useless \r\n before reply
			if c != "\r" and c != "\n" :
				first = 0
				data = c
		else :
			data += c

	if false in data :
		data = ''
	else :
		data = data.replace("\r\n\r\n","\r\n")

	return data

# Commands
def sendMsg(msg) :
	my_print('Sending message...')
	if transfert("AT$SS={0}\r".format(msg), 'OK', 'ERROR') :
		my_print('OK!')
		return 0
	else:
		sys.stderr.write('Sending failed!')
		return 1

def returnID() :
	my_print('Request ID...')
	data = transfert('ATI7', 'OK', 'ERROR')
	if data == '' :
		sys.stderr.write('ERROR: No reply!')
		return 1
	else :
		lists = data.split("\r\n");
		print '{}'.format(lists.pop(0))
		print '{}'.format(lists.pop(0))
		return 0

def returnHardwareVersion() :
	my_print('Request firmware version...')
	data = transfert('ATI11', 'OK', 'ERROR')
	if data == '' :
		sys.stderr.write('ERROR: No reply!')
		return 1
	else :
		lists = data.split("\r\n");
		print '{}'.format(lists.pop(0))
		return 0

def returnFirmwareVersion() :
	my_print('Request firmware version...')
	data = transfert('ATI13', 'OK', 'ERROR')
	if data == '' :
		sys.stderr.write('ERROR: No reply!')
		return 1
	else :
		lists = data.split("\r\n");
		print '{}'.format(lists.pop(0))
		return 0

def returnTemperature() :
	my_print('Request temperature...')
	data = transfert('ATI26', 'OK', 'ERROR')
	if data == '' :
		sys.stderr.write('ERROR: No reply!')
		return 1
	else :
		lists = data.split("\r\n");
		print '{}C'.format(lists.pop(0))
		return 0

def returnSupplyVoltage() :
	my_print('Request supply voltage...')
	data = transfert('ATI27', 'OK', 'ERROR')
	if data == '' :
		sys.stderr.write('ERROR: No reply!')
		return 1
	else :
		lists = data.split("\r\n");
		print '{}V'.format(lists.pop(0))
		return 0

### Main ###
ret = 2
quiet = 0

# Parsing args
device = '/dev/ttyAMA0'
message = ''
commands = []
try:
	opts, args = getopt.getopt(sys.argv[1:],"hD:m:tvtiHSq", \
		["device", "message", "supply-voltage", "temperature", "identity", \
		"hardware-version", "software-version", "quiet", "help"])
except getopt.GetoptError:
	usages()
	sys.exit(2)
for opt, arg in opts:
	if opt in ("-h", "--help"):
		usages()
		sys.exit()
	elif opt in ("-q", "--quiet"):
		quiet = 1
	elif opt in ("-D", "--device"):
		device = arg
	elif opt in ("-m", "--message"):
		message = arg
		commands.append('MSG')
	elif opt in ("-v", "--supply-voltage"):
		commands.append('SVOLT')
	elif opt in ("-t", "--temperature"):
		commands.append('TEMP')
	elif opt in ("-i", "--identity"):
		commands.append('ID')
	elif opt in ("-H", "--hardware-version"):
		commands.append('HWVERSION')
	elif opt in ("-S", "--software-version"):
		commands.append('SWVERSION')

my_print('akeru.py V1.0')

# No commands? exit
if len(commands) == 0 :
	usages()
	sys.exit(1)

# Initialisation
try:
	serialFd = serial.Serial(
			port=device,
			timeout=10,
			baudrate=9600,
			bytesize=serial.EIGHTBITS,
			parity=serial.PARITY_NONE,
			stopbits=serial.STOPBITS_ONE,
			xonxoff=False,
			rtscts=False
		)
	#serialFd.open()
except serial.SerialException as e:
	sys.stderr.write("Open device {} failed :\n\t{}\n".format(device, e))
	sys.exit(1)

# Flush serial buffer
serialFd.reset_input_buffer()
serialFd.reset_output_buffer()

# Test modem presence & echo disabling
if not transfert('ATE0', 'OK', 'ERROR') :
	sys.stderr.write(' ERROR: No reply')
	serialFd.close()
	sys.exit(1)

# Excute commands
for cmd in commands :
	if cmd == 'MSG':
		if message == '' :
			sys.stderr.write('ERROR: message is void!')
			ret = 1
		else :
			ret = sendMsg(message)
	elif cmd == 'SVOLT':
		ret = returnSupplyVoltage()
	elif cmd == 'TEMP' :
		ret = returnTemperature()
	elif cmd == 'HWVERSION' :
		ret = returnHardwareVersion()
	elif cmd == 'SWVERSION' :
		ret = returnFirmwareVersion()
	elif cmd == 'ID' :
		ret = returnID()
	else :
		sys.stderr.write('Unknown command')
	if ret != 0 :
		break;

# Close device
serialFd.close()

sys.exit(ret)
