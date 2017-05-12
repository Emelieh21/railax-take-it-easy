# Railax: Bringing Peace to Your Journey

### Description

Sometimes, you want to enjoy a quit trip, and get some work done - or just have a siesta. But suddenly, it turns out a bunch that a bunch of noisy people jump in the train, and your peace is gone. The weekly football match attract all hooligans to the train. Wouldn't it be nice to know in advance what to expect from your trip? 

The goal of this project is to collect data from a sound sensor and implements it with other (travel) data (weekday, time, segment, etc.) so eventually predictions can be made on how busy/quite your next trip will be. For this we want to use data from the Deutsche Bahn API, sound sensors (fora "real world" proof of concept), R (to process/represent data) and C/Adruino (electronics).

_This project is a result of the DB Mindbox Hackathon Berlin 12-13 May of 2017._

---

### Make a Mp3 go off when the noise goes wild

We want a pleasant voice to kindly remind people to keep their mouth shut. Luckily, there are many TTS (TextToSpeech) services online out there - and also free ones. I used [texttospeech](http://www.fromtexttospeech.com/) to create an audio file we could use.

Text English: _Dear Passengers, I would like to kindly remind you that this is a silent wagon._

Text German: _Liebe Passagiere, ich möchte Sie freundlich daran erinnern, dass Sie sich in einem stillen Wagen befinden. Vielen dank für Ihre verständnis_

### Find a Python library to play Mp3 with

```python
from pygame import mixer # Load the required library

mixer.init()
mixer.music.load('e:/LOCAL/Betrayer/Metalik Klinik1-Anak Sekolah.mp3')
mixer.music.play()
```

