#include "CreditCardStrategy.hpp"
#include <sstream>
#include <iomanip>

// Complexity: 1 (simple string formatting)
std::string CreditCardStrategy::processPayment(double amount) const {
    return "Processing payment via Credit Card for " + formatAmount(amount) + ".";
    // Placeholder: Integrate Stripe/Braintree SDK
    // Example: stripe::Charge::create(token, amount);
}

// Complexity: 1 (return constant)
std::string CreditCardStrategy::getPaymentType() const {
    return "CreditCard";
}

// Complexity: 1 (compound comparison with && counts as 1 decision point)
bool CreditCardStrategy::isValidAmount(double amount) const {
    return amount > 0.0 && amount <= MAX_AMOUNT;
}

// Complexity: 1 (string formatting only)
std::string CreditCardStrategy::formatAmount(double amount) const {
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}
