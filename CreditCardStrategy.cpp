#include "strategies/CreditCardStrategy.hpp"
#include <sstream>
#include <iomanip>

std::string CreditCardStrategy::processPayment(double amount) const {
    std::ostringstream oss;
    oss << "Processing payment via Credit Card for " << formatAmount(amount) << ".";
    // Placeholder: Integrate Stripe/Braintree SDK
    // Example: stripe::Charge::create(token, amount);
    return oss.str();
}

std::string CreditCardStrategy::getPaymentType() const {
    return "CreditCard";
}

bool CreditCardStrategy::isValidAmount(double amount) const {
    return amount > 0.0 && amount <= MAX_AMOUNT;
}

std::string CreditCardStrategy::formatAmount(double amount) const {
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}
