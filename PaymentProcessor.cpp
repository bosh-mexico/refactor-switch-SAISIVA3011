#include "PaymentProcessor.hpp"
#include <sstream>
#include <iomanip>

void PaymentProcessor::registerStrategy(const std::string& name, 
                                        std::shared_ptr<PaymentStrategy> strategy) {
    if (strategy == nullptr) {
        throw std::invalid_argument("Cannot register null strategy");
    }
    strategies_[name] = strategy;
}

PaymentProcessor::ProcessingResult 
PaymentProcessor::checkout(const std::string& paymentMode, double amount) {
    // Validate amount first
    if (!validateAmount(amount)) {
        return ProcessingResult(false, 
            formatErrorMessage("Payment amount must be positive"));
    }
    
    // Check if strategy exists
    auto it = strategies_.find(paymentMode);
    if (it == strategies_.end()) {
        std::ostringstream oss;
        oss << "Unsupported payment mode: '" << paymentMode << "'";
        return ProcessingResult(false, formatErrorMessage(oss.str()));
    }
    
    // Strategy-specific validation
    const auto& strategy = it->second;
    if (!strategy->isValidAmount(amount)) {
        return ProcessingResult(false, 
            formatErrorMessage("Invalid amount for " + paymentMode));
    }
    
    // Process payment
    try {
        std::string confirmation = strategy->processPayment(amount);
        return ProcessingResult(true, confirmation);
    } catch (const std::exception& e) {
        return ProcessingResult(false, 
            formatErrorMessage(std::string("Processing failed: ") + e.what()));
    }
}

bool PaymentProcessor::hasStrategy(const std::string& paymentMode) const {
    return strategies_.find(paymentMode) != strategies_.end();
}

bool PaymentProcessor::validateAmount(double amount) const {
    return amount > 0.0;
}

std::string PaymentProcessor::formatErrorMessage(const std::string& error) const {
    return "Error: " + error;
}
