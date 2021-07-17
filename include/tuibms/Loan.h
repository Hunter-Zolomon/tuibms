#include <string>

class Loan{
    int book_id, patron_id;
    std::wstring book_isbn,book_title,patron_name,loan_day,loan_month;

    public:
        Loan();
        Loan(int book_id, int patron_id, 
             std::wstring book_isbn,std::wstring book_title,
             std::wstring patron_name,std::wstring loan_day, 
             std::wstring loan_month);

        int getBookId();
        int getPatronId();

        std::wstring getBookIsbn();
        std::wstring getBookName();
        std::wstring getPatronName();
        std::wstring getLoanDay();
        std::wstring getLoanMonth();

        std::wstring getMenuEntry();

        void setBookId(int book_id);
        void setPatronId(int patron_id);
        void setBookIsbn(std::wstring book_isbn);
        void setBookTitle(std::wstring book_title);
        void setPatronName(std::wstring patron_name);
        void setLoanDay(std::wstring loan_day);
        void setLoanMonth(std::wstring loan_month);
};