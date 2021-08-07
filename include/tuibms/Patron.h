#include <string>
#include <vector>

#ifndef PATRON_H_
#define PATRON_H_

class Patron{
    unsigned int patron_num_borrowed;
    std::wstring patron_name, patron_email, patron_address, patron_postcode,patron_phone;
    bool patron_is_active;
    std::vector<std::wstring> last_loans, current_loans;
    public:
        Patron();
        Patron(bool isActive, std::wstring name, std::wstring email, std::wstring address, std::wstring postcode, std::wstring phone);
        bool getIsActive();
        std::wstring getName();
        std::wstring getEmail();
        std::wstring getAddress();
        std::wstring getPostcode();
        std::wstring getPhone();
        unsigned int getNumBorrowed();
        std::wstring getMenuEntry();
        std::vector<std::wstring> getLastBorrowed();
        std::vector<std::wstring> getCurrentBorrows();
        void setIsActive(bool is_active);
        void setName(std::wstring name);
        void setEmail(std::wstring email);
        void setAddress(std::wstring address);
        void setPostcode(std::wstring postcode);
        void setPhone(std::wstring phone);
        void setNumBorrowed(unsigned int num_borrowed);
        void incrementNumBorrowed();
        void decrementNumBorrowed();
        void addToLastBorrowed(std::wstring loan_entry);
        void addToCurrentBorrows(std::wstring loan_entry);
        void delFromCurrentBorrows(std::wstring loan_entry);
        
};
#endif
