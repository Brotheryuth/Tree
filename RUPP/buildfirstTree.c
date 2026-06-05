#include<stdio.h>
#include<stdlib.h>
#define null NULL 
typedef char datatype;

struct myTree{
    datatype info;
    struct myTree *left;
    struct myTree *right;
};
// hold block address 
typedef struct myTree *NodeAdress;

// allocate memory 
NodeAdress getNode(){
    NodeAdress p; 
    p = (struct myTree *)malloc(sizeof(struct myTree));
    return p;
}

void freeNode( NodeAdress p ){
    free(p);
}

void initialize(NodeAdress *pRoot){
    *pRoot = null;
}

NodeAdress makeNode( datatype item){
    NodeAdress p = getNode();
    p->info = item;
    p->left = null;
    p->right = null;
    return p;
}


void makeLeft( NodeAdress p , datatype item){
    if(p == null){
        printf("Parent does not exist\n");
        return; 
    }
    if (p->left != null){
        printf("Left child already exists\n");
        return; 
    }
    
    p->left = makeNode(item);
}

void makeRight(NodeAdress p , datatype item){
    if(p == null){
        printf("Parent does not exist\n");
        return;
    }
    if (p->right != null){
        printf("Right child already exists\n");
        return;
    }
    
    p->right = makeNode(item);
}

NodeAdress buildTree(int total_node){
    datatype item; 
    int nl , nr ;
    NodeAdress p;
    if(total_node == 0){
        return null;
    }
    else{
        printf("Info of node: ");

        scanf(" %c", &item);
        
        nl = total_node / 2;
        nr = total_node - nl - 1;
        
        p = makeNode(item);
        p->left = buildTree(nl);
        p->right = buildTree(nr);
        return (p);
    }
}

/**
 * print from node root to subtree left and right  NLR
 */
void preOrder(NodeAdress node ){
    if(node !=null){
    printf("\t%c", node->info );
    preOrder(node->left);
    preOrder(node->right);
    }

}
/**
 * Print node left ->root and right 
 * LNR
 */
void inOrder(NodeAdress node){
    if(node!=null){
        inOrder(node->left);
        printf("\t%c",node->info);
        inOrder(node->right);
    }
}

/**
 * printf from left to right then Root at last 
 * LRN
 */
void postOrder(NodeAdress node){
    if(node!=null){
        postOrder(node->left);
        postOrder(node->right);
        printf("\t%c" , node->info);
    }
}

int main ( ){
    NodeAdress pRoot ; 
    int size = 5;
    initialize(&pRoot);

    printf("Building tree with %d nodes...\n", size);
    pRoot = buildTree(size); 
    printf("Info");
    printf("\nPreorder traversal\n");
    preOrder(pRoot);
    printf("\nIn order traversal\n");
    inOrder(pRoot);
    printf("\nPost order traversal\n");
    postOrder(pRoot);
    return 0;
}