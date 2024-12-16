#include <iostream>

using namespace std;
class Node{
public:
    int data;
    Node* right;
    Node* left;
    Node(int data){
        this->data=data;
        right=left=NULL;
    }
};
class BinarySearchTree{
private:

    Node* root;
    Node* getNodeByData(int data){
        Node* current =root;
        while(current != NULL){
            if(data ==current->data){
                return current;
            }else if(data>current->data){
                current=current->right;
            }else{
                current=current->left;
            }
        }
        return NULL;
    }
    Node* getParent(Node* node){
        Node* parent =root;
        while(parent != NULL){
            if(parent->right== node || parent->left == node){
                return parent;
            }else if(node->data > parent->data){
                parent=parent->right;
            }else{
                parent=parent->left;
            }
        }
        return NULL;
    }
    Node * getMaxRight(Node * node){
            Node * current=node;
            while(current -> right !=NULL ){
                current=current->right;
            }
            return current;
    }
    void display(Node *node){
                if (node==NULL){
                    return;
                }
                display(node->left);
                cout<< node->data <<"  ";
                display(node->right);

    }
    int calculateMaxDepth(Node* node) {
        if (node == NULL) {
            return 0;
        }
        int leftDepth = calculateMaxDepth(node->left);
        int rightDepth = calculateMaxDepth(node->right);
        return (leftDepth > rightDepth)?leftDepth+1:rightDepth+1;
    }

public:
    BinarySearchTree(){
        root=NULL;
    }
    void add(int data){
        Node* newNode=new Node(data);
        if(root==NULL){
            root=newNode;
        }else{
            Node* current=root;
            Node* parent;
            while(current != NULL){
                parent=current;
                if(data > current->data){
                    current=current->right;
                }else {
                    current=current->left;
                }
            }
            if(data > parent->data){
                parent->right=newNode;
            }
            else{
                parent->left=newNode;
            }
        }
    }
    void removeNode(int data){
        Node* node=getNodeByData(data);
        if(node==NULL){
            return;
        }
        if(node==root){
            cout<<"it is root node so it can not be deleted"<<endl;
        }else{
            Node* parent=getParent(node);
            Node* newChild=NULL;
            if(node->left==NULL && node->right==NULL){
                newChild=NULL;
            }else if(node->left==NULL){
                newChild=node->right;
            }else if(node->right==NULL){
                newChild=node->left;
            }else{
                Node* newParent=node->left;
                Node* maxRightofLeftChild=getMaxRight(newParent);
                maxRightofLeftChild->right=node->right;
                newChild=newParent;
            }
            if(parent->left==node){
                        parent->left=newChild;
                }else{
                    parent->right=newChild;
                }
        }
        delete node;
    }
     Node* minimum(){
        if(root==NULL){
            cout<<"tree is empty"<<endl;
            return NULL;
        }
        Node* current=root;
         while(current->left != NULL){
                current=current->left;
         }
         return current;
    }
    Node* maximum(){
        if(root==NULL){
            return NULL;
        }
        Node* current=root;
         while(current->right != NULL){
                current=current->right;
         }
         return current;
    }
    void displayAll(){
            display(root);
            cout<<endl;
        }
    int maxDepth() {
        return calculateMaxDepth(root);
    }

};
int main()
{
     BinarySearchTree bst;
     bst.add(5);
     bst.add(3);
     bst.add(7);
     bst.add(2);
     bst.add(4);
     bst.add(6);
     bst.add(8);
     bst.displayAll();
     cout<<bst.maxDepth()<<endl;
     Node* minNode = bst.minimum();
     Node* maxNode = bst.maximum();
     (minNode==NULL)?cout<<"tree is empty"<<endl:cout<<"min = "<<minNode->data <<endl;
     (maxNode==NULL)?cout<<"tree is empty"<<endl:cout<<"max = "<<maxNode->data <<endl;
     bst.removeNode(4);
     bst.displayAll();
    return 0;
}
