#include <HashTable.h>

#define HASH_P 14

/**
 * Hashtable constructor. Requires a fixed table size and an object data type T. All fields will be initialized to nullptr and no AVL tree extensions will be formed prior to future table insertion.
 */

template<class T>
HashTable<T>::HashTable(unsigned int tablesize) {
	this->tblsize = tablesize;
	this->datacount = 0;
    this->hashtable = new HTO<T>[tablesize];
    for (int i = 0; i < tablesize; i++) {
        (this->hashtable + i)->data = nullptr;
        (this->hashtable + i)->treeptr = new AVL<T>();
    }
}

template<class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < this->tblsize; i++) {
        if (nullptr != (this->hashtable + i)) {
            delete (this->hashtable + i);
            delete[] this->hashtable;
        }
    }
}

template<class T>
unsigned int HashTable<T>::hashFunction(unsigned int key, unsigned int p) {
	// Change Hash Function If Required
	short mach_word_bit_size = sizeof(size_t) * 5; // Using half of machine's word size
	long double A = (sqrt(5) - 1) / 2;
	size_t s = floor(A * (long double)(2^mach_word_bit_size)); 
	unsigned int generated_key = ((size_t)(key * s >> (mach_word_bit_size - p))) % this->tblsize; //This temp step is for debugging the gen-key.
	return generated_key; 
}

/**
 * Returns pointer to a DTO object cointaining class T as specified in the hashtable constructor. Easy index return -> e.g. hashtable[2] returns DTO at index 2.
 */

template<class T>
DTO<T>* HashTable<T>::operator[](unsigned int key) {
    unsigned int searchidx = hashFunction(key, HASH_P);
	if ((this->hashtable + searchidx)->data->id == key) {
        return (this->hashtable + searchidx)->data;
    }
    else {
        DTO<T>* searchobj = (this->hashtable + searchidx)->treeptr->searchTree(key);
		if (nullptr != searchobj) {
            return searchobj;
        }
        else {
			return searchobj;
        } 
    }
}

/**
 * Returns a vector containing all DTO pointers contained within the hashtable and collision resolution trees.
 */

template<class T>
std::vector<DTO<T>*> HashTable<T>::getAllElements() {
	std::vector<DTO<T>*> returnvector;
	for (int i = 0; i < this->tblsize; i++) {
		if (nullptr != (this->hashtable + i)->data)
			returnvector.push_back((this->hashtable + i)->data);
		if (nullptr != (this->hashtable + i)->treeptr) {
			std::vector<DTO<T>*> avlreturnvector = (this->hashtable + i)->treeptr->getAllElements();
			returnvector.insert(returnvector.end(), avlreturnvector.begin(), avlreturnvector.end()); 
		}
	}
	return returnvector;
}

/**
 * Takes pointer to DTO object containing data type T as specified in the hashtable constructor and attempts to add it to the table.
 *
 * Returns a false if object already exists or if an error occurred during the insertion process. Returns a true if the object was successfully added.
 */

template<class T>
DTO<T>* HashTable<T>::operator()(DTO<T>* dataobj) {
	unsigned int inputindx = hashFunction(dataobj->id, HASH_P);
	if (nullptr != (this->hashtable + inputindx)->data) {
		if ((this->hashtable + inputindx)->treeptr->insertIntoTree(dataobj)) {
			this->datacount++;
			return dataobj;
		}
    } else {
        (this->hashtable + inputindx)->data = dataobj;
		this->datacount++;
		return dataobj;
    }
    return nullptr;
}

/**
 * Takes the integer key value to be used for a unique table search and deletion.
 *
 * Returns a false if the object was not found or if an error occurred during the deletion process. Returns a true if the object with id 'key' was successfully deleted.
 */

template<class T>
bool HashTable<T>::removeFromTable(unsigned int key) {
    unsigned int searchidx = hashFunction(key, HASH_P);
	if (nullptr != (this->hashtable + searchidx)->data) {
		if ((this->hashtable + searchidx)->data->id == key) {
			delete (hashtable + searchidx)->data;
			(hashtable + searchidx)->data = nullptr;
			this->datacount--;
			return true;
		}
		else {
			if((this->hashtable + searchidx)->treeptr->deleteFromTree(key)) {
				this->datacount--;
				return true;
			}
		} 
    }
    else {
        if ((this->hashtable + searchidx)->treeptr->deleteFromTree(key)) {
			this->datacount--;
			return true;
		}
    }
    return false;
}

template class HashTable<Book>;
template class HashTable<Patron>;
template class HashTable<Loan>;
