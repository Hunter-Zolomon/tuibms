//#include <string>
#include <DTO.hpp>
#include <AVLTree.h>

template<class T>
struct HTO {
    DTO<T> data;
    AVL* treeprt;
};

template<class T>
class HashTable {
    //static_assert(std::is_base_of<std::string, T>::value && std::is_base_of<int, T>::value, "T must inherit from string or int");
    private:
        HTO<T>* hashtable;

        int hashFunction(int key);
    public:
        int datacount;
        int tblsize;

        HashTable(int tablesize);
        ~HashTable();
        bool addToTable(DTO<T> dataobj);
        bool removeFromTable(int key);
        DTO<T>* operator[](int key); 
};