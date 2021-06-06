#include <cstddef>
#include <string>
#include <HashTable.h>

template<class T>
HashTable<T>::HashTable(int tablesize) {
    hashtable = new HTO<T>[tablesize];
    for (int i = 0; i < tablesize; i++) {
        (hashtable + i)->data = nullptr;
        (hashtable + i)->treeptr = nullptr;
    }
    tblsize = tablesize;
}

template<class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < tblsize; i++) {
        if ((hashtable + i) != nullptr) {
            delete (hashtable + i);
            delete[] hashtable;
        }
    }
}

template<class T>
int HashTable<T>::hashFunction(int key) {
    return key % tblsize; // TODO Implement better hashfunction
}

template<class T>
DTO<T>* HashTable<T>::operator[](int key) {
    int searchidx = hashFunction(key);
    if ((*((hashtable + searchidx)->data)).id == key) {
        //searchidx = NULL; Needs to nullify
        return (hashtable + searchidx)->data;
    }
    else {
        DTO<T>* searchobj = (hashtable + searchidx)->treeptr->searchTree(key);
        if (searchobj != nullptr) {
            searchidx = NULL;
            return searchobj;
        }
        else {
            searchidx = NULL;
            delete searchobj;
            return nullptr;
        } 
    }
}

template<class T>
bool HashTable<T>::addToTable(DTO<T>* dataobj) {
    int inputindx = hashFunction(dataobj->id);
    if ((hashtable + inputindx)->data != nullptr) {
        return (hashtable + inputindx)->treeptr->insertIntoTree(dataobj);
    } else {
        (hashtable + inputindx)->data = dataobj;
        return true;
    }
    return false;
}

template<class T>
bool HashTable<T>::removeFromTable(int key) {
    int searchidx = hashFunction(key);
    if ((hashtable + searchidx)->data != nullptr) {
        //searchidx = NULL; Needs to nullify
        delete (hashtable + searchidx);
        return true;
    }
    else {
        //return (*(hashtable + searchidx))->treeptr->deleteFromTree(key); // delete function argument RECHECK after AVL implementation
        return (hashtable + searchidx)->treeptr->deleteFromTree(key);
    }
    return false;
}

template class HashTable<std::string>; //Provided for testing purposes DELETE AFTER PRODUCTION