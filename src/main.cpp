#include <iostream>
#include <exception>

#include "CitySearch.h"
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
       

        // Check if the city exists
        if (citySearch.isCity(cityName)) {
            std::cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again." << std::endl;
            continue;
        }

        std::cout << "Please enter the wanted radius:" << std::endl;
        double radius;
        try {
            if (!(std::cin >> radius)) {
                throw std::runtime_error("Invalid radius: ");
            }
            while  (radius <= 0) {
                std::cout << "ERROR: Radius cannot be negative. Please enter a non-negative value." << std::endl;
                if(!(std::cin >> radius)) {
                    throw std::runtime_error("Invalid radius: ");
                }
            }
        }
        catch (const std::exception& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
            return 1;  // Terminate the program
        }

        std::cout << "Please enter the wanted norm: \n 0 = L2, Euclidean distance,\n 1 = Linf, Chebyshev distance,\n 2 = L1, Manhattan distance):\n" << std::endl;
        int norm;
        try {
            if (!(std::cin >> norm)) {
                throw std::runtime_error("Invalid norm: ");
            }
            while (norm != 0 and norm != 1 and norm != 2)
            {
                std::cout << "ERROR: Invalid norm value. Please enter a value of 0, 1, or 2." << std::endl;
                if (!(std::cin >> norm)) {
                    throw std::runtime_error("Invalid norm: ");
                }
            }

        }
        catch (const std::exception& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
            return 1;  // Terminate the program
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Search result:" << std::endl;
        citySearch.searchCities(cityName, radius, norm);
        std::cout << std::endl;
    }

    std::cout << "Bye" << std::endl;
    return 0;
}
