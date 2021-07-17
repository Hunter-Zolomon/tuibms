#include <cstdlib>

#ifndef DTO_H_
#define DTO_H_

template<class T>
struct DTO {
    unsigned int id; // 32 bit with max 4,294,967,295. Can be increased to u_int64_t
    T dataobj;
	
	DTO(T datobj) : id(rand() % 4294967295) { 
		dataobj = datobj; 
	} 
};

#endif
