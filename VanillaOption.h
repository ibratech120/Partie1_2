#pragma once


#include "Option.h"

enum class optionType { call, put };

class VanillaOption : public Option {
private:
    double _strike;

public:

    VanillaOption(double expiry, double strike) : Option(expiry), _strike(strike) {
        if (expiry < 0 || strike < 0) {
            throw std::invalid_argument("The date and price should be >0");
        }
    }

    // Méthode virtuelle pure pour obtenir le type d'option (call ou put)
    virtual optionType GetOptionType() = 0;

    double getStrike() const {
        return _strike;
    }
};

