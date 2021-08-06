#include <string>
#include <vector>
#include <Patron.h>

Patron::Patron(){}

Patron::Patron(bool isActive, std::wstring name,std::wstring email,std::wstring address,std::wstring postcode,std::wstring phone){  
                    setIsActive(isActive);
                    setName(name);
                    setEmail(email);
                    setAddress(address);
                    setPostcode(postcode);
                    setPhone(phone);
                    setNumBorrowed(0);                
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

std::wstring Patron::getPhone(){
    return patron_phone;
}

unsigned int Patron::getNumBorrowed(){
    return patron_num_borrowed;
}

std::wstring Patron::getMenuEntry(){
    return  std::to_wstring(patron_is_active) + L" - " + 
            patron_name     + L" - " + 
            patron_email    + L" - " + 
            patron_address  + L" - " + 
            patron_postcode + L" - " + 
            patron_phone    + L" - " + 
            std::to_wstring(patron_num_borrowed);
}

std::vector<std::wstring> Patron::getLastBorrowed(){
    return last_borrowed;
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

void Patron::setPhone(std::wstring phone){
    patron_phone = phone;
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

void Patron::addToLastBorrowed(std::wstring loan_entry){
    if (10==last_borrowed.size())
        last_borrowed.erase(last_borrowed.begin());
    last_borrowed.push_back(loan_entry);
}