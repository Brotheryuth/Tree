#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<limits>

using namespace std;


const auto null = nullptr;

typedef int datatype;

struct myTree
{
    datatype info;
    struct myTree *left;
    struct myTree *right;
};
// hold block address
typedef struct myTree *NodeAdress;
// allocate memory
NodeAdress getNode()
{
    NodeAdress p;
    p = new myTree;
    return p;
}

void freeNode(NodeAdress p)
{
    free(p);
}

void initialize(NodeAdress *pRoot)
{
    *pRoot = null;
}

NodeAdress makeNode(datatype item)
{
    NodeAdress p = getNode();
    p->info = item;
    p->left = null;
    p->right = null;
    return p;
}

void insert(NodeAdress &root , datatype item){
    if(root ==null){
        root = makeNode(item);

    }else{
        if(item ==root->info){
            printf("%d already exist\n",item);
        }
        else if( root->info >item){
            insert(root->left,item);
        }
        else{
            insert(root->right,item);
        }
    }
}

NodeAdress findParent(NodeAdress root, datatype target) {
    if (root == nullptr || root->info == target) {
        return nullptr;
    }
    NodeAdress curr = root;
    NodeAdress parent = nullptr;
    while (curr != nullptr && curr->info != target) {
        parent = curr;
        if (target < curr->info) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return (curr != nullptr) ? parent : nullptr;
}

// Finds the minimum node in a BST (helper for deletion)
NodeAdress findMin(NodeAdress root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Finds the maximum node in a BST (helper for deletion)
NodeAdress findMax(NodeAdress root) {
    while (root && root->right != nullptr) {
        root = root->right;
    }
    return root;
}

// Deletes a node from BST maintaining the invariants
NodeAdress deleteNode(NodeAdress root, datatype target, bool& success) {
    if (root == nullptr) {
        return nullptr;
    }
    if (target < root->info) {
        root->left = deleteNode(root->left, target, success);
    } else if (target > root->info) {
        root->right = deleteNode(root->right, target, success);
    } else {
        success = true;
        // Case 1: Node with 0 or 1 child
        if (root->left == nullptr) {
            NodeAdress temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            NodeAdress temp = root->left;
            delete root;
            return temp;
        }
        // Case 2: Node with 2 children
        char choice;
        while (true) {
            cout << "\nNode '" << root->info << "' has two children. Prefer replacement from left or right subtree? (l/r): ";
            cin >> choice;
            cin.clear();
            cin.ignore();

            if (choice == 'l' || choice == 'L' || choice == 'r' || choice == 'R') {
                break;
            }
            cout << "Invalid choice! Enter 'l' or 'r'.\n";
        }

        if (choice == 'l' || choice == 'L') {
            // Traverse to the right of left subtree (find the biggest)
            NodeAdress temp = findMax(root->left);
            root->info = temp->info;
            root->left = deleteNode(root->left, temp->info, success);
        } else {
            // Traverse to the left of right subtree (find the smallest)
            NodeAdress temp = findMin(root->right);
            root->info = temp->info;
            root->right = deleteNode(root->right, temp->info, success);
        }
    }
    return root;
}


void deleteNode(NodeAdress& root, datatype target) {
    bool success = false;
    root = deleteNode(root, target, success);
    if (success) {
        cout << "Node '" << target << "' has been deleted successfully.\n";
    } else {
        cout << "Node '" << target << "' not found in the tree.\n";
    }
}

// Traversals (NLR)
void preOrder(NodeAdress root) {
    if (root == nullptr) return;
    cout << "\t" << root->info;
    preOrder(root->left);
    preOrder(root->right);
}

// Traversals (LNR)
void inOrder(NodeAdress root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << "\t" << root->info;
    inOrder(root->right);
}

// Traversals (LRN)
void postOrder(NodeAdress root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << "\t" << root->info;
}

int getHeight(NodeAdress root) {
    if (root == nullptr) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

void fillCanvas(NodeAdress node, int row, int col, int depth, int height, vector<string>& canvas) {
    if (node == nullptr || row >= canvas.size() || col < 1 || col >= canvas[0].size() - 1)
        return;

    string V = to_string(node->info);
    int L = V.length();
    int start_col = col - L / 2;
    for (int i = 0; i < L; ++i) {
        if (start_col + i >= 0 && start_col + i < canvas[0].size()) {
            canvas[row][start_col + i] = V[i];
        }
    }
    if (start_col - 1 >= 0) canvas[row][start_col - 1] = '[';
    if (start_col + L < canvas[0].size()) canvas[row][start_col + L] = ']';

    if (depth < height - 1) {
        int shift = 2 << (height - 2 - depth);

        if (node->left != nullptr && col - shift > 0) {
            canvas[row + 1][col - shift + 1] = '/';
            fillCanvas(node->left, row + 2, col - shift, depth + 1, height, canvas);
        }

        if (node->right != nullptr && col + shift < canvas[0].size()) {
            canvas[row + 1][col + shift - 1] = '\\';
            fillCanvas(node->right, row + 2, col + shift, depth + 1, height, canvas);
        }
    }
}

// Renders the visual representation
void displayTree(NodeAdress root) {
    int h = getHeight(root);
    if (h == 0) {
        cout << "\nTree is completely empty.\n";
        return;
    }

    int max_rows = 2 * h - 1;
    int max_cols = (1 << (h + 1)) + 10;

    vector<string> canvas(max_rows, string(max_cols, ' '));
    int root_col = (1 << h) + 2;

    fillCanvas(root, 0, root_col, 0, h, canvas);

    cout << "\n\n";
    for (const auto& row : canvas) {
        int last_non_space = row.find_last_not_of(' ');
        if (last_non_space != string::npos) {
            cout << row.substr(0, last_non_space + 1) << "\n";
        } else {
            cout << "\n";
        }
    }
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Clears standard input buffer safely
void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void runInsertionLoop(NodeAdress &root) {
    char addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        clearScreen();
        cout << "============================================\n";
        cout << "               INSERT NODE                  \n";
        cout << "============================================\n";
        displayTree(root);
        cout << "============================================\n";
        
        cout << "Enter integer value to insert: ";
        datatype item;
        cin >> item;
        clearBuffer();

        insert(root, item);


        clearScreen();
        cout << "============================================\n";
        cout << "               INSERT NODE                  \n";
        cout << "============================================\n";
        displayTree(root);
        cout << "============================================\n";

        
        cout << "Do you want to add more? (y/n): ";
        cin >> addMore;
        clearBuffer();
    }
}

int main() {
    NodeAdress root;
    initialize(&root);


    int choice = -1;
    do {
        clearScreen();
        cout << "============================================\n";
        cout << "            CURRENT TREE         \n";
        cout << "============================================\n";
        displayTree(root);
        cout << " [1] Insert Node(s)\n";
        cout << " [2] Show Traversals (Pre, In, Post)\n";
        cout << " [3] Delete Node\n";
        cout << " [0] Exit Program\n";
        cout << "============================================\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid choice input! Press Enter to try again...";
            clearBuffer();
            cin.get();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                runInsertionLoop(root);
                break;
            case 2: {
                clearScreen();
                cout << "============================================\n";
                cout << "            CURRENT TREE        \n";
                cout << "============================================\n";
                displayTree(root);
                cout << "============================================\n";
                cout << "               BST TRAVERSALS               \n";
                cout << "============================================\n";
                if (root == nullptr) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "Pre-order (NLR) Traversal:\n";
                    preOrder(root);
                    cout << "\n\nIn-order (LNR) Traversal (Sorted):\n";
                    inOrder(root);
                    cout << "\n\nPost-order (LRN) Traversal:\n";
                    postOrder(root);
                    cout << "\n";
                }
                cout << "============================================\n";
                cout << "Press Enter to return to menu...";
                cin.get();
                break;
            }


            case 3:{
                cout << "\n============================================\n";
                cout << "         DELETE A NODE IN BST       \n";
                cout << "============================================\n";
                displayTree(root);
                cout << "\n============================================\n";
                cout << "Enter the value of the node to delete: ";
                datatype target;
                cin >> target;
                clearBuffer();
                deleteNode(root, target);
                cout << "\n============================================\n";
                cout << "Press Enter to return to menu...";
                cin.get();
                break;
            }
            case 0:
                cout << "\nExiting BST program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please select 1, 2, or 0. Press Enter to retry...";
                cin.get();
                break;
        }
    } while (choice != 0);

    return 0;
}
