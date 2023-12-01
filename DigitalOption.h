#pragma once
#include <stdexcept>
#include "VanillaOption.h"



class DigitalOption : public VanillaOption {
private:
    double _strike;

public:
    DigitalOption(double expiry, double strike) : VanillaOption(expiry, strike), _strike(strike) {
        if (expiry < 0 || strike < 0) {
            throw std::invalid_argument("The date and price should be >0");
        }
    }
    virtual optionType GetOptionType() = 0;

    double getStrike() const {
        return _strike;
    }
};
