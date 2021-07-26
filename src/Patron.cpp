#include <string>
#include <Patron.h>

Patron::Patron(){}

Patron::Patron(bool is_active, std::wstring name,  std::wstring email,
                std::wstring address, std::wstring postcode, 
                std::wstring contact, unsigned int num_borrowed){  
                    setIsActive(is_active);
                    setName(name);
                    setEmail(email);
                    setAddress(address);
                    setPostcode(postcode);
                    setContact(contact);
                    setNumBorrowed(num_borrowed);                
                }

// Patron - Getters

bool Patron::getIsActive(){
    return patron_is_active;
}

std::wstring Patron::getName(){
    return patron_name;
}

std::wstring Patron::getEmail(){
    return patron_email;
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

unsigned int Patron::getNumBorrowed(){
    return patron_num_borrowed;
}

std::wstring Patron::getMenuEntry(){
    return  std::to_wstring(patron_is_active) + L" - " + 
            patron_name  + L" - " + 
            patron_email  + L" - " + 
            patron_address   + L" - " + 
            patron_postcode+ L" - " + 
            patron_contact  + L" - " + 
            std::to_wstring(patron_num_borrowed);
}

// Patron - Setters

void Patron::setIsActive(bool is_active){
    patron_is_active = is_active;
}

void Patron::setName(std::wstring name){
    patron_name = name;
}

void Patron::setEmail(std::wstring email){
    patron_email = email;
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

void Patron::setNumBorrowed(unsigned int num_borrowed){
    patron_num_borrowed = num_borrowed;
}

void Patron::incrementNumBorrowed(){
    patron_num_borrowed++;
}

void Patron::decrementNumBorrowed(){
    patron_num_borrowed--;
}
