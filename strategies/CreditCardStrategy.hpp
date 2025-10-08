#ifndef CREDITCARD_STRATEGY_HPP
#define CREDITCARD_STRATEGY_HPP

#include "PaymentStrategy.hpp"

class CreditCardStrategy : public PaymentStrategy {
public:
    std::string processPayment(double amount) const override;
    std::string getPaymentType() const override;
    
    // Credit cards have maximum transaction limits
    bool isValidAmount(double amount) const override;
    
private:
    static constexpr double MAX_AMOUNT = 10000.00;
    std::string formatAmount(double amount) const;
};

#endif // CREDITCARD_STRATEGY_HPP
