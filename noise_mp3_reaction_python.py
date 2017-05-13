import requests
import json
import time
import datetime
import urllib2
from pygame import mixer

#def passed_time(initial_time):
#	return datetime.timedelta.total_seconds(datetime.datetime.now() - initial_time) * 1000

headers = {'content-type': 'application/json', 'Authorization': '<RELAYR_TOKEN>', 'Cache-Control':'no-cache'}

noise_count = 0
#soundStatus = 595

while True:
	r = requests.get('https://api.relayr.io/devices/<DEVICE_ID>/readings', headers=headers)
	response = json.loads(r.text)
	#print response
	
	try:
		#print response['readings'][0]['value']
		soundStatus = response['readings'][0]['value']
		#soundStatus = soundStatus + 1
		print soundStatus
		if soundStatus > 300:
			noise_count = noise_count + 1
		if noise_count > 3:
			print "Pssssht."
			mixer.init()
			mixer.music.load('D:/railax-take-it-easy/assets/SilentCoupe_Deutsch.mp3')
			mixer.music.play()
			noise_count = 0
			time.sleep(20)
	except:
		print "response failed."	
	

	time.sleep(0.1)