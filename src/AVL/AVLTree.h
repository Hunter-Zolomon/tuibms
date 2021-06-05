#include <AVLNode.h>

template <class T>
class AVL {
    public:
        AVL();
        ~AVL();

        bool insertIntoTree(DTO<T> data);
        bool searchTree(DTO<T> data);
        bool deleteFromTree(DTO<T> data);
        bool updateTree(DTO<T> datatochange, DTO<T> newdata);
        void clearTree();
    private:
        AVLNode<T>* rootNode;

        AVLNode<T>* search(DTO<T> data, AVLNode<T>* node);
        AVLNode<T>* leftRotate(AVLNode<T>* node);
        AVLNode<T>* leftRightRotate(AVLNode<T>* node);
        AVLNode<T>* rightRotate(AVLNode<T>* node);
        AVLNode<T>* rightLeftRotate(AVLNode<T>* node);
        AVLNode<T>* insertInto(DTO<T> data, AVLNode<T>* node);
        AVLNode<T>* deleteFrom(DTO<T> data, AVLNode<T>* node);
        int getHeight(AVLNode<T>* node);
};