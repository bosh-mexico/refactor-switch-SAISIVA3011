#ifndef PAYMENT_STRATEGY_HPP
#define PAYMENT_STRATEGY_HPP

#include <string>

/**
 * @brief Abstract base class for payment processing strategies
 * 
 * This class defines the contract that all payment methods must implement.
 * Following Open/Closed Principle - open for extension, closed for modification.
 */
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    
    /**
     * @brief Process a payment transaction
     * @param amount The payment amount to process
     * @return Confirmation message with transaction details
     */
    virtual std::string processPayment(double amount) const = 0;
    
    /**
     * @brief Validate if the amount is acceptable for this payment method
     * @param amount The amount to validate
     * @return true if valid, false otherwise
     * Complexity: 1 (default implementation)
     */
    virtual bool isValidAmount(double amount) const {
        return amount > 0.0;
    }
    
    /**
     * @brief Get the payment type identifier
     * @return String identifier for the payment type
     */
    virtual std::string getPaymentType() const = 0;
};

#endif // PAYMENT_STRATEGY_HPP
