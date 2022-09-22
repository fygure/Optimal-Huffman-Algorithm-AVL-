#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <cmath>
using namespace std;
/////////////////////////////////////////////////////
struct node
{
  node* left;
  node* right;
  int key;
  char symbol;
  int height;
  node() {left = nullptr; right = nullptr; height = 0;}
};
/////////////////////////////////////////////////////
class AVL
{
private:
  node* root;
  node* insertPrivate(node* ptr, int key, char symbol);
  node* removePrivate(node* root, int key);
  void displayPrivate(node* root);
  int getMinPrivate(node* root);
  node* getMinNode(node* root);
  int getHeight(node* ptr);
  int getBalance(node* ptr);
  node* singleLeftRotate(node* &ptr);
  node* singleRightRotate(node* &ptr);
  node* doubleLeftRotate(node* &ptr);
  node* doubleRightRotate(node* &ptr);
  

public:
  AVL() {root = nullptr;}
  node* createLeaf(int key, char symbol);
  void insert(int key, char symbol) {root = insertPrivate(root, key, symbol);}
  void remove(int key) {root = removePrivate(root, key);}
  void display() {displayPrivate(root);}
  int getMin() {return getMinPrivate(root);}
  node* getMinNode() {return getMinNode(root);}

};
/////////////////////////////////////////////////////
int AVL::getBalance(node* ptr)
{
  if (ptr == nullptr)
    return 0;
  return getHeight(ptr->left) - getHeight(ptr->right);
}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
node* AVL::doubleRightRotate(node* &ptr)
{
  ptr->left = singleLeftRotate(ptr->left);
  return singleRightRotate(ptr);
}
/////////////////////////////////////////////////////
node* AVL::doubleLeftRotate(node* &ptr)
{
  ptr->right = singleRightRotate(ptr->right);
  return singleLeftRotate(ptr);
}
/////////////////////////////////////////////////////
node* AVL::singleRightRotate(node* &ptr)
{
  node* u = ptr->left;
  ptr->left = u->right;
  u->right = ptr;
  ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
  u->height = max(getHeight(u->left), ptr->height) + 1;
  return u;
}
/////////////////////////////////////////////////////
node* AVL::singleLeftRotate(node*& ptr)
{
  node* u = ptr->right;
  ptr->right = u->left;
  u->left = ptr;
  ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
  u->height = max(getHeight(u->left), ptr->height) + 1;
  return u;
}
/////////////////////////////////////////////////////
int AVL::getHeight(node* ptr)
{
  if (ptr == nullptr)
    return -1;
  else
    return ptr->height;
}
/////////////////////////////////////////////////////
node* AVL::createLeaf(int key, char symbol)
{
  node* newnode = new node();
  newnode->key = key;
  newnode->symbol = symbol;
  return newnode;
}
/////////////////////////////////////////////////////
node* AVL::insertPrivate(node* ptr, int key, char symbol)
{
  if (ptr == nullptr)
  {
    ptr = createLeaf(key, symbol);
  }
  else if (key > ptr->key)
  {
    ptr->right = insertPrivate(ptr->right, key, symbol);
    if (getHeight(ptr->left) - getHeight(ptr->right) == 2)
    {
      if (key < ptr->left->key)
        ptr = singleRightRotate(ptr);
      else
        ptr = doubleLeftRotate(ptr);
    }
  }
  else if (key < ptr->key)
  {
    ptr->left = insertPrivate(ptr->left, key, symbol);
    if (getHeight(ptr->left) - getHeight(ptr->right) == 2)
    {
      if (key > ptr->right->key)
        ptr = singleLeftRotate(ptr);
      else
        ptr = doubleRightRotate(ptr);
    }
  }
  
  ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
  return ptr;
}
/////////////////////////////////////////////////////
void AVL::displayPrivate(node* root)
{
  if (root == nullptr)
    return;

  displayPrivate(root->left);
  cout << root->symbol << ": " << root->key << endl;
  displayPrivate(root->right);
}
/////////////////////////////////////////////////////
int AVL::getMinPrivate(node* root)
{
  if (root->left == nullptr)
    return root->key;
  
  return getMinPrivate(root->left);
}
/////////////////////////////////////////////////////
node* AVL::getMinNode(node* root)
{
  if (root->left == nullptr)
    return root;
  
  return getMinNode(root->left);
}
/////////////////////////////////////////////////////
node* AVL::removePrivate(node* root, int key)
{
  // STEP 1: Perform BST Deletion
  if (root == nullptr)
    return root;

  // if key smaller, go left
  if (key < root->key)
    root->left = removePrivate(root->left, key);

  // if key bigger, go right
  else if (key > root->key)
    root->right = removePrivate(root->right, key);

  // else the key is the same as root's key
  else
  {
    // case 1 and 2 (leaf node removal = no children or one child)
    if ( (root->left == nullptr) || (root->right == nullptr) )
    {
      node *temp = root->left ? root->left : root->right;

      // case 1 no children
      if (temp == nullptr)
      {
        temp = root;
        root = nullptr;
      }
      // case 2 one child
      else
      {
        *root = *temp;
      }
      delete temp;
    }
    // case 3 (two children)
    else
    {
      // Smallest in right subtree
      node* temp = getMinNode(root->right);

      // Assign root data to copy inorder successor's
      root->key = temp->key;

      // Remove inorder successor
      root->right = removePrivate(root->right, temp->key);

    }
  }

  // If tree had only one node
  if (root == nullptr)
    return root;

  // STEP 2: Update height of current node
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));


  // STEP 3: Get balance factor of current node
  int balance = getBalance(root);

  // Four cases

  // Left Left 
  if (balance > 1 && getBalance(root->left) >= 0)
    return singleRightRotate(root);

  // Left Right
  if (balance > 1 && getBalance(root->left) < 0)
    return doubleRightRotate(root);

  // Right Right
  if (balance < -1 && getBalance(root->right) <= 0)
    return singleLeftRotate(root);
  
  // Right Left
  if (balance < -1 && getBalance(root->right) > 0)
    return doubleLeftRotate(root);
  

  return root;

}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

#endif