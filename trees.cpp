#include <iostream>
#define SPACE 25 // do drukowania drzewa ilosc spacji miedzy wezlami!
using namespace std;
//wspomagalem sie filmem pana z youtube: https://www.youtube.com/watch?v=FNeL18KsWPc oraz https://www.youtube.com/watch?v=otiDcwZbCo4
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
            if(new_node->value < r->value) r->left = insert(r->left, new_node); //rekurencyjne dodawanie wezla
            else if (new_node->value > r->value) r->right = insert(r->right, new_node);
            else {cout<<"nie mozna dodac dwoch tych samych wartosci!\n"; return r;}
            int bf = getBalanceFactor(r); // pobieramy balans drzewa
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
        void print2D(TreeNode * r, int space){ // wziete z filmiku podlinkowanego na poczatku
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
            if (root == nullptr) // If the tree is empty
                return root;

            // Perform standard BST delete
            if (key < root->value)
                root->left = deleteNode(root->left, key);
            else if (key > root->value)
                root->right = deleteNode(root->right, key);
            else {
                // Node with one child or no child
                if ((root->left == nullptr) || (root->right == nullptr)) {
                    TreeNode* temp = root->left ? root->left : root->right;
                    if (temp == nullptr) { // No child case
                        temp = root;
                        root = nullptr;
                    } else { // One child case
                        *root = *temp; // Copy the contents of the non-empty child
                    }
                    delete temp;
                } else {
                    // Node with two children: Get the inorder successor
                    TreeNode* temp = minValueNode(root->right);
                    root->value = temp->value; // Copy the inorder successor's data to this node
                    root->right = deleteNode(root->right, temp->value); // Delete the inorder successor
                }
            }

            // If the tree had only one node then return
            if (root == nullptr)
                return root;

            // Get the balance factor
            int balance = getBalanceFactor(root);

            // Balance the tree
            // Left Left Case
            if (balance > 1 && getBalanceFactor(root->left) >= 0)
                return rightRotate(root);

            // Left Right Case
            if (balance > 1 && getBalanceFactor(root->left) < 0) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            // Right Right Case
            if (balance < -1 && getBalanceFactor(root->right) <= 0)
                return leftRotate(root);

            // Right Left Case
            if (balance < -1 && getBalanceFactor(root->right) > 0) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;
        }

        TreeNode* ancestor(TreeNode* root, int val){
            if(root == nullptr) return nullptr; //jesli nie ma drzewa
            if(root->value == val) return root; //jesli znaleziono wartosc
            if(root->value > val) return ancestor(root->left, val); //jesli wartosc jest mniejsza niz wartosc wezla
            return ancestor(root->right, val);// zwraca przodka
        }
        TreeNode* successor(TreeNode* root, int val){
            if(root == nullptr) return nullptr; //analogicznie
            if(root->value == val){ // jesli znaleziono wartosc
                if(root->right != nullptr){ //jesli istnieje prawe dziecko
                    TreeNode* temp = root->right; //przechodzimy do prawego dziecka
                    while(temp->left != nullptr) temp = temp->left; //przechodzimy do lewego dziecka
                    return temp;//zwracamy wartosc
                }
            }
            if(root->value < val) return successor(root->right, val); //jesli wartosc jest wieksza niz wartosc wezla zwraca nastepnika
            TreeNode* temp = successor(root->left, val);
            if(temp == nullptr) return root;
            return temp;
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
        cout<<"6. znajdz przodka\n";
        cout<<"7. znajdz nastepnika\n";
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
            case 6:
                cout<<"wpisz wartosc\n";
                cin>>val;
                if(objekt.ancestor(objekt.root, val)!=nullptr) 
                    cout<<"przodek znaleziony i wynosi: "<<objekt.ancestor(objekt.root, val)->value<<endl;
                else cout<<"przodek nie znaleziony\n";
                break;
            case 7:
                cout<<"wpisz wartosc\n";
                cin>>val;
                if(objekt.successor(objekt.root, val)!=nullptr) 
                    cout<<"nastepnik znaleziony i wynosi: "<<objekt.successor(objekt.root,val)->value<<endl;
                else cout<<"nastepnik nie znaleziony\n";
            case 8: {
                // Insert nodes in the specified order
                int values[] = {10, 7, 12, 3, 8, 11, 13, 2, 5, 9, 14, 4, 6};
                for (int val : values) {
                    TreeNode* new_node = new TreeNode(val);
                    objekt.root = objekt.insert(objekt.root, new_node);
                }
                cout << "Initial AVL Tree:" << endl;
                objekt.print2D(objekt.root, 0);

                // Delete node with value 10
                objekt.root = objekt.deleteNode(objekt.root, 10);
                cout << "\nAVL Tree after deleting 10:" << endl;
                objekt.print2D(objekt.root, 0);
                break;
            }
            default:
                cout<<"wybierz poprawna opcje\n";
        };
    }
    while(option!=0);
    return 0;
}
