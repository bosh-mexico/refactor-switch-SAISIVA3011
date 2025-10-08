#ifndef PAYPAL_STRATEGY_HPP
#define PAYPAL_STRATEGY_HPP

#include "PaymentStrategy.hpp"

class PayPalStrategy : public PaymentStrategy {
public:
    std::string processPayment(double amount) const override;
    std::string getPaymentType() const override;
    
    // PayPal has minimum transaction amount
    bool isValidAmount(double amount) const override;
    
private:
    static constexpr double MIN_AMOUNT = 0.01;
    std::string formatAmount(double amount) const;
};

#endif // PAYPAL_STRATEGY_HPP
