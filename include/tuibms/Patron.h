#include <string>
#include <vector>

#ifndef PATRON_H_
#define PATRON_H_

class Patron{
	private:
		unsigned int patron_num_borrowed;
		std::string patron_name, patron_email, patron_address, patron_postcode,patron_phone;
		bool patron_is_active;
		std::vector<std::string> last_loans, current_loans;
    public:
        Patron();
        Patron(bool isActive, std::string name, std::string email, std::string address, std::string postcode, std::string phone);
        bool getIsActive();
        std::string getName();
        std::string getEmail();
        std::string getAddress();
        std::string getPostcode();
        std::string getPhone();
        unsigned int getNumBorrowed();
        std::string getMenuEntry();
        std::vector<std::string> getLastBorrowed();
        std::vector<std::string> getCurrentBorrows();
        void setIsActive(bool is_active);
        void setName(std::string name);
        void setEmail(std::string email);
        void setAddress(std::string address);
        void setPostcode(std::string postcode);
        void setPhone(std::string phone);
        void setNumBorrowed(unsigned int num_borrowed);
        void incrementNumBorrowed();
        void decrementNumBorrowed();
        void addToLastBorrowed(std::string loan_entry);
        void addToCurrentBorrows(std::string loan_entry);
        void delFromCurrentBorrows(std::string loan_entry);
        
};

#endif
