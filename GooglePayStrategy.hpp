#ifndef GOOGLEPAY_STRATEGY_HPP
#define GOOGLEPAY_STRATEGY_HPP

#include "PaymentStrategy.hpp"

/**
 * @brief Google Pay payment processing strategy
 * 
 * Implements Google Pay-specific payment logic.
 * All methods maintain cyclomatic complexity <= 3.
 */
class GooglePayStrategy : public PaymentStrategy {
public:
    /**
     * @brief Process Google Pay payment
     * Complexity: 1 (string formatting only)
     */
    std::string processPayment(double amount) const override;
    
    /**
     * @brief Get payment type identifier
     * Complexity: 1 (return constant)
     */
    std::string getPaymentType() const override;
    
private:
    /**
     * @brief Format amount to currency string
     * Complexity: 1 (string formatting)
     */
    std::string formatAmount(double amount) const;
};

#endif // GOOGLEPAY_STRATEGY_HPP
