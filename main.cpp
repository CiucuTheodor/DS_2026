#include <iostream>
#include <iomanip>

using namespace std;

// Step 1: Define Structures
struct Book {
    int isbn;
    float price;
};

struct TreeNode {
    Book info;
    TreeNode* left;
    TreeNode* right;
    int balanceFactor;
};

// Step 2: Book Functions
Book read_book() {
    Book b;
    cout << "Enter ISBN: ";
    cin >> b.isbn;
    cout << "Enter Price: ";
    cin >> b.price;
    return b;
}

void print_book(Book b) {
    cout << "Book [ISBN: " << b.isbn << ", Price: $" << fixed << setprecision(2) << b.price << "]\n";
}

// Step 3: Create Node
TreeNode* create_node(Book b) {
    TreeNode* newNode = new TreeNode;
    newNode->info = b;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->balanceFactor = 0;
    return newNode;
}

int main() {
    return 0;
}
