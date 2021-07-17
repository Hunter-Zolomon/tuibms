#include <string>
#include <AVLNode.h>
#include <AVLTree.h>
#include <vector>
#include <Book.h>
#include <Patron.h>
#include <Loan.h>

/**
 * AVL tree constructor. Creates root node with no left/right pointers and an empty container.
 */

template<class T>
AVL<T>::AVL() { rootNode = nullptr; }

template<class T>
AVL<T>::~AVL() { deleteTree(rootNode); }

template<class T>
void AVL<T>::deleteTree(AVLNode<T>* node) {
	if (node == nullptr)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
    if (node==rootNode){
        rootNode = nullptr;
    }
    node = nullptr;
}

/**
 * Deletes entire tree starting with the root node. 
 *
 * NOTE: Use ~AVL() destructor whenever possible instead of this method.
 */

template<class T>
void AVL<T>::clearTree() { deleteTree(rootNode); };

template<class T>
unsigned int AVL<T>::getHeight(AVLNode<T>* node) { return node == nullptr ? -1 : node->height; }

template<class T>
AVLNode<T>* AVL<T>::search(unsigned int key, AVLNode<T>* node) {
    if (node == nullptr)
        return nullptr;
    else if (key == node->data->id)
        return node;
    else if (key < node->data->id)
        return search(key, node->left);
    else if (key > node->data->id)
        return search(key, node->right);
    else throw 100;
}

/**
 * Takes integer key (ideally unique) to search entire tree for the first match. 
 *
 * Returns pointer to the DTO object containing specified data type T on AVL construction. nullptr is returned if the search was unsuccessful or if the object was not found.
 */

template<class T>
DTO<T>* AVL<T>::searchTree(unsigned int key) {
    AVLNode<T>* searchresult = search(key, rootNode);
	if (nullptr == searchresult)
        return nullptr;
    return searchresult->data;
}

template<class T>
AVLNode<T>* AVL<T>::leftRotate(AVLNode<T>* node) {
    AVLNode<T>* leftchildnode = node->right->left,*newroot = node->right;
    node->right->left = node;
    node->right = leftchildnode;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
	if (nullptr != node->right)
        node->right->height = std::max(getHeight(node->right->left), getHeight(node->right->right)) + 1;
    return newroot;
}

template<class T>
AVLNode<T>* AVL<T>::rightRotate(AVLNode<T>* node) {
    AVLNode<T>* rightchildnode = node->left->right,*newroot = node->left;
    node->left->right = node;
    node->left = rightchildnode;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
	if (nullptr != node->left)
        node->left->height = std::max(getHeight(node->left->left), getHeight(node->left->right)) + 1;
    return newroot;
}

