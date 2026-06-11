#include<iostream>
#define null NULL
using namespace std;
typedef char datatype ;
struct Tree {
    struct Tree *left;
    struct Tree *right;
    datatype info;
};
typedef struct Tree Node;

Node getNode(){
    Node p;
    p = (struct Tree*)malloc(sizeof(struct Tree));
    return p;
}
void initialize(Node *p){
    *p=null;
}
int main(){

}