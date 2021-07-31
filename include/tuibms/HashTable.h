//#include <string>
#include <vector>
#include "DTO.h"
#include "AVLTree.h"

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

template<class T>
struct HTO {
    DTO<T>* data;
    AVL<T>* treeptr;
};

template<class T>
class HashTable {
    private:
        HTO<T>* hashtable;

		unsigned int hashFunction(unsigned int key, unsigned int p);
    public:
        unsigned int datacount;
        unsigned int tblsize;

        HashTable(unsigned int tablesize);
        ~HashTable();
        bool removeFromTable(unsigned int key);
		DTO<T>* operator()(DTO<T>* dataobj);
        DTO<T>* operator[](unsigned int key); 
		std::vector<DTO<T>*> getAllElements();
};

#endif
