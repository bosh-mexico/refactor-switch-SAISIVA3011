#ifndef CREDITCARD_STRATEGY_HPP
#define CREDITCARD_STRATEGY_HPP

#include "PaymentStrategy.hpp"

/**
 * @brief Credit Card payment processing strategy
 * 
 * Implements credit card-specific payment logic with maximum transaction limits.
 * All methods maintain cyclomatic complexity <= 3.
 */
class CreditCardStrategy : public PaymentStrategy {
public:
    /**
     * @brief Process credit card payment
     * Complexity: 1 (string formatting only)
     */
    std::string processPayment(double amount) const override;
    
    /**
     * @brief Get payment type identifier
     * Complexity: 1 (return constant)
     */
    std::string getPaymentType() const override;
    
    /**
     * @brief Credit cards have a maximum transaction limit of $10,000
     * Complexity: 1 (compound comparison counts as 1 decision)
     */
    bool isValidAmount(double amount) const override;
    
private:
    static constexpr double MAX_AMOUNT = 10000.00;
    
    /**
     * @brief Format amount to currency string
     * Complexity: 1 (string formatting)
     */
    std::string formatAmount(double amount) const;
};

#endif // CREDITCARD_STRATEGY_HPP
