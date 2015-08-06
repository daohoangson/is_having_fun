//
//  spanish.h
//  number2text
//
//  Created by Son Dao on 8/6/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#ifndef __number2text__spanish__
#define __number2text__spanish__

#include "engine.h"

class Spanish: public Engine {

protected:
    virtual std::string doZero() override;
    virtual void doOne(std::vector<std::string> &results, size_t offset, std::string number) override;
    virtual void doTwo(std::vector<std::string> &results, size_t offset, std::string number) override;
    virtual void doThree(std::vector<std::string> &results, size_t offset, std::string number) override;
    virtual void doUnit(std::vector<std::string> &results, size_t offset, std::string text) override;
    virtual std::string doAnd(std::string results, std::string lastResult) override;

private:
    std::string makeTwo(std::string firstDigitText, std::string lastDigit);
    std::string makeThree(std::string firstDigitText, std::string lastTwoDigits);

};

#endif /* defined(__number2text__spanish__) */
