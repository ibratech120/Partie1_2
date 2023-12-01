#pragma once


#include "VanillaOption.h"

class CallOption : public VanillaOption {
public:
    CallOption(double expiry, double strike) : VanillaOption(expiry, strike) {
        if (expiry < 0 || strike < 0) {
            throw std::invalid_argument("Expiry date and price should be >0");
        }
    }

    virtual optionType GetOptionType() override {
        return optionType::call;
    }

    virtual double payoff(double S) override {
        return (S - getStrike() > 0) ? S - getStrike() : 0;
    }
};