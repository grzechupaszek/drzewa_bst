#include <iostream>
#define SPACE 10 // do drukowania drzewa ilosc spacji miedzy wezlami!
using namespace std;

class TreeNode {
    public:
        int value;
        TreeNode * left;
        TreeNode * right;
    TreeNode(){
        value = 0;
        left = nullptr;
        right = nullptr;
    }
    TreeNode(int v){
        value = v;
        left = nullptr;
        right = nullptr;
    }
};
class AVLTree{
    public:
        TreeNode * root;
        AVLTree(){
            root = nullptr;
        }
        bool isTreeEmpty(){
            if(root==nullptr) return true;
            else return false;
        }
        int height(TreeNode* r){
            if (r == nullptr) return -1;
            else{
                //compute the height of each subtree
                int lheight = height(r->left);
                int rheight = height(r->right);
                // use the larger one
                if (lheight>rheight) return  (lheight+1);
                else return (rheight+1);
            }
        }
        int getBalanceFactor(TreeNode * n){
            if(n==nullptr) return -1;
            return height(n->left) - height(n->right);
        }
        TreeNode *rightRotate(TreeNode * y){
            TreeNode *x = y->left;
            TreeNode *T2 = x->right;
            //performing rotation
            x->right = y;
            y->left = T2;
            return x;
        }
        TreeNode *leftRotate(TreeNode * x){
            TreeNode *y = x->right;
            TreeNode *T2 = y->left;
            //performing rotation
            y->left = x;
            x->right = T2;
            return y;
        }
        TreeNode* insert (TreeNode * r, TreeNode * new_node){
            if(r == nullptr){
                r = new_node;
                cout<< "Wartosc wrzucona prawidlowo!\n";
                return r;
            }
            if(new_node->value < r->value) r->left = insert(r->left, new_node);
            else if (new_node->value > r->value) r->right = insert(r->right, new_node);
            else {cout<<"nie mozna dodac dwoch tych samych wartosci!\n"; return r;}
            int bf = getBalanceFactor(r);
            //Left Left Case
            if(bf > 1 && new_node->value < r->left->value) return rightRotate(r);
            //Right Right case
            if(bf < -1 && new_node->value > r->right->value) return leftRotate(r);
            //Left Right case
            if(bf > 1 && new_node->value > r->right->value){
                r->left = leftRotate(r->left);
                return rightRotate(r);
            }
            //Right Left case
            if(bf < -1 && new_node->value < r->right->value){
                r->right = rightRotate(r->right);
                return leftRotate(r);
            }
            return r;
        }
        void print2D(TreeNode * r, int space){
            if (r==nullptr) return;
            space += SPACE;
            print2D(r->right,space);
            cout<<endl;
            for(int i = SPACE; i<space; i++){
                cout<<" ";
            }
            cout<<r->value<<endl;
            print2D(r->left, space);
        }
        TreeNode* recursiveSearch(TreeNode* r, int val){
            if(r == nullptr || r->value == val) return r;
            else if ( val < r->value) return recursiveSearch(r->left, val);
            else return recursiveSearch(r->right, val);
        }

        TreeNode* minValueNode(TreeNode* node) {
            TreeNode* current = node;
            while (current->left != nullptr)
                current = current->left;
            return current;
        }

        TreeNode* deleteNode(TreeNode* root, int key) {
            if (root == nullptr)
                return root;

            if (key < root->value)
                root->left = deleteNode(root->left, key);
            else if (key > root->value)
                root->right = deleteNode(root->right, key);
            else {
                if ((root->left == nullptr) || (root->right == nullptr)) {
                    TreeNode* temp = root->left ? root->left : root->right;
                    if (temp == nullptr) {
                        temp = root;
                        root = nullptr;
                    } else
                        *root = *temp;
                    delete temp;
                } else {
                    TreeNode* temp = minValueNode(root->right);
                    root->value = temp->value;
                    root->right = deleteNode(root->right, temp->value);
                }
            }

            if (root == nullptr)
                return root;

            // Update height of the current node
            int leftHeight = height(root->left);
            int rightHeight = height(root->right);

            // Get the balance factor
            int balance = leftHeight - rightHeight;

            // Balance the tree
            if (balance > 1 && key < root->left->value)
                return rightRotate(root);

            if (balance < -1 && key > root->right->value)
                return leftRotate(root);

            if (balance > 1 && key > root->left->value) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            if (balance < -1 && key < root->right->value) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;
        }
};
int main()
{
    AVLTree objekt;
    int option, val;
    do {
        cout<<"1. Wstaw wezel\n";
        cout<<"2. szukaj wezla\n";
        cout<<"3. usun wezel\n";
        cout<<"4. wyswietl drzewo\n";
        cout<<"5. wysokosc drzewa\n";
        cout<<"0. wyjdz\n";
        cin>>option;
        TreeNode *new_node = new TreeNode();

        switch (option){
            case 0: break;
            case 1:
                cout<<"wpisz wartosc do drzewa avl!\n";
                cin>> val;
                new_node->value  = val;
                objekt.root=objekt.insert(objekt.root, new_node);
                cout<<endl;
                break;
            case 2:
                cout<<"wpisz szukana wartosc\n";
                cin>>val;
                if(objekt.recursiveSearch(objekt.root, val)!=nullptr) cout<<"Znaleziono wartosc\n";
                else cout<<"Nie znaleziono wartosci\n";
                break;
            case 3:
                cout<<"wpisz wartosc do usuniecia\n";
                cin>>val;
                objekt.root = objekt.deleteNode(objekt.root, val);
                cout<< "wezel usuniety\n";
                break;
            case 4:
                objekt.print2D(objekt.root, 0);
                break;
            case 5:
                cout<<"wysokosc drzewa: "<<objekt.height(objekt.root)<<endl;
                break;
            default:
                cout<<"wybierz poprawna opcje\n";
        };
    
    }
    while(option!=0);
    return 0;
}