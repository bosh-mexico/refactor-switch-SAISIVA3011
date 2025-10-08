#include "strategies/GooglePayStrategy.hpp"
#include <sstream>
#include <iomanip>

std::string GooglePayStrategy::processPayment(double amount) const {
    std::ostringstream oss;
    oss << "Processing payment via Google Pay for " << formatAmount(amount) << ".";
    // Placeholder: Integrate Google Pay API
    // Example: PaymentDataRequest request; gpay.loadPaymentData(request);
    return oss.str();
}

std::string GooglePayStrategy::getPaymentType() const {
    return "GooglePay";
}

std::string GooglePayStrategy::formatAmount(double amount) const {
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}
