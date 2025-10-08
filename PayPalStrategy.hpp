#ifndef PAYPAL_STRATEGY_HPP
#define PAYPAL_STRATEGY_HPP

#include "PaymentStrategy.hpp"

/**
 * @brief PayPal payment processing strategy
 * 
 * Implements PayPal-specific payment logic with minimum transaction validation.
 * All methods maintain cyclomatic complexity <= 3.
 */
class PayPalStrategy : public PaymentStrategy {
public:
    /**
     * @brief Process PayPal payment
     * Complexity: 1 (string formatting only)
     */
    std::string processPayment(double amount) const override;
    
    /**
     * @brief Get payment type identifier
     * Complexity: 1 (return constant)
     */
    std::string getPaymentType() const override;
    
    /**
     * @brief PayPal has a minimum transaction amount of $0.01
     * Complexity: 1 (single comparison)
     */
    bool isValidAmount(double amount) const override;
    
private:
    static constexpr double MIN_AMOUNT = 0.01;
    
    /**
     * @brief Format amount to currency string
     * Complexity: 1 (string formatting)
     */
    std::string formatAmount(double amount) const;
};

#endif // PAYPAL_STRATEGY_HPP
