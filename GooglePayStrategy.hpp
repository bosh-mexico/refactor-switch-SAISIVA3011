#ifndef GOOGLEPAY_STRATEGY_HPP
#define GOOGLEPAY_STRATEGY_HPP

#include "PaymentStrategy.hpp"

class GooglePayStrategy : public PaymentStrategy {
public:
    std::string processPayment(double amount) const override;
    std::string getPaymentType() const override;
    
private:
    std::string formatAmount(double amount) const;
};

#endif // GOOGLEPAY_STRATEGY_HPP
