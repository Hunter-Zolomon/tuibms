template <class T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(T data) {
        this.height = 0;
        this.data = data;
        left = NULL;
        right = NULL;
    }
};