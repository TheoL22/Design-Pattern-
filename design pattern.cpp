#include <iostream>
#include <string>
using namespace std;

class Discount {
public:
    virtual double apply(double amount) = 0;
    virtual string getDescription() = 0;
    virtual ~Discount() {}
};

class NoDiscount : public Discount {
public:
    double apply(double amount) override {
        return amount;
    }

    string getDescription() override {
        return "No discount";
    }
};

class TenPercentDiscount : public Discount {
public:
    double apply(double amount) override {
        return amount * 0.9;
    }

    string getDescription() override {
        return "10% discount";
    }
};

class TwentyPercentDiscount : public Discount {
public:
    double apply(double amount) override {
        return amount * 0.8;
    }

    string getDescription() override {
        return "20% discount";
    }
};

class DiscountCalculator {
private:
    Discount* discount;

public:
    DiscountCalculator() : discount(nullptr) {}

    ~DiscountCalculator() {
        delete discount;
    }

    void setDiscount(Discount* d) {
        delete discount;
        discount = d;
    }

    double calculate(double amount) {
        if (discount) {
            return discount->apply(amount);
        } else {
            cout << "Discount not set." << endl;
            return amount;
        }
    }

    string getDiscountDescription() {
        return discount ? discount->getDescription() : "No discount set";
    }
};

int main() {
    double amount;
    string input;
    DiscountCalculator calculator;

    cout << "Enter Amount: ";
    cin >> amount;

    cin.ignore(); 

    cout << "Enter discount (No discount, 10%, 20%): ";
    getline(cin, input);

    if (input == "No discount") {
        calculator.setDiscount(new NoDiscount());
    } else if (input == "10%") {
        calculator.setDiscount(new TenPercentDiscount());
    } else if (input == "20%") {
        calculator.setDiscount(new TwentyPercentDiscount());
    } else {
        cout << "Invalid discount option. Using no discount by default.\n";
        calculator.setDiscount(new NoDiscount());
    }

    double total = calculator.calculate(amount);

    cout << "Discount: " << calculator.getDiscountDescription() << endl;
    cout << "Total: " << total << endl;

    return 0;  
}
