#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const float TAX_RATE = 0.16;

struct Product {
public:
    int id;
    string name;
    float price;
    int stock;

    Product() {
        id = 0;
        name = "None";
        price = 0;
        stock = 0;
    }

    Product(int a, string b, float c, int d) {
        id = a;
        name = b;
        price = c;
        stock = d;
    }
};

struct CartItem {
    int productId;
    string productName;
    float price;
    int quantity;

    CartItem() {
        productId = 0;
        productName = "None";
        price = 0;
        quantity = 0;
    }

    float getSubtotal() const {
        return price * quantity;
    }

    float getTax() const {
        return getSubtotal() * TAX_RATE ;
    }

    float getTotal() const {
        return getSubtotal() + getTax();
    }
};

// FUNCTION DECLARATIONS
void addProduct(vector<Product>& products);
void listProducts(const vector<Product>& products);
void editProduct(vector<Product>& products);
void removeProduct(vector<Product>& products);
void addToCart(vector<Product>& products);
void viewCart();
void reportsMenu(vector<Product>& products);
void loadProductsFromCSV(vector<Product>& products);
void saveProductsToCSV(vector<Product>& products);



// GLOBAL VARIABLES
vector<CartItem> cart;
const string PRODUCTS_FILE = "products.csv";



// MAIN FUNCTION
int main()
{
    vector<Product> products;
    int menuOptions;
    loadProductsFromCSV(products);

    do {
        system("cls");
        cout << "---Main Menu--- \n1- Products \n2- Sales \n3- Reports \n4- Exit" << endl;
        cin >> menuOptions;

        if (menuOptions == 1) {
            system("cls");

            int productOptions;
            cout << "--- Products Menu ---" << endl;
            cout << "1- Add new Product. " << endl;
            cout << "2- Edit an Existing Product. " << endl;
            cout << "3- Remove a Product. " << endl;
            cout << "4- List all Products. " << endl;
            cin >> productOptions;


            switch (productOptions) {
            case 1:
                addProduct(products);
                break;
            case 2:
                editProduct(products);
                break;
            case 3:
                removeProduct(products);
                break;
            case 4:
                listProducts(products);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                system("pause");
            }

        }
        else if (menuOptions == 2) {
            system("cls");
            int choice;
            cout << "--- Sales Menu ---\n";
            cout << "1. Add to Cart\n";
            cout << "2. View Cart\n";
            cin >> choice;

            switch (choice) {
            case 1: 
                addToCart(products);
                break;
            case 2: 
                viewCart();
                break;
            
            default:
                cout << "Invalid option. Try again\n";
                system("pause");
            }


        }
        else if (menuOptions == 3) {
            system("cls");
            reportsMenu(products);
            system("pause");
        }
        else if (menuOptions == 4) {
            system("cls");
            cout << "Exiting...\n";
        }
        else {
            system("cls");
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (menuOptions != 4);

}

void addProduct(vector<Product>& products) {
    Product newProduct;
    cout << "\nEnter Product ID: ";
    cin >> newProduct.id;
    cin.ignore();
    cout << "Enter Product Name: ";
    cin >> newProduct.name;
    cout << "Enter Product Price: ";
    cin >> newProduct.price;
    cout << "Enter Product Stock: ";
    cin >> newProduct.stock;

    products.push_back(newProduct);
    saveProductsToCSV(products);
    cout << "Product added successfully!" << endl;
    
    system("pause");
}

void editProduct(vector<Product>& products) {
    int id;
    bool found = 0;
    cout << "Enter Product ID to edit: " << endl;
    cin >> id;

    for (int i = 0; i < products.size(); i++) {
        if (products[i].id == id) {
            found = 1;
            cout << "Enter new name (current: " << products[i].name << "): " << endl;
            cin >> products[i].name;
            cout << "Enter new price (current: " << products[i].price << "): " << endl;
            cin >> products[i].price;
            cout << "Enter new stock (current: " << products[i].stock << "): " << endl;
            cin >> products[i].stock;


            cout << "Product updated.\n";
            saveProductsToCSV(products);
            system("pause");
            return;
        }
    }

    if (found == 0) {
        cout << "Product with ID " << id << " not found.\n";
        
        system("pause");
    }
}

void removeProduct(vector<Product>& products) {
    int id;
    bool found = 0;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    for (int i = 0; i < products.size(); i++) {
        if (products[i].id == id) {
            found = 1;
            products.erase(products.begin() + i);
            cout << "Product removed.\n";
            saveProductsToCSV(products);
            system("pause");
            return;
        }
    }

    if (found == 0) {
        cout << "Product with ID " << id << " not found.\n";
       
        system("pause");
    }
}

void listProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "\nNo products to display." << endl;
       
        system("pause");
        return;
    }

    cout << "\n--- Product List ---" << endl;
    for (int i = 0; i < products.size(); i++) {
        cout << "Product ID: " << products[i].id << endl;
        cout << "Product Name: " << products[i].name << endl;
        cout << "Product Price: " << products[i].price << endl;
        cout << "Product Stock: " << products[i].stock << endl << endl;
    }
   
    system("pause");
}

