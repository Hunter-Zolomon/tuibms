#include <AVLNode.h>

template <class T>
class AVL {
    public:
        AVL();

        bool insertIntoTree(T data);
        bool searchTree(T data);
        bool deleteFromTree(T data);
        bool updateTree(T datatochange, T newdata);
        void clearTree();
    private:
        AVLNode* rootNode;

        AVLNode<T>* search(T data, AVLNode<T>* node);
        AVLNode<T>* leftRotate(AVLNode<T>* node);
        AVLNode<T>* leftRightRotate(AVLNode<T>* node);
        AVLNode<T>* rightRotate(AVLNode<T>* node);
        AVLNode<T>* rightLeftRotate(AVLNode<T>* node);
        AVLNode<T>* insertInto(T data, AVLNode<T>* node);
        AVLNode<T>* deleteFrom(T data, AVLNode<T>* node);
        int getHeight(AVLNode<T>* node);
};