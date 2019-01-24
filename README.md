# MorphingClockRemix
Remix from HarryFun's great Morphing Digital Clock idea https://www.instructables.com/id/Morphing-Digital-Clock/
Follow the great tutorial there and eventually use this code as alternative.
![alt text](https://raw.githubusercontent.com/lmirel/MorphingClockRemix/master/MorphingClockRemix.jpg?raw=true)

- main code is based on the NTPClient lib example for ESP, the lib itself is used as is for NTP sync https://github.com/2dom/NtpClient
- use fast NTP sync on start then adapt to one sync per day (or so)
- 12/24h time format
- date format and display below the clock
- Morphing clock code/logic is kept almost as is from https://github.com/hwiguna/HariFun_166_Morphing_Clock
- WiFiManager code/logic is also from https://github.com/hwiguna/HariFun_166_Morphing_Clock - the password for connecting to ESP AP is: MorphClk
- it uses TinyFont and TinyIcons as my own implementation
- it uses openweathermap.org so you'll need a free account for the weather data (sync every 5min or so)
  !! you'll need to update the apiKey and location variables (around line 300)
- metric or imperial units support for weather data display above the clock
- it uses animated icons for weather: sunny, cloudy, rainy, thunders, snow, etc.. (not all tested yet)
- it has night mode from 8pm to 8am when it only shows a moon and 2 twinkling stars and a dimmed display
- temperature and humidity change color based on (what most might consider) comfortable values

[Note]: In case you have issues running the WiFi configuration applet, disable ICONS usage.
//#define USE_ICONS
//#define USE_FIREWORKS
//#define USE_WEATHER_ANI
You can re-enable it after configuration is done.
Alternatively, you can use the 'no-wm' branch for a static configuration approach.

tested ONLY using the NodeMCU variant listed as NodeMCU 1.0 (ESP-12E Module) in Arduino Studio

provided 'AS IS', use at your own risk
