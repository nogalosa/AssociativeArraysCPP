//
// Created by Nerijus on 2019-05-29.
//

#ifndef ASSOCIATIVEARRAYSCPP_MAIN_H
#define ASSOCIATIVEARRAYSCPP_MAIN_H

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <locale>
#include <cctype>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <regex>

class main {
public:
    std::string loadFile();
    void printURLs(std::string text, std::ofstream& to);
    std::string refactorText(std::string);
};


#endif //ASSOCIATIVEARRAYSCPP_MAIN_H