template<class T>
AVLNode<T>* AVL<T>::leftRightRotate(AVLNode<T>* node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

template<class T>
AVLNode<T>* AVL<T>::rightLeftRotate(AVLNode<T>* node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

template<class T>
AVLNode<T>* AVL<T>::insertInto(DTO<T>* data, AVLNode<T>* node) {
	if ((node == rootNode) && (nullptr == node))
		return rootNode = new AVLNode<T>(data);
	else if (nullptr == node)
        return node = new AVLNode<T>(data);
    else {
        if (data->id == node->data->id)
            return node;
        else if (data->id < node->data->id)
            node->left = insertInto(data, node->left);
        else if (data->id > node->data->id)
            node->right = insertInto(data, node->right);
        else throw 200;
    }

    if (getHeight(node->left) - getHeight(node->right) == 2) {
        if (data->id < node->left->data->id)
            node = rightRotate(node);
        else node = leftRightRotate(node);
    }
    else if (getHeight(node->left) - getHeight(node->right) == -2) {
        if (data->id > node->right->data->id)
            node = leftRotate(node);
        else node = rightLeftRotate(node);
    }
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

/**
 * Takes DTO object pointer and attempts to insert it into the tree.
 *
 * Returns true if the operation was successful. Returns false if the operation failed.
 */

template<class T>
bool AVL<T>::insertIntoTree(DTO<T>* data) { 
	if (nullptr != insertInto(data, rootNode))
        return true;
    else return false;
}

template<class T>
AVLNode<T>* AVL<T>::deleteFrom(unsigned int key, AVLNode<T>* node) {
	if (nullptr == node)
        return nullptr;
    else {
        if (key == node->data->id) {
			if (nullptr == node->right) {
                AVLNode<T>* currentnode = node;
                node = node->left; //node = nullptr
                delete currentnode; //node 
                return node;
            }
            else {
                AVLNode<T>* currentnode = node->right;
				while (nullptr != currentnode->left)
                    currentnode = currentnode->left;
                node->data = currentnode->data;
                //node->right = deleteFrom(currentnode->data, node->right); Changed
                node->right = deleteFrom(currentnode->data->id, node->right);
            }
        }
        else if (key < node->data->id)
            node->left = deleteFrom(key, node->left);
        else if (key > node->data->id)
            node->right = deleteFrom(key, node->right);
        else throw 300;

        if (getHeight(node->left) - getHeight(node->right) == 2) {
            if (getHeight(node->left->left) >= getHeight(node->left->right))
                node = rightRotate(node);
            else node = leftRightRotate(node);
        }
        else if (getHeight(node->left) - getHeight(node->right) == -2) {
            if (getHeight(node->right->right) >= getHeight(node->right->left))
                node = leftRotate(node);
            else node = rightLeftRotate(node);
        }
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    return node;
}

/**
 * Deletes DTO object from the tree. Takes integer key (ideally unique) to search for in the tree. 
 *
 * Returns true if the object is found and successfully deleted. If object is not found or operation fails, boolean false is returned.
 */

template<class T>
bool AVL<T>::deleteFromTree(unsigned int key) {
    if (rootNode->data->id == key && rootNode->height==0){
        deleteFrom(key, rootNode);
        rootNode = nullptr;
        return true;
    }
    else if (nullptr != deleteFrom(key, rootNode))
        return true;
    else return false;
}

/**
 * Updates DTO object in the tree with a new DTO object. Note that this operation does not replace the parameter 'datatochange' but rather removes it from the tree and inserts the 'newdata' parameter into the tree. This is performed to ensure that the BST property as well as balancing factor of the AVL tree is maintained.
 *
 * Returns true if the update succeeds. Returns false if the 'datatochange' DTO is not found or if the operation fails.
 */

template<class T>
bool AVL<T>::updateTree(unsigned int id_of_dto_tochange, T newdata) {
    //if (deleteFromTree(datatochange)) { Changed
	AVLNode<T>* tobeswapped = search(id_of_dto_tochange, rootNode);
	if (nullptr == tobeswapped)
		return false;
	tobeswapped->data->dataobj = newdata;
	return true;
	/* Changed
    if (deleteFromTree(datatochange->id)) {
        insertIntoTree(newdata);
        return true;
    }
    else return false;
	*/
}

template<class T>
std::vector<DTO<T>*> AVL<T>::getAllInorder(AVLNode<T>* node) {
	std::vector<DTO<T>*> returnvector;

	if (nullptr == node)
		return returnvector;

	std::vector<DTO<T>*> returnvector2;
 
	if (nullptr != node->left) {
		returnvector2 = getAllInorder(node->left);
		returnvector.insert(returnvector.end(), returnvector2.begin(), returnvector2.end());
	}
	returnvector.push_back(node->data);
	if (nullptr != node->right) {
		returnvector2 = getAllInorder(node->right);
		returnvector.insert(returnvector.end(), returnvector2.begin(), returnvector2.end());
	}
	return returnvector;
}

template<class T>
std::vector<DTO<T>*> AVL<T>::getAllElements() {
	return this->getAllInorder(this->rootNode);
}

template class AVL<std::string>; //Provided for testing purposes DELETE AFTER PRODUCTION
template class AVL<std::wstring>; //Provided for testing purposes DELETE AFTER PRODUCTION
template class AVL<Book>;
template class AVL<Patron>;
template class AVL<Loan>;
