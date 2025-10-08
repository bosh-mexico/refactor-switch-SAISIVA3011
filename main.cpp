#include <iostream>
#include "PaymentProcessor.hpp"
#include "PayPalStrategy.hpp"
#include "GooglePayStrategy.hpp"
#include "CreditCardStrategy.hpp"

// Complexity: 2 (1 if + 1 base)
void printResult(const PaymentProcessor::ProcessingResult& result) {
    if (result.success) {
        std::cout << "✓ " << result.message << std::endl;
    } else {
        std::cerr << "✗ " << result.message << std::endl;
    }
}

// Complexity: 1 (no branching, sequential calls)
void registerStrategies(PaymentProcessor& processor) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
}

// Complexity: 1 (sequential operations only)
void printHeader() {
    std::cout << "=== Payment Processing System ===" << std::endl;
    std::cout << "Demonstrating Clean Code & SOLID Principles\n" << std::endl;
}

// Complexity: 1 (sequential operations only)
void demonstrateSuccessfulTransactions(PaymentProcessor& processor) {
    std::cout << "Processing transactions:\n" << std::endl;
    
    std::cout << "1. PayPal Payment:" << std::endl;
    printResult(processor.checkout("PayPal", 100.50));
    std::cout << std::endl;
    
    std::cout << "2. Google Pay Payment:" << std::endl;
    printResult(processor.checkout("GooglePay", 75.00));
    std::cout << std::endl;
    
    std::cout << "3. Credit Card Payment:" << std::endl;
    printResult(processor.checkout("CreditCard", 250.75));
    std::cout << std::endl;
}

// Complexity: 1 (sequential operations only)
void demonstrateErrorHandling(PaymentProcessor& processor) {
    std::cout << "Demonstrating error handling:\n" << std::endl;
    
    std::cout << "4. Unsupported Payment Method (Bitcoin):" << std::endl;
    printResult(processor.checkout("Bitcoin", 50.00));
    std::cout << std::endl;
    
    std::cout << "5. Invalid Amount (Negative):" << std::endl;
    printResult(processor.checkout("PayPal", -10.00));
    std::cout << std::endl;
    
    std::cout << "6. Invalid Amount (Zero):" << std::endl;
    printResult(processor.checkout("GooglePay", 0.00));
    std::cout << std::endl;
    
    std::cout << "7. Credit Card Exceeding Limit:" << std::endl;
    printResult(processor.checkout("CreditCard", 15000.00));
    std::cout << std::endl;
    
    std::cout << "8. PayPal Below Minimum:" << std::endl;
    printResult(processor.checkout("PayPal", 0.001));
    std::cout << std::endl;
}

// Complexity: 1 (sequential orchestration)
int main() {
    printHeader();
    
    PaymentProcessor processor;
    
    std::cout << "Registering payment strategies..." << std::endl;
    registerStrategies(processor);
    std::cout << "Registration complete!\n" << std::endl;
    
    demonstrateSuccessfulTransactions(processor);
    demonstrateErrorHandling(processor);
    
    std::cout << "=== Demo Complete ===" << std::endl;
    
    return 0;
}
