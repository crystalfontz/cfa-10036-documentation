import json,os,datetime,time

fridgeTemp = []
freezerTemp = []
slaves = []
times = []

def LoadSlaves():
	slavesFile = open('/sys/devices/w1_bus_master1/w1_master_slaves')

	i = 0
	for slave in slavesFile:
		print("Slave " + str(i) + ": "+ slave[0:-1])
		slaves.append(slave[0:-1])
		i += 1
	slavesFile.close()

def _GetTemps():
	slaveTemps = []
	global slaves
	for slave in slaves:
		slaveFile = open('/sys/devices/w1_bus_master1/'+slave+'/w1_slave')	
		slaveFile.readline()
		slaveData = slaveFile.readline()
		slaveTempC = int(slaveData[slaveData.find('t=')+2:-1])/1000
		slaveTempF = (slaveTempC * 9 / 5) + 32
		slaveTemps.append(slaveTempF)
	slaveFile.close()
	return slaveTemps

def GetTemps():
	temps = _GetTemps()
	if len(fridgeTemp)>10000:
		fridgeTemp.pop(0)
	if len(freezerTemp)>10000:
		freezerTemp.pop(0)
	if len(times)>10000:
				times.pop(0)
				
	freezerTemp.append(temps[0])
	fridgeTemp.append(temps[1])
	
	times.append(datetime.datetime.now().strftime('%b-%d-%I%M%p-%G'))

def DumpData():
	fridgeLogFile = open('fridge_log.json','w')
	freezerLogFile = open('freezer_log.json','w')
	timeLogFile = open('time_log.json','w')

	fridgeLogFile.write("var fridgeData = " + json.dumps(fridgeTemp))
	freezerLogFile.write("var freezerData = " + json.dumps(freezerTemp))
	timeLogFile.write("var timeData = " + json.dumps(times))

	fridgeLogFile.close()
	freezerLogFile.close()
	timeLogFile.close()

def LoadData():
	try:
		fridgeLogFile = open('fridge_log.json')
		freezerLogFile = open('freezer_log.json')
		timeLogFile = open('time_log.json')

		fridgeLog = fridgeLogFile.read()
		freezerLog = freezerLogFile.read()
		timeLog  = timeLogFile.read()

		global fridgeTemp
		global freezerTemp
		global times

		freezerTemp = json.loads(freezerLog[freezerLog.find(' = ')+3:len(freezerLog)])
		fridgeTemp = json.loads(fridgeLog[fridgeLog.find(' = ')+3:len(fridgeLog)])
		times = json.loads(timeLog[timeLog.find(' = ')+3:len(timeLog)])

		fridgeLogFile.close()
		freezerLogFile.close()
		timeLogFile.close()
	except IOError:
		print("First run, can't load nonexisting data")

def Upload():
	os.system("""ftpput --verbose --user=######## --password=######## 
		--port=21 ########################### /public_html/fridge_log.json fridge_log.json;""")
	os.system("""ftpput --verbose --user=######## --password=########
		--port=21 ########################### /public_html/freezer_log.json freezer_log.json;""")
	os.system("""ftpput --verbose --user=######## --password=########
		--port=21 ########################### /public_html/time_log.json time_log.json;""")

LoadSlaves()
LoadData()
while True:
	i=60
	while i > 0:
		GetTemps()
		print(str(i) + " seconds left till next upload")
		i -= 1
	DumpData()
	print("Saved")
	Upload()
	print(str(len(times)) + "records are recorded")

