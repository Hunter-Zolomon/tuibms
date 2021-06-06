#include "AVLNode.h"

#ifndef AVLTREE_H_
#define AVLTREE_H_

template <class T>
class AVL {
    public:
        AVL();
        ~AVL();

        bool insertIntoTree(DTO<T>* data);
        //bool searchTree(DTO<T>* data); Changed
        DTO<T>* searchTree(int key);
        //bool deleteFromTree(DTO<T>* data); Changed
        bool deleteFromTree(int key);
        bool updateTree(DTO<T>* datatochange, DTO<T>* newdata);
        void clearTree();
    private:
        AVLNode<T>* rootNode;

        //AVLNode<T>* search(DTO<T>* data, AVLNode<T>* node); Changed
        AVLNode<T>* search(int key, AVLNode<T>* node);
        AVLNode<T>* leftRotate(AVLNode<T>* node);
        AVLNode<T>* leftRightRotate(AVLNode<T>* node);
        AVLNode<T>* rightRotate(AVLNode<T>* node);
        AVLNode<T>* rightLeftRotate(AVLNode<T>* node);
        AVLNode<T>* insertInto(DTO<T>* data, AVLNode<T>* node);
        //AVLNode<T>* deleteFrom(DTO<T>* data, AVLNode<T>* node); Changed
        AVLNode<T>* deleteFrom(int key, AVLNode<T>* node);
        int getHeight(AVLNode<T>* node);
};

#endif