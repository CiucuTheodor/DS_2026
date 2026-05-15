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

// Step 4: Tree Traversal
void print(TreeNode* root) {
    if (root != nullptr) {
        print_book(root->info);
        print(root->left);
        print(root->right);
    }
}

// Step 5: Tree Height and Balance Factor
int tree_height(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = tree_height(root->left);
    int rightHeight = tree_height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int balance_factor(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return tree_height(root->left) - tree_height(root->right);
}

int main() {
    return 0;
}
