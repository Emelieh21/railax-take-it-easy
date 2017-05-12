import requests
import json
import time
import datetime
import urllib2

#def passed_time(initial_time):
#	return datetime.timedelta.total_seconds(datetime.datetime.now() - initial_time) * 1000

headers = {'content-type': 'application/json', 'Authorization': '<YOUR_RELAYR_TOKEN>', 'Cache-Control':'no-cache'}

noise_count = 0

while True:
	r = requests.get('https://api.relayr.io/devices/<DEVICE_ID_OF_ALEXA_DEVICE>/readings', headers=headers)
	response = json.loads(r.text)
	#print response
	
	try:
		print response['readings'][0]['value']
		soundStatus = response['readings'][0]['value']
		if soundStatus > 600:
			noise_count = noise_count + 1
		if noise_count > 3:
			#play audio
			noise_count = 0
	except:
		print "response failed."	
	

	time.sleep(0.5)