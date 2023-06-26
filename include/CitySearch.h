#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>

class CitySearch {
public:
    void readCityData(const std::string& filename);
    bool isCity(const std::string& cityName);
    void searchCities(const std::string& cityName, double radius, int norm);
    int countCitiesNorthOf(const std::string& cityName);


private:
    std::unordered_map<std::string, std::pair<double, double>> cities;

    static double euclideanDistance(double x0, double y0, double x1, double y1);
    static double chebyshevDistance(double x0, double y0, double x1, double y1);
    static double manhattanDistance(double x0, double y0, double x1, double y1);
    static std::array<std::function<double(double, double, double, double)>, 3> distanceFunctions;

};

