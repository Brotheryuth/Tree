#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
struct Node {
    char id[50];
    char name[100];
    int level;
    struct Node* parent;
    struct Node* children;
    struct Node* nextSibling;
};

struct Node* root = NULL;

// ===================== BASIC FUNCTIONS =====================

// Create new node
struct Node* createNode(char* id, char* name, int level) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->id, id);
    strcpy(newNode->name, name);
    newNode->level = level;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Find node by ID
struct Node* findNode(struct Node* current, char* id) {
    if (current == NULL) return NULL;
    if (strcmp(current->id, id) == 0) return current;
    
    struct Node* result = findNode(current->children, id);
    if (result != NULL) return result;
    
    return findNode(current->nextSibling, id);
}

// Add child to parent
void addChild(struct Node* parent, struct Node* child) {
    child->parent = parent;
    
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        struct Node* temp = parent->children;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Add node to tree
void addNode(char* parentId, char* id, char* name, int level) {
    struct Node* newNode = createNode(id, name, level);
    
    if (strcmp(parentId, "") == 0) {
        root = newNode;
        return;
    }
    
    struct Node* parent = findNode(root, parentId);
    if (parent != NULL) {
        addChild(parent, newNode);
    }
}

// ===================== OPERATION 1: LIST CHILDREN =====================
void listChildren(char* nodeId) {
    struct Node* node = findNode(root, nodeId);
    if (node == NULL) {
        printf("Not found!\n");
        return;
    }
    
    printf("Children of %s:\n", node->name);
    
    struct Node* child = node->children;
    int count = 1;
    while (child != NULL) {
        printf("  %d. %s\n", count, child->name);
        child = child->nextSibling;
        count++;
    }
}

// ===================== OPERATION 2: COUNT DESCENDANTS =====================
int countDescendants(struct Node* node) {
    if (node == NULL) return 0;
    
    int count = 0;
    struct Node* child = node->children;
    
    while (child != NULL) {
        count = count + 1 + countDescendants(child);
        child = child->nextSibling;
    }
    
    return count;
}

// ===================== OPERATION 3: FIND PARENT =====================
void findParent(char* nodeId) {
    struct Node* node = findNode(root, nodeId);
    if (node == NULL) {
        printf("Not found!\n");
        return;
    }
    
    if (node->parent == NULL) {
        printf("%s is the root\n", node->name);
    } else {
        printf("Parent of %s: %s\n", node->name, node->parent->name);
    }
}

// ===================== OPERATION 4: PATH TO ROOT =====================
void pathToRoot(char* nodeId) {
    struct Node* node = findNode(root, nodeId);
    if (node == NULL) {
        printf("Not found!\n");
        return;
    }
    
    printf("Path: ");
    struct Node* current = node;
    while (current != NULL) {
        printf("%s", current->name);
        if (current->parent != NULL) printf(" -> ");
        current = current->parent;
    }
    printf("\n");
}

// ===================== OPERATION 5: LEVEL LISTING =====================
void showLevel(struct Node* node, int targetLevel) {
    if (node == NULL) return;
    
    if (node->level == targetLevel) {
        printf("  - %s\n", node->name);
    }
    
    showLevel(node->children, targetLevel);
    showLevel(node->nextSibling, targetLevel);
}

void listLevel(int level) {
    printf("All at Level %d:\n", level);
    showLevel(root, level);
}

// ===================== OPERATION 6: REPARENT =====================
void removeFromParent(struct Node* node) {
    if (node == NULL || node->parent == NULL) return;
    
    struct Node* parent = node->parent;
    
    if (parent->children == node) {
        parent->children = node->nextSibling;
        node->nextSibling = NULL;
        return;
    }
    
    struct Node* prev = parent->children;
    while (prev != NULL && prev->nextSibling != node) {
        prev = prev->nextSibling;
    }
    
    if (prev != NULL) {
        prev->nextSibling = node->nextSibling;
        node->nextSibling = NULL;
    }
}

void reparent(char* nodeId, char* newParentId) {
    struct Node* node = findNode(root, nodeId);
    struct Node* newParent = findNode(root, newParentId);
    
    if (node == NULL || newParent == NULL) {
        printf("Not found!\n");
        return;
    }
    
    printf("Moving %s to %s\n", node->name, newParent->name);
    
    removeFromParent(node);
    addChild(newParent, node);
}

// ===================== OPERATION 7: SEARCH =====================
struct Node* search(struct Node* current, char* query) {
    if (current == NULL) return NULL;
    
    if (strstr(current->name, query) != NULL || 
        strstr(current->id, query) != NULL) {
        return current;
    }
    
    struct Node* result = search(current->children, query);
    if (result != NULL) return result;
    
    return search(current->nextSibling, query);
}

void searchNode(char* query) {
    struct Node* result = search(root, query);
    
    if (result == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found: %s (ID: %s)\n", result->name, result->id);
    }
}

// ===================== DISPLAY TREE =====================
void displayTree(struct Node* node, char* indent) {
    if (node == NULL) return;
    
    printf("%s+-- %s (ID: %s)\n", indent, node->name, node->id);
    
    char newIndent[200];
    strcpy(newIndent, indent);
    strcat(newIndent, "|   ");
    
    struct Node* child = node->children;
    while (child != NULL) {
        displayTree(child, newIndent);
        child = child->nextSibling;
    }
}

// ===================== BUILD TREE =====================
void buildTree() {
    // Root
    addNode("", "Cambodia", "Cambodia", 0);
    
    // Provinces
    addNode("Cambodia", "PNH", "Phnom_Penh", 1);
    addNode("Cambodia", "KDL", "Kandal", 1);
    addNode("Cambodia", "PVG", "Prey_Veng", 1);

    // Phnom Penh Districts
    addNode("PNH", "PNH_CM", "Khan_Chamkarmon", 2);
    addNode("PNH", "PNH_DP", "Khan_Daun_Penh", 2);
    addNode("PNH", "PNH_7M", "Khan_7_Makara", 2);

    // Kandal Districts
    addNode("KDL", "KDL_KS", "Kandal_Stueng_District", 2);
    addNode("KDL", "KDL_KH", "Kien_Svay_District", 2);
    addNode("KDL", "KDL_TA", "Ta_Khmao_District", 2);

    // Prey Veng Districts
    addNode("PVG", "PVG_BA", "Ba_Phnum_District", 2);
    addNode("PVG", "PVG_KP", "Kampong_Trabaek_District", 2);
    addNode("PVG", "PVG_PV", "Prey_Veng_District", 2);

    // Khan Chamkarmon Sangkats
    addNode("PNH_CM", "PNH_CM_TSP1", "Sangkat_Toul_Svay_PreI", 3);
    addNode("PNH_CM", "PNH_CM_TSP2", "Sangkat_Toul_Svay_PreII", 3);
    addNode("PNH_CM", "PNH_CM_BKK", "Sangkat_Boeung_Keng_Kang", 3);
    
    // Khan Daun Penh Sangkats
    addNode("PNH_DP", "PNH_DP_CH", "Sangkat_Chaktomuk", 3);
    addNode("PNH_DP", "PNH_DP_PS", "Sangkat_Phsar_Thmei", 3);
    addNode("PNH_DP", "PNH_DP_SR", "Sangkat_Srah_Chak", 3);
    
    // Khan 7 Makara Sangkats
    addNode("PNH_7M", "PNH_7M_BT", "Sangkat_Boeng_Trabaek", 3);
    addNode("PNH_7M", "PNH_7M_CP", "Sangkat_Chak_Angrae_Leu", 3);
    addNode("PNH_7M", "PNH_7M_MT", "Sangkat_Mittapheap", 3);
    
    // Kandal Communes
    addNode("KDL_KS", "KDL_KS_KS", "Khum_Kandal_Stueng", 3);
    addNode("KDL_KS", "KDL_KS_PP", "Khum_Preah_Pnov", 3);
    addNode("KDL_KS", "KDL_KS_RL", "Khum_Roluos", 3);

    addNode("KDL_KH", "KDL_KH_KS", "Khum_Kien_Svay", 3);
    addNode("KDL_KH", "KDL_KH_PT", "Khum_Preah_Ban", 3);
    addNode("KDL_KH", "KDL_KH_TK", "Khum_Tuek_Thla", 3);
    
    addNode("KDL_TA", "KDL_TA_TK", "Khum_Ta_Khmao", 3);
    addNode("KDL_TA", "KDL_TA_PL", "Khum_Preuk_Leap", 3);
    addNode("KDL_TA", "KDL_TA_KA", "Khum_Krangthnung", 3);
    
    // Prey Veng Communes
    addNode("PVG_BA", "PVG_BA_BP", "Khum_Ba_Phnum", 3);
    addNode("PVG_BA", "PVG_BA_PK", "Khum_Preah_Krabas", 3);
    addNode("PVG_BA", "PVG_BA_RP", "Khum_Roka_Khnol", 3);

    addNode("PVG_KP", "PVG_KP_KT", "Khum_Kampong_Trabaek", 3);
    addNode("PVG_KP", "PVG_KP_AP", "Khum_Ampil_Tuek", 3);
    addNode("PVG_KP", "PVG_KP_CH", "Khum_Chheu_Teal", 3);

    addNode("PVG_PV", "PVG_PV_PV", "Khum_Prey_Veng", 3);
    addNode("PVG_PV", "PVG_PV_KT", "Khum_Kouk_Thlok_Lech", 3);
    addNode("PVG_PV", "PVG_PV_PR", "Khum_Preah_Anhchanh", 3);
    
    // Villages - Sangkat Toul Svay Prey I
    addNode("PNH_CM_TSP1", "V1", "Phum_Toul_Svay_PreI_1", 4);
    addNode("PNH_CM_TSP1", "V2", "Phum_Toul_Svay_PreI_2", 4);
    addNode("PNH_CM_TSP1", "V3", "Phum_Toul_Svay_PreI_3", 4);
    
    // Villages - Sangkat Toul Svay Prey II
    addNode("PNH_CM_TSP2", "V4", "Phum_Boeng_Keng_Kang_1", 4);
    addNode("PNH_CM_TSP2", "V5", "Phum_Boeng_Keng_Kang_2", 4);
    addNode("PNH_CM_TSP2", "V6", "Phum_Boeng_Keng_Kang_3", 4);

    // Villages - Sangkat Boeung Keng Kang
    addNode("PNH_CM_BKK", "V7", "Phum_BKK_Muoy", 4);
    addNode("PNH_CM_BKK", "V8", "Phum_BKK_Pir", 4);
    addNode("PNH_CM_BKK", "V9", "Phum_BKK_Bei", 4);

    // Villages - Sangkat Chaktomuk
    addNode("PNH_DP_CH", "V10", "Phum_Wat_Phnom", 4);
    addNode("PNH_DP_CH", "V11", "Phum_Olympic", 4);
    addNode("PNH_DP_CH", "V12", "Phum_Riverside", 4);

    // Villages - Sangkat Phsar Thmei
    addNode("PNH_DP_PS", "V13", "Phum_Central_Market", 4);
    addNode("PNH_DP_PS", "V14", "Phum_Sorya_Mall", 4);
    addNode("PNH_DP_PS", "V15", "Phum_Phsar_Thmei_Bei", 4);

    // Villages - Sangkat Srah Chak
    addNode("PNH_DP_SR", "V16", "Phum_Srah_Chak_Muoy", 4);
    addNode("PNH_DP_SR", "V17", "Phum_Srah_Chak_Pir", 4);
    addNode("PNH_DP_SR", "V18", "Phum_Srah_Chak_Bei", 4);

    // Villages - Sangkat Boeng Trabaek
    addNode("PNH_7M_BT", "V19", "Phum_Trabaek_Lech", 4);
    addNode("PNH_7M_BT", "V20", "Phum_Trabaek_Kaeut", 4);
    addNode("PNH_7M_BT", "V21", "Phum_Trabaek_Kandal", 4);

    // Villages - Sangkat Chak Angrae Leu
    addNode("PNH_7M_CP", "V22", "Phum_Angrae_Lech", 4);
    addNode("PNH_7M_CP", "V23", "Phum_Angrae_Kaeut", 4);
    addNode("PNH_7M_CP", "V24", "Phum_Angrae_Kandal", 4);

    // Villages - Sangkat Mittapheap
    addNode("PNH_7M_MT", "V25", "Phum_Mittapheap_Muoy", 4);
    addNode("PNH_7M_MT", "V26", "Phum_Mittapheap_Pir", 4);
    addNode("PNH_7M_MT", "V27", "Phum_Mittapheap_Bei", 4);

    // Villages - Khum Kandal Stueng
    addNode("KDL_KS_KS", "V28", "Phum_Kandal_Stueng_Lech", 4);
    addNode("KDL_KS_KS", "V29", "Phum_Kandal_Stueng_Kaeut", 4);
    addNode("KDL_KS_KS", "V30", "Phum_Kandal_Stueng_Kandal", 4);

    // Villages - Khum Preaek Pnov
    addNode("KDL_KS_PP", "V31", "Phum_Preaek_Pnov_Lech", 4);
    addNode("KDL_KS_PP", "V32", "Phum_Preaek_Pnov_Kaeut", 4);
    addNode("KDL_KS_PP", "V33", "Phum_Preaek_Pnov_Kandal", 4);

    // Villages - Khum Roluos
    addNode("KDL_KS_RL", "V34", "Phum_Roluos_Muoy", 4);
    addNode("KDL_KS_RL", "V35", "Phum_Roluos_Pir", 4);
    addNode("KDL_KS_RL", "V36", "Phum_Roluos_Bei", 4);

    // Villages - Khum Kien Svay
    addNode("KDL_KH_KS", "V37", "Phum_Kien_Svay_Lech", 4);
    addNode("KDL_KH_KS", "V38", "Phum_Kien_Svay_Kaeut", 4);
    addNode("KDL_KH_KS", "V39", "Phum_Kien_Svay_Kandal", 4);

    // Villages - Khum Pouthi Ban
    addNode("KDL_KH_PT", "V40", "Phum_Pouthi_Ban_Lech", 4);
    addNode("KDL_KH_PT", "V41", "Phum_Pouthi_Ban_Kaeut", 4);
    addNode("KDL_KH_PT", "V42", "Phum_Pouthi_Ban_Kandal", 4);

    // Villages - Khum Tuek Thla
    addNode("KDL_KH_TK", "V43", "Phum_Tuek_Thla_Lech", 4);
    addNode("KDL_KH_TK", "V44", "Phum_Tuek_Thla_Kaeut", 4);
    addNode("KDL_KH_TK", "V45", "Phum_Tuek_Thla_Kandal", 4);

    // Villages - Khum Ta Khmao
    addNode("KDL_TA_TK", "V46", "Phum_Ta_Khmao_Muoy", 4);
    addNode("KDL_TA_TK", "V47", "Phum_Ta_Khmao_Pir", 4);
    addNode("KDL_TA_TK", "V48", "Phum_Ta_Khmao_Bei", 4);

    // Villages - Khum Prek Leap
    addNode("KDL_TA_PL", "V49", "Phum_Prek_Leap_Lech", 4);
    addNode("KDL_TA_PL", "V50", "Phum_Prek_Leap_Kaeut", 4);
    addNode("KDL_TA_PL", "V51", "Phum_Prek_Leap_Kandal", 4);

    // Villages - Khum Krangthnung
    addNode("KDL_TA_KA", "V52", "Phum_Krangthnung_Lech", 4);
    addNode("KDL_TA_KA", "V53", "Phum_Krangthnung_Kaeut", 4);
    addNode("KDL_TA_KA", "V54", "Phum_Krangthnung_Kandal", 4);

    // Villages - Khum Ba Phnum
    addNode("PVG_BA_BP", "V55", "Phum_Ba_Phnum_Lech", 4);
    addNode("PVG_BA_BP", "V56", "Phum_Ba_Phnum_Kaeut", 4);
    addNode("PVG_BA_BP", "V57", "Phum_Ba_Phnum_Kandal", 4);

    // Villages - Khum Prey Krabas
    addNode("PVG_BA_PK", "V58", "Phum_Preyk_Krabas_Lech", 4);
    addNode("PVG_BA_PK", "V59", "Phum_Preyk_Krabas_Kaeut", 4);
    addNode("PVG_BA_PK", "V60", "Phum_Preyk_Krabas_Kandal", 4);

    // Villages - Khum Roka Khnol
    addNode("PVG_BA_RP", "V61", "Phum_Roka_Khnol_Lech", 4);
    addNode("PVG_BA_RP", "V62", "Phum_Roka_Khnol_Kaeut", 4);
    addNode("PVG_BA_RP", "V63", "Phum_Roka_Khnol_Kandal", 4);

    // Villages - Khum Kampong Trabaek
    addNode("PVG_KP_KT", "V64", "Phum_Kampong_Trabaek_Lech", 4);
    addNode("PVG_KP_KT", "V65", "Phum_Kampong_Trabaek_Kaeut", 4);
    addNode("PVG_KP_KT", "V66", "Phum_Kampong_Trabaek_Kandal", 4);

    // Villages - Khum Ampil Tuek
    addNode("PVG_KP_AP", "V67", "Phum_Ampil_Tuek_Lech", 4);
    addNode("PVG_KP_AP", "V68", "Phum_Ampil_Tuek_Kaeut", 4);
    addNode("PVG_KP_AP", "V69", "Phum_Ampil_Tuek_Kandal", 4);

    // Villages - Khum Chheu Teal
    addNode("PVG_KP_CH", "V70", "Phum_Chheu_Teal_Lech", 4);
    addNode("PVG_KP_CH", "V71", "Phum_Chheu_Teal_Kaeut", 4);
    addNode("PVG_KP_CH", "V72", "Phum_Chheu_Teal_Kandal", 4);

    // Villages - Khum Prey Veng
    addNode("PVG_PV_PV", "V73", "Phum_Preyk_Veng_Muoy", 4);
    addNode("PVG_PV_PV", "V74", "Phum_Preyk_Veng_Pir", 4);
    addNode("PVG_PV_PV", "V75", "Phum_Preyk_Veng_Bei", 4);

    // Villages - Khum Kouk Thlok Lech
    addNode("PVG_PV_KT", "V76", "Phum_Kouk_Thlok_Lech_1", 4);
    addNode("PVG_PV_KT", "V77", "Phum_Kouk_Thlok_Lech_2", 4);
    addNode("PVG_PV_KT", "V78", "Phum_Kouk_Thlok_Lech_3", 4);

    // Villages - Khum Preaek Anhchanh
    addNode("PVG_PV_PR", "V79", "Phum_Preyk_Anhchanh_Lech", 4);
    addNode("PVG_PV_PR", "V80", "Phum_Preyk_Anhchanh_Kaeut", 4);
    addNode("PVG_PV_PR", "V81", "Phum_Preyk_Anhchanh_Kandal", 4);
}

// ===================== MAIN =====================
int main() {
    char findChild[50];
    char choice;
    
    buildTree();
    
    do {
        printf("\n=== Cambodia Administrative Tree ===\n");
        printf("1. List Children\n");
        printf("2. Display Tree\n");
        printf("3. Count Descendants\n");
        printf("4. Find Parent\n");
        printf("5. Path to Root\n");
        printf("6. List Level\n");
        printf("7. Reparent\n");
        printf("8. Search\n");
        printf("q. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1': {
                printf("Enter node ID: ");
                scanf("%s", findChild);
                listChildren(findChild);
                break;
            }
            case '2': {
                char indent[10] = "";
                displayTree(root, indent);
                break;
            }
            case '3': {
                printf("Enter node ID: ");
                scanf("%s", findChild);
                struct Node* node = findNode(root, findChild);
                if (node != NULL) {
                    int count = countDescendants(node);
                    printf("Descendants of %s: %d\n", node->name, count);
                } else {
                    printf("Not found!\n");
                }
                break;
            }
            case '4': {
                printf("Enter node ID: ");
                scanf("%s", findChild);
                findParent(findChild);
                break;
            }
            case '5': {
                printf("Enter node ID: ");
                scanf("%s", findChild);
                pathToRoot(findChild);
                break;
            }
            case '6': {
                int level;
                printf("Enter level (0-4): ");
                scanf("%d", &level);
                listLevel(level);
                break;
            }
            case '7': {
                char nodeId[50], newParentId[50];
                printf("Enter node ID to move: ");
                scanf("%s", nodeId);
                printf("Enter new parent ID: ");
                scanf("%s", newParentId);
                reparent(nodeId, newParentId);
                break;
            }
            case '8': {
                char query[50];
                printf("Enter name or ID: ");
                scanf("%s", query);
                searchNode(query);
                break;
            }
            case 'q':
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
        
    } while(choice != 'q');
    
    return 0;
}