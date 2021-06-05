#include <HashTable.h>

template<class T>
HashTable<T>::HashTable(int tablesize) {
    hashtable = new HTO[tablesize];
    for (int i = 0; i < tablesize; i++)
        *(hashtable + i) = NULL;
    tblsize = tablesize;
}

template<class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < tblsize; i++) {
        if (*(hashtable + i) != NULL) {
            delete (hashtable + i);
            delete[] hashtable;
        }
    }
}

template<class T>
int HashTable<T>::hashFunction(int key) {
    //TODO implement hash function.
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
bool HashTable<T>::addToTable(DTO<T> dataobj) {
    int inputindx = hashFunction(dataobj.id);
    if ((hashtable + inputindx)->data != NULL) {
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
    if ((hashtable + searchidx)->data != NULL) {
        //searchidx = NULL; Needs to nullify
        //delete (*(hashtable + searchidx))->data;
        (hashtable + searchidx)->data = NULL;
        return true;
    }
    else {
        //return (*(hashtable + searchidx))->treeptr->deleteFromTree(key); // delete function argument RECHECK after AVL implementation
        return (hashtable + searchidx)->treeptr->deleteFromTree(key);
    }
    return false;
}