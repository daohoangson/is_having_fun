//
//  vietnamese.cpp
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include "vietnamese.h"

#include <cassert>

void Vietnamese::doOne(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 1);
    int value = atoi(number.c_str());
    std::string result;
    
    switch (value) {
        case 1:
            result = "một";
            break;
        case 2:
            result = "hai";
            break;
        case 3:
            result = "ba";
            break;
        case 4:
            result = "bốn";
            break;
        case 5:
            result = "năm";
            break;
        case 6:
            result = "sáu";
            break;
        case 7:
            result = "bảy";
            break;
        case 8:
            result = "tám";
            break;
        case 9:
            result = "chín";
            break;
    }
    
    doUnit(results, offset, result);
}

void Vietnamese::doTwo(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 2);
    int value = atoi(number.c_str());
    
    int b = value % 10;
    value -= b;
    value /= 10;
    int a = value;
    std::vector<std::string> tmp;
    
    switch (a) {
        case 0:
            doOne(tmp, 0, number.substr(1, 1));
            break;
        case 1:
            doTwoSimple(tmp, number.substr(1, 1));
            tmp.insert(tmp.begin(), "mười");
            break;
        default:
            doTwoSpecial(tmp, number.substr(1, 1));
            doOne(tmp, 0, number.substr(0, 1));
    }
    
    doUnit(results, offset, implode(tmp));
}

void Vietnamese::doThree(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 3);
    int value = atoi(number.c_str());
    
    int a = value / 100;
    if (a > 0) {
        std::vector<std::string> tmp;
        doOne(tmp, 0, number.substr(0, 1));
        tmp.push_back("trăm");
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

void Vietnamese::doUnit(std::vector<std::string> &results, size_t offset, std::string text) {
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
            switch (tmp) {
                case 3:
                    unit = "nghìn";
                    break;
                case 6:
                    unit = "triệu";
                    break;
                case 9:
                    unit = "tỉ";
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

std::string Vietnamese::doAnd(std::string results, std::string lastResult) {
    return results + " lẻ " + lastResult;
}

void Vietnamese::doTwoSimple(std::vector<std::string> &tmp, std::string lastDigit) {
    doOne(tmp, 0, lastDigit);
}

void Vietnamese::doTwoSpecial(std::vector<std::string> &tmp, std::string lastDigit) {
    size_t tmpSize = tmp.size();
    std::string lastDigitText;
    if (lastDigit.compare("1") == 0) {
        lastDigitText = "mốt";
    } else if (lastDigit.compare("4") == 0) {
        lastDigitText = "tư";
    } else if (lastDigit.compare("5") == 0) {
        lastDigitText = "lăm";
    }
    
    if (lastDigitText.length() > 0) {
        tmp.insert(tmp.begin(), lastDigitText);
    } else {
        doTwoSimple(tmp, lastDigit);
    }
    
    if (tmp.size() == tmpSize) {
        tmp.insert(tmp.begin(), "mươi");
    }
}
