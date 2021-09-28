#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node{
    string name;
    string phonenum;
    Node* left;
    Node* right;

    Node() {}

    Node(string name, string phonenum){
        this->name = name;
        this->phonenum = phonenum;
        this->left = NULL;
        this->right = NULL;
    }
};

Node tree[10000];

void right_rotation(Node* &x){
    Node* y = x->left;
    Node* g = y->right;

    x->left = g;
    y->right = x;

    x = y;
}

void left_rotation(Node* &y) {
    Node *x = y->right;
    Node *g = x->left;

    x->left = y;
    y->right = g;

    y = x;
}

void insertion(Node* &root, string name, string phonenum){
    if(root == NULL) return void(root = new Node(name, phonenum));

    insertion(name <= root->name ? root->left : root->right, name, phonenum);

    if (root->left && root->left->name > root->name)
        right_rotation(root);

    if (root->right && root->right->name > root->name)
        left_rotation(root);
}
// delete node
bool deleteNode(Node* &root, string name){
    if(root == NULL) return false;

    if(name < root->name)
        return deleteNode(root->left, name);
    if(name > root->name)
        return deleteNode(root->right, name);

    
    //no child
    if(root->left == NULL && root->right == NULL){
        delete root;
        root = NULL;
        cout << "Deleted\n";
    }
    //one child
    else if(!root->right || !root->left){
        Node* child = (root->left) ? root->left : root->right;
        Node* old_root = root;
        root = child;
        delete old_root;
        cout << "Deleted\n";
    }
    //two child
    else{
        if(root->left->name < root->right->name){
            left_rotation(root);
            deleteNode(root->left, name);
        }
        else{
            right_rotation(root);
            deleteNode(root->right, name);
        }
    }
    
    return true;
}
//inorder tree traversal
void inorder(Node* node){
    if(node == NULL){ 
        return;
    }
    inorder(node->left);
    cout << node->name << "  " << node-> phonenum << "\n";
    inorder(node->right);
}

void search(Node* &node, string name){
    if(node == NULL){
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
    string phonenum;
    bool b = true;
    while(b){
        int button;
        cout << "insertion 1, remove 2, arrange 3, save 4, search 5, escape 6" << "\n";
        cin >> button;
        switch(button){
            case 1:
                cin >> name >> phonenum;
                insertion(root, name, phonenum);
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