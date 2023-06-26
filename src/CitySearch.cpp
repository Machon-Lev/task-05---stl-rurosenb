#include "CitySearch.h"
using namespace std;

std::array<std::function<double(double, double, double, double)>, 3> CitySearch::distanceFunctions = {
    euclideanDistance,
    chebyshevDistance,
    manhattanDistance
};

double CitySearch::euclideanDistance(double x0, double y0, double x1, double y1) {
    return std::sqrt(std::pow(x0 - x1, 2) + std::pow(y0 - y1, 2));
}

double CitySearch::chebyshevDistance(double x0, double y0, double x1, double y1) {
    return std::max(std::abs(x0 - x1), std::abs(y0 - y1));
}

double CitySearch::manhattanDistance(double x0, double y0, double x1, double y1) {
    return std::abs(x0 - x1) + std::abs(y0 - y1);
}

void CitySearch::readCityData(const std::string& filename) {
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
        if (!(iss >> latitude >> dash >> longitude)) {
            file.close();
            throw std::runtime_error("Invalid data format in file: " + filename);
        }
        cities[cityName] = std::make_pair(latitude, longitude);
    }
    file.close();
    //for (auto i = cities.cbegin(); i != cities.cend(); ++i)
    //    std::cout << i->first << "\n" << i->second.first << i->second.second << '\n';
}

bool CitySearch::isCity(const std::string& cityName) {
    return (cities.find(cityName) == cities.end());
}

void CitySearch::searchCities(const std::string& cityName, double radius, int norm) {
    double x0 = cities[cityName].first;
    //cout << "the x0 is "<< x0<<endl;
    double y0 = cities[cityName].second;
    //cout <<"the y0 is " <<y0<<endl;

    std::vector<std::pair<std::string, double>> results;

    std::unordered_map<std::string, std::pair<double, double>> other;


    std::copy_if(cities.begin(), cities.end(), std::inserter(other, other.end()), [&](const auto& cityPair) {
        const auto& cityName1 = cityPair.first;
        const auto& cityCoordinates = cityPair.second;
        if (cityName1 != cityName)
        {
            double x1 = cityCoordinates.first;
            double y1 = cityCoordinates.second;
            double distance = distanceFunctions[norm](x0, y0, x1, y1);

            if (distance <= radius)
            {
                results.push_back(std::make_pair(cityName1, distance));
                return true;
            }
            return false;
        }
        });


    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
        });

    std::cout << results.size() << " city/cities found in the given radius." << std::endl;
    int northCount = countCitiesNorthOf(cityName);
    cout << northCount << " cities are to the north of the selected city." << std::endl;

    std::transform(results.begin(), results.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
        [](const auto& result) { return result.first;
        });
}

int CitySearch::countCitiesNorthOf(const std::string& cityName) {
    std::unordered_map<std::string, std::pair<double, double>> other;
    double selectedY = cities[cityName].second;
    std::copy_if(cities.begin(), cities.end(), std::inserter(other, other.begin()), [&](const auto& city) {
        return city.second.second < selectedY;
        });

    return other.size();
}



