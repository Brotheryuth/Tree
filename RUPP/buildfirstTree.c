#include <stdio.h>
#include <stdlib.h>
#define null NULL
typedef char datatype;

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
    p = (struct myTree *)malloc(sizeof(struct myTree));
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

void makeLeft(NodeAdress p, datatype item)
{
    if (p == null)
    {
        printf("Parent does not exist\n");
        return;
    }
    if (p->left != null)
    {
        printf("Left child already exists\n");
        return;
    }

    p->left = makeNode(item);
}

void makeRight(NodeAdress p, datatype item)
{
    if (p == null)
    {
        printf("Parent does not exist\n");
        return;
    }
    if (p->right != null)
    {
        printf("Right child already exists\n");
        return;
    }

    p->right = makeNode(item);
}

/**
 * print from node root to subtree left and right  NLR
 */
void preOrder(NodeAdress node)
{
    if (node != null)
    {
        printf("\t%c", node->info);
        preOrder(node->left);
        preOrder(node->right);
    }
}
/**
 * Print node left ->root and right
 * LNR
 */
void inOrder(NodeAdress node)
{
    if (node != null)
    {
        inOrder(node->left);
        printf("\t%c", node->info);
        inOrder(node->right);
    }
}

/**
 * printf from left to right then Root at last
 * LRN
 */
void postOrder(NodeAdress node)
{
    if (node != null)
    {
        postOrder(node->left);
        postOrder(node->right);
        printf("\t%c", node->info);
    }
}

NodeAdress findParent(NodeAdress current, datatype target)
{
    // Base Case
    if (current == null)
        return null;

    if ((current->left != null && current->left->info == target) ||
        (current->right != null && current->right->info == target))
    {
        return current;
    }

    NodeAdress findLeft = findParent(current->left, target);

    if (findLeft != null)
    {
        return findLeft;
    }

    // If it wasn't on the left, search the right subtree and return the result
    return findParent(current->right, target);
}

NodeAdress searchNode(NodeAdress root, datatype target)
{
    if (root == null)
    {
        return null;
    }
    if (root->info == target)
    {
        return root;
    }
    NodeAdress findLeft = searchNode(root->left, target);
    if (findLeft != null)
    {
        return findLeft;
    }
    return searchNode(root->right, target);
}

void updateNode(NodeAdress node, datatype targetNode, datatype uNode)
{
    NodeAdress searchForNode = searchNode(node, targetNode);
    if (searchForNode != null)
    {
        searchForNode->info = uNode;
    }
}

void insertRight(NodeAdress root, datatype targetParent, datatype item)
{
    NodeAdress getNodeParent = searchNode(root, targetParent);
    if (getNodeParent == null)
    {
        return;
    }
    makeRight(getNodeParent, item);
}

void insertLeft(NodeAdress root, datatype targetParent, datatype item)
{
    NodeAdress getLeftParent = searchNode(root, targetParent);
    if (getLeftParent == null)
    {
        return;
    }
    makeLeft(getLeftParent, item);
}
void freeChildren(NodeAdress root)
{
    if (root == null)
    {
        return;
    }
    freeChildren(root->left);
    freeChildren(root->right);
    free(root);
}
void deleteNode(NodeAdress *root, datatype target)
{
    if (*root == null)
    {
        return;
    }
    // if delete node is the root
    if ((*root)->info == target)
    {
        NodeAdress temp = *root;
        freeChildren(temp);
        *root = null;
        printf("Delete successfully");
        return;
    }
    // if not
    NodeAdress parent = findParent(*root, target);
    if (parent == null)
    {
        printf("Root not found ");
        return;
    }
    NodeAdress branch = null; // a temp branch to grab the entire branch
    if (parent->left != null && parent->left->info == target)
    {
        branch = parent->left; // get the address of the target node
        parent->left = null;   // disconnect it from the tree
    }
    else
    {
        branch = parent->right;
        parent->right = null;
    }

    freeChildren(branch);
    printf("Node is being deleted successfully");
}

