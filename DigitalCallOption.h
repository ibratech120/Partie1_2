#pragma once
#include "DigitalOption.h"

class DigitalCallOption : public DigitalOption {
public:
    DigitalCallOption(double expiry, double strike) : DigitalOption(expiry, strike) {}
    virtual optionType GetOptionType() override {
        return optionType::call;
    }

    virtual double payoff(double S) override {
        return (S - getStrike() >= 0) ? 1 : 0;
    }
};