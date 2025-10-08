#include "PaymentProcessor.hpp"
#include <sstream>
#include <stdexcept>

// Complexity: 2 (1 if + 1 base)
void PaymentProcessor::registerStrategy(const std::string& name, 
                                        std::shared_ptr<PaymentStrategy> strategy) {
    if (strategy == nullptr) {
        throw std::invalid_argument("Cannot register null strategy");
    }
    strategies_[name] = strategy;
}

// Complexity: 1 (early return pattern, delegates to helpers)
PaymentProcessor::ProcessingResult 
PaymentProcessor::checkout(const std::string& paymentMode, double amount) {
    // Early return pattern - each check is in separate method
    if (!isAmountPositive(amount)) {
        return createErrorResult("Payment amount must be positive");
    }
    
    if (!hasRegisteredStrategy(paymentMode)) {
        return createErrorResult(formatUnsupportedModeError(paymentMode));
    }
    
    auto strategy = strategies_[paymentMode];
    if (!isAmountValidForStrategy(strategy, amount)) {
        return createErrorResult(formatInvalidAmountError(paymentMode));
    }
    
    return processWithStrategy(strategy, amount);
}

// Complexity: 1 (single lookup)
bool PaymentProcessor::hasStrategy(const std::string& paymentMode) const {
    return strategies_.find(paymentMode) != strategies_.end();
}

// ========== Private Helper Methods ==========

// Complexity: 1 (single comparison)
bool PaymentProcessor::isAmountPositive(double amount) const {
    return amount > 0.0;
}

// Complexity: 1 (single lookup)
bool PaymentProcessor::hasRegisteredStrategy(const std::string& mode) const {
    return strategies_.find(mode) != strategies_.end();
}

// Complexity: 1 (single method call)
bool PaymentProcessor::isAmountValidForStrategy(
    const std::shared_ptr<PaymentStrategy>& strategy, double amount) const {
    return strategy->isValidAmount(amount);
}

// Complexity: 1 (simple construction)
PaymentProcessor::ProcessingResult 
PaymentProcessor::createErrorResult(const std::string& error) const {
    return ProcessingResult(false, "Error: " + error);
}

// Complexity: 1 (simple construction)
PaymentProcessor::ProcessingResult 
PaymentProcessor::createSuccessResult(const std::string& message) const {
    return ProcessingResult(true, message);
}

// Complexity: 2 (1 try-catch + 1 base)
PaymentProcessor::ProcessingResult 
PaymentProcessor::processWithStrategy(const std::shared_ptr<PaymentStrategy>& strategy,
                                      double amount) const {
    try {
        std::string confirmation = strategy->processPayment(amount);
        return createSuccessResult(confirmation);
    } catch (const std::exception& e) {
        return createErrorResult("Processing failed: " + std::string(e.what()));
    }
}

// Complexity: 1 (string formatting only)
std::string PaymentProcessor::formatUnsupportedModeError(const std::string& mode) const {
    return "Unsupported payment mode: '" + mode + "'";
}

// Complexity: 1 (string formatting only)
std::string PaymentProcessor::formatInvalidAmountError(const std::string& mode) const {
    return "Invalid amount for " + mode;
}
