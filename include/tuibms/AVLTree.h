#include "AVLNode.h"
#include <vector>

#ifndef AVLTREE_H_
#define AVLTREE_H_

template <class T>
class AVL {
    public:
        AVL();
        ~AVL();

        bool insertIntoTree(DTO<T>* data);
        //bool searchTree(DTO<T>* data); Changed
        DTO<T>* searchTree(int key); //Possibly change to reference instead
        //bool deleteFromTree(DTO<T>* data); Changed
        bool deleteFromTree(int key);
        //bool updateTree(DTO<T>* datatochange, DTO<T>* newdata); Changed
		bool updateTree(int id_of_dto_tochange, T newdata);
		std::vector<DTO<T>*> getAllElements();
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
		void deleteTree(AVLNode<T>* node);
        int getHeight(AVLNode<T>* node);
		std::vector<DTO<T>*> getAllInorder(AVLNode<T>* node);
};

#endif
