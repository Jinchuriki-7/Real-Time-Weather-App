# Weather App

A simple C++ console-based weather application that fetches real-time weather data using the OpenWeather API.

## Features

- Real-time weather updates
- Search weather by city name
- Temperature display
- Humidity display
- Weather condition display
- Wind speed display
- Pressure display
- Error handling for invalid city names
- Error handling for internet connection issues

## Technologies Used

- C++17
- OpenWeather API
- libcurl
- nlohmann/json
- vcpkg

## Example Output

```text
+---------------------------+
|      Weather App          |
+---------------------------+

Enter city name: Khulna

City: Khulna
Temperature: 29.13 C
Humidity: 66%
Weather: overcast clouds
Wind Speed: 5.88 m/s
Pressure: 1001 hPa
```

## Installation

1. Clone the repository

```bash
git clone https://github.com/your-username/CPP-Weather-App.git
```

2. Install dependencies

```bash
vcpkg install curl:x64-windows
vcpkg install nlohmann-json:x64-windows
```

3. Add your OpenWeather API key

```cpp
string apiKey = "YOUR_API_KEY";
```

4. Build and run the project

## Author

Farhanul Haque
