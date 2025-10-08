#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "PayPalStrategy.hpp"
#include "GooglePayStrategy.hpp"
#include "CreditCardStrategy.hpp"

using Catch::Matchers::ContainsSubstring;

TEST_CASE("PayPalStrategy - Payment Processing", "[strategy][paypal]") {
    PayPalStrategy strategy;
    
    SECTION("Format message correctly") {
        std::string result = strategy.processPayment(100.50);
        REQUIRE_THAT(result, ContainsSubstring("PayPal"));
        REQUIRE_THAT(result, ContainsSubstring("$100.50"));
    }
    
    SECTION("Return correct payment type") {
        REQUIRE(strategy.getPaymentType() == "PayPal");
    }
    
    SECTION("Validate minimum amount") {
        REQUIRE(strategy.isValidAmount(0.01));
        REQUIRE_FALSE(strategy.isValidAmount(0.001));
    }
}

TEST_CASE("GooglePayStrategy - Payment Processing", "[strategy][googlepay]") {
    GooglePayStrategy strategy;
    
    SECTION("Format message correctly") {
        std::string result = strategy.processPayment(75.25);
        REQUIRE_THAT(result, ContainsSubstring("Google Pay"));
        REQUIRE_THAT(result, ContainsSubstring("$75.25"));
    }
    
    SECTION("Return correct payment type") {
        REQUIRE(strategy.getPaymentType() == "GooglePay");
    }
}

TEST_CASE("CreditCardStrategy - Payment Processing", "[strategy][creditcard]") {
    CreditCardStrategy strategy;
    
    SECTION("Format message correctly") {
        std::string result = strategy.processPayment(500.00);
        REQUIRE_THAT(result, ContainsSubstring("Credit Card"));
        REQUIRE_THAT(result, ContainsSubstring("$500.00"));
    }
    
    SECTION("Return correct payment type") {
        REQUIRE(strategy.getPaymentType() == "CreditCard");
    }
    
    SECTION("Validate maximum transaction limit") {
        REQUIRE(strategy.isValidAmount(10000.00));
        REQUIRE_FALSE(strategy.isValidAmount(10000.01));
    }
}

TEST_CASE("Strategy Polymorphism", "[strategy][polymorphism]") {
    SECTION("All strategies work through base pointer") {
        std::shared_ptr<PaymentStrategy> strategies[] = {
            std::make_shared<PayPalStrategy>(),
            std::make_shared<GooglePayStrategy>(),
            std::make_shared<CreditCardStrategy>()
        };
        
        for (const auto& strategy : strategies) {
            REQUIRE_FALSE(strategy->getPaymentType().empty());
            REQUIRE(strategy->isValidAmount(100.0));
            std::string result = strategy->processPayment(100.0);
            REQUIRE_THAT(result, ContainsSubstring("Processing payment"));
        }
    }
}
