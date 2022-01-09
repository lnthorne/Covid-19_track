//
//  View.hpp
//  CovidAPI
//
//  Created by Liam Thorne on 2022-01-07.
//

#ifndef View_h
#define View_h

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <json.h>

class view {
public:
    view() {}
    ~view() {}
    
//    Asks user what country they would like to look up
//    return string of country
    std::string countryQuery() {
        std::string userIN;
        
        std::cout << "Hello welcome to Covid API\n"
                   << "By: Liam Thorne\n\n";
        std::cout << "Please type in the name of the country you are looking for : ";
        std::getline (std::cin, userIN);
//        setting string tolower case
        std::transform(userIN.begin(), userIN.end(), userIN.begin(), ::tolower);
//        erasing the spaces in the string
//        isspace clears repeating spaces
        userIN.erase(std::remove_if(userIN.begin(), userIN.end(), isspace), userIN.end());
        
        return userIN;
    }
    
//    param Json::Value json data about the country
    void displayInfo(Json::Value country) {
        const int newConfirmed = country["NewConfirmed"].asInt();
        const int newDeaths = country["NewDeaths"].asInt();
        const int newRecovered = country["NewRecovered"].asInt();
        const int ttlConfirmed = country["TotalConfirmed"].asInt();
        const int ttlDeaths = country["TotalDeaths"].asInt();
        std::string currCountry = country["Country"].asString();
        
        std::cout << "\n\nToday in " << currCountry << ", there were " << newConfirmed
        << " newly confirmed cases and " << newDeaths << " new deaths\n"
        << "raising the total confirmed cases to " << ttlConfirmed << ", and the total deaths to "
        << ttlDeaths << std::endl;
        
        std::cout << "there have also been " << newRecovered << " newly recovered\n";
    }
};

#endif /* View_h */
