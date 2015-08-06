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
#include "spanish.h"
#include "vietnamese.h"

void testData(Engine *e, std::string testName, std::string data[], size_t testCount) {
    for (size_t i = 0; i < testCount; i+=2) {
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
    
    std::cout << testName << " (" << testCount << " test cases) ok" << std::endl;
}

void testEnglish() {
    English *e = new English();
    
    std::string data[] = {
        "0", "zero",
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
    
    testData(e, "English", data, sizeof(data) / sizeof(std::string));
}

void testSpanish() {
    Spanish *e = new Spanish();
    
    // http://www.studyspanish.com/lessons/cardnum3.htm
    std::string data[] = {
        "0", "cero",
        "1", "uno",
        "2", "dos",
        "3", "tres",
        "4", "cuatro",
        "5", "cinco",
        "6", "seis",
        "7", "siete",
        "8", "ocho",
        "9", "nueve",
        "01", "uno",
        "10", "diez",
        "11", "once",
        "12", "doce",
        "13", "trece",
        "14", "catorce",
        "15", "quince",
        "16", "dieciséis",
        "17", "diecisiete",
        "18", "dieciocho",
        "19", "diecinueve",
        "20", "veinte",
        "21", "veintiuno",
        "22", "veintidós",
        "23", "veintitrés",
        "24", "veinticuatro",
        "25", "veinticinco",
        "26", "veintiséis",
        "27", "veintisiete",
        "28", "veintiocho",
        "29", "veintinueve",
        "30", "treinta",
        "31", "treinta y uno",
        "40", "cuarenta",
        "50", "cincuenta",
        "60", "sesenta",
        "70", "setenta",
        "80", "ochenta",
        "90", "noventa",
        "001", "uno",
        "100", "cien",
        "101", "ciento uno",
        "200", "doscientos",
        "300", "trescientos",
        "400", "cuatrocientos",
        "500", "quinientos",
        "600", "seiscientos",
        "700", "setecientos",
        "800", "ochocientos",
        "900", "novecientos",
        "1000", "mil",
        "2000", "dos mil",
        "10000", "diez mil",
        "100000", "cien mil",
        "1000000", "un millón",
        "2000000", "dos millones",
        "1000000000", "un billón",
        "2000000000", "dos billones",
        "1000000000000", "un trillón",
        "2000000000000", "dos trillones",
    };
    
    testData(e, "Spanish", data, sizeof(data) / sizeof(std::string));
}

void testVietnamese() {
    Vietnamese *e = new Vietnamese();
    
    std::string data[] = {
        "0", "không",
        "1", "một",
        "2", "hai",
        "3", "ba",
        "4", "bốn",
        "5", "năm",
        "6", "sáu",
        "7", "bảy",
        "8", "tám",
        "9", "chín",
        "10", "mười",
        "11", "mười một",
        "20", "hai mươi",
        "21", "hai mốt",
        "22", "hai hai",
        "24", "hai tư",
        "25", "hai lăm",
        "100", "một trăm",
        "101", "một trăm lẻ một",
        "1000", "một nghìn",
        "10000", "mười nghìn",
        "100000", "một trăm nghìn",
        "1000000", "một triệu",
        "1000000000", "một tỉ",
    };
    
    testData(e, "Vietnamese", data, sizeof(data) / sizeof(std::string));
}