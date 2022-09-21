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
  int height;
  node() {left = nullptr; right = nullptr; height = 0;}
};
/////////////////////////////////////////////////////
class AVL
{
private:
  node* root;
  node* insertPrivate(node* ptr, int key);
  void displayPrivate(node* root);
  int getHeight(node* ptr);
  node* singleLeftRotate(node* &ptr);
  node* singleRightRotate(node* &ptr);
  node* doubleLeftRotate(node* &ptr);
  node* doubleRightRotate(node* &ptr);

public:
  AVL() {root = nullptr;}
  node* createLeaf(int key);
  void insert(int key) {root = insertPrivate(root, key);}
  void remove(int key);
  void display() {displayPrivate(root);}

};
/////////////////////////////////////////////////////
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
node* AVL::createLeaf(int key)
{
  node* newnode = new node();
  newnode->key = key;
  return newnode;
}
/////////////////////////////////////////////////////
node* AVL::insertPrivate(node* ptr, int key)
{
  if (ptr == nullptr)
  {
    ptr = createLeaf(key);
  }
  else if (key > ptr->key)
  {
    ptr->right = insertPrivate(ptr->right, key);
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
    ptr->left = insertPrivate(ptr->left, key);
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
  cout << root->key << endl;
  displayPrivate(root->right);
}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

#endif