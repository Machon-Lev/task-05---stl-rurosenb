#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
class CitySearch {
public:
    void readCityData(const std::string& filename) // Reading city data from file and storing it in the cities map
    {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string line;
        std::string cityName;
        double latitude, longitude;
        char dash;
        while (std::getline(file, line)) {
            cityName = line;
            //std::cout << line<<std::endl;
            std::getline(file, line);
            //std::cout << line << std::endl;
            std::istringstream iss(line);
            if (!(iss >> latitude >> dash >>longitude)) {
                file.close();
                throw std::runtime_error("Invalid data format in file: " + filename);
            }
            cities[cityName] = std::make_pair(latitude, longitude);
        }
        file.close();
        //for (auto i = cities.cbegin(); i != cities.cend(); ++i)
        //    std::cout << i->first << "\n" << i->second.first << i->second.second << '\n';

    }
    void searchCities(const std::string& cityName, double radius, int norm)// Searching for cities within the given radius and norm
    {
        if (cities.find(cityName) == cities.end()) {
            std::cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again." << std::endl;
            return;
        }

        double x0 = cities[cityName].first;
        double y0 = cities[cityName].second;

        std::vector<std::pair<std::string, double>> results;

        for (const auto& city : cities) {
            if (city.first != cityName) {
                double x1 = city.second.first;
                double y1 = city.second.second;
                double distance;

                if (norm == 0) {
                    distance = euclideanDistance(x0, y0, x1, y1);
                }
                else if (norm == 1) {
                    distance = chebyshevDistance(x0, y0, x1, y1);
                }
                else if (norm == 2) {
                    distance = manhattanDistance(x0, y0, x1, y1);
                }
                else {
                    std::cout << "Invalid norm value. Please try again." << std::endl;
                    return;
                }

                if (distance <= radius) {
                    results.push_back(std::make_pair(city.first, distance));
                }
            }
        }

        std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
            });

        std::cout << results.size() << " city/cities found in the given radius." << std::endl;
        int northCount = countCitiesNorthOf(cityName);
        std::cout << northCount << " cities are to the north of the selected city." << std::endl;

        for (const auto& result : results) {
            std::cout << result.first << std::endl;
        }
    }
private:
    std::map<std::string, std::pair<double, double>> cities;

    double euclideanDistance(double x0, double y0, double x1, double y1) {
        return std::sqrt(std::pow(x0 - x1, 2) + std::pow(y0 - y1, 2));
    }

    double chebyshevDistance(double x0, double y0, double x1, double y1) {
        return std::max(std::abs(x0 - x1), std::abs(y0 - y1));
    }

    double manhattanDistance(double x0, double y0, double x1, double y1) {
        return std::abs(x0 - x1) + std::abs(y0 - y1);
    }

    int countCitiesNorthOf(const std::string& cityName) {
        double selectedLatitude = cities[cityName].first;
        int northCount = 0;

        for (const auto& city : cities) {
            if (city.second.first < selectedLatitude) {
                northCount++;
            }
        }

        return northCount;
    }
};