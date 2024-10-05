#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

class Item {
private:
    string id;
    string name;
    int quantity;
    double price;

public:
    Item(string i, string n, int q, double p) : id(i), name(n), quantity(q), price(p) {
    }

    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int newQuantity) {
        if (newQuantity >= 0) {
            quantity = newQuantity;
        } else {
            cout << "Invalid quantity!" << endl;
        }
    }

    void setPrice(double newPrice) {
        if (newPrice >= 0) {
            price = newPrice;
        } else {
            cout << "Invalid price!" << endl;
        }
    }
};

class Inventory {
private:
    vector<Item> clothing;
    vector<Item> electronics;
    vector<Item> entertainment;
    vector<Item> emptyItems;



public:
    virtual ~Inventory() = default;

    Inventory() = default;

    bool isValidCategory(string category) {
        string uppercaseCategory = category;
        for (char &c: uppercaseCategory) {
            c = toupper(c);
        }
        return uppercaseCategory == "CLOTHING" || uppercaseCategory == "ELECTRONICS" || uppercaseCategory == "ENTERTAINMENT";
    }

    vector<Item> &getCategory(string category) {
        string uppercaseCategory = category;
        for (char &c: uppercaseCategory) {
            c = toupper(c);
        }


        if (uppercaseCategory == "CLOTHING") return clothing;
        else if (uppercaseCategory == "ELECTRONICS") return electronics;
        else if (uppercaseCategory == "ENETRAINMENT") return entertainment;
        // return empty
        else {
            return emptyItems;
        }
    }

    void addItem(string category, string id, string name, int quantity, double price) {
        if (!isValidCategory(category)) {
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }
        Item newItem(id, name, quantity, price);
        getCategory(category).push_back(newItem);
        cout << "Item added successfully!" << endl;
    }

