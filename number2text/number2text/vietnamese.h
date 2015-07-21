//
//  vietnamese.h
//  number2text
//
//  Created by Dao Hoang Son on 7/21/15.
//  Copyright (c) 2015 daohoangson. All rights reserved.
//

#ifndef __number2text__vietnamese__
#define __number2text__vietnamese__

#include "engine.h"

class Vietnamese: public Engine {
    
protected:
    virtual void doOne(std::vector<std::string> &results, size_t offset, std::string number) override;
    virtual void doTwo(std::vector<std::string> &results, size_t offset, std::string number) override;
    virtual void doThree(std::vector<std::string> &results, size_t offset, std::string number) override;
    virtual void doUnit(std::vector<std::string> &results, size_t offset, std::string text) override;
    virtual std::string doAnd(std::string results, std::string lastResult) override;
    
private:
    void doTwoSimple(std::vector<std::string> &tmp, std::string lastDigit);
    void doTwoSpecial(std::vector<std::string> &tmp, std::string lastDigit);
    
};

#endif /* defined(__number2text__vietnamese__) */
