#include <iostream>
#include <exception>

#include "CitySearch.cpp"
using namespace std;
int main() 
{
    CitySearch citySearch;

    try {
        citySearch.readCityData("data.txt");
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    while (true) {
        std::cout << "Please enter selected city name (with line break after it):" << std::endl;
        std::string cityName;
        std::getline(std::cin, cityName);

        if (cityName == "0") {
            break;
        } 

        std::cout << "Please enter the wanted radius:" << std::endl;
        double radius;
        std::cin >> radius;

        std::cout << "Please enter the wanted norm: \n 0 = L2, Euclidean distance,\n 1 = Linf, Chebyshev distance,\n 2 = L1, Manhattan distance):\n" << std::endl;
        int norm;
        std::cin >> norm;

        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Search result:" << std::endl;
        citySearch.searchCities(cityName, radius, norm);
        std::cout << std::endl;
    }

    std::cout << "Bye" << std::endl;
    return 0;
}
