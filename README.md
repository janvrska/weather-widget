# Weather widget
Plotting of local weather from Wunderground [stations](https://www.wunderground.com/wundermap) (PWS)

![weather_widget](https://user-images.githubusercontent.com/1644599/194778146-e5c9455d-138c-4973-9d2b-2a8896a1e0ab.png)

## **Build prerequisites**
 - Installed vcpkg and these packages
	 - vcpkg install imgui
	 - vcpkg install implot
	 - vcpkg install glew
	 - vcpkg install cpr
	 - vcpkg install nlohmann_json
	
CMake parameter: -DCMAKE_TOOLCHAIN_FILE=path to vcpkg directory

## **Third-party libraries** and their usage:

 - [ImGUI](https://github.com/ocornut/imgui) - GUI for whole application
 - [ImPlot](https://github.com/epezent/implot) - custom plots for weather (temperature, humidity)
 - [Glew](https://github.com/nigels-com/glew) - needed by ImGUI, not using explicitly
 - [Cpr](https://github.com/libcpr/cpr) - requesting Wunderground API over HTTP
 - [Json](https://github.com/nlohmann/json)  - deserializing JSON from request body

## **Usage:**

For usage is necessary to be [registered](https://www.wunderground.com/signup) on Wunderground and then [generate API key](https://www.wunderground.com/member/api-keys)

 1. Obtain Wunderground API key ↑
 2. Find some near PWS in their [map](https://www.wunderground.com/wundermap)
 3. Copy that PWS ID (station id), for [example](https://www.wunderground.com/dashboard/pws/IPRAGU386) IPRAGU386
 4. Open this app
 5. Paste API key and PWS ID to this in-app Settings
 6. Click "Save"
 7. Temperature and Humidity plot should appear

**Screenshots:**

Widget is by default semi-transparent and always-on-top, and therefore can be seen pernamently.

![weather_widget](https://user-images.githubusercontent.com/1644599/194778146-e5c9455d-138c-4973-9d2b-2a8896a1e0ab.png)
![weather_widget_transparent](https://user-images.githubusercontent.com/1644599/194778174-d25ea6ad-4b3c-4cbf-9074-04f9c76f329f.png)
![weather_widget_full](https://user-images.githubusercontent.com/1644599/194778166-679794b4-2fda-40aa-b3db-8b898cc360c4.png)

Tested on Windows 10, 1920x1080px
