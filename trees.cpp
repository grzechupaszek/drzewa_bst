#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};
//wstawianie nowego drzewa
Node* insert(Node* root, int key){
    if(root == nullptr){
        return new Node(key);
    }
    if(key<root->data){
        Node* leftchild = insert(root->left, key);
        root->left = leftchild;
        leftchild->parent = root;
    }
    else{
        Node* rightchild = insert(root->right, key);
        root->right = rightchild;
        rightchild->parent = root;
    }
    return root;
};
//wyszukiwanie wezla o danej wartosci
Node* search(Node* root, int key){
    if(root == nullptr || root->data == key){
        return root;
    }
    if(key < root->data){
        return search(root->left, key);
    }
    else{return search(root->right, key);}
}

void inorder(Node* root){
    if (root != nullptr){
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
}
Node* findmax(Node* root){
    while(root->right != nullptr){
        root = root->right;
    }
    return root;
}
Node* findmin(Node* root){
    while(root->left != nullptr){
        root = root->left;
    }
    return root;
}
Node* successor(Node* node){
    if(node->right != nullptr){
        return findmin(node->right);
    }
    Node* p = node -> parent;
    while (p != nullptr && node == p->right){
        node = p;
        p = p->parent;
    }
    return p;
}
Node* ancestor(Node* node){
    if(node->left != nullptr){
        return findmax(node->left);
    }
    Node* p = node -> parent;
    while(p != nullptr && node == p->left){
        node = p;
        p = p->parent;
    }
    return p;
}
//8, 4, 10, 2, 6, 1
void rotationL(Node* & root){ // ROTACJE ZMIENIC BO NIE DZIALA
    Node* newroot = root->right; // nowy korzen
    root->right = newroot->left; // przeniesienie lewego wezla na prawy
    if(newroot->left != nullptr){ // aktualizacja wskaznikow do lewego poddrzewa
        newroot->left->parent;
    }
    newroot->left = root; //nowy korzen jako rodzic starego
    newroot->parent = root->parent; 
    root->parent = newroot; // aktualizacja wskaznika
}
void rotationP(Node* &root){
    Node* newroot = root->left;
    root->right = newroot->right;
    if(newroot->right != nullptr){
        newroot->right->parent;
    }
    newroot->right = root;
    newroot->parent = root->parent;
    root->parent = newroot;
}
int main()
{
    Node* root = nullptr;
    int values[] = {8, 4, 10, 9, 2, 6, 1, 13};
    for (int value : values){
        root = insert(root, value);
    }
    // in-order
    cout << "Przejscie in-order: ";
    inorder(root);
    cout << endl;
     rotationL(root);
    inorder(root);
    // Wyszukiwanie wezla
    int key = 10;
    Node* node = search(root, key);
    if (node != nullptr) {
        cout << "wezel o wartosci to " << node->data << endl;
    } else {
        cout << "Nie znaleziono wezla " << key << endl;
    }

    //znajdowanie minimalnej wartosci w drzewie
    Node* min = findmin(root);
    Node* max = findmax(root);
    cout<<"minimalna wartosc w drzewie to "<< min->data<<endl;
    cout<<"max wartosc w drzewie to "<<max->data<<endl;


    //znajdowanie nastepcy
 
    Node* nastepca = successor(node);
    if(nastepca != nullptr){
        cout<<"nastepca wezla "<< node->data<< " to "<< nastepca->data<<endl;
    }
    else{
        cout<<"nastepca wezla "<< node->data<<" nie istnieje\n";
    }


    //znajdowanie przodka

    Node* przodek = ancestor(node);
    if(przodek != nullptr){
        cout<<"przodek wezla "<< node->data<< " to "<<przodek->data<<endl;
    }
    else{
        cout<<"przodek wezla "<<node->data<<" nie istnieje\n";
    }
    //rotacja drzewa

    
    return 0;
}