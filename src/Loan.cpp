#include <string>
#include <Loan.h>

Loan::Loan(){}

Loan::Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::wstring loan_day, std::wstring loan_month){
    setBook(book_dto);
    setPatron(patron_dto);
    setLoanDay(loan_day);
    setLoanMonth(loan_month);
}

// Loan - Getters
unsigned int Loan::getBookId(){
    return book_dto->id;
}

unsigned int Loan::getPatronId(){
    return patron_dto->id;
}


std::wstring Loan::getBookIsbn(){
    return book_dto->dataobj.getIsbn();
}

std::wstring Loan::getBookName(){
    return book_dto->dataobj.getTitle();
}

std::wstring Loan::getPatronName(){
    return  patron_dto->dataobj.getName();
}

std::wstring Loan::getLoanDay(){
    return loan_day;
}

std::wstring Loan::getLoanMonth(){
    return loan_month;
}


std::wstring Loan::getMenuEntry(){
    return  book_dto->dataobj.getTitle() + L" - " + 
            patron_dto->dataobj.getName() + L" " + 
            loan_month + L" - " + 
            loan_day; 
}

// Loan - Setters 
void Loan::setBook(DTO<Book>* book){
    book_dto = book;
}
void Loan::setPatron(DTO<Patron>* patron){
    patron_dto = patron;
}

void Loan::setLoanDay(std::wstring day){
    loan_day = day;
}

void Loan::setLoanMonth(std::wstring month){
    loan_month = month;
}