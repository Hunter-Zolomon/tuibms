#include "DTO.h"

#ifndef AVLNODE_H_
#define AVLNODE_H_

template <class T>
struct AVLNode {
    DTO<T>* data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(DTO<T>* data) {
        this->height = 0;
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

#endif
