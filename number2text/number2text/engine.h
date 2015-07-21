//
//  engine.h
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#ifndef __number2text__engine__
#define __number2text__engine__

#include <string>
#include <vector>

class Engine {

public:
    std::string input(int argc, const char * argv[]);
    std::string process(std::string number);

protected:
    virtual void doOne(std::vector<std::string> &results, size_t offset, std::string number) = 0;
    virtual void doTwo(std::vector<std::string> &results, size_t offset, std::string number) = 0;
    virtual void doThree(std::vector<std::string> &results, size_t offset, std::string number) = 0;
    virtual void doUnit(std::vector<std::string> &results, size_t offset, std::string text) = 0;
    virtual std::string doAnd(std::string results, std::string lastResult) = 0;
    
    std::string implode(std::vector<std::string> &vector);
    
private:
    bool verifyInput(std::string input);

};

#endif /* defined(__number2text__engine__) */
