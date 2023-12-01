#pragma once

#include "BlackScholesPricer.h"
#include "Option.h"
#include "VanillaOption.h"
#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class CRRPricer {
private:
    Option* _option;
    int _depth;
    double _assetPrice, _up, _down, _interestRate;
    BinaryTree<double> _priceTree;

    void checkArbitrage() {
        if (_up <= -1 || _down <= -1 || _up <= _down || (exp(_interestRate) - 1) <= _down || (exp(_interestRate) - 1) >= _up) {
            throw std::invalid_argument("Arbitrage condition violated");
        }
    }

    void buildTree() {
        _priceTree.setDepth(_depth);
        for (int i = 0; i <= _depth; ++i) {
            for (int j = 0; j <= i; ++j) {
                double stockPrice = _assetPrice * pow(1 + _up, j) * pow(1 + _down, i - j);
                _priceTree.setNode(i, j, stockPrice);
            }
        }
    }

    double optionValueAtNode(int n, int i) {
        double stockPrice = _priceTree.getNode(n, i);
        return _option->payoff(stockPrice);
    }

public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
        : _option(option), _depth(depth), _assetPrice(asset_price), _up(up), _down(down), _interestRate(interest_rate) {
        checkArbitrage();
        buildTree();
    }

    void compute() {
        double q = (exp(_interestRate) - 1 - _down) / (_up - _down);
        for (int i = _depth; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                if (i == _depth) {
                    _priceTree.setNode(i, j, optionValueAtNode(i, j));
                }
                else {
                    double discountedValue = (q * _priceTree.getNode(i + 1, j + 1) + (1 - q) * _priceTree.getNode(i + 1, j)) / (1 + _interestRate);
                    _priceTree.setNode(i, j, discountedValue);
                }
            }
        }
    }

    double get(int n, int i) const {
        return _priceTree.getNode(n, i);
    }

    // N is the standard normal PDF
    double N(double x) const {

        return 0.5 * (1.0 + erf(x / sqrt(2.0)));
    }

    double operator()(bool closed_form = false, double volatility = 0.0) {
        VanillaOption* vanillaOption = dynamic_cast<VanillaOption*>(_option);
        if (!vanillaOption) {
            throw std::invalid_argument("Option must be a VanillaOption");
        }

        if (closed_form) {
            double T = vanillaOption->getExpiry();
            double K = vanillaOption->getStrike();
            double S = _assetPrice;
            double r = _interestRate;
            double sigma = volatility;

            double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
            double d2 = d1 - sigma * sqrt(T);

            if (vanillaOption->GetOptionType()==optionType::call) {
                return S * N(d1) - K * exp(-r * T) * N(d2);
            }
            else {
                return K * exp(-r * T) * N(-d2) - S * N(-d1);
            }
        }
        else {
            compute();
            return get(0, 0);
        }
    }

};