#include <iostream>
#include <string>
using namespace std;

// Base class: Cafe
class Cafe {
private:
    static int nextOrderID; // Static variable for unique order IDs
    int *espressoQty, *latteQty, *coffeeQty, *cappuccinoQty, *chocolateQty, *mochaQty; // Dynamic memory for quantities

public:
    int orderID, cost;

    // Default Constructor
    Cafe() : orderID(++nextOrderID), cost(0) {
        espressoQty = new int(0);
        latteQty = new int(0);
        coffeeQty = new int(0);
        cappuccinoQty = new int(0);
        chocolateQty = new int(0);
        mochaQty = new int(0);
    }

    // Destructor for memory cleanup
    virtual ~Cafe() {
        delete espressoQty;
        delete latteQty;
        delete coffeeQty;
        delete cappuccinoQty;
        delete chocolateQty;
        delete mochaQty;
    }

    // Static function to display total orders
    static void showTotalOrders() {
        cout << "Total Orders Placed: " << nextOrderID << endl;
    }

    // Menu display function
    void menu() const {
        cout << "\nCafe Menu:\n";
        cout << "1. Espresso      - 200\n";
        cout << "2. Latte         - 250\n";
        cout << "3. Filter Coffee - 300\n";
        cout << "4. Cappuccino    - 350\n";
        cout << "5. Hot Chocolate - 400\n";
        cout << "6. Mocha         - 450\n";
    }

    // Adding items to the cart (pass by reference)
    void addToCart(int id, int &qty) {
        switch (id) {
            case 1: *espressoQty += qty; cost += qty * 200; break;
            case 2: *latteQty += qty; cost += qty * 250; break;
            case 3: *coffeeQty += qty; cost += qty * 300; break;
            case 4: *cappuccinoQty += qty; cost += qty * 350; break;
            case 5: *chocolateQty += qty; cost += qty * 400; break;
            case 6: *mochaQty += qty; cost += qty * 450; break;
            default: cout << "Invalid item ID\n"; break;
        }
    }

    // Virtual function to display order summary
    virtual void displaySummary() const {
        cout << "\nOrder Summary (Order ID: " << orderID << ")\n";
        if (*espressoQty > 0) cout << "Espresso Qty: " << *espressoQty << ", Total: " << (*espressoQty * 200) << "\n";
        if (*latteQty > 0) cout << "Latte Qty: " << *latteQty << ", Total: " << (*latteQty * 250) << "\n";
        if (*coffeeQty > 0) cout << "Filter Coffee Qty: " << *coffeeQty << ", Total: " << (*coffeeQty * 300) << "\n";
        if (*cappuccinoQty > 0) cout << "Cappuccino Qty: " << *cappuccinoQty << ", Total: " << (*cappuccinoQty * 350) << "\n";
        if (*chocolateQty > 0) cout << "Hot Chocolate Qty: " << *chocolateQty << ", Total: " << (*chocolateQty * 400) << "\n";
        if (*mochaQty > 0) cout << "Mocha Qty: " << *mochaQty << ", Total: " << (*mochaQty * 450) << "\n";
        cout << "Total Cost: " << cost << "\n";
    }

    // Apply discount to an order
    void applyDiscount(int discountPercent) {
        int discountAmount = (cost * discountPercent) / 100;
        cost -= discountAmount;
        cout << "Discount of " << discountPercent << "% applied. Final Cost: " << cost << "\n";
    }

    // Handle payment and calculate change
    void processPayment() {
        int moneyGiven;
        cout << "Enter money given by customer: ";
        cin >> moneyGiven;

        while (moneyGiven < cost) {
            cout << "Insufficient amount! Additional " << (cost - moneyGiven) << " required.\n";
            int additionalAmount;
            cout << "Enter additional money: ";
            cin >> additionalAmount;
            moneyGiven += additionalAmount;
        }

        int change = moneyGiven - cost;
        cout << "Change to be returned: " << change << "\n";
        cout << "Thank you for ordering!\n";
    }
};

// Static member initialization
int Cafe::nextOrderID = 0;

// Derived class
class SpecialCafe : public Cafe {
public:
    void displaySummary() const override {
        cout << "\n[Special Cafe] Order Summary (ID: " << orderID << ")\n";
        Cafe::displaySummary();
        cout << "Special rates applied!\n";
    }
};


int main() {
    int choice, qty, itemID, numOrders, discountPercent;

    cout << "Enter the number of orders: ";
    cin >> numOrders;

    Cafe *orders = new SpecialCafe[numOrders]; // Dynamic allocation of orders

    // Taking orders
    for (int i = 0; i < numOrders; i++) {
        cout << "\nOrder " << (i + 1) << ":\n";
        do {
            orders[i].menu();
            cout << "Enter item ID to order (1-6): ";
            cin >> itemID;
            if (itemID >= 1 && itemID <= 6) {
                cout << "Enter quantity: ";
                cin >> qty;
                orders[i].addToCart(itemID, qty);
            } else {
                cout << "Invalid item ID. Try again.\n";
            }
            cout << "Order more items? (1-Yes / 0-No): ";
            cin >> choice;
        } while (choice == 1);
    }

    // Displaying all orders
    cout << "\n=== All Orders Summary ===\n";
    for (int i = 0; i < numOrders; i++) {
        cout << "\nOrder " << (i + 1) << " Summary:\n";
        orders[i].displaySummary();
    }

    // Applying discount to all orders
    cout << "\nEnter discount percentage to apply to all orders: ";
    cin >> discountPercent;
    for (int i = 0; i < numOrders; i++) {
        cout << "\nApplying discount to Order " << (i + 1) << "...\n";
        orders[i].applyDiscount(discountPercent);
    }

    // Processing payment for all orders
    cout << "\n=== Payment Processing ===\n";
    for (int i = 0; i < numOrders; i++) {
        cout << "\nProcessing payment for Order " << (i + 1) << "...\n";
        orders[i].processPayment();
    }

    // Display total orders placed
    Cafe::showTotalOrders();

    //deallocation of memory
    delete[] orders;
    return 0;
}

