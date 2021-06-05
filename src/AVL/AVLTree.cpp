#include <AVLNode.h>
#include <AVLTree.h>

template<class T>
AVL<T>::AVL() { rootNode = nullptr; }

template<class T>
int AVL<T>::getHeight(AVLNode<T>* node) { return node == nullptr ? -1 : node->height; }

template<class T>
AVLNode<T>* AVL<T>::search(DTO<T> data, AVLNode<T>* node) {
    if (node == nullptr)
        return nullptr;
    else if (data == node->data)
        return node;
    else if (data < node->data)
        return search(data, node->left);
    else if (data > node->data)
        return search(data, node->right);
    else throw 100;
}

template<class T>
bool AVL<T>::searchTree(DTO<T> data) {
    if (search(data, rootNode) == nullptr)
        return false;
    return true;
}

template<class T>
AVLNode<T>* AVL<T>::leftRotate(AVLNode<T>* node) {
    AVLNode<T>* leftchildnode = node->right->left,*newroot = node->right;
    node->right->left = node;
    node->right = leftchildnode;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    if (node->right != nullptr)
        node->right->height = max(getHeight(node->right->left), getHeight(node->right->right)) + 1;
    return newroot;
}

template<class T>
AVLNode<T>* AVL<T>::rightRotate(AVLNode<T>* node) {
    AVLNode<T>* rightchildnode = node->left->right,*newroot = node->left;
    node->left->right = node;
    node->left = rightchildnode;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    if (node->left != nullptr)
        node->left->height = max(getHeight(node->left->left), getHeight(node->left->right)) + 1;
    return newroot;
}

template<class T>
AVLNode<T>* AVL<T>::leftRightRotate(AVLNode<T>* node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

template<class T>
AVLNode<T>* AVL<T>::rightLeftRotate(AVLNode<T>* node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

template<class T>
AVLNode<T>* AVL<T>::insertInto(DTO<T> data, AVLNode<T>* node) {
    if (node == nullptr)
        return node = new AVLNode<T>(data);
    else {
        if (data = node->data)
            return node;
        else if (data < node->data)
            node->left = insertInto(data, node->left);
        else if (data > node->data)
            node->right = insertInto(data, node->right);
        else throw 200;
    }

    if (getHeight(node->left) - getHeight(node->right) == 2) {
        if (data < node->left->data)
            node = rightRotate(node);
        else node = leftRightRotate(node);
    }
    else if (getHeight(node->left) - getHeight(node->right) == -2) {
        if (data > node->right->data)
            node = leftRotate(node);
        else node = rightLeftRotate(node);
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

template<class T>
bool AVL<T>::insertIntoTree(DTO<T> data) { rootNode = insertInto(data, rootNode); }

template<class T>
AVLNode<T>* AVL<T>::deleteFrom(DTO<T> data, AVLNode<T>* node) {
    if (node == nullptr)
        return nullptr;
    else {
        if (data == node->data) {
            if (node->right == nullptr) {
                AVLNode<T>* currentnode = node;
                node = node->left;
                delete currentnode;
                return node;
            }
            else {
                AVLNode<T>* currentnode = node->right;
                while (currentnode->left != nullptr)
                    currentnode = currentnode->left;
                node->data = currentnode->data;
                node->right = deleteFrom(currentnode->data, node->right);
            }
        }
        else if (data < node->data)
            node->left = deleteFrom(data, node->left);
        else if (data > node->data)
            node->right = deleteFrom(data, node->right);
        else throw 300;

        if (getHeight(node->left) - getHeight(node->right) == 2) {
            if (getHeight(node->left->left) >= getHeight(node->left->right))
                node = rightRotate(node);
            else node = leftRightRotate(node);
        }
        else if (getHeight(node->left) - getHeight(node->right) == -2) {
            if (getHeight(node->right->right) >= getHeight(node->right->left))
                node = leftRotate(node);
            else node = rightLeftRotate(node);
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    return node;
}

template<class T>
bool AVL<T>::deleteFromTree(DTO<T> data) {
    if (deleteFrom(data, node) != nullptr)
        return true;
    else return false;
}

template<class T>
bool AVL<T>::updateTree(DTO<T> datatochange, DTO<T> newdata) {
    if (deleteFromTree(datatochange)) {
        insertIntoTree(newdata);
        return true;
    }
    else return false;
}