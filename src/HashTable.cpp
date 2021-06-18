#include <cstddef>
#include <cmath>
#include <string>
#include <HashTable.h>

#define HASH_P 14

/**
 * Hashtable constructor. Requires a fixed table size and an object data type T. All fields will be initialized to nullptr and no AVL tree extensions will be formed prior to future table insertion.
 */

template<class T>
HashTable<T>::HashTable(int tablesize) {
    hashtable = new HTO<T>[tablesize];
    for (int i = 0; i < tablesize; i++) {
        (hashtable + i)->data = nullptr;
        (hashtable + i)->treeptr = new AVL<T>();
    }
    tblsize = tablesize;
    datacount = 0;
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
size_t HashTable<T>::hashFunction(int key, int p) {
	// Change Hash Function If Required
	short mach_word_bit_size = sizeof(size_t) * 5; // Using half of machine's word size
	long double A = (sqrt(5) - 1) / 2;
	size_t s = floor(A * (long double)(2^mach_word_bit_size)); 
	return (size_t)(key * s >> (mach_word_bit_size - p));
}

/**
 * Returns pointer to a DTO object cointaining class T as specified in the hashtable constructor. Easy index return -> e.g. hashtable[2] returns DTO at index 2.
 */

template<class T>
DTO<T>* HashTable<T>::operator[](int key) {
    int searchidx = hashFunction(key, HASH_P);
	if ((hashtable + searchidx)->data->id == key) {
        //searchidx = NULL; Needs to nullify
        return (hashtable + searchidx)->data;
    }
    else {
        DTO<T>* searchobj = (hashtable + searchidx)->treeptr->searchTree(key);
        if (searchobj != nullptr) {
            //searchidx = NULL;
            return searchobj;
        }
        else {
            //searchidx = NULL;
            delete searchobj;
            return nullptr;
        } 
    }
}

template<class T>
DTO<T>* HashTable<T>::getFromHashTable(int key){
    int searchidx = hashFunction(key, HASH_P);
	if ((hashtable + searchidx)->data->id == key) {
        //searchidx = NULL; Needs to nullify
        return (hashtable + searchidx)->data;
    }
    else {
        try{
            DTO<T>* searchobj = (hashtable + searchidx)->treeptr->searchTree(key);
            if (searchobj != nullptr) {
                //searchidx = NULL;
                return searchobj;
            }
            else {
                //searchidx = NULL;
                delete searchobj;
                return nullptr;
            } 
        }
        catch(...){
            return nullptr;
        }
        
    }
}

/**
 * Takes pointer to DTO object containing data type T as specified in the hashtable constructor and attempts to add it to the table.
 *
 * Returns a false if object already exists or if an error occurred during the insertion process. Returns a true if the object was successfully added.
 */

template<class T>
bool HashTable<T>::addToTable(DTO<T>* dataobj) {
    int inputindx = hashFunction(dataobj->id, HASH_P);
    if ((hashtable + inputindx)->data != nullptr) {
        if ((hashtable + inputindx)->treeptr->insertIntoTree(dataobj)){
            datacount++;
            return true;
        }
        else return false;
        //return (hashtable + inputindx)->treeptr->insertIntoTree(dataobj);
    } else {
        (hashtable + inputindx)->data = dataobj;
        datacount++;
        return true;
    }
    return false;
}

/**
 * Takes the integer key value to be used for a unique table search and deletion.
 *
 * Returns a false if the object was not found or if an error occurred during the deletion process. Returns a true if the object with id 'key' was successfully deleted.
 */

template<class T>
bool HashTable<T>::removeFromTable(int key) {
    int searchidx = hashFunction(key, HASH_P);
    if ((hashtable + searchidx)->data != nullptr) {
        //searchidx = NULL; Needs to nullify
		if ((hashtable + searchidx)->data->id == key) {
			delete (hashtable + searchidx)->data;
            datacount--;
			return true;
		}
		else {
            if ((hashtable + searchidx)->treeptr->deleteFromTree(key)){
                datacount--;
                return true;
            }
            else return false;
			//return (hashtable + searchidx)->treeptr->deleteFromTree(key);
		} 
    }
    else {
        //return (*(hashtable + searchidx))->treeptr->deleteFromTree(key); // delete function argument RECHECK after AVL implementation
        if ((hashtable + searchidx)->treeptr->deleteFromTree(key)){
            datacount--;
            return true;
        }
        else return false;
        //return (hashtable + searchidx)->treeptr->deleteFromTree(key);
    }
    return false;
}

template class HashTable<std::string>; //Provided for testing purposes DELETE AFTER PRODUCTION
template class HashTable<std::wstring>;
