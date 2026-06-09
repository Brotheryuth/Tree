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

    NodeAdress findParent(NodeAdress current, datatype target){
        // Base Case
        if(current == null) return null;


        if((current->left != null && current->left->info == target) || 
        (current->right != null && current->right->info == target)){
            return current;
        }

        
        NodeAdress findLeft = findParent(current->left, target);

        
        if(findLeft != null){
            return findLeft;
        }
        
        // If it wasn't on the left, search the right subtree and return the result
        return findParent(current->right, target);
    }

    NodeAdress searchNode(NodeAdress root, datatype target){
        if(root ==null){
            return null;
        }
        if(root->info==target){
            return root;
        }
        NodeAdress findLeft = searchNode(root->left,target);
        if(findLeft!=null){
            return findLeft;
        }
        return searchNode(root->right,target);
    }

    void updateNode(NodeAdress node , datatype targetNode , datatype uNode){
        NodeAdress searchForNode = searchNode(node,targetNode);
        if(searchForNode==null){
            return ;
        }else{
            searchForNode->info = uNode;
            return searchForNode;
        }
    }

    void insertRight(NodeAdress root ,NodeAdress targetParent ,datatype item){
        NodeAdress getNodeParent = searchNode(root,targetParent);
        if(getNodeParent==null){
            return;
        }
            makeRight(getNodeParent , item);
    }

    void insertLeft (NodeAdress root , datatype targetParent , datatype item){
        NodeAdress getLeftParent  = searchNode(root , targetParent);
        if(getLeftParent ==null){
            return;
        }
        makeLeft(getLeftParent,item);
    }


    int main ( ){
        NodeAdress pRoot ; 
        int size;
        printf("Enter the size of node : ");
        scanf("%d",&size);
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

        // find parent 
        char targetNode;
        printf("\nEnter the Node you want to search for its parent:");
        scanf(" %c",&targetNode);
        if(pRoot->info ==targetNode){
            printf("\n%c is the root\n",targetNode);
        }else{
            NodeAdress findNode = findParent(pRoot , targetNode);
            if(findNode!=null)
            printf("\n The parent of %c is  :%c\n",targetNode,findNode->info);
            else
                printf("\nSearch not Found\n");
        }

        datatype tNode;
        datatype UpdateNode;
        printf("\nEnter the Node that you want to Update  :");
        scanf(" %c",&targetNode);
        printf("\nEnter new Value                         :");
        scanf(" %c",&UpdateNode);
        updateNode(pRoot, targetNode,UpdateNode);
        preOrder(pRoot);

        insertRight(pRoot ,'2','A');

        return 0;
    }