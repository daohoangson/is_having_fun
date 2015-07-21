//
//  main.cpp
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#include <iostream>
#include "english.h"
#include "tests.h"

int main(int argc, const char * argv[]) {
    if (argc == 2 && strcmp(argv[1], "test") == 0) {
        testEnglish();
        return 0;
    }
    
    Engine *engine = new English();
    std::string number = engine->input(argc, argv);
    
    std::string text = engine->process(number);
    std::cout << text << std::endl;
    
    return 0;
}
