
#include <iostream>
using namespace std;
struct Node
{
    int data;

    struct Node* next;
    Node(int value){
        data=value;
        next=NULL;
    }

};

Node*  insertAttheEnd(Node** head, int value  ){
    Node* newNode=new Node(value);
    if(*head==NULL){
        return newNode;
    }
    Node* current=*head;
    while(current->next!=NULL){
        current=current->next;
    }
    current->next=newNode;
    return *head;

}
void displayList(Node** head){
    if(*head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    Node* current= *head;
    while(current!=NULL){
        cout<<current->data<<"\t->\t";
        current=current->next;
    }

}
// delete node by value 
void deleteNode(Node** head,int value ){
    if(*head==NULL){
        cout<<"list iss empty "<<endl;
        return;
    }
    // if head need to be deleted
    Node* curr= *head;
    if(curr->data==value){

    }

}
 int main(){
    Node* head=NULL;
    int value;
    
    char op;
    while(op!='n'){
        cout<<"Enter value :"; cin>>value;
        insertAttheEnd(&head,value);
        cout<<"Enter again? "; 
        cin>>op;
    }
    displayList(&head);
    free(head);
 }
