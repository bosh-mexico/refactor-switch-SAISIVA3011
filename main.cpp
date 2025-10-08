#include <iostream>
#include "PaymentProcessor.hpp"
#include "PayPalStrategy.hpp"
#include "GooglePayStrategy.hpp"
#include "CreditCardStrategy.hpp"

int main() {
    PaymentProcessor processor;
    
    // Register all available payment strategies
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    // Example transactions
    auto result1 = processor.checkout("PayPal", 100.50);
    std::cout << result1.message << std::endl;
    
    auto result2 = processor.checkout("GooglePay", 75.00);
    std::cout << result2.message << std::endl;
    
    auto result3 = processor.checkout("CreditCard", 250.75);
    std::cout << result3.message << std::endl;
    
    // Error handling example
    auto result4 = processor.checkout("Bitcoin", 50.00);
    std::cout << result4.message << std::endl;
    
    return 0;
}
