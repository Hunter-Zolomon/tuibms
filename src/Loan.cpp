#include <string>
#include <Loan.h>

Loan::Loan(){}

Loan::Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::wstring loan_date_issue, std::wstring loan_date_due){
    setBook(book_dto);
    book_dto->dataobj.setIsAvailable(false);
    setPatron(patron_dto);
    patron_dto->dataobj.incrementNumBorrowed();
    setLoanDateIssue(loan_date_issue);
    setLoanDateDue(loan_date_due);
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

std::wstring Loan::getBookAuthor(){
    return book_dto->dataobj.getAuthor();
}

std::wstring Loan::getPatronName(){
    return patron_dto->dataobj.getName();
}

std::wstring Loan::getLoanDateIssue(){
    return loan_date_issue;
}

std::wstring Loan::getLoanDateDue(){
    return loan_date_due;
}


std::wstring Loan::getMenuEntry(){
    return  std::to_wstring(getBookId())     + L" - " +
            getBookName()   + L" - " + 
            getBookAuthor() + L" - " + 
            getPatronName() + L" - " + 
            getLoanDateIssue() + L" - " + 
            getLoanDateDue(); 
}


// Loan - Setters 
void Loan::setBook(DTO<Book>* book){
    book_dto = book;
}
void Loan::setPatron(DTO<Patron>* patron){
    patron_dto = patron;
}

void Loan::setLoanDateIssue(std::wstring date_issue){
    loan_date_issue = date_issue;
}

void Loan::setLoanDateDue(std::wstring date_due){
    loan_date_due = date_due;
}

void Loan::prepForLoanReturn(){
    book_dto->dataobj.setIsAvailable(true);
    patron_dto->dataobj.decrementNumBorrowed();
}
