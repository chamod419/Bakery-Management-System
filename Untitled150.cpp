#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;


struct User {
    string username;
    string password;
};

struct BakeryItem {
    int id;
    string name;
    string description;
    double price;
    int quantity; 
};

struct CartItem {
    int itemId;
    string itemName;
    double itemPrice;
    int quantity;  
};

void displayBakeryItems(BakeryItem items[], int itemCount) {
    cout << "Bakery Items:" << endl;
    for (int i = 0; i < itemCount; ++i) {
        cout << "ID: " << items[i].id << endl;
        cout << "Name: " << items[i].name << endl;
        cout << "Description: " << items[i].description << endl;
        cout << "Price: $" << fixed << setprecision(2) << items[i].price << endl;
        cout << "Quantity in Stock: " << items[i].quantity << endl;  
        cout << "---------------------------------------" << endl;
    }
}

void addBakeryItem(BakeryItem items[], int &itemCount) {
    BakeryItem newItem;

    cout << "Enter item name: ";
    cin.ignore();
    getline(cin, newItem.name);

    cout << "Enter item description: ";
    getline(cin, newItem.description);

    cout << "Enter item price: ";
    cin >> newItem.price;

    cout << "Enter quantity in stock: ";
    cin >> newItem.quantity;

    newItem.id = itemCount + 1;

    items[itemCount] = newItem;
    itemCount++;

    cout << "New item added successfully!" << endl;
}

void searchBakeryItems(BakeryItem items[], int itemCount, int searchId, string searchName) {
    bool found = false;

    for (int i = 0; i < itemCount; ++i) {
        if ((searchId != -1 && items[i].id == searchId) || (searchName != "" && items[i].name == searchName)) {
            cout << "ID: " << items[i].id << endl;
            cout << "Name: " << items[i].name << endl;
            cout << "Description: " << items[i].description << endl;
            cout << "Price: $" << fixed << setprecision(2) << items[i].price << endl;
            cout << "Availability: " << (items[i].quantity > 0 ? "Available" : "Not Available") << endl;
            cout << "---------------------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matching items found." << endl;
    }
}

bool loginUser(User users[], int userCount, string &loggedInUser) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username && users[i].password == password) {
            loggedInUser = username;
            return true;
        }
    }

    cout << "Login failed. Invalid username or password. Please check your credentials." << endl;
    return false;
}

void addToCart(vector<CartItem> &cart, BakeryItem items[], int itemCount, int itemId, int quantity) {
    for (int i = 0; i < itemCount; ++i) {
        if (items[i].id == itemId) {
            if (items[i].quantity >= quantity) {  
                CartItem newItem;
                newItem.itemId = items[i].id;
                newItem.itemName = items[i].name;
                newItem.itemPrice = items[i].price;
                newItem.quantity = quantity;
                cart.push_back(newItem);
                items[i].quantity -= quantity;  
                cout << "Item added to your cart!" << endl;
            } else {
                cout << "Insufficient quantity in stock." << endl;
            }
            return;
        }
    }
    cout << "Item not found." << endl;
}

void displayCart(vector<CartItem> &cart) {
    cout << "Shopping Cart:" << endl;
    double total = 0.0;
    for (const CartItem &item : cart) {
        cout << "ID: " << item.itemId << ", Name: " << item.itemName << ", Price: $" << fixed << setprecision(2) << item.itemPrice << ", Quantity: " << item.quantity << endl;
        total += item.itemPrice * item.quantity;
    }
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
}

void checkout(vector<CartItem> &cart, BakeryItem items[], int itemCount) {
    cout << "Checkout - Receipt:" << endl;
    double total = 0.0;
    for (const CartItem &item : cart) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].id == item.itemId) {
                cout << "Name: " << items[i].name << ", Price: $" << fixed << setprecision(2) << items[i].price << ", Quantity: " << item.quantity << endl;
                total += items[i].price * item.quantity;
            }
        }
    }
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
    cout << "Thank you for your purchase!" << endl;

   
    cart.clear();
}

