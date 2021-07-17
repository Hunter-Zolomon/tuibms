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
    //static_assert(std::is_base_of<std::string, T>::value && std::is_base_of<int, T>::value, "T must inherit from string or int");
    private:
        HTO<T>* hashtable;

		size_t hashFunction(int key, int p);
    public:
        int datacount;
        int tblsize;

        HashTable(int tablesize);
        ~HashTable();
        //bool addToTable(DTO<T>* dataobj); Depracated. Use operator() instead
        bool removeFromTable(int key);
		bool operator()(DTO<T>* dataobj);
        DTO<T>& operator[](int key); 
		std::vector<DTO<T>*> getAllElements();
};

#endif
