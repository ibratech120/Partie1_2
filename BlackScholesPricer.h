#pragma once
#include "VanillaOption.h"
#include <cmath>
#include "DigitalOption.h"



class BlackScholesPricer {
private:
    VanillaOption* option;


public:
    double S;      // Asset price
    double r;      // Interest rate
    double sigma;  // Volatility

    BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility)
        : option(option), S(asset_price), r(interest_rate), sigma(volatility) {}

    friend class VanillaOption;

    double operator()() const {
        double K = option->getStrike();
        double T = option->getExpiry();

        double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
        double d2 = d1 - sigma * sqrt(T);

        double N_d1 = N(d1);
        double N_d2 = N(d2);
        if (dynamic_cast<DigitalOption*>(option)) {
            if (option->GetOptionType() == optionType::call) {
                return exp(-r * T) * N(d2);
            }
            else {
                return exp(-r * T) * N(-d2);
            }
        }
        else {
            if (option->GetOptionType() == optionType::call) {
                return S * N_d1 - K * exp(-r * T) * N_d2;
            }
            else {
                return K * exp(-r * T) * (1.0 - N_d2) - S * (1.0 - N_d1);
            }
        }
    }
    // N is the standard normal PDF
    double N(double x) const {

        return 0.5 * (1.0 + erf(x / sqrt(2.0)));
    }

    // Method delta() to calculate the Delta of the option
    double delta() const {
        double K = option->getStrike();
        double T = option->getExpiry();
        double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));

        if (option->GetOptionType() == optionType::call) {
            return exp(-r * T) * N(d1);
        }
        else {
            return exp(-r * T) * (N(d1) - 1.0);
        }
    }
};