#include <iostream>
#include <string>
using namespace std;

// Base class: Cafe
class Cafe {
private:
    static int nextorderid; // Static variable for unique order IDs
    int *espressoqty, *latteqty, *coffeeqty, *cappuccinqty, *chocolateqty, *mochaqty; // Dynamic memory for quantities

public:
    int orderid, cost;

    // Default Constructor
    Cafe() : orderid(++nextorderid), cost(0) {
        espressoqty = new int(0);
        latteqty = new int(0);
        coffeeqty = new int(0);
        cappuccinqty = new int(0);
        chocolateqty = new int(0);
        mochaqty = new int(0);
    }

    // Destructor for memory cleanup
    virtual ~Cafe() {
        delete espressoqty;
        delete latteqty;
        delete coffeeqty;
        delete cappuccinqty;
        delete chocolateqty;
        delete mochaqty;
    }

    // Static function to display total orders
    static void showtotalorders() {
        cout << "Total Orders Placed: " << nextorderid << endl;
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
    void addtocart(int id, int &qty) {
        switch (id) {
            case 1: *espressoqty += qty; cost += qty * 200; break;
            case 2: *latteqty += qty; cost += qty * 250; break;
            case 3: *coffeeqty += qty; cost += qty * 300; break;
            case 4: *cappuccinqty += qty; cost += qty * 350; break;
            case 5: *chocolateqty += qty; cost += qty * 400; break;
            case 6: *mochaqty += qty; cost += qty * 450; break;
            default: cout << "Invalid item ID\n"; break;
        }
    }

    // Virtual function to display order summary
    virtual void displaysummary() const {
        cout << "\nOrder Summary (Order ID: " << orderid << ")\n";
        if (*espressoqty > 0) cout << "Espresso Qty: " << *espressoqty << ", Total: " << (*espressoqty * 200) << "\n";
        if (*latteqty > 0) cout << "Latte Qty: " << *latteqty << ", Total: " << (*latteqty * 250) << "\n";
        if (*coffeeqty > 0) cout << "Filter Coffee Qty: " << *coffeeqty << ", Total: " << (*coffeeqty * 300) << "\n";
        if (*cappuccinqty > 0) cout << "Cappuccino Qty: " << *cappuccinqty << ", Total: " << (*cappuccinqty * 350) << "\n";
        if (*chocolateqty > 0) cout << "Hot Chocolate Qty: " << *chocolateqty << ", Total: " << (*chocolateqty * 400) << "\n";
        if (*mochaqty > 0) cout << "Mocha Qty: " << *mochaqty << ", Total: " << (*mochaqty * 450) << "\n";
        cout << "Total Cost: " << cost << "\n";
    }

    // Apply discount to an order
    void applydiscount(int discountpercent) {
        int discountamount = (cost * discountpercent) / 100;
        cost -= discountamount;
        cout << "Discount of " << discountpercent << "% applied. Final Cost: " << cost << "\n";
    }

    // Handle payment and calculate change
    void processpayment() {
        int moneygiven;
        cout << "Enter money given by customer: ";
        cin >> moneygiven;

        while (moneygiven < cost) {
            cout << "Insufficient amount! Additional " << (cost - moneygiven) << " required.\n";
            int additionalamount;
            cout << "Enter additional money: ";
            cin >> additionalamount;
            moneygiven += additionalamount;
        }

        int change = moneygiven - cost;
        cout << "Change to be returned: " << change << "\n";
        cout << "Thank you for ordering!\n";
    }
};

// Static member initialization
int Cafe::nextorderid = 0;

// Derived class
class SpecialCafe : public Cafe {
public:
    void displaysummary() const override {
        cout << "\n[Special Cafe] Order Summary (ID: " << orderid << ")\n";
        Cafe::displaysummary();
        cout << "Special rates applied!\n";
    }
};


int main() {
    int choice, qty, itemid, numorders, discountpercent;

    cout << "Enter the number of orders: ";
    cin >> numorders;

    Cafe *orders = new SpecialCafe[numorders]; // Dynamic allocation of orders

    // Taking orders
    for (int i = 0; i < numorders; i++) {
        cout << "\nOrder " << (i + 1) << ":\n";
        do {
            orders[i].menu();
            cout << "Enter item ID to order (1-6): ";
            cin >> itemid;
            if (itemid >= 1 && itemid <= 6) {
                cout << "Enter quantity: ";
                cin >> qty;
                orders[i].addtocart(itemid, qty);
            } else {
                cout << "Invalid item ID. Try again.\n";
            }
            cout << "Order more items? (1-Yes / 0-No): ";
            cin >> choice;
        } while (choice == 1);
    }

    // Displaying all orders
    cout << "\n=== All Orders Summary ===\n";
    for (int i = 0; i < numorders; i++) {
        cout << "\nOrder " << (i + 1) << " Summary:\n";
        orders[i].displaysummary();
    }

    // Applying discount to all orders
    cout << "\nEnter discount percentage to apply to all orders: ";
    cin >> discountpercent;
    for (int i = 0; i < numorders; i++) {
        cout << "\nApplying discount to Order " << (i + 1) << "...\n";
        orders[i].applydiscount(discountpercent);
    }

    // Processing payment for all orders
    cout << "\n=== Payment Processing ===\n";
    for (int i = 0; i < numorders; i++) {
        cout << "\nProcessing payment for Order " << (i + 1) << "...\n";
        orders[i].processpayment();
    }

    // Display total orders placed
    Cafe::showtotalorders();

    //deallocation of memory
    delete[] orders;
    return 0;
}
