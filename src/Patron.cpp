#include <string>
#include <Patron.h>

Patron::Patron(int id, bool is_active, std::wstring fname, std::wstring lname, 
                std::wstring address, std::wstring postcode, 
                std::wstring contact, int num_borrowed){  
                    setId(id);
                    setIsActive(is_active);
                    setFname(fname);
                    setLname(lname);
                    setAddress(address);
                    setPostcode(postcode);
                    setContact(contact);
                    setNumBorrowed(num_borrowed);                
                }

// Patron - Getters
int Patron::getId(){
    return patron_id;
}

bool Patron::getIsActive(){
    return patron_is_active;
}

std::wstring Patron::getFname(){
    return patron_fname;
}

std::wstring Patron::getLname(){
    return patron_lname;
}

std::wstring Patron::getAddress(){
    return patron_address;
}

std::wstring Patron::getPostcode(){
    return patron_postcode;
}

std::wstring Patron::getContact(){
    return patron_contact;
}

int Patron::getNumBorrowed(){
    return patron_num_borrowed;
}

std::wstring Patron::getPatronMenuEntry(){
    return  std::to_wstring(patron_id) + L" - " + 
            std::to_wstring(patron_is_active) + L" - " + 
            patron_fname  + L" - " + 
            patron_lname + L" - " + 
            patron_address   + L" - " + 
            patron_postcode+ L" - " + 
            patron_contact  + L" - " + 
            std::to_wstring(patron_num_borrowed);
}

// Patron - Setters
void Patron::setId(int id){
    patron_id = id;
}

void Patron::setIsActive(bool is_active){
    patron_is_active = is_active;
}

void Patron::setFname(std::wstring fname){
    patron_fname = fname;
}

void Patron::setLname(std::wstring lname){
    patron_lname = lname;
}

void Patron::setAddress(std::wstring address){
    patron_address = address;
}

void Patron::setPostcode(std::wstring postcode){
    patron_postcode = postcode;
}

void Patron::setContact(std::wstring contact){
    patron_contact = contact;
}

void Patron::setNumBorrowed(int num_borrowed){
    patron_num_borrowed = num_borrowed;
}

void Patron::incrementNumBorrowed(){
    patron_num_borrowed++;
}

void Patron::decrementNumBorrowed(){
    patron_num_borrowed--;
}