void addToCart(vector<Product>& products) {
    CartItem newCart;
    int id, quantity, count=0;
    bool found = 0;
    cout << "Enter Product ID to add to cart: ";
    cin >> id;

    for (int i = 0; i < products.size(); i++) {
        

        if (products[i].id == id) {
            count = i;
            found = 1;
            newCart.productId = products[i].id;
            newCart.productName = products[i].name;
            newCart.price = products[i].price;
            cout << "Enter quantity: " << endl;
            cin >> quantity;

            if (quantity > products[i].stock) {
                cout << "Not enough stock available.\n";
                system("pause");
                return;
            }
            else {
                newCart.quantity = quantity;
            }
          
        }
    }

    if (found ==0) {
        cout << "Product not found.\n";
        system("pause");
        return;
    }
    cart.push_back(newCart);
    
    products[count].stock -= quantity;
    saveProductsToCSV(products);
  
    cout << "Item added to cart.\n";
    system("pause");
}

void viewCart() {

    if (cart.empty()) {
        cout << "Cart is empty.\n";
        system("pause");
        return;
    }

    float totalSubtotal = 0, totalTax = 0, grandTotal = 0;

    cout << "\n--- Cart ---\n";
    for (const auto& item : cart) {
        float subtotal = item.getSubtotal();
        float tax = item.getTax();
        float total = item.getTotal();

        totalSubtotal += subtotal;
        totalTax += tax;
        grandTotal += total;

        cout << "Product: " << item.productName
            << " | Qty: " << item.quantity
            << " | Subtotal: $" << subtotal
            << " | Tax: $" << tax
            << " | Total: $" << total << "\n";
    }

    cout << "------------------------\n";
    cout << "Subtotal: $" << totalSubtotal << endl;
    cout << "Tax: $" << totalTax << endl;
    cout << "Total: $" << grandTotal << endl;
    system("pause");
}

void reportsMenu(vector<Product>& products) {
    cout << "--- Reports ---" << endl;
    cout << "Total Products in Inventory: " << products.size() << endl;
    int totalStock = 0;
    float totalValue = 0;
    for (auto& p : products) {
        totalStock += p.stock;
        totalValue += p.price * p.stock;
    }
    cout << "Total Stock Units: " << totalStock << endl;
    cout << "Total Inventory Value: $" << totalValue << endl;
}

void loadProductsFromCSV(vector<Product>& products) {
    Product newProduct;
    ifstream myFile;
    int location = 0;

    string line = "";
    myFile.open(PRODUCTS_FILE);
    

    while (getline(myFile, line)) {

        location = line.find(',');
        newProduct.id = stoi(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        location = line.find(',');
        newProduct.name = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        location = line.find(',');
        newProduct.price = stof(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        location = line.find(',');
        newProduct.stock = stoi(line.substr(0, location));
        line = line.substr(location + 1, line.length());


        products.push_back(newProduct);
    }
    myFile.close();
}

void saveProductsToCSV(vector<Product>& products) {
    ofstream file(PRODUCTS_FILE);
    for (auto& p : products) {
        file << p.id << "," << p.name << "," << p.price << "," << p.stock << "\n";
    }
    file.close();
}
