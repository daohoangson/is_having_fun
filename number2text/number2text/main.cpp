//
//  main.cpp
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include <iostream>
#include "english.h"
#include "vietnamese.h"
#include "tests.h"

int main(int argc, const char * argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "test") == 0) {
            // run simple tests
            // I really should use GoogleTest...
            testEnglish();
            testVietnamese();
            return 0;
        }
    }
    
    Engine *engine = nullptr;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "vietnamese") == 0) {
            // use Vietnamese if specified via command line argument
            engine = new Vietnamese();
        }
    }
    if (engine == nullptr) {
        // fallback to English
        engine = new English();
    }
    
    std::string number = engine->input(argc, argv);
    std::string text = engine->process(number);
    std::cout << text << std::endl;
    
    return 0;
}
