# MorphingClockRemix
 * Remix from HarryFun's great MorphingClock idea https://www.instructables.com/id/Morphing-Digital-Clock/
 * Follow the great tutorial there and eventually use this code as alternative.
 * 
 * - main code is based on the NTP lib example for ESP, the lib itself is used as is for NTP sync;
 * - use fast NTP sync then adapt to one sync per day (or so)
 * - Morphing clock logic is kept almost as is from https://github.com/hwiguna/HariFun_166_Morphing_Clock
 * - WiFiManager logic is also from https://github.com/hwiguna/HariFun_166_Morphing_Clock
 * - it uses TinyFont and TinyIcons as my own implementation
 * - it uses openweathermap.org so you'll need a free account for the weather data
 *  !! you'll need to update the apiKey and location variables (around line 300)
 * - it uses animated icons for weather sunny, cloudy, rainy, thunders, snow, etc.. (not all tested yet)
 * 
 * tested ONLY using the NodeMCU variant listed as NodeMCU 1.0 (ESP-12E Module) in Arduino Studio
 * 
 * provided 'AS IS' use at your own risk
