//
//  spanish.cpp
//  number2text
//
//  Created by Son Dao on 8/6/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include "spanish.h"

#include <cassert>
#include <iostream>

std::string Spanish::doZero() {
    return "cero";
}

void Spanish::doOne(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 1);
    int value = atoi(number.c_str());
    std::string result;
    
    switch (value) {
        case 1:
            result = "uno";
            break;
        case 2:
            result = "dos";
            break;
        case 3:
            result = "tres";
            break;
        case 4:
            result = "cuatro";
            break;
        case 5:
            result = "cinco";
            break;
        case 6:
            result = "seis";
            break;
        case 7:
            result = "siete";
            break;
        case 8:
            result = "ocho";
            break;
        case 9:
            result = "nueve";
            break;
    }
    
    doUnit(results, offset, result);
}

void Spanish::doTwo(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 2);
    int value = atoi(number.c_str());
    
    int b = value % 10;
    value -= b;
    value /= 10;
    int a = value;
    std::string result;
    
    switch (a) {
        case 0:
            // treat as single digit number
            doOne(results, offset, number.substr(1, 1));
            return;
        case 1:
            switch (b) {
                case 0:
                    result = "diez";
                    break;
                case 1:
                    result = "once";
                    break;
                case 2:
                    result = "doce";
                    break;
                case 3:
                    result = "trece";
                    break;
                case 4:
                    result = "catorce";
                    break;
                case 5:
                    result = "quince";
                    break;
                case 6:
                    result = "dieciséis";
                    break;
                case 7:
                    result = "diecisiete";
                    break;
                case 8:
                    result = "dieciocho";
                    break;
                case 9:
                    result = "diecinueve";
                    break;
            }
            break;
        case 2:
            switch (b) {
                case 0:
                    result = "veinte";
                    break;
                case 1:
                    result = "veintiuno";
                    break;
                case 2:
                    result = "veintidós";
                    break;
                case 3:
                    result = "veintitrés";
                    break;
                case 4:
                    result = "veinticuatro";
                    break;
                case 5:
                    result = "veinticinco";
                    break;
                case 6:
                    result = "veintiséis";
                    break;
                case 7:
                    result = "veintisiete";
                    break;
                case 8:
                    result = "veintiocho";
                    break;
                case 9:
                    result = "veintinueve";
                    break;
            }
            break;
        case 3:
            result = makeTwo("treinta", number.substr(1, 1));
            break;
        case 4:
            result = makeTwo("cuarenta", number.substr(1, 1));
            break;
        case 5:
            result = makeTwo("cincuenta", number.substr(1, 1));
            break;
        case 6:
            result = makeTwo("sesenta", number.substr(1, 1));
            break;
        case 7:
            result = makeTwo("setenta", number.substr(1, 1));
            break;
        case 8:
            result = makeTwo("ochenta", number.substr(1, 1));
            break;
        case 9:
            result = makeTwo("noventa", number.substr(1, 1));
            break;
    }
    
    doUnit(results, offset, result);
}

void Spanish::doThree(std::vector<std::string> &results, size_t offset, std::string number) {
    assert(number.length() == 3);
    int value = atoi(number.c_str());
    
    int a = value / 100;
    std::string result;
    
    switch (a) {
        case 0:
            // treat as two digit number
            doTwo(results, offset, number.substr(1, 2));
            return;
        case 1:
            if (value - (a * 100) > 0) {
                result = makeThree("ciento", number.substr(1, 2));
            } else {
                result = "cien";
            }
            break;
        case 2:
            result = makeThree("doscientos", number.substr(1, 2));
            break;
        case 3:
            result = makeThree("trescientos", number.substr(1, 2));
            break;
        case 4:
            result = makeThree("cuatrocientos", number.substr(1, 2));
            break;
        case 5:
            result = makeThree("quinientos", number.substr(1, 2));
            break;
        case 6:
            result = makeThree("seiscientos", number.substr(1, 2));
            break;
        case 7:
            result = makeThree("setecientos", number.substr(1, 2));
            break;
        case 8:
            result = makeThree("ochocientos", number.substr(1, 2));
            break;
        case 9:
            result = makeThree("novecientos", number.substr(1, 2));
            break;
    }
    
    doUnit(results, offset, result);
}

void Spanish::doUnit(std::vector<std::string> &results, size_t offset, std::string text) {
    if (text.length() == 0) {
        return;
    }
    
    if (offset < 3) {
        results.insert(results.begin(), text);
        return;
    }
    assert(offset % 3 == 0);
    
    bool isSingular = false;
    if (text.compare("uno") == 0) {
        // special case for one something: use "un" instead
        text = "un";
        isSingular = true;
    }

    std::vector<std::string> units;
    size_t remaining = offset;
    while (remaining > 0) {
        std::string unit;
        
        size_t tmp = remaining;
        while (tmp > 0 && unit.length() == 0) {
            switch (tmp) {
                case 3:
                    unit = "mil";
                    break;
                case 6:
                    if (isSingular) {
                        unit = "millón";
                    } else {
                        unit = "millones";
                    }
                    break;
                case 9:
                    if (isSingular) {
                        unit = "billón";
                    } else {
                        unit = "billones";
                    }
                    break;
                case 12:
                    if (isSingular) {
                        unit = "trillón";
                    } else {
                        unit = "trillones";
                    }
                    break;
                default:
                    tmp -= 3;
            }
        }
        
        units.insert(units.begin(), unit);
        remaining -= tmp;
    }
    
    std::string unitsStr = implode(units);
    if (unitsStr.compare("mil") == 0 && text.compare("un") == 0) {
        // special case for one thousand: only return "mil"
        results.insert(results.begin(), unitsStr);
    } else {
        results.insert(results.begin(), text + " " + unitsStr);
    }
}

std::string Spanish::doAnd(std::string results, std::string lastResult) {
    return results + " " + lastResult;
}

std::string Spanish::makeTwo(std::string firstDigitText, std::string lastDigit) {
    std::vector<std::string> tmp;
    doOne(tmp, 0, lastDigit);
    
    if (tmp.size() > 0) {
        tmp.insert(tmp.begin(), "y");
    }
    
    tmp.insert(tmp.begin(), firstDigitText);
    
    return implode(tmp);
}

std::string Spanish::makeThree(std::string firstDigitText, std::string lastTwoDigits) {
    std::vector<std::string> tmp;
    doTwo(tmp, 0, lastTwoDigits);
    tmp.insert(tmp.begin(), firstDigitText);
    
    return implode(tmp);
}