#include <gtest/gtest.h>
#include "PaymentProcessor.hpp"
#include "PayPalStrategy.hpp"
#include "GooglePayStrategy.hpp"
#include "CreditCardStrategy.hpp"
#include "TestUtils.hpp"

// Test Fixture for PaymentProcessor
class PaymentProcessorTest : public ::testing::Test {
protected:
    PaymentProcessor processor;
};

// ========== Strategy Registration Tests ==========

TEST_F(PaymentProcessorTest, RegisterValidStrategy) {
    auto strategy = std::make_shared<PayPalStrategy>();
    EXPECT_NO_THROW(processor.registerStrategy("PayPal", strategy));
    EXPECT_TRUE(processor.hasStrategy("PayPal"));
}

TEST_F(PaymentProcessorTest, RegisterNullStrategyThrowsException) {
    EXPECT_THROW(
        processor.registerStrategy("Invalid", nullptr),
        std::invalid_argument
    );
}

TEST_F(PaymentProcessorTest, StrategyNotRegisteredInitially) {
    EXPECT_FALSE(processor.hasStrategy("PayPal"));
}

TEST_F(PaymentProcessorTest, RegisterMultipleStrategies) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    EXPECT_TRUE(processor.hasStrategy("PayPal"));
    EXPECT_TRUE(processor.hasStrategy("GooglePay"));
    EXPECT_TRUE(processor.hasStrategy("CreditCard"));
}

TEST_F(PaymentProcessorTest, OverrideExistingStrategy) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    EXPECT_TRUE(processor.hasStrategy("PayPal"));
    
    // Re-register with same name
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    EXPECT_TRUE(processor.hasStrategy("PayPal"));
}

// ========== Checkout Validation Tests ==========

TEST_F(PaymentProcessorTest, RejectNegativeAmount) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("PayPal", -10.0);
    
    EXPECT_FALSE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "positive"));
}

TEST_F(PaymentProcessorTest, RejectZeroAmount) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("PayPal", 0.0);
    
    EXPECT_FALSE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "positive"));
}

TEST_F(PaymentProcessorTest, AcceptValidPositiveAmount) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("PayPal", 100.50);
    
    EXPECT_TRUE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "PayPal"));
    EXPECT_TRUE(ContainsSubstring(result.message, "100.50"));
}

TEST_F(PaymentProcessorTest, AcceptSmallValidAmount) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("PayPal", 0.01);
    
    EXPECT_TRUE(result.success);
}

TEST_F(PaymentProcessorTest, AcceptLargeValidAmount) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("PayPal", 9999.99);
    
    EXPECT_TRUE(result.success);
}

// ========== Unsupported Payment Mode Tests ==========

TEST_F(PaymentProcessorTest, HandleUnknownPaymentModeGracefully) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("Bitcoin", 50.0);
    
    EXPECT_FALSE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "Unsupported"));
    EXPECT_TRUE(ContainsSubstring(result.message, "Bitcoin"));
}

TEST_F(PaymentProcessorTest, CaseSensitivePaymentModeNames) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("paypal", 50.0);  // lowercase
    
    EXPECT_FALSE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "Unsupported"));
}

TEST_F(PaymentProcessorTest, EmptyPaymentMode) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    auto result = processor.checkout("", 50.0);
    
    EXPECT_FALSE(result.success);
}

// ========== Multiple Strategy Support Tests ==========

TEST_F(PaymentProcessorTest, ProcessPayPalPayment) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto result = processor.checkout("PayPal", 100.00);
    EXPECT_TRUE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "PayPal"));
}

TEST_F(PaymentProcessorTest, ProcessGooglePayPayment) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto result = processor.checkout("GooglePay", 75.50);
    EXPECT_TRUE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "Google Pay"));
}

TEST_F(PaymentProcessorTest, ProcessCreditCardPayment) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto result = processor.checkout("CreditCard", 200.00);
    EXPECT_TRUE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "Credit Card"));
}

TEST_F(PaymentProcessorTest, MultipleSequentialTransactions) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("GooglePay", std::make_shared<GooglePayStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto r1 = processor.checkout("PayPal", 50.0);
    auto r2 = processor.checkout("GooglePay", 75.0);
    auto r3 = processor.checkout("CreditCard", 100.0);
    
    EXPECT_TRUE(r1.success);
    EXPECT_TRUE(r2.success);
    EXPECT_TRUE(r3.success);
}

// ========== Strategy-Specific Validation Tests ==========

TEST_F(PaymentProcessorTest, PayPalMinimumAmountValidation) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto result = processor.checkout("PayPal", 0.001);
    EXPECT_FALSE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "Invalid amount"));
}

TEST_F(PaymentProcessorTest, CreditCardMaximumAmountValidation) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto result = processor.checkout("CreditCard", 10000.01);
    EXPECT_FALSE(result.success);
    EXPECT_TRUE(ContainsSubstring(result.message, "Invalid amount"));
}

TEST_F(PaymentProcessorTest, CreditCardAtMaximumLimitSucceeds) {
    processor.registerStrategy("PayPal", std::make_shared<PayPalStrategy>());
    processor.registerStrategy("CreditCard", std::make_shared<CreditCardStrategy>());
    
    auto result = processor.checkout("CreditCard", 10000.00);
    EXPECT_TRUE(result.success);
}
