#include <string>

class Patron{

    int patron_num_borrowed;
    
    std::wstring    patron_fname,   patron_lname,   
    patron_address, patron_postcode,patron_contact;

    bool patron_is_active;

    int last_borrowed_book_id[10];

    public:
        Patron(bool is_active, std::wstring fname, std::wstring lname, 
                std::wstring address, std::wstring postcode, 
                std::wstring contact, int num_borrowed);


        bool getIsActive();
        std::wstring getFname();
        std::wstring getLname();
        std::wstring getAddress();
        std::wstring getPostcode();
        std::wstring getContact();
        int getNumBorrowed();

        std::wstring getMenuEntry();

 
        void setIsActive(bool is_active);
        void setFname(std::wstring fname);
        void setLname(std::wstring lname);
        void setAddress(std::wstring address);
        void setPostcode(std::wstring postcode);
        void setContact(std::wstring contact);
        void setNumBorrowed(int num_borrowed);

        void incrementNumBorrowed();
        void decrementNumBorrowed();
};