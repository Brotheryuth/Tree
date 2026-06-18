#include<iostream>
#define null nullptr
#include<stdexcept>

typedef char datatype;
struct BinaryTree{
    datatype info;
    struct BinaryTree *left;
    struct BinaryTree *right;
};
using bTree =BinaryTree*;

bTree getNode(){
    bTree newNode= new BinaryTree;
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
    if(isLeftExist(parent)){    
        throw std::runtime_error("Left child already exist");
    }
    parent->left= makeNode(item);
}

void makeRight( bTree parent , datatype item){
    if(!isParentExist(parent)){
        throw  std::runtime_error("Parent does  not exsit ");
    }
    if(!isRightExist(parent)){
        throw std::runtime_error("Node right already exist ");
    }
    parent->right= makeNode(item);
}
/**
 *@brief pkert binary node
 */
void insert (bTree *root , datatype item){
     bTree p;
     /**
      * ber sin jea ot torn mean node ey node tbong ke ng jea root.
      */
    if(*root ==nullptr){
        p = getNode();
        p->info=item;
        p->left = null;
        p->right=null;
        *root = p; // make the first node to be the root
    }
    else{
        if(item == (*root)->info){
            throw std::runtime_error("Value already exsit");
        }
        else if (item < (*root)->info) {
            insert(&((*root)->left),  item);  // jol tv khang jveng jong kroty ke. doysa yg point tv left jg left ber left yg null yg dak node kleng ng
        }
        else{
            insert(&((*root)->right),  item); // doch knea
        }
    }
}

void preOrder(bTree root){
    if(root==null){
        return;
    }
    std::cout<<root->info<<"\t";
    preOrder(root->left);
    preOrder(root->right);
}

/**
 * can be use for sort since binary search tree it already oragnize the value
 */
void inOrder(bTree root){
    if(root==null) return;
    inOrder(root->left);
    std::cout<<root->info<<"\t";
    inOrder(root->right);

}

void postOrder(bTree root){
    if(root==null){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    std::cout<<root->info<<"\t";
}

int main(){
    bTree p;
    inititalize(&p);
    insert(&p,  '5');
    insert(&p,  '2');
    insert(&p,  '1');
    insert(&p,'7');
    preOrder(p);
    std::cout<<"\n";
    inOrder(p);
    
}
