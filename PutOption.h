#pragma once

#include "VanillaOption.h"

class PutOption : public VanillaOption {
public:
    PutOption(double expiry, double strike) : VanillaOption(expiry, strike) {
        if (expiry < 0 || strike < 0) {
            throw std::invalid_argument("Expiry date and price should be >0");
        }
    }

    virtual optionType GetOptionType() override {
        return optionType::put;
    }

    virtual double payoff(double S) override {
        return (getStrike() - S > 0) ? getStrike() - S : 0;
    }
};