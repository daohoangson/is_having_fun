//
//  tests.cpp
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include "tests.h"

#include <cassert>
#include <iostream>
#include "english.h"

void testEnglish() {
    English *e = new English();
    
    std::string data[] = {
        "0", "",
        "1", "one",
        "2", "two",
        "3", "three",
        "4", "four",
        "5", "five",
        "6", "six",
        "7", "seven",
        "8", "eight",
        "9", "nine",
        "01", "one",
        "10", "ten",
        "11", "eleven",
        "12", "twelve",
        "13", "thirteen",
        "14", "fourteen",
        "15", "fifteen",
        "16", "sixteen",
        "17", "seventeen",
        "18", "eighteen",
        "19", "nineteen",
        "20", "twenty",
        "21", "twenty one",
        "30", "thirty",
        "40", "forty",
        "50", "fifty",
        "60", "sixty",
        "70", "seventy",
        "80", "eighty",
        "90", "ninety",
        "001", "one",
        "100", "one hundred",
        "101", "one hundred and one",
        "1000", "one thousand",
        "10000", "ten thousand",
        "100000", "one hundred thousand",
        "1000000", "one million",
        "1000000000", "one billion",
        "1000000000000", "one trillion",
        "1000000000000000", "one quadrillion",
        "1000000000000000000", "one quintillion",
        "1000000000000000000000", "one sextillion",
        "1000000000000000000000000", "one septillion",
        "1000000000000000000000000000", "one octillion",
        "1000000000000000000000000000000", "one nonillion",
        "1000000000000000000000000000000000", "one decillion",
        "1000000000000000000000000000000000000", "one undecillion",
        "1000000000000000000000000000000000000000", "one duodecillion",
        "1000000000000000000000000000000000000000000", "one tredecillion",
        "1000000000000000000000000000000000000000000000", "one quattuordecillion",
        "1000000000000000000000000000000000000000000000000", "one quindecillion",
        "1000000000000000000000000000000000000000000000000000", "one sedecillion",
        "1000000000000000000000000000000000000000000000000000000", "one septendecillion",
        "1000000000000000000000000000000000000000000000000000000000", "one octodecillion",
        "1000000000000000000000000000000000000000000000000000000000000", "one novendecillion",
        "1000000000000000000000000000000000000000000000000000000000000000", "one vigintillion",
        "1000000000000000000000000000000000000000000000000000000000000000000", "one thousand vigintillion",
        "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "one vigintillion vigintillion",
        "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "one vigintillion vigintillion vigintillion",
        "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "one centillion",
    };
    
    for (size_t i = 0, l = sizeof(data) / sizeof(std::string); i < l; i+=2) {
        std::cout << data[i] << "...";
        std::string result = e->process(data[i]);
        std::cout << result << " ";
        
        if (result.compare(data[i+1]) == 0) {
            std::cout << std::endl;
        } else {
            std::cout << "!= " << data[i+1] << std::endl;
            assert(false);
        }
    }
    
    std::cout << "ok" << std::endl;
}