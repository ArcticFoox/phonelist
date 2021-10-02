#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>

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

ifstream readfromFile;
ofstream writeFile;
bool savepoint = false;

//rotation process 를 하기 위한 함수
void right_rotation(Node* &x){
    Node* y = x->left;
    Node* g = y->right;

    x->left = g;
    y->right = x;

    x = y;
}
//rotation process 를 하기 위한 함수
void left_rotation(Node* &y) {
    Node *x = y->right;
    Node *g = x->left;

    x->left = y;
    y->right = g;

    y = x;
}
//add를 하기 위한 함수
void insertion(Node* &root, string name, string phonenum){
    if(root == NULL) return void(root = new Node(name, phonenum));

    insertion(name <= root->name ? root->left : root->right, name, phonenum);

    if (root->left && root->left->name > root->name)
        right_rotation(root);

    if (root->right && root->right->name > root->name)
        left_rotation(root);
}
// delete node를 하기 위한 함수
bool deleteNode(Node* &root, string name){
    if(root == NULL) return false;

    if(name < root->name)
        return deleteNode(root->left, name);
    if(name > root->name)
        return deleteNode(root->right, name);
    
    //no child 일 경우
    if(root->left == NULL && root->right == NULL){
        delete root;
        root = NULL;
        cout << "Deleted\n";
    }
    //one child 일 경우
    else if(!root->right || !root->left){
        Node* child = (root->left) ? root->left : root->right;
        Node* old_root = root;
        root = child;
        delete old_root;
        cout << "Deleted\n";
    }
    //two child 일 경우
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
//inorder tree traversal(arrange)를 하기 위한 함수
void inorder(Node* &root){
    if(root == NULL){ 
        return;
    }
    inorder(root->left);
    cout << root->name << "  " << root-> phonenum << "\n";
    inorder(root->right);
}
//search를 하기 위한 함수
void search(Node* &root, string name){
    if(root == NULL){
        return;
    }

    Node* current = root;

    while(current){
        if(current->name == name){
            cout << current->name << " " << current->phonenum << "\n";
            if(current->left->name == name){
                current = current->left;
                continue;
            }
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
//save를 하기 위한 함수
void save(Node* &root){
    writeFile.open("phonelist.txt");

    if(savepoint){
        writeFile.clear();
    }
    
    if(root == NULL){ 
        return;
    }

    save(root->left);
    writeFile.write(root->name.c_str(), root->name.size());
    writeFile.write(" ", 1);
    writeFile.write(root->phonenum.c_str(), root->phonenum.size());
    writeFile.write("\n", 1);
    save(root->right);
}
// load를 하기 위한 함수
void load(Node* &root){
    readfromFile.open("phonelist.txt");

    if(readfromFile.is_open()){
        while(!readfromFile.eof()){
            string str1, str2;
            bool judge = true;

            if(judge){
                readfromFile >> str1;
                judge = false;
            }

            if(!judge){
                readfromFile >> str2;
                judge = true;
            }

            insertion(root, str1, str2);
        }
        readfromFile.close();
    }
    return;
}

int main() {
    Node* root = NULL;
    string name;
    string phonenum;
    bool it = true;
    load(root);
    while(it){
        int button;
        cout << "insertion 1, remove 2, arrange 3, save 4, search 5, escape 6" << "\n";
        cin >> button;
        switch(button){
            case 1:
                cout << "Enter name and phonenumber\n";
                cin >> name >> phonenum;
                insertion(root, name, phonenum);
                break;
            case 2:
                cout << "Enter the name\n";
                cin >> name;
                if(deleteNode(root, name))
                    cout << name << " is removed\n";
                else
                    cout << name << " is not found\n";
                break;
            case 3:
                inorder(root);
                break;
            case 4:
                savepoint = true;
                save(root);
                writeFile.close();
                cout << "List is saved"<< "\n";
                break;
            case 5:
                cout << "Enter the name\n";
                cin >> name;
                search(root, name);
                break;
            case 6:
                it = false;
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