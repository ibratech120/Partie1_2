#pragma once
#pragma once

#include "DigitalOption.h"

class DigitalPutOption : public DigitalOption {
public:
    DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike) {}

    virtual optionType GetOptionType() override {
        return optionType::put;
    }

    virtual double payoff(double S) override {
        return (getStrike() - S <= 0) ? 1 : 0;
    }
};
