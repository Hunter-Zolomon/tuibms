#include <cstdlib>

#ifndef DTO_H_
#define DTO_H_

template<class T>
struct DTO {
    int id; 
    T dataobj;
	
	DTO(T datobj) : id(rand() % 1000) { 
		//Change+Increase ID Generation THIS IS A PLACEHOLDER
		dataobj = datobj; 
	} 
};

#endif
