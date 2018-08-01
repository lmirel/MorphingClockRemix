# MorphingClockRemix
Remix from HarryFun's great Morphing Digital Clock idea https://www.instructables.com/id/Morphing-Digital-Clock/
Follow the great tutorial there and eventually use this code as alternative.
 
- main code is based on the NTPClient lib example for ESP, the lib itself is used as is for NTP sync https://github.com/2dom/NtpClient
- use fast NTP sync on start then adapt to one sync per day (or so)
- Morphing clock code/logic is kept almost as is from https://github.com/hwiguna/HariFun_166_Morphing_Clock
- WiFiManager code/logic is also from https://github.com/hwiguna/HariFun_166_Morphing_Clock
- it uses TinyFont and TinyIcons as my own implementation
- it uses openweathermap.org so you'll need a free account for the weather data (sync every 5min or so)
  !! you'll need to update the apiKey and location variables (around line 300)
- it uses animated icons for weather: sunny, cloudy, rainy, thunders, snow, etc.. (not all tested yet)
- it has night mode from 8pm to 8am when it only shows a moon and 2 twinkling stars and a dimmed display
- temperature and humidity change color based on (what most might consider) comfortable values

tested ONLY using the NodeMCU variant listed as NodeMCU 1.0 (ESP-12E Module) in Arduino Studio

provided 'AS IS', use at your own risk
