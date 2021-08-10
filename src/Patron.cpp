#include <Patron.h>

Patron::Patron(){}

Patron::Patron(bool isActive, std::string name,std::string email,std::string address,std::string postcode,std::string phone){  
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

std::string Patron::getName(){
    return patron_name;
}

std::string Patron::getEmail(){
    return patron_email;
}

std::string Patron::getAddress(){
    return patron_address;
}

std::string Patron::getPostcode(){
    return patron_postcode;
}

std::string Patron::getPhone(){
    return patron_phone;
}

unsigned int Patron::getNumBorrowed(){
    return patron_num_borrowed;
}

std::string Patron::getMenuEntry(){
    return  std::to_string(patron_is_active) + " - " + 
            patron_name     + " - " + 
            patron_email    + " - " + 
            patron_address  + " - " + 
            patron_postcode + " - " + 
            patron_phone    + " - " + 
            std::to_string(patron_num_borrowed);
}

std::vector<std::string> Patron::getLastBorrowed(){
    return last_loans;
}

std::vector<std::string> Patron::getCurrentBorrows(){
    return current_loans;
}

// Patron - Setters

void Patron::setIsActive(bool is_active){
    patron_is_active = is_active;
}

void Patron::setName(std::string name){
    patron_name = name;
}

void Patron::setEmail(std::string email){
    patron_email = email;
}

void Patron::setAddress(std::string address){
    patron_address = address;
}

void Patron::setPostcode(std::string postcode){
    patron_postcode = postcode;
}

void Patron::setPhone(std::string phone){
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

void Patron::addToLastBorrowed(std::string loan_entry){
    if (10==last_loans.size())
        last_loans.erase(last_loans.begin());
    last_loans.push_back(loan_entry);
    delFromCurrentBorrows(loan_entry);
}

void Patron::addToCurrentBorrows(std::string loan_entry){
    current_loans.push_back(loan_entry);
}

void Patron::delFromCurrentBorrows(std::string loan_entry){
    int c = 0;
    for (std::string loan: current_loans){
        c++;
        if (loan==loan_entry){
            current_loans.erase(current_loans.begin(), current_loans.begin()+c);
        }
    }
}
