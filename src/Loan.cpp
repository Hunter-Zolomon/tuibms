#include <string>
#include <Loan.h>

Loan::Loan(){
    int a = 3;
}

Loan::Loan(unsigned int book_id, unsigned int patron_id, 
             std::wstring book_isbn,std::wstring book_title,
             std::wstring patron_name,std::wstring loan_day, std::wstring loan_month){
                setBookId(book_id);
                setPatronId(patron_id);
                setBookIsbn(book_isbn);
                setBookTitle(book_title);
                setPatronName(patron_name);
                setLoanDay(loan_day);
                setLoanMonth(loan_month);
}

// Loan - Getters

unsigned int Loan::getBookId(){
    return book_id;
}

unsigned int Loan::getPatronId(){
    return patron_id;
}

std::wstring Loan::getBookIsbn(){
    return book_isbn;
}

std::wstring Loan::getBookName(){
    return book_title;
}

std::wstring Loan::getPatronName(){
    return patron_name;
}

std::wstring Loan::getLoanDay(){
    return loan_day;
}

std::wstring Loan::getLoanMonth(){
    return loan_month;
}

std::wstring Loan::getMenuEntry(){
    return  std::to_wstring(book_id)    + L" - " + 
            std::to_wstring(patron_id)  + L" - " + 
            book_isbn   + L" - " + 
            book_title  + L" - " + 
            patron_name + L" - " + 
            loan_day    + L" - " + 
            loan_month;
}

// Loan - Setters

void Loan::setBookId(unsigned int book_id){
    book_id = book_id;
}

void Loan::setPatronId(unsigned int patron_id){
    patron_id = patron_id;
}

void Loan::setBookIsbn(std::wstring book_isbn){
    book_isbn = book_isbn;
}

void Loan::setBookTitle(std::wstring book_title){
    book_title = book_title;
}

void Loan::setPatronName(std::wstring patron_name){
    patron_name = patron_name;
}

void Loan::setLoanDay(std::wstring loan_day){
    loan_day = loan_day;
}

void Loan::setLoanMonth(std::wstring loan_month){
    loan_month = loan_month;
}
