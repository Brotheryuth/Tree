#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>

typedef char datatype;

struct BinaryTree {
    datatype info;
    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;
};

using bTree = BinaryTree*;

// Allocates memory for a node
bTree makeNode(datatype item) {
    bTree newNode = new BinaryTree;
    newNode->info = item;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Deallocates the tree nodes safely (post-order traversal)
void destroyTree(bTree root) {
    if (root == nullptr) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

// Calculates tree height (1-based, empty tree is height 0)
int getHeight(bTree root) {
    if (root == nullptr) return 0;
    return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

// Inserts a node maintaining the BST property (no duplicates)
void insert(bTree& root, datatype item) {
    if (root == nullptr) {
        root = makeNode(item);
    } else {
        if (item == root->info) {
            std::cout << "\nValue '" << item << "' already exists in the BST.\n";
        } else if (item < root->info) {
            insert(root->left, item);
        } else {
            insert(root->right, item);
        }
    }
}

// Search for a node in $O(\log n)$
bTree searchNode(bTree root, datatype target) {
    if (root == nullptr || root->info == target) {
        return root;
    }
    if (target < root->info) {
        return searchNode(root->left, target);
    }
    return searchNode(root->right, target);
}

// Finds the parent of a target node in $O(\log n)$
bTree findParent(bTree root, datatype target) {
    if (root == nullptr || root->info == target) {
        return nullptr;
    }
    bTree curr = root;
    bTree parent = nullptr;
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
bTree findMin(bTree root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Finds the maximum node in a BST (helper for deletion)
bTree findMax(bTree root) {
    while (root && root->right != nullptr) {
        root = root->right;
    }
    return root;
}

// Deletes a node from BST maintaining the invariants
bTree deleteNode(bTree root, datatype target, bool& success) {
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
            bTree temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            bTree temp = root->left;
            delete root;
            return temp;
        }
        // Case 2: Node with 2 children
        char choice;
        while (true) {
            std::cout << "\nNode '" << root->info << "' has two children. Prefer replacement from left or right subtree? (l/r): ";
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 'l' || choice == 'L' || choice == 'r' || choice == 'R') {
                break;
            }
            std::cout << "Invalid choice! Enter 'l' or 'r'.\n";
        }

        if (choice == 'l' || choice == 'L') {
            // Traverse to the right of left subtree (find the biggest)
            bTree temp = findMax(root->left);
            root->info = temp->info;
            root->left = deleteNode(root->left, temp->info, success);
        } else {
            // Traverse to the left of right subtree (find the smallest)
            bTree temp = findMin(root->right);
            root->info = temp->info;
            root->right = deleteNode(root->right, temp->info, success);
        }
    }
    return root;
}

// Wrapper for delete action printouts
void deleteNodeWrapper(bTree& root, datatype target) {
    bool success = false;
    root = deleteNode(root, target, success);
    if (success) {
        std::cout << "Node '" << target << "' and its sub-relationships updated successfully.\n";
    } else {
        std::cout << "Node '" << target << "' not found in the tree.\n";
    }
}

// Updates a node safely without breaking BST invariants
void updateNode(bTree& root, datatype targetVal, datatype newVal) {
    if (searchNode(root, targetVal) == nullptr) {
        std::cout << "\nNode '" << targetVal << "' not found in the tree.\n";
        return;
    }
    if (targetVal != newVal && searchNode(root, newVal) != nullptr) {
        std::cout << "\nNode with value '" << newVal << "' already exists. Update aborted to prevent duplicates.\n";
        return;
    }
    bool success = false;
    root = deleteNode(root, targetVal, success);
    if (success) {
        insert(root, newVal);
        std::cout << "\nNode updated successfully!\n";
    }
}
#pragma region  Traversal
// Traversals (NLR)
void preOrder(bTree root) {
    if (root == nullptr) return;
    std::cout << "\t" << root->info;
    preOrder(root->left);
    preOrder(root->right);
}

// Traversals (LNR)
void inOrder(bTree root) {
    if (root == nullptr) return;
    inOrder(root->left);
    std::cout << "\t" << root->info;
    inOrder(root->right);
}

// Traversals (LRN)
void postOrder(bTree root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    std::cout << "\t" << root->info;
}
#pragma endregion
#pragma region Canva

// Populates layout recursively
void fillCanvas(bTree node, int row, int col, int depth, int height, std::vector<std::string>& canvas) {
    if (node == nullptr || row >= canvas.size() || col < 1 || col >= canvas[0].size() - 1)
        return;

    canvas[row][col] = node->info;
    canvas[row][col - 1] = '[';
    canvas[row][col + 1] = ']';

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
void displayTree(bTree root) {
    int h = getHeight(root);
    if (h == 0) {
        std::cout << "\nTree is completely empty.\n";
        return;
    }

    int max_rows = 2 * h - 1;
    int max_cols = (1 << (h + 1)) + 10;

    std::vector<std::string> canvas(max_rows, std::string(max_cols, ' '));
    int root_col = (1 << h) + 2;

    fillCanvas(root, 0, root_col, 0, h, canvas);

    std::cout << "\n\n";
    for (const auto& row : canvas) {
        int last_non_space = row.find_last_not_of(' ');
        if (last_non_space != std::string::npos) {
            std::cout << row.substr(0, last_non_space + 1) << "\n";
        } else {
            std::cout << "\n";
        }
    }
}

#pragma endregion 

// Clears console screen cleanly
void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Clears standard input buffer safely
void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    bTree pRoot = nullptr;

    int choice;
    datatype targetNode;
    datatype updateNodeVal;
    datatype itemVal;
    std::string sequence;

    do {
        std::cout << "\n============================================\n";
        std::cout << "          BINARY SEARCH TREE MENU          \n";
        std::cout << "============================================\n";
        std::cout << " [1] Build Tree from Sequence (Reinitialize)\n";
        std::cout << " [2] Display Tree (Visual Graph Layout)\n";
        std::cout << " [3] Show All Traversals (Pre, In, Post)\n";
        std::cout << " [4] Find Parent of a Node\n";
        std::cout << " [5] Search for a Node\n";
        std::cout << " [6] Insert a Node\n";
        std::cout << " [7] Update a Node's Value\n";
        std::cout << " [8] Delete Node\n";
        std::cout << " [0] Exit Program\n";
        std::cout << "============================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "\nInvalid input! Press Enter to try again...";
            clearBuffer();
            std::cin.get();
            clearScreen();
            continue;
        }
        clearBuffer();

        clearScreen();

        switch (choice) {
        case 1:
            if (pRoot != nullptr) {
                std::cout << "Existing tree detected. Deallocating memory first...\n";
                destroyTree(pRoot);
                pRoot = nullptr;
            }
            std::cout << "Enter a sequence of characters to build the BST (e.g. 527138): ";
            std::cin >> sequence;
            clearBuffer();
            for (char c : sequence) {
                insert(pRoot, c);
            }
            std::cout << "\nTree built successfully from sequence: " << sequence << "\n";
            std::cout << "\nPress Enter to clear and continue...";
            std::cin.get();
            clearScreen();
            break;

        case 2:
            displayTree(pRoot);
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 3:
            if (pRoot == nullptr) {
                std::cout << "Tree is empty.\n";
            } else {
                std::cout << "\n--- Tree Traversals ---\n";
                std::cout << "\nPre-order (NLR) Traversal:\n";
                preOrder(pRoot);
                std::cout << "\n\nIn-order (LNR) Traversal (Sorted):\n";
                inOrder(pRoot);
                std::cout << "\n\nPost-order (LRN) Traversal:\n";
                postOrder(pRoot);
                std::cout << "\n";
            }
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 4:
            if (pRoot == nullptr) {
                std::cout << "Tree is empty. Cannot search.\n";
            } else {
                std::cout << "Enter the target node character to search for its parent: ";
                std::cin >> targetNode;
                clearBuffer();

                if (pRoot->info == targetNode) {
                    std::cout << "\nNode [" << targetNode << "] is the absolute Root (It has no parent).\n";
                } else {
                    bTree parentNode = findParent(pRoot, targetNode);
                    if (parentNode != nullptr)
                        std::cout << "\nThe parent of [" << targetNode << "] is: -> [" << parentNode->info << "]\n";
                    else
                        std::cout << "\nTarget node [" << targetNode << "] not found in the tree.\n";
                }
            }
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 5:
            if (pRoot == nullptr) {
                std::cout << "Tree is empty. Cannot search.\n";
            } else {
                std::cout << "Enter target node character to search: ";
                std::cin >> targetNode;
                clearBuffer();

                bTree found = searchNode(pRoot, targetNode);
                if (found != nullptr) {
                    std::cout << "\nNode [" << targetNode << "] found in the BST!\n";
                } else {
                    std::cout << "\nNode [" << targetNode << "] not found in the BST.\n";
                }
            }
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 6:
            std::cout << "Enter character value for the new node: ";
            std::cin >> itemVal;
            clearBuffer();

            insert(pRoot, itemVal);
            std::cout << "\nNode inserted. Verify changes via Display option.\n";
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 7:
            if (pRoot == nullptr) {
                std::cout << "Tree is empty.\n";
            } else {
                std::cout << "Enter the node value you want to Update: ";
                std::cin >> targetNode;
                std::cout << "Enter its new replacement character value: ";
                std::cin >> updateNodeVal;
                clearBuffer();

                updateNode(pRoot, targetNode, updateNodeVal);
            }
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 8:
            if (pRoot == nullptr) {
                std::cout << "Tree is empty. Nothing to delete.\n";
            } else {
                std::cout << "Enter target node character to delete: ";
                std::cin >> targetNode;
                clearBuffer();

                deleteNodeWrapper(pRoot, targetNode);
            }
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get();
            clearScreen();
            break;

        case 0:
            std::cout << "Deallocating runtime tree components...\n";
            destroyTree(pRoot);
            std::cout << "Exiting application safely. Goodbye!\n";
            break;

        default:
            std::cout << "Option choice unrecognized. Select an item from 0 to 8.\n";
            std::cout << "\nPress Enter to retry...";
            std::cin.get();
            clearScreen();
            break;
        }
    } while (choice != 0);

    return 0;
}
