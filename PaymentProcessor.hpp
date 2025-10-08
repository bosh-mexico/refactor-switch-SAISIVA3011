#ifndef PAYMENT_PROCESSOR_HPP
#define PAYMENT_PROCESSOR_HPP

#include "PaymentStrategy.hpp"
#include <memory>
#include <unordered_map>
#include <string>

/**
 * @brief Central payment processing system
 * 
 * All functions maintain cyclomatic complexity <= 3 for maintainability.
 * Follows Dependency Inversion Principle by depending on PaymentStrategy abstraction.
 */
class PaymentProcessor {
public:
    /**
     * @brief Result structure for payment operations
     */
    struct ProcessingResult {
        bool success;
        std::string message;
        
        ProcessingResult(bool s, const std::string& m) 
            : success(s), message(m) {}
    };

    PaymentProcessor() = default;
    ~PaymentProcessor() = default;

    // Prevent copying
    PaymentProcessor(const PaymentProcessor&) = delete;
    PaymentProcessor& operator=(const PaymentProcessor&) = delete;

    /**
     * @brief Register a payment strategy
     * @param name Unique identifier for the payment method
     * @param strategy Shared pointer to the strategy implementation
     * @throws std::invalid_argument if strategy is null
     * Complexity: 2 (1 if + 1 base path)
     */
    void registerStrategy(const std::string& name, 
                         std::shared_ptr<PaymentStrategy> strategy);
    
    /**
     * @brief Process a payment using registered strategy
     * @param paymentMode The payment method to use
     * @param amount The payment amount
     * @return ProcessingResult with success status and message
     * Complexity: 3 (amount check + strategy check + delegate)
     */
    ProcessingResult checkout(const std::string& paymentMode, double amount);
    
    /**
     * @brief Check if a payment strategy is registered
     * @param paymentMode The payment method name
     * @return true if registered, false otherwise
     * Complexity: 1 (single lookup operation)
     */
    bool hasStrategy(const std::string& paymentMode) const;

private:
    std::unordered_map<std::string, std::shared_ptr<PaymentStrategy>> strategies_;
    
    // Validation helpers - Complexity: 1 each
    bool isAmountPositive(double amount) const;
    bool hasRegisteredStrategy(const std::string& mode) const;
    
    // Processing helper - Complexity: 2 (validation + processing)
    ProcessingResult processStrategyPayment(const std::string& paymentMode, double amount);
    
    // Result creation helpers - Complexity: 1 each
    ProcessingResult createErrorResult(const std::string& error) const;
    ProcessingResult createSuccessResult(const std::string& message) const;
    ProcessingResult processWithStrategy(const std::shared_ptr<PaymentStrategy>& strategy,
                                        double amount) const;
    
    // Error formatting helpers - Complexity: 1 each
    std::string formatUnsupportedModeError(const std::string& mode) const;
    std::string formatInvalidAmountError(const std::string& mode) const;
};

#endif // PAYMENT_PROCESSOR_HPP
