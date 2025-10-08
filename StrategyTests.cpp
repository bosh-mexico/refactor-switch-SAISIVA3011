#include <gtest/gtest.h>
#include "PayPalStrategy.hpp"
#include "GooglePayStrategy.hpp"
#include "CreditCardStrategy.hpp"
#include "TestUtils.hpp"

// ========== PayPalStrategy Tests ==========

TEST(PayPalStrategyTest, FormatMessageCorrectly) {
    PayPalStrategy strategy;
    std::string result = strategy.processPayment(100.50);
    
    EXPECT_TRUE(ContainsSubstring(result, "PayPal"));
    EXPECT_TRUE(ContainsSubstring(result, "$100.50"));
}

TEST(PayPalStrategyTest, ReturnCorrectPaymentType) {
    PayPalStrategy strategy;
    EXPECT_EQ(strategy.getPaymentType(), "PayPal");
}

TEST(PayPalStrategyTest, ValidateMinimumAmount) {
    PayPalStrategy strategy;
    
    EXPECT_TRUE(strategy.isValidAmount(0.01));
    EXPECT_FALSE(strategy.isValidAmount(0.001));
    EXPECT_FALSE(strategy.isValidAmount(0.009));
}

TEST(PayPalStrategyTest, AcceptNormalAmounts) {
    PayPalStrategy strategy;
    
    EXPECT_TRUE(strategy.isValidAmount(1.0));
    EXPECT_TRUE(strategy.isValidAmount(100.0));
    EXPECT_TRUE(strategy.isValidAmount(9999.99));
}

TEST(PayPalStrategyTest, FormatVariousAmountsCorrectly) {
    PayPalStrategy strategy;
    
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(0.01), "$0.01"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(1.00), "$1.00"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(99.99), "$99.99"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(1234.56), "$1234.56"));
}

// ========== GooglePayStrategy Tests ==========

TEST(GooglePayStrategyTest, FormatMessageCorrectly) {
    GooglePayStrategy strategy;
    std::string result = strategy.processPayment(75.25);
    
    EXPECT_TRUE(ContainsSubstring(result, "Google Pay"));
    EXPECT_TRUE(ContainsSubstring(result, "$75.25"));
}

TEST(GooglePayStrategyTest, ReturnCorrectPaymentType) {
    GooglePayStrategy strategy;
    EXPECT_EQ(strategy.getPaymentType(), "GooglePay");
}

TEST(GooglePayStrategyTest, UseDefaultValidation) {
    GooglePayStrategy strategy;
    
    EXPECT_TRUE(strategy.isValidAmount(0.01));
    EXPECT_TRUE(strategy.isValidAmount(100.0));
    EXPECT_TRUE(strategy.isValidAmount(10000.0));
}

TEST(GooglePayStrategyTest, FormatVariousAmountsCorrectly) {
    GooglePayStrategy strategy;
    
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(0.50), "$0.50"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(50.00), "$50.00"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(999.99), "$999.99"));
}

// ========== CreditCardStrategy Tests ==========

TEST(CreditCardStrategyTest, FormatMessageCorrectly) {
    CreditCardStrategy strategy;
    std::string result = strategy.processPayment(500.00);
    
    EXPECT_TRUE(ContainsSubstring(result, "Credit Card"));
    EXPECT_TRUE(ContainsSubstring(result, "$500.00"));
}

TEST(CreditCardStrategyTest, ReturnCorrectPaymentType) {
    CreditCardStrategy strategy;
    EXPECT_EQ(strategy.getPaymentType(), "CreditCard");
}

TEST(CreditCardStrategyTest, ValidateMaximumTransactionLimit) {
    CreditCardStrategy strategy;
    
    EXPECT_TRUE(strategy.isValidAmount(10000.00));
    EXPECT_FALSE(strategy.isValidAmount(10000.01));
    EXPECT_FALSE(strategy.isValidAmount(15000.00));
}

TEST(CreditCardStrategyTest, AcceptAmountsWithinLimit) {
    CreditCardStrategy strategy;
    
    EXPECT_TRUE(strategy.isValidAmount(0.01));
    EXPECT_TRUE(strategy.isValidAmount(5000.00));
    EXPECT_TRUE(strategy.isValidAmount(9999.99));
}

TEST(CreditCardStrategyTest, RejectBoundaryViolations) {
    CreditCardStrategy strategy;
    
    EXPECT_FALSE(strategy.isValidAmount(10001.00));
    EXPECT_FALSE(strategy.isValidAmount(20000.00));
}

TEST(CreditCardStrategyTest, FormatVariousAmountsCorrectly) {
    CreditCardStrategy strategy;
    
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(100.00), "$100.00"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(5000.00), "$5000.00"));
    EXPECT_TRUE(ContainsSubstring(strategy.processPayment(9999.99), "$9999.99"));
}

// ========== Polymorphism Tests ==========

TEST(StrategyPolymorphismTest, AllStrategiesWorkThroughBasePointer) {
    std::shared_ptr<PaymentStrategy> strategies[] = {
        std::make_shared<PayPalStrategy>(),
        std::make_shared<GooglePayStrategy>(),
        std::make_shared<CreditCardStrategy>()
    };
    
    for (const auto& strategy : strategies) {
        EXPECT_FALSE(strategy->getPaymentType().empty());
        EXPECT_TRUE(strategy->isValidAmount(100.0));
        std::string result = strategy->processPayment(100.0);
        EXPECT_TRUE(ContainsSubstring(result, "Processing payment"));
    }
}

TEST(StrategyPolymorphismTest, EachStrategyHasUniquePaymentType) {
    PayPalStrategy paypal;
    GooglePayStrategy googlepay;
    CreditCardStrategy creditcard;
    
    EXPECT_NE(paypal.getPaymentType(), googlepay.getPaymentType());
    EXPECT_NE(googlepay.getPaymentType(), creditcard.getPaymentType());
    EXPECT_NE(creditcard.getPaymentType(), paypal.getPaymentType());
}

TEST(StrategyPolymorphismTest, StrategiesMaintainIndependentState) {
    auto strategy1 = std::make_shared<PayPalStrategy>();
    auto strategy2 = std::make_shared<PayPalStrategy>();
    
    // Process payments independently
    std::string result1 = strategy1->processPayment(50.0);
    std::string result2 = strategy2->processPayment(100.0);
    
    EXPECT_TRUE(ContainsSubstring(result1, "$50.00"));
    EXPECT_TRUE(ContainsSubstring(result2, "$100.00"));
}

TEST(StrategyInterfaceTest, AllStrategiesImplementRequiredMethods) {
    PayPalStrategy paypal;
    GooglePayStrategy googlepay;
    CreditCardStrategy creditcard;
    
    // processPayment
    EXPECT_NO_THROW(paypal.processPayment(100.0));
    EXPECT_NO_THROW(googlepay.processPayment(100.0));
    EXPECT_NO_THROW(creditcard.processPayment(100.0));
    
    // getPaymentType
    EXPECT_NO_THROW(paypal.getPaymentType());
    EXPECT_NO_THROW(googlepay.getPaymentType());
    EXPECT_NO_THROW(creditcard.getPaymentType());
    
    // isValidAmount
    EXPECT_NO_THROW(paypal.isValidAmount(100.0));
    EXPECT_NO_THROW(googlepay.isValidAmount(100.0));
    EXPECT_NO_THROW(creditcard.isValidAmount(100.0));
}
