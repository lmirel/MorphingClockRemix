# MorphingClockRemix
Remix from HarryFun's great Morphing Digital Clock idea https://www.instructables.com/id/Morphing-Digital-Clock/
Follow the great tutorial there and eventually use this code as alternative.
![alt text](https://raw.githubusercontent.com/lmirel/MorphingClockRemix/master/MorphingClockRemix.jpg?raw=true)

- main code is based on the NTPClient lib example for ESP, the lib itself is used as is for NTP sync https://github.com/2dom/NtpClient
- use fast NTP sync on start then adapt to one sync per day (or so)
- 12/24h time format
- date format and display below the clock
- Morphing clock code/logic is kept almost as is from https://github.com/hwiguna/HariFun_166_Morphing_Clock
- it uses TinyFont and TinyIcons as my own implementation
- it uses openweathermap.org so you'll need a free account for the weather data (sync every 5min or so)
  !! you'll need to update the apiKey and location variables (around line 300)
- metric or imperial units support for weather data display above the clock
- it uses animated icons for weather: sunny, cloudy, rainy, thunders, snow, etc.. (not all tested yet)
- it has night mode from 8pm to 8am when it only shows a moon and 2 twinkling stars and a dimmed display
- temperature and humidity change color based on (what most might consider) comfortable values
- fireworks for special ocasions ;-)= adapted for Arduino from https://r3dux.org/2010/10/how-to-create-a-simple-fireworks-effect-in-opengl-and-sdl/

depends on following libraries:
- Time 1.5 by Michael Margolis https://github.com/PaulStoffregen/Time
- NtpClientLib 3.0.2-beta by Germán Martín https://github.com/gmag11/NtpClient
- PxMatrix 1.6.0 by Dominic Buchstaler https://github.com/2dom/PxMatrix

[Note]: In case you have issues running the WiFi configuration applet, disable ICONS usage.

- #define USE_ICONS
- #define USE_FIREWORKS
- #define USE_WEATHER_ANI You can re-enable it after configuration is done.
The 'no-wm' branch uses a static configuration approach.
<br>
- Use the small WEB server for various settings (wip) at http://[esp-ip]/ like below:
<br>
use the following configuration links
<br>
daylight on
<br>
daylight off
<br>
timezone 0
<br>
timezone 1
<br>
timezone 2
<br>
use /timezone/x for specific timezone 'x'
<br>
<br>
tested ONLY using the NodeMCU variant listed as NodeMCU 1.0 (ESP-12E Module) in Arduino Studio
<br>
provided 'AS IS', use at your own risk