int main() {
    const int MAX_ITEMS = 100;
    BakeryItem bakeryItems[MAX_ITEMS];
    int itemCount = 0;

    const int MAX_USERS = 10;
    User users[MAX_USERS];
    users[0] = {"chamod", "1234"};
    

    bakeryItems[itemCount++] = {1, "Chocolate Cake", "Delicious chocolate cake", 15.99, 10};  // Initial quantity in stock: 10
    bakeryItems[itemCount++] = {2, "Blueberry Muffin", "Fresh blueberry muffin", 4.99, 20};  
    bakeryItems[itemCount++] = {3, "Cinnamon Roll", "Warm cinnamon roll", 3.49, 15};         
    bakeryItems[itemCount++] = {4, "Vanilla Cupcake", "Classic vanilla cupcake", 2.99, 30};   
    bakeryItems[itemCount++] = {5, "Strawberry Donut", "Sweet strawberry glazed donut", 3.99, 25};  
    bakeryItems[itemCount++] = {6, "Cheesecake Slice", "Creamy cheesecake slice", 6.49, 12};  
    bakeryItems[itemCount++] = {7, "Chocolate Chip Cookie", "Homemade chocolate chip cookie", 1.49, 40};  
    bakeryItems[itemCount++] = {8, "Pecan Pie", "Delicious pecan pie", 8.99, 8};               
    bakeryItems[itemCount++] = {9, "Lemon Tart", "Zesty lemon tart", 4.49, 18};               
    bakeryItems[itemCount++] = {10, "Red Velvet Cupcake", "Rich red velvet cupcake", 3.49, 35};  

    int choice;
    bool loggedIn = false;
    string loggedInUser;
    vector<CartItem> cart;

    cout << "************ Welcome to Amber Bakery! ************\n";

    do {
        cout << "\n\n~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "1. User Login" << endl;
        cout << "2. View Bakery Items" << endl;
        cout << "3. Add Bakery Item" << endl;
        cout << "4. Search Bakery Items" << endl;
        cout << "5. Add to Cart" << endl;
        cout << "6. View Cart" << endl;
        cout << "7. Checkout" << endl;
        cout << "8. View Company Details" << endl;
        cout << "9. Logout" << endl;
        cout << "10. Exit" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!loggedIn) {
                    loggedIn = loginUser(users, MAX_USERS, loggedInUser);
                    if (loggedIn) {
                        cout << "Login successful. Welcome " << loggedInUser << "!" << endl;
                    }
                } else {
                    cout << "You are already logged in as " << loggedInUser << "." << endl;
                }
                break;
            case 2:
                displayBakeryItems(bakeryItems, itemCount);
                break;
            case 3:
                if (loggedIn) {
                    addBakeryItem(bakeryItems, itemCount);
                } else {
                    cout << "Please log in to add items." << endl;
                }
                break;
            case 4: {
                int searchId;
                string searchName;
                cout << "Enter search ID (or -1 if not searching by ID): ";
                cin >> searchId;
                cout << "Enter search name (or leave blank if not searching by name): ";
                cin.ignore();
                getline(cin, searchName);
                searchBakeryItems(bakeryItems, itemCount, searchId, searchName);
                break;
            }
            case 5: {
                if (loggedIn) {
                    int itemId, quantity;
                    cout << "Enter the ID of the item you want to add to your cart: ";
                    cin >> itemId;
                    cout << "Enter the quantity: ";
                    cin >> quantity;
                    addToCart(cart, bakeryItems, itemCount, itemId, quantity);
                } else {
                    cout << "Please log in to add items to your cart." << endl;
                }
                break;
            }
            case 6:
                displayCart(cart);
                break;
            case 7:
                if (loggedIn) {
                    if (!cart.empty()) {
                        checkout(cart, bakeryItems, itemCount);
                    } else {
                        cout << "Your cart is empty. Add items to your cart before checking out." << endl;
                    }
                } else {
                    cout << "Please log in to checkout." << endl;
                }
                break;
            case 8:
                cout << "Amber Bakery Company Details:" << endl;
                cout << "Address: No 123, Bakery Street, London, UK." << endl;
                cout << "Phone: +44 123-456-7890" << endl;
                break;
            case 9:
                if (loggedIn) {
                    cout << "Logout successful. Goodbye, " << loggedInUser << "!" << endl;
                    loggedIn = false;
                    loggedInUser.clear();
                } else {
                    cout << "You are not logged in." << endl;
                }
                break;
            case 10:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    } while (choice != 10);

  

    return 0;
}