    void updateItem(string id, string updateField, double newValue) {
        string upperUpdateField = updateField;
        for (char &c: upperUpdateField) {
            c = tolower(c);
        }
        for (auto &item: getAllItems()) {
            if (item.getId() == id) {
                if (updateField == "quantity") {
                    int oldQuantity = item.getQuantity();
                    item.setQuantity((int) newValue);
                    cout << "Quantity of Item " << item.getName() << " is updated from " << oldQuantity << " to " <<
                            item.getQuantity() << endl;
                } else if (updateField == "price") {
                    double oldPrice = item.getPrice();
                    item.setPrice(newValue);
                    cout << "Price of Item " << item.getName() << " is updated from " << oldPrice << " to " << item.
                            getPrice() << endl;
                }
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void removeItem(string id) {
        for (auto &item: getAllItems()) {
            if (item.getId() == id) {
                cout << "Item " << item.getName() << " has been removed from the inventory" << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    virtual void displayItemsByCategory(string category) = 0;

    virtual void displayAllItems() = 0;

    virtual void displayLowStockItems() = 0;

    virtual void displaySearchItem() = 0;

    virtual void displaySortItems() = 0;

    vector<Item> getAllItems() {
        vector<Item> allItems;
        allItems.insert(allItems.end(), clothing.begin(), clothing.end());
        allItems.insert(allItems.end(), electronics.begin(), electronics.end());
        allItems.insert(allItems.end(), entertainment.begin(), entertainment.end());
        return allItems;
    }
};

class InventoryImplementation : public Inventory {
public:
    void bubbleSortPrice(vector<Item> &items, bool ascending) {
        for (int i = 0; i < items.size() - 1; i++) {
            for (int j = 0; j < items.size() - i - 1; j++) {
                if (ascending) {
                    if (items[j].getPrice() > items[j + 1].getPrice()) {
                        // swap items[j] and items[j+1]
                        const Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                } else {
                    if (items[j].getPrice() < items[j + 1].getPrice()) {
                        // swap items[j] and items[j+1]
                        const Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                }
            }
        }
    }

    void bubbleSortQuantity(vector<Item> &items, bool ascending) {
        for (int i = 0; i < items.size() - 1; i++) {
            for (int j = 0; j < items.size() - i - 1; j++) {
                if (ascending) {
                    if (items[j].getQuantity() > items[j + 1].getQuantity()) {
                        // swap items[j] and items[j+1]
                        const Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                } else {
                    if (items[j].getQuantity() < items[j + 1].getQuantity()) {
                        // swap items[j] and items[j+1]
                        const Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                }
            }
        }
    }

    void displaySortItems() override {
        vector<Item> allItems = getAllItems();
        while (true) {
            cout << "Sort by (price/quantity): ";
            string sortField;
            cin >> sortField;
            for (char &c: sortField) {
                c = tolower(c);
            }
            if (sortField == "price") {
                cout << "Sort in (ascending/descending): ";
                string sortOrder;
                cin >> sortOrder;
                for (char &c: sortOrder) {
                    c = tolower(c);
                }
                if (sortOrder == "ascending") {
                    bubbleSortPrice(allItems, true);
                } else if (sortOrder == "descending") {
                    bubbleSortPrice(allItems, false);
                } else {
                    cout << "Invalid sort order!" << endl;
                    continue;
                }
                break; // Exit the loop after successful sorting
            } else if (sortField == "quantity") {
                cout << "Sort in (ascending/descending): ";
                string sortOrder;
                cin >> sortOrder;
                for (char &c: sortOrder) {
                    c = tolower(c);
                }
                if (sortOrder == "ascending") {
                    bubbleSortQuantity(allItems, true);
                } else if (sortOrder == "descending") {
                    bubbleSortQuantity(allItems, false);
                } else {
                    cout << "Invalid sort order!" << endl;
                    continue;
                }
                break; // Exit the loop after successful sorting
            } else {
                cout << "Invalid sort field!" << endl;
            }
        }

        // Display the sorted items
        cout << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
        for (const auto &item : allItems) {
            cout << setw(10) << item.getId() << setw(15) << item.getName()
                 << setw(10) << item.getQuantity() << setw(10) << item.getPrice() << endl;
        }
    }


    void displayItemsByCategory(string category) override {
        if (!isValidCategory(category)) {
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }
        vector<Item> &items = getCategory(category);
        if (items.empty()) {
            cout << "No items in category " << category << endl;
        } else {
            cout << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
            for (const auto &item: items) {
                cout << setw(10) << item.getId() << setw(15) << item.getName() << setw(10) << item.getQuantity() <<
                        setw(10) << item.getPrice() << endl;
            }
        }
    }

    void displaySearchItem() override {
        string search;
        cout << "Enter search: ";
        cin >> search;
        for (char &c: search) {
            c = tolower(c);
        }
        vector<Item> allItems = getAllItems();
        vector<Item> searchItems;
        for (const auto &item: allItems) {
            if (item.getId() == search) {
                searchItems.push_back(item);
            }
        }

        if (searchItems.empty()) {
            cout << "No items found" << endl;
        } else {
            cout << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
            for (const auto &item: searchItems) {
                cout << setw(10) << item.getId() << setw(15) << item.getName() << setw(10) << item.getQuantity() <<
                        setw(10) << item.getPrice() << endl;
            }
        }
    }

    void displayAllItems() override {
        vector<Item> allItems = getAllItems();
        if (allItems.empty()) {
            cout << "No items in inventory" << endl;
        } else {
            cout << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
            for (const auto &item: allItems) {
                cout << setw(10) << item.getId() << setw(15) << item.getName() << setw(10) << item.getQuantity() <<
                        setw(10) << item.getPrice() << endl;
            }
        }
    }

    void displayLowStockItems() override {
        vector<Item> allItems = getAllItems();
        vector<Item> lowStockItems;
        for (const auto &item: allItems) {
            if (item.getQuantity() <= 5) {
                lowStockItems.push_back(item);
            }
        }

        if (lowStockItems.empty()) {
            cout << "No low stock items" << endl;
        } else {
            cout << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
            for (const auto &item: lowStockItems) {
                cout << setw(10) << item.getId() << setw(15) << item.getName() << setw(10) << item.getQuantity() <<
                        setw(10) << item.getPrice() << endl;
            }
        }
    }
};

// function to get valid price
double getValidPrice() {
    double value;
    while (true) {
        std::cout << "Enter price: "; // Prompt the user
        std::cin >> value; // Attempt to read the input

        // Check if the input is valid
        if (std::cin.good() && value > 0) {
            // If valid, clear the input and return the value
            std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            return value;
        }
        // If invalid, clear the error state and ignore the invalid input
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a non-negative price." << std::endl;
    }
}

// function to get valid quantity, with optional message
// it should not allow negative values, and should not allow
// non-integer values such as 1.5
int getValidInt(const std::string& message = "Enter quantity: ") {
    int value;
    while (true) {
        std::cout << message; // Prompt the user
        std::cin >> value; // Attempt to read the input

        // Check if the input is valid
        if (std::cin.good()) {
            // If valid, clear the input and return the value
            std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            return value;
        } else {
            // If invalid, clear the error state and ignore the invalid input
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        }
    }

}

int main() {
    InventoryImplementation inventory;
    int choice;
    bool running = true; // Flag to control the loop

    while (running) {
        cout << "\nMenu\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display Items by Category\n";
        cout << "5 - Display All Items\n";
        cout << "6 - Search Item\n";
        cout << "7 - Sort Items\n";
        cout << "8 - Display Low Stock Items\n";
        cout << "9 - Exit\n";
        choice = getValidInt("Enter choice: ");

        switch (choice) {
            case 1: {
                string category, id, name;
                cout << "Enter Category: (Clothing, Electronics, Entertainment)";
                cin >> category;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                const int quantity = getValidInt();
                const double price = getValidPrice();


                inventory.addItem(category, id, name, quantity, price);
                break;
            }
            case 2: {
                if (inventory.getAllItems().empty()) {
                    cout << "No items in inventory" << endl;
                    break;
                }
                string id, field;
                double newValue;
                cout << "Enter Item ID: ";
                cin >> id;
                cout << "Update (quantity/price): ";
                cin >> field;
                cout << "Enter new value: ";
                cin >> newValue;
                inventory.updateItem(id, field, newValue);
                break;
            }
            case 3: {
                if (inventory.getAllItems().empty()) {
                    cout << "No items in inventory" << endl;
                    break;
                }
                string id;
                cout << "Enter Item ID: ";
                cin >> id;
                inventory.removeItem(id);
                break;
            }
            case 4: {
                string category;
                cout << "Enter Category: ";
                cin >> category;
                inventory.displayItemsByCategory(category);
                break;
            }
            case 5: {
                inventory.displayAllItems();
                break;
            }
            case 6: {
                cout << "Search Item" << endl;
                inventory.displaySearchItem();
                break;
            }
            case 7: {
                inventory.displaySortItems();
                break;
            }
            case 8: {
                inventory.displayLowStockItems();
                break;
            }
            case 9:
                running = false; // Exit the loop
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
