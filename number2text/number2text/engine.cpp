//
//  engine.cpp
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include "engine.h"

#include <iostream>
#include <regex>
#include <sstream>

std::string Engine::input(int argc, const char * argv[]) {
    std::string number = "";
    
    if (argc == 2) {
        number = argv[1];
    }
    
    while (number.length() == 0 || !verifyInput(number)) {
        std::cout << "n=? ";
        std::getline(std::cin, number);
    }
    
    return number;
}

std::string Engine::process(std::string number) {
    size_t length = number.length();
    size_t offset = 0;
    std::vector<std::string> results;
    
    while (offset < length) {
        size_t remaining = length - offset;
        size_t workingLength = (remaining > 3 ? 3 : remaining);
        std::string substr = number.substr(length - offset - workingLength, workingLength);
        
        std::string result;
        switch (workingLength) {
            case 1:
                doOne(results, offset, substr);
                break;
            case 2:
                doTwo(results, offset, substr);
                break;
            case 3:
                doThree(results, offset, substr);
                break;
        }
        
        offset += workingLength;
    }
    
    if (results.size() > 1) {
        std::string lastResult = results[results.size() - 1];
        results.pop_back();
        return doAnd(implode(results), lastResult);
    } else {
        return implode(results);
    }
}

std::string Engine::implode(std::vector<std::string> &vector) {
    std::ostringstream builder;
    copy(vector.begin(), vector.end(), std::ostream_iterator<std::string>(builder, " "));
    std::string result = builder.str();
    
    // we have to remove the trailing space
    size_t pos = result.find_last_not_of(" ");
    if(std::string::npos != pos) {
        result = result.substr(0, pos + 1);
    }
    
    return result;
}

bool Engine::verifyInput(std::string input) {
    return std::regex_match(input, std::regex("^[0-9]+$"));
}