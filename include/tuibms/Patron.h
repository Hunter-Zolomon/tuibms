#include <string>

#ifndef PATRON_H_
#define PATRON_H_

class Patron{
    unsigned int patron_num_borrowed;
    std::wstring patron_name, patron_email, patron_address, patron_postcode,patron_contact;
    bool patron_is_active;
    unsigned int last_borrowed_book_id[10];
    public:
        Patron();
        Patron(bool is_active, std::wstring name, std::wstring email, std::wstring address, std::wstring postcode,  std::wstring contact, unsigned int num_borrowed);
        bool getIsActive();
        std::wstring getName();
        std::wstring getEmail();
        std::wstring getAddress();
        std::wstring getPostcode();
        std::wstring getContact();
        unsigned int getNumBorrowed();
        std::wstring getMenuEntry();
        void setIsActive(bool is_active);
        void setName(std::wstring name);
        void setEmail(std::wstring email);
        void setAddress(std::wstring address);
        void setPostcode(std::wstring postcode);
        void setContact(std::wstring contact);
        void setNumBorrowed(unsigned int num_borrowed);
        void incrementNumBorrowed();
        void decrementNumBorrowed();
};
#endif
