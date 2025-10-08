#include "strategies/PayPalStrategy.hpp"
#include <sstream>
#include <iomanip>

std::string PayPalStrategy::processPayment(double amount) const {
    std::ostringstream oss;
    oss << "Processing payment via PayPal for " << formatAmount(amount) << ".";
    // Placeholder: Integrate PayPal REST API
    // Example: paypal::Payment payment; payment.create(apiContext);
    return oss.str();
}

std::string PayPalStrategy::getPaymentType() const {
    return "PayPal";
}

bool PayPalStrategy::isValidAmount(double amount) const {
    return amount >= MIN_AMOUNT;
}

std::string PayPalStrategy::formatAmount(double amount) const {
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}