NodeAdress buildTree(int total_node, char parent_info)
{
    datatype item;
    int nl, nr;
    NodeAdress p;

    if (total_node == 0)
    {
        return null;
    }
    else
    {
        printf("\nInfo of node: ");
        scanf(" %c", &item);

        //'#', it means this node is the ROOT
        if (parent_info == '#')
        {
            printf("\n -> [%c] is the ROOT of the entire tree (No Parent) \n", item);
        }
        else
        {
            printf("\n -> [%c] is The Parent of [%c]\n", parent_info, item);
        }

        nl = total_node / 2;
        nr = total_node - nl - 1;

        printf("The left node count for [%c] is %d\n", item, nl);
        printf("The Right node count for [%c] is %d\n", item, nr);

        p = makeNode(item);

        // RECURSION FIX: Pass the current 'item' as the parent for the next nodes!
        p->left = buildTree(nl, item);
        p->right = buildTree(nr, item);

        return (p);
    }
}

int getHeight(NodeAdress root)
{
    if (root == null)
        return 0;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    return (lh > rh ? lh : rh) + 1;
}

void fillCanvas(NodeAdress node, int row, int col, int depth, int height, char **canvas, int max_rows, int max_cols)
{
    if (node == null || row >= max_rows || col < 1 || col >= max_cols - 1)
        return;

    // Place the current node with brackets
    canvas[row][col] = node->info;
    canvas[row][col - 1] = '[';
    canvas[row][col + 1] = ']';

    // If there are children below, calculate spacing dynamically
    if (depth < height - 1)
    {
        // Exponentially scale shift distance based on remaining height
        int shift = 2 << (height - 2 - depth);

        // Process Left Child
        if (node->left != null && col - shift > 0)
        {
            canvas[row + 1][col - shift + 1] = '/';
            fillCanvas(node->left, row + 2, col - shift, depth + 1, height, canvas, max_rows, max_cols);
        }

        // Process Right Child
        if (node->right != null && col + shift < max_cols)
        {
            canvas[row + 1][col + shift - 1] = '\\';
            fillCanvas(node->right, row + 2, col + shift, depth + 1, height, canvas, max_rows, max_cols);
        }
    }
}

