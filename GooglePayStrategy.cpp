#include "GooglePayStrategy.hpp"
#include <sstream>
#include <iomanip>

// Complexity: 1 (simple string formatting)
std::string GooglePayStrategy::processPayment(double amount) const {
    return "Processing payment via Google Pay for " + formatAmount(amount) + ".";
    // Placeholder: Integrate Google Pay API
    // Example: PaymentDataRequest request; gpay.loadPaymentData(request);
}

// Complexity: 1 (return constant)
std::string GooglePayStrategy::getPaymentType() const {
    return "GooglePay";
}

// Complexity: 1 (string formatting only)
std::string GooglePayStrategy::formatAmount(double amount) const {
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}
