#pragma once


class Option {
private:
    double _expiry;

public:
    Option(double expiry) : _expiry(expiry) {}

    double getExpiry() {
        return _expiry;
    }

    virtual double payoff(double S) = 0;

};

