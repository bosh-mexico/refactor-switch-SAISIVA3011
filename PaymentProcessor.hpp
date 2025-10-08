#ifndef PAYMENT_PROCESSOR_HPP
#define PAYMENT_PROCESSOR_HPP

#include "PaymentStrategy.hpp"
#include <memory>
#include <unordered_map>
#include <string>

class PaymentProcessor {
public:
    // Result structure for better error handling
    struct ProcessingResult {
        bool success;
        std::string message;
        
        ProcessingResult(bool s, const std::string& m) 
            : success(s), message(m) {}
    };

    PaymentProcessor() = default;
    ~PaymentProcessor() = default;

    // Register a payment strategy (Open/Closed Principle)
    void registerStrategy(const std::string& name, 
                         std::shared_ptr<PaymentStrategy> strategy);
    
    // Process payment using registered strategy
    ProcessingResult checkout(const std::string& paymentMode, double amount);
    
    // Check if strategy is registered
    bool hasStrategy(const std::string& paymentMode) const;

private:
    std::unordered_map<std::string, std::shared_ptr<PaymentStrategy>> strategies_;
    
    // Helper methods for validation
    bool validateAmount(double amount) const;
    std::string formatErrorMessage(const std::string& error) const;
};

#endif // PAYMENT_PROCESSOR_HPP
