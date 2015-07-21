//
//  english.cpp
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include "english.h"

#include <cassert>

std::string English::doZero() {
    return "zero";
}

void English::doOne(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 1);
    int value = atoi(number.c_str());
    std::string result;
    
    switch (value) {
        case 1:
            result = "one";
            break;
        case 2:
            result = "two";
            break;
        case 3:
            result = "three";
            break;
        case 4:
            result = "four";
            break;
        case 5:
            result = "five";
            break;
        case 6:
            result = "six";
            break;
        case 7:
            result = "seven";
            break;
        case 8:
            result = "eight";
            break;
        case 9:
            result = "nine";
            break;
    }
    
    doUnit(results, offset, result);
}

void English::doTwo(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 2);
    int value = atoi(number.c_str());
    
    int b = value % 10;
    value -= b;
    value /= 10;
    int a = value;
    std::string result;
    
    switch (a) {
        case 0:
            doOne(results, offset, number.substr(1, 1));
            return;
        case 1:
            switch (b) {
                case 0:
                    result = "ten";
                    break;
                case 1:
                    result = "eleven";
                    break;
                case 2:
                    result = "twelve";
                    break;
                case 3:
                    result = "thirteen";
                    break;
                case 4:
                    result = "fourteen";
                    break;
                case 5:
                    result = "fifteen";
                    break;
                case 6:
                    result = "sixteen";
                    break;
                case 7:
                    result = "seventeen";
                    break;
                case 8:
                    result = "eighteen";
                    break;
                case 9:
                    result = "nineteen";
                    break;
            }
            break;
        case 2:
            result = makeTwo("twenty", number.substr(1, 1));
            break;
        case 3:
            result = makeTwo("thirty", number.substr(1, 1));
            break;
        case 4:
            result = makeTwo("forty", number.substr(1, 1));
            break;
        case 5:
            result = makeTwo("fifty", number.substr(1, 1));
            break;
        case 6:
            result = makeTwo("sixty", number.substr(1, 1));
            break;
        case 7:
            result = makeTwo("seventy", number.substr(1, 1));
            break;
        case 8:
            result = makeTwo("eighty", number.substr(1, 1));
            break;
        case 9:
            result = makeTwo("ninety", number.substr(1, 1));
            break;
    }
    
    doUnit(results, offset, result);
}

void English::doThree(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 3);
    int value = atoi(number.c_str());
    
    int a = value / 100;
    if (a > 0) {
        std::vector<std::string> tmp;
        doOne(tmp, 0, number.substr(0, 1));
        tmp.push_back("hundred");
        std::string partialResult = implode(tmp);
        
        size_t resultsSize = results.size();
        doTwo(results, offset, number.substr(1, 2));
        
        if (results.size() == resultsSize) {
            // no data for the last two digits
            // we have to call doUnit ourself
            doUnit(results, offset, partialResult);
        } else {
            results.insert(results.begin(), partialResult);
        }
    } else {
        doTwo(results, offset, number.substr(1, 2));
    }
}

void English::doUnit(std::vector<std::string> &results, size_t offset, std::string text) {
    if (text.length() == 0) {
        return;
    }
    
    if (offset < 3) {
        results.insert(results.begin(), text);
        return;
    }
    
    std::vector<std::string> units;
    size_t remaining = offset;
    while (remaining > 0) {
        std::string unit;
        
        size_t tmp = remaining;
        while (tmp > 0 && unit.length() == 0) {
            // https://en.wikipedia.org/wiki/Names_of_large_numbers
            switch (tmp) {
                case 3:
                    unit = "thousand";
                    break;
                case 6:
                    unit = "million";
                    break;
                case 9:
                    unit = "billion";
                    break;
                case 12:
                    unit = "trillion";
                    break;
                case 15:
                    unit = "quadrillion";
                    break;
                case 18:
                    unit = "quintillion";
                    break;
                case 21:
                    unit = "sextillion";
                    break;
                case 24:
                    unit = "septillion";
                    break;
                case 27:
                    unit = "octillion";
                    break;
                case 30:
                    unit = "nonillion";
                    break;
                case 33:
                    unit = "decillion";
                    break;
                case 36:
                    unit = "undecillion";
                    break;
                case 39:
                    unit = "duodecillion";
                    break;
                case 42:
                    unit = "tredecillion";
                    break;
                case 45:
                    unit = "quattuordecillion";
                    break;
                case 48:
                    unit = "quindecillion";
                    break;
                case 51:
                    unit = "sedecillion";
                    break;
                case 54:
                    unit = "septendecillion";
                    break;
                case 57:
                    unit = "octodecillion";
                    break;
                case 60:
                    unit = "novendecillion";
                    break;
                case 63:
                    unit = "vigintillion";
                    break;
                case 303:
                    unit = "centillion";
                    break;
                default:
                    tmp -= 3;
            }
        }
        
        units.insert(units.begin(), unit);
        remaining -= tmp;
    }
    
    results.insert(results.begin(), text + " " + implode(units));
}

std::string English::doAnd(std::string results, std::string lastResult) {
    return results + " and " + lastResult;
}

std::string English::makeTwo(std::string firstDigitText, std::string lastDigit) {
    std::vector<std::string> tmp;
    doOne(tmp, 0, lastDigit);
    tmp.insert(tmp.begin(), firstDigitText);
    
    return implode(tmp);
}
