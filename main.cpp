#include <iostream>
#include <iomanip>

using namespace std;

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

TreeNode* create_node(Book b) {
    TreeNode* newNode = new TreeNode;
    newNode->info = b;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->balanceFactor = 0;
    return newNode;
}

void print(TreeNode* root) {
    if (root != nullptr) {
        print_book(root->info);
        print(root->left);
        print(root->right);
    }
}

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

TreeNode* rotate_left(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->balanceFactor = balance_factor(x);
    y->balanceFactor = balance_factor(y);
    
    return y;
}

TreeNode* rotate_right(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->balanceFactor = balance_factor(y);
    x->balanceFactor = balance_factor(x);
    
    return x;
}

TreeNode* rotate_left_right(TreeNode* root) {
    root->left = rotate_left(root->left);
    return rotate_right(root);
}

TreeNode* rotate_right_left(TreeNode* root) {
    root->right = rotate_right(root->right);
    return rotate_left(root);
}

TreeNode* balance(TreeNode* root) {
    if (root == nullptr) return root;

    root->balanceFactor = balance_factor(root);

    if (root->balanceFactor > 1) { // Left heavy
        if (balance_factor(root->left) < 0) {
            root = rotate_left_right(root);
        } else {
            root = rotate_right(root);
        }
    } else if (root->balanceFactor < -1) { // Right heavy
        if (balance_factor(root->right) > 0) {
            root = rotate_right_left(root);
        } else {
            root = rotate_left(root);
        }
    }

    return root;
}

TreeNode* insert_node(Book b, TreeNode* root) {
    if (root == nullptr) {
        return create_node(b);
    }
    
    if (b.isbn < root->info.isbn) {
        root->left = insert_node(b, root->left);
    } else if (b.isbn > root->info.isbn) {
        root->right = insert_node(b, root->right);
    } else {
        // ISBN already exists
        return root;
    }
    
    return balance(root);
}

TreeNode* delete_node(int isbn, TreeNode* root);

TreeNode* get_min_value_node(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* delete_root_node(TreeNode* root) {
    if (root == nullptr) return root;

    if (root->left == nullptr) {
        TreeNode* temp = root->right;
        delete root;
        return balance(temp);
    } else if (root->right == nullptr) {
        TreeNode* temp = root->left;
        delete root;
        return balance(temp);
    }

    TreeNode* temp = get_min_value_node(root->right);
    root->info = temp->info;
    root->right = delete_node(temp->info.isbn, root->right);
    
    return balance(root);
}

TreeNode* delete_node(int isbn, TreeNode* root) {
    if (root == nullptr) return root;

    if (isbn < root->info.isbn) {
        root->left = delete_node(isbn, root->left);
    } else if (isbn > root->info.isbn) {
        root->right = delete_node(isbn, root->right);
    } else {
        return delete_root_node(root);
    }

    return balance(root);
}

int main() {
    TreeNode* root = nullptr;
    int num_books;
    
    cout << "Enter number of books to insert: ";
    cin >> num_books;
    
    for (int i = 0; i < num_books; ++i) {
        cout << "\nBook " << (i + 1) << ":" << endl;
        Book b = read_book();
        root = insert_node(b, root);
    }
    
    cout << "\n--- AVL Tree Preorder Traversal ---" << endl;
    print(root);
    
    int delete_isbn;
    cout << "\nEnter ISBN of book to delete: ";
    cin >> delete_isbn;
    
    root = delete_node(delete_isbn, root);
    
    cout << "\n--- AVL Tree Preorder Traversal after Deletion ---" << endl;
    print(root);
    
    return 0;
}
