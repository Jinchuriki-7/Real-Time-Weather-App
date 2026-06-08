#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output)
{
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    string city;

    cout << "+---------------------------+\n";
    cout << "|      Weather App          |\n";
    cout << "+---------------------------+\n\n";

    cout << "Enter city name: ";
    getline(cin, city);

    string apiKey = "bd0e1581f1088d2df073cd6748dd1739";

    string url =
        "https://api.openweathermap.org/data/2.5/weather?q=" +
        city +
        "&appid=" +
        apiKey;

    CURL* curl = curl_easy_init();

    if (!curl)
    {
        cout << "Failed to initialize CURL.\n";
        return 1;
    }

    string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        cout << "\nInternet connection error!\n";
        cout << curl_easy_strerror(result) << endl;

        curl_easy_cleanup(curl);
        return 1;
    }

    curl_easy_cleanup(curl);

    try
    {
        json data = json::parse(response);

        if (data.contains("cod"))
        {
            if ((data["cod"].is_string() && data["cod"] == "404") ||
                (data["cod"].is_number() && data["cod"] == 404))
            {
                cout << "\nCity not found!\n";
                return 1;
            }
        }

        string cityName = data["name"];

        double tempKelvin = data["main"]["temp"];
        double tempCelsius = tempKelvin - 273.15;

        int humidity = data["main"]["humidity"];
        int pressure = data["main"]["pressure"];

        string weather = data["weather"][0]["description"];
        double windSpeed = data["wind"]["speed"];

        cout << "\nCity: " << cityName << endl;
        cout << "Temperature: " << tempCelsius << " C" << endl;
        cout << "Humidity: " << humidity << "%" << endl;
        cout << "Weather: " << weather << endl;
        cout << "Wind Speed: " << windSpeed << " m/s" << endl;
        cout << "Pressure: " << pressure << " hPa" << endl;
    }
    catch (exception& e)
    {
        cout << "\nError parsing weather data.\n";
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}