void displayTree(NodeAdress root)
{
    int h = getHeight(root);
    if (h == 0)
    {
        printf("\nTree is completely empty.\n");
        return;
    }

    int max_rows = 2 * h - 1;
    // Calculate total layout width dynamically based on tree height
    int max_cols = (1 << (h + 1)) + 10;

    // Allocate 2D canvas dynamically
    char **canvas = (char **)malloc(max_rows * sizeof(char *));
    for (int i = 0; i < max_rows; i++)
    {
        canvas[i] = (char *)malloc(max_cols * sizeof(char));
        for (int j = 0; j < max_cols; j++)
        {
            canvas[i][j] = ' '; // Populate with spaces
        }
    }

    // Determine the optimal middle coordinate for the root node
    int root_col = (1 << h) + 2;

    // Populate the canvas recursively
    fillCanvas(root, 0, root_col, 0, h, canvas, max_rows, max_cols);

    // Print the canvas row by row, automatically trimming trailing spaces
    printf("\n\n");
    for (int i = 0; i < max_rows; i++)
    {
        int last_non_space = -1;
        for (int j = max_cols - 1; j >= 0; j--)
        {
            if (canvas[i][j] != ' ')
            {
                last_non_space = j;
                break;
            }
        }
        if (last_non_space != -1)
        {
            for (int j = 0; j <= last_non_space; j++)
            {
                putchar(canvas[i][j]);
            }
        }
        putchar('\n');
    }


    // Clean up allocated memory
    for (int i = 0; i < max_rows; i++)
    {
        free(canvas[i]);
    }
    free(canvas);
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Helper utility to flush input buffer and prevent character skipping bugs
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    NodeAdress pRoot;
    initialize(&pRoot);

    int choice;
    int size;
    datatype targetNode;
    datatype updateNodeVal;
    datatype itemVal;

    do
    {
        printf("\n============================================\n");
        printf("         BINARY TREE MANAGEMENT MENU        \n");
        printf("============================================\n");
        printf(" [1] Build / Reinitialize Tree\n");
        printf(" [2] Display Tree (Visual Graph Layout)\n");
        printf(" [3] Show All Traversals (Pre, In, Post)\n");
        printf(" [4] Find Parent of a Node\n");
        printf(" [5] Update a Node's Value\n");
        printf(" [6] Insert Left Child\n");
        printf(" [7] Insert Right Child\n");
        printf(" [8] Delete Node / Branch\n");
        printf(" [0] Exit Program\n");
        printf("============================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Press Enter to try again...");
            clearBuffer();
            getchar();
            clearScreen();
            continue;
        }
        clearBuffer(); // Clean line buffer after integer read

        // Clear terminal right after an option is selected for clean workspace
        clearScreen(); 

        switch (choice)
        {
        case 1:
            if (pRoot != null)
            {
                printf("Existing tree detected. Deallocating memory first...\n");
                freeChildren(pRoot);
                initialize(&pRoot);
            }
            printf("Enter the total size of the tree (number of nodes): ");
            scanf("%d", &size);
            clearBuffer();
            
            printf("Building tree with %d nodes...\n", size);
            pRoot = buildTree(size, '#');
            
            printf("\nTree initialized successfully! Press Enter to clear and continue...");
            getchar();
            clearScreen();
            break;

        case 2:
            displayTree(pRoot);
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 3:
            if (pRoot == null)
            {
                printf("Tree is empty.\n");
            }
            else
            {
                printf("\n--- Tree Traversals ---\n");
                printf("\nPre-order (NLR) Traversal:\n");
                preOrder(pRoot);
                printf("\n\nIn-order (LNR) Traversal:\n");
                inOrder(pRoot);
                printf("\n\nPost-order (LRN) Traversal:\n");
                postOrder(pRoot);
                printf("\n");
            }
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 4:
            if (pRoot == null)
            {
                printf("Tree is empty. Cannot search.\n");
            }
            else
            {
                printf("Enter the target node character to search for its parent: ");
                scanf(" %c", &targetNode);
                clearBuffer();

                if (pRoot->info == targetNode)
                {
                    printf("\nNode [%c] is the absolute Root (It has no parent).\n", targetNode);
                }
                else
                {
                    NodeAdress findNode = findParent(pRoot, targetNode);
                    if (findNode != null)
                        printf("\nThe parent of [%c] is: -> [%c]\n", targetNode, findNode->info);
                    else
                        printf("\nTarget node [%c] not found in the tree.\n", targetNode);
                }
            }
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 5:
            if (pRoot == null)
            {
                printf("Tree is empty.\n");
            }
            else
            {
                printf("Enter the node value you want to Update: ");
                scanf(" %c", &targetNode);
                printf("Enter its new replacement character value: ");
                scanf(" %c", &updateNodeVal);
                clearBuffer();

                updateNode(pRoot, targetNode, updateNodeVal);
                printf("\nUpdate action completed. Verify changes via Display option.\n");
            }
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 6:
            if (pRoot == null)
            {
                printf("Tree is empty. Please build a root node first.\n");
            }
            else
            {
                printf("Enter parent target node character: ");
                scanf(" %c", &targetNode);
                printf("Enter character value for the new LEFT child: ");
                scanf(" %c", &itemVal);
                clearBuffer();

                insertLeft(pRoot, targetNode, itemVal);
            }
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 7:
            if (pRoot == null)
            {
                printf("Tree is empty. Please build a root node first.\n");
            }
            else
            {
                printf("Enter parent target node character: ");
                scanf(" %c", &targetNode);
                printf("Enter character value for the new RIGHT child: ");
                scanf(" %c", &itemVal);
                clearBuffer();

                insertRight(pRoot, targetNode, itemVal);
            }
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 8:
            if (pRoot == null)
            {
                printf("Tree is empty. Nothing to delete.\n");
            }
            else
            {
                printf("Enter target node character to delete (Warning: This drops its whole branch): ");
                scanf(" %c", &targetNode);
                clearBuffer();

                deleteNode(&pRoot, targetNode);
                printf("\n");
            }
            printf("\nPress Enter to return to menu...");
            getchar();
            clearScreen();
            break;

        case 0:
            printf("Deallocating runtime tree components...\n");
            freeChildren(pRoot);
            printf("Exiting application safely. Goodbye!\n");
            break;

        default:
            printf("Option choice unrecognized. Select an item from 0 to 8.\n");
            printf("\nPress Enter to retry...");
            getchar();
            clearScreen();
            break;
        }
    } while (choice != 0);

    return 0;
}