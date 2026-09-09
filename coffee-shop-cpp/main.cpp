// A beginner-friendly terminal ordering system.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int MENU_SIZE = 6;
const string DRINKS[MENU_SIZE] = {
    "Espresso", "Americano", "Latte", "Cappuccino",
    "Iced Vanilla Latte", "Mocha"
};
// Store money as whole cents to keep calculations exact.
const int PRICES[MENU_SIZE] = {300, 350, 450, 450, 525, 500};
const int MAX_QUANTITY = 99;
const int LATTE_COUNT = 5;
const string latteFlavors[LATTE_COUNT] = {
    "Caramel Latte", "Salted Caramel Latte", "Mocha Latte",
    "White Mocha Latte", "Matcha Latte"
};
// All flavors currently cost $4.50. Prices are in cents.
const int lattePrices[LATTE_COUNT] = {450, 450, 450, 450, 450};

string money(int cents)
{
    ostringstream output;
    output << '$' << cents / 100 << '.' << setfill('0') << setw(2)
           << cents % 100;
    return output.str();
}

// Read a whole line so text, decimals, and extra characters are rejected.
// Return false if the input stream closes (for example, Ctrl+D on Mac).
bool readNumber(const string& prompt, int minimum, int maximum, int& value)
{
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) {
            return false;
        }
        istringstream input(line);
        char extra;
        if ((input >> value) && !(input >> extra)
            && value >= minimum && value <= maximum) {
            return true;
        }
        cout << "Please enter a whole number from " << minimum
             << " to " << maximum << ".\n";
    }
}

void showMenu()
{
    cout << "\nADEEP'S COFFEE SHOP\n"
         << "------------------------------\n";
    for (int i = 0; i < MENU_SIZE; ++i) {
        cout << i + 1 << ". " << left << setw(22) << DRINKS[i]
             << right << setw(6) << money(PRICES[i]) << '\n';
    }
    cout << "7. View order\n8. Checkout\n9. Clear order\n0. Exit\n";
}

int showOrder(const int quantities[], const int latteQuantities[])
{
    int total = 0;
    cout << "\nYOUR ORDER\n"
         << "--------------------------------------------------\n"
         << left << setw(23) << "Drink" << right << setw(5) << "Qty"
         << setw(10) << "Each" << setw(12) << "Amount" << '\n';
    for (int i = 0; i < MENU_SIZE; ++i) {
        if (quantities[i] > 0) {
            int lineTotal = quantities[i] * PRICES[i];
            total += lineTotal;
            cout << left << setw(23) << DRINKS[i] << right
                 << setw(5) << quantities[i] << setw(10) << money(PRICES[i])
                 << setw(12) << money(lineTotal) << '\n';
        }
    }
    for (int i = 0; i < LATTE_COUNT; ++i) {
        if (latteQuantities[i] > 0) {
            int lineTotal = latteQuantities[i] * lattePrices[i];
            total += lineTotal;
            cout << left << setw(23) << latteFlavors[i] << right
                 << setw(5) << latteQuantities[i]
                 << setw(10) << money(lattePrices[i])
                 << setw(12) << money(lineTotal) << '\n';
        }
    }
    if (total == 0) {
        cout << "Your order is empty.\n";
    }
    cout << "--------------------------------------------------\n"
         << "Total: " << money(total) << '\n';
    return total;
}

int main()
{
    int quantities[MENU_SIZE] = {};
    int latteQuantities[LATTE_COUNT] = {};
    cout << "Welcome! Choose a drink and quantity to begin.\n"
         << "Demo prices in USD. No tax, tips, or payments included.\n";

    while (true) {
        showMenu();
        int choice;
        if (!readNumber("\nYour choice: ", 0, 9, choice) || choice == 0) {
            cout << "\nGoodbye! Any unfinished order has been discarded.\n";
            break;
        }

        // Handle Latte first so a flavored latte is not also added as plain.
        if (choice == 3) {
            cout << "\nChoose your latte:\n";
            for (int i = 0; i < LATTE_COUNT; ++i) {
                cout << i + 1 << ". " << latteFlavors[i]
                     << " - " << money(lattePrices[i]) << '\n';
            }
            cout << "0. Back to main menu\n";
            int flavor;
            if (!readNumber("Your flavor: ", 0, LATTE_COUNT, flavor)) {
                cout << "\nInput closed. Unfinished order discarded.\n";
                break;
            }
            if (flavor == 0) continue;
            int index = flavor - 1;
            int remaining = MAX_QUANTITY - latteQuantities[index];
            if (remaining == 0) {
                cout << "You already have 99 of this flavor.\n";
                continue;
            }
            int quantity;
            if (!readNumber("Quantity (1-" + to_string(remaining) + "): ",
                            1, remaining, quantity)) {
                cout << "\nInput closed. Unfinished order discarded.\n";
                break;
            }
            latteQuantities[index] += quantity;
            cout << "Added " << quantity << " x "
                 << latteFlavors[index] << ".\n";
            continue;
        }

        if (choice >= 1 && choice <= MENU_SIZE) {
            int index = choice - 1;
            int remaining = MAX_QUANTITY - quantities[index];
            if (remaining == 0) {
                cout << "You already have the maximum of 99 for this drink.\n";
                continue;
            }
            int quantity;
            if (!readNumber("Quantity (1-" + to_string(remaining) + "): ",
                            1, remaining, quantity)) {
                cout << "\nInput closed. Unfinished order discarded.\n";
                break;
            }
            quantities[index] += quantity;
            cout << "Added " << quantity << " x " << DRINKS[index] << ".\n";
        } else if (choice == 7) {
            showOrder(quantities, latteQuantities);
        } else if (choice == 8) {
            if (showOrder(quantities, latteQuantities) > 0) {
                cout << "Thank you! Your receipt is shown above.\n"
                     << "Starting a new order.\n";
                for (int& quantity : quantities) quantity = 0;
            for (int& quantity : latteQuantities) quantity = 0;
            } else {
                cout << "Add a drink before checking out.\n";
            }
        } else if (choice == 9) {
            for (int& quantity : quantities) quantity = 0;
            for (int& quantity : latteQuantities) quantity = 0;
            cout << "Order cleared.\n";
        }
    }
    return 0;
}
