#include "strategies/PayPalStrategy.hpp"
#include <sstream>
#include <iomanip>

// Complexity: 1 (simple string formatting)
std::string PayPalStrategy::processPayment(double amount) const {
    return "Processing payment via PayPal for " + formatAmount(amount) + ".";
    // Placeholder: Integrate PayPal REST API
    // Example: paypal::Payment payment; payment.create(apiContext);
}

// Complexity: 1 (return constant)
std::string PayPalStrategy::getPaymentType() const {
    return "PayPal";
}

// Complexity: 1 (single comparison)
bool PayPalStrategy::isValidAmount(double amount) const {
    return amount >= MIN_AMOUNT;
}

// Complexity: 1 (string formatting only)
std::string PayPalStrategy::formatAmount(double amount) const {
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}
