#include<iostream>
#define null NULL
#include<stdexcept>

typedef char datatype;
struct BinaryTree{
    datatype info;
    struct BinaryTree *left;
    struct BinaryTree *right;
};
typedef struct BinaryTree  *bTree;

bTree getNode(){
    bTree newNode= (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    if(newNode ==null){
        throw std::runtime_error("Node is not being created");
    }
    return newNode;
}

void inititalize(bTree *node){
        *node=null;
}
/**
 * function brer derm3 pkert node. pel pkert node vea oy field info = item tea left right null doysa kleng ng tuk connect tv node pseng tt 
 * @param item oy item mk pkert node del mean domlai smer item ng
 *  
 */
bTree makeNode(datatype item){
    bTree newNode = getNode();
    if(newNode ==null){
        throw std::runtime_error("new not is not being created");
    }
    newNode->info = item;
    newNode->left = null;
    newNode->right = null;
    return newNode;
}

/**
 * tuk check mer tha parent ng mean ot
 * @param parent ng 
 */
bool isParentExist(bTree parent){
    if(parent !=null){
        return true;
    }
        return false;
}

/**
 * @brief check mer child khang jveng, kron tah yk parent bos vea mk hz check khang jveng ber sin jea min men null te ah ng vea ot torn mean child te
 * @return 
 *  true ber sin jea ot mean child te
 *  false ber sin jea left child mean hz 
 */
bool isLeftExist(bTree parent){
    if(parent->left!=null){
        return true;
    }
    return false;
}

bool isRightExist(bTree parent){
    if(parent->right !=null){
        return true;
    }
    return false;
}

void   makeLeft(bTree parent , datatype item){
    if(!isParentExist(parent)){
        return;
    }

    if(!isLeftExist(parent)){}
    return;

    }
    bTree newNode = getNode();
    newNode->inf
}

int main(){

}