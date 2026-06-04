#include <iostream>
#include <string>
using namespace std;

// Simple Node structure
struct Node {
    string id;
    string name;
    int level;
    Node* parent;
    Node* children;
    Node* nextSibling;
};

Node* root = nullptr;

// ===================== BASIC FUNCTIONS =====================

// Create new node
Node* createNode(string id, string name, int level) {
    Node* newNode = new Node;
    newNode->id = id;
    newNode->name = name;
    newNode->level = level;
    newNode->parent = nullptr;
    newNode->children = nullptr;
    newNode->nextSibling = nullptr;
    return newNode;
}

// Find node by ID
Node* findNode(Node* current, string id) {
    if (current == nullptr) return nullptr;
    if (current->id == id) return current;
    
    Node* result = findNode(current->children, id);
    if (result != nullptr) return result;
    
    return findNode(current->nextSibling, id);
}

// Add child to parent
void addChild(Node* parent, Node* child) {
    child->parent = parent;

    if (parent->children == nullptr) { // check if there's no child, so it becomes the first child
        parent->children = child;
    } else {
        Node* temp = parent->children;
        while (temp->nextSibling != nullptr) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Add node to tree
void addNode(string parentId, string id, string name, int level) {
    Node* newNode = createNode(id, name, level);
    
    if (parentId == "") { //check if it is empty to, so it becomes the root
        root = newNode;
        return;
    }

    Node* parent = findNode(root, parentId); //otherwise, it finds the parent by id and attaches the new node to it 
    if (parent != nullptr) {
        addChild(parent, newNode);
    }
}

// ===================== OPERATION 1: LIST CHILDREN =====================
void listChildren(string nodeId) {
    Node* node = findNode(root, nodeId);
    if (node == nullptr) { // it check if the node is found 
        cout << "Not found!" << endl;
        return; //leave the function if not found 
    }
    cout << "Children of " << node->name << ":" << endl; // print the name of the node  example children of Cambodia...
    
    Node* child = node->children; //get the first child 
    int count = 1; // for listing 
    while (child != nullptr) { // traverse until there is no more child 
        cout << "  " << count << ". " << child->name << endl;
        child = child->nextSibling; //move to its sibling 
        count++;
    }
}

// ===================== OPERATION 2: COUNT DESCENDANTS =====================
int countDescendants(Node* node) {
    if (node == nullptr) return 0;
    
    int count = 0;
    Node* child = node->children;
    
    while (child != nullptr) {
        count = count + 1 + countDescendants(child);
        child = child->nextSibling;
    }
    
    return count;
}

void showCount(string nodeId) {
    Node* node = findNode(root, nodeId);
    if (node == nullptr) {
        cout << "Not found!" << endl;
        return;
    }
    
    int total = countDescendants(node);
    cout << "Total under " << node->name << ": " << total << endl;
}

// ===================== OPERATION 3: FIND PARENT =====================
void findParent(string nodeId) {
    Node* node = findNode(root, nodeId);
    if (node == nullptr) {
        cout << "Not found!" << endl;
        return;
    }
    
    if (node->parent == nullptr) {
        cout << node->name << " is the root" << endl;
    } else {
        cout << "Parent of " << node->name << ": " << node->parent->name << endl;
    }
}

// ===================== OPERATION 4: PATH TO ROOT =====================
void pathToRoot(string nodeId) {
    Node* node = findNode(root, nodeId);
    if (node == nullptr) {
        cout << "Not found!" << endl;
        return;
    }
    
    cout << "Path: ";
    Node* current = node;
    while (current != nullptr) {
        cout << current->name;
        if (current->parent != nullptr) cout << " -> ";
        current = current->parent;
    }
    cout << endl;
}

// ===================== OPERATION 5: LEVEL LISTING =====================
void showLevel(Node* node, int targetLevel) {
    if (node == nullptr) return;
    
    if (node->level == targetLevel) {
        cout << "  - " << node->name << endl;
    }
    
    showLevel(node->children, targetLevel);
    showLevel(node->nextSibling, targetLevel);
}

void listLevel(int level) {
    cout << "All at Level " << level << ":" << endl;
    showLevel(root, level);
}

// ===================== OPERATION 6: REPARENT =====================
void removeFromParent(Node* node) {
    if (node == nullptr || node->parent == nullptr) return;
    
    Node* parent = node->parent;
    
    if (parent->children == node) {
        parent->children = node->nextSibling;
        node->nextSibling = nullptr;
        return;
    }
    
    Node* prev = parent->children;
    while (prev != nullptr && prev->nextSibling != node) {
        prev = prev->nextSibling;
    }
    
    if (prev != nullptr) {
        prev->nextSibling = node->nextSibling;
        node->nextSibling = nullptr;
    }
}

void reparent(string nodeId, string newParentId) {
    Node* node = findNode(root, nodeId);
    Node* newParent = findNode(root, newParentId);
    
    if (node == nullptr || newParent == nullptr) {
        cout << "Not found!" << endl;
        return;
    }
    
    cout << "Moving " << node->name << " to " << newParent->name << endl;
    
    removeFromParent(node);
    addChild(newParent, node);
}

// ===================== OPERATION 7: SEARCH =====================
Node* search(Node* current, string query) {
    if (current == nullptr) return nullptr;
    
    if (current->name.find(query) != string::npos || 
        current->id.find(query) != string::npos) {
        return current;
    }
    
    Node* result = search(current->children, query);
    if (result != nullptr) return result;
    
    return search(current->nextSibling, query);
}

void searchNode(string query) {
    Node* result = search(root, query);
    
    if (result == nullptr) {
        cout << "Not found!" << endl;
    } else {
        cout << "Found: " << result->name << " (ID: " << result->id << ")" << endl;
    }
}

// ===================== BUILD TREE =====================
void buildTree() {
    // Root
    addNode("", "Cambodia", "Cambodia", 0);

    // Provinces
    addNode("Cambodia", "PNH", "Phnom Penh", 1);
    addNode("Cambodia", "KDL", "Kandal", 1);
    addNode("Cambodia", "PVG", "Prey Veng", 1);
    
    // Phnom Penh Districts
    addNode("PNH", "PNH_CM", "Khan Chamkarmon", 2);
    addNode("PNH", "PNH_DP", "Khan Daun Penh", 2);
    addNode("PNH", "PNH_7M", "Khan 7 Makara", 2);
    
    // Kandal Districts
    addNode("KDL", "KDL_KS", "Kandal Stueng District", 2);
    addNode("KDL", "KDL_KH", "Kien Svay District", 2);
    addNode("KDL", "KDL_TA", "Ta Khmao District", 2);
    
    // Prey Veng Districts
    addNode("PVG", "PVG_BA", "Ba Phnum District", 2);
    addNode("PVG", "PVG_KP", "Kampong Trabaek District", 2);
    addNode("PVG", "PVG_PV", "Prey Veng District", 2);
    
    // Khan Chamkarmon Sangkats
    addNode("PNH_CM", "PNH_CM_TSP1", "Sangkat Toul Svay Prey I", 3);
    addNode("PNH_CM", "PNH_CM_TSP2", "Sangkat Toul Svay Prey II", 3);
    addNode("PNH_CM", "PNH_CM_BKK", "Sangkat Boeung Keng Kang", 3);
    
    // Khan Daun Penh Sangkats
    addNode("PNH_DP", "PNH_DP_CH", "Sangkat Chaktomuk", 3);
    addNode("PNH_DP", "PNH_DP_PS", "Sangkat Phsar Thmei", 3);
    addNode("PNH_DP", "PNH_DP_SR", "Sangkat Srah Chak", 3);
    
    // Khan 7 Makara Sangkats
    addNode("PNH_7M", "PNH_7M_BT", "Sangkat Boeng Trabaek", 3);
    addNode("PNH_7M", "PNH_7M_CP", "Sangkat Chak Angrae Leu", 3);
    addNode("PNH_7M", "PNH_7M_MT", "Sangkat Mittapheap", 3);
    
    // Kandal Communes
    addNode("KDL_KS", "KDL_KS_KS", "Khum Kandal Stueng", 3);
    addNode("KDL_KS", "KDL_KS_PP", "Khum Preaek Pnov", 3);
    addNode("KDL_KS", "KDL_KS_RL", "Khum Roluos", 3);
    
    addNode("KDL_KH", "KDL_KH_KS", "Khum Kien Svay", 3);
    addNode("KDL_KH", "KDL_KH_PT", "Khum Pouthi Ban", 3);
    addNode("KDL_KH", "KDL_KH_TK", "Khum Tuek Thla", 3);
    
    addNode("KDL_TA", "KDL_TA_TK", "Khum Ta Khmao", 3);
    addNode("KDL_TA", "KDL_TA_PL", "Khum Prek Leap", 3);
    addNode("KDL_TA", "KDL_TA_KA", "Khum Krangthnung", 3);
    
    // Prey Veng Communes
    addNode("PVG_BA", "PVG_BA_BP", "Khum Ba Phnum", 3);
    addNode("PVG_BA", "PVG_BA_PK", "Khum Prey Krabas", 3);
    addNode("PVG_BA", "PVG_BA_RP", "Khum Roka Khnol", 3);
    
    addNode("PVG_KP", "PVG_KP_KT", "Khum Kampong Trabaek", 3);
    addNode("PVG_KP", "PVG_KP_AP", "Khum Ampil Tuek", 3);
    addNode("PVG_KP", "PVG_KP_CH", "Khum Chheu Teal", 3);
    
    addNode("PVG_PV", "PVG_PV_PV", "Khum Prey Veng", 3);
    addNode("PVG_PV", "PVG_PV_KT", "Khum Kouk Thlok Lech", 3);
    addNode("PVG_PV", "PVG_PV_PR", "Khum Preaek Anhchanh", 3);
    
    // Villages - Just a sample to keep it simple
    addNode("PNH_CM_TSP1", "V1", "Phum Toul Svay Prey 1", 4);
    addNode("PNH_CM_TSP1", "V2", "Phum Toul Svay Prey 2", 4);
    addNode("PNH_CM_TSP1", "V3", "Phum Toul Svay Prey 3", 4);
    
    addNode("PNH_CM_TSP2", "V4", "Phum Boeng Keng Kang 1", 4);
    addNode("PNH_CM_TSP2", "V5", "Phum Boeng Keng Kang 2", 4);
    
    addNode("PNH_DP_CH", "V10", "Phum Wat Phnom", 4);
    addNode("PNH_DP_CH", "V11", "Phum Olympic", 4);
    
    addNode("KDL_KS_KS", "V28", "Phum Kandal Stueng Lech", 4);
    addNode("KDL_KS_KS", "V29", "Phum Kandal Stueng Kaeut", 4);
    
    addNode("PVG_BA_BP", "V55", "Phum Ba Phnum Lech", 4);
    addNode("PVG_BA_BP", "V56", "Phum Ba Phnum Kaeut", 4);
}

// ===================== MAIN =====================
int main() {
    cout << "=== Cambodia Administrative Tree ===\n\n";
    
    buildTree();
    cout << "Tree built!\n\n";
    
    // Test Operation 1: List Children
    cout << "1. LIST CHILDREN\n";
    listChildren("PNH");
    cout << endl;
    listChildren("PNH_CM");
    cout << "\n---\n\n";
    
    // Test Operation 2: Count Descendants
    cout << "2. COUNT DESCENDANTS\n";
    showCount("PNH");
    showCount("PNH_CM");
    cout << "\n---\n\n";
    
    // Test Operation 3: Find Parent
    cout << "3. FIND PARENT\n";
    findParent("PNH_CM_TSP1");
    findParent("KDL_KS");
    cout << "\n---\n\n";
    
    // Test Operation 4: Path to Root
    cout << "4. PATH TO ROOT\n";
    pathToRoot("V1");
    pathToRoot("PVG_BA_BP");
    cout << "\n---\n\n";
    
    // Test Operation 5: Level Listing
    cout << "5. LEVEL LISTING\n";
    listLevel(1);
    cout << endl;
    listLevel(2);
    cout << "\n---\n\n";
    
    // Test Operation 6: Reparent
    cout << "6. REPARENT SUBTREE\n";
    cout << "Before: ";
    findParent("PNH_CM_TSP1");
    reparent("PNH_CM_TSP1", "PNH_DP");
    cout << "After: ";
    findParent("PNH_CM_TSP1");
    cout << "\n---\n\n";
    
    // Test Operation 7: Search
    cout << "7. SEARCH\n";
    searchNode("Toul Svay Prey I");
    searchNode("PVG_BA");
    searchNode("Phnom");
    
    return 0;
}