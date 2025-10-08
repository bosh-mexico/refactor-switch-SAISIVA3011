#ifndef PAYMENT_STRATEGY_HPP
#define PAYMENT_STRATEGY_HPP

#include <string>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    
    // Process payment and return confirmation message
    virtual std::string processPayment(double amount) const = 0;
    
    // Validate payment amount (can be overridden for specific validations)
    virtual bool isValidAmount(double amount) const {
        return amount > 0.0;
    }
    
    // Get payment type identifier
    virtual std::string getPaymentType() const = 0;
};

#endif // PAYMENT_STRATEGY_HPP
