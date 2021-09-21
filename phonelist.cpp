#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node{
    string name;
    long phonenum;
    Node* left;
    Node* right;
};

Node tree[10000];

Node* insertion(Node* node, string name, long phonenum){
    if(node == NULL){
        node = new Node();
        node->name = name;
        node->phonenum = phonenum;
        node->left = node->right = NULL;
    }

    else if(name <= node->name){
        node->left = insertion(node->left, name, phonenum);
    }
    else {
        node->right = insertion(node->right, name, phonenum);
    }
    return node;
}

Node* FindMax(Node* root){
    if(root == NULL) return NULL;

    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

Node* deleteNode(Node* root, string name){
    if(root == NULL) return root;
    else if(name < root->name)
        root->left = deleteNode(root->left, name);
    else if(name > root->name)
        root->right = deleteNode(root->right, name);
    else{
        //no child
        if(root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
            cout << "Deleted\n";
        }
        //one child
        else if(root->right == NULL){
            Node* temp = root;
            root = root->left;
            delete temp;
            cout << "Deleted\n";
        }
        else if(root->left == NULL){
            Node* temp = root;
            root = root->right;
            delete temp;
            cout << "Deleted\n";
        }
        //two child
        else{
            Node* temp = FindMax(root->left);
            root->name = temp->name;
            root->left = deleteNode(root->left, temp->name);
        }
    }
    return root;
}


void preorder(Node* node){
    cout << node->name << "  " << node-> phonenum << "\n";

    if(node->left != NULL)
        preorder(node->left);
    if(node->right != NULL)
        preorder(node->right);
}

void inorder(Node* node){
    if(node->left != NULL)
        inorder(node->left);
    cout << node->name << "  " << node-> phonenum << "\n";
    if(node->right != NULL)
        inorder(node->right);
}

void search(Node* node, string name){
    if(node == NULL){
        cout << "This is empty\n";
        return;
    }

    Node* current = node;

    while(current){
        if(current->name == name){
            cout << current->name << " " << current->phonenum << "\n";
            return;
        }
        else if(current->name > name)
            current = current->left;
        else
            current = current->right;
    }

    cout << name << " does not exist" <<"\n";
    return;
}

int main() {
    Node* root = NULL;
    string name;
    long phonenum;
    bool b = true;
    while(b){
        int button;
        cout << "insertion 1, remove 2, arrange 3, save 4, search 5, escape 6" << "\n";
        cin >> button;
        switch(button){
            case 1:
                cin >> name >> phonenum;
                root = insertion(root, name, phonenum);
                break;
            case 2:
                cin >> name;
                deleteNode(root, name);
                break;
            case 3:
                inorder(root);
                break;
            case 4:
                break;
            case 5:
                cin >> name;
                search(root, name);
                break;
            case 6:
                b = false;
                break;
            default:
                cout << "wrong button try again" << "\n";
                break; 
        }
    }

    return 0;
}
//https://www.codegrepper.com/code-examples/cpp/delete+node+from+tree+c%2B%2B
//https://blog.weirdx.io/post/3120