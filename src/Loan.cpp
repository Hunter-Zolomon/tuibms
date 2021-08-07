#include <string>
#include <Loan.h>

Loan::Loan(){}

Loan::Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::wstring user_loan_date_issue, std::wstring user_loan_date_due){
    setBook(book_dto);
    book_dto->dataobj.changeAvailValue(-1);
    setPatron(patron_dto);
    patron_dto->dataobj.incrementNumBorrowed();
	loan_date_issue = {0};
	loan_date_due = {0};
    setLoanDateIssue(user_loan_date_issue);
    //setLoanDateDue(user_loan_date_due);
	setLoanDateDue();
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
	//std::wstring temp_loan_date_issue = std::to_wstring(this->loan_date_issue->tm_mday) + L"/" + std::to_wstring(this->loan_date_issue->tm_mon + 1) + L"/" + std::to_wstring(this->loan_date_issue->tm_year);
	time_t calculated_time = std::mktime(&this->loan_date_issue);
	std::tm calculated_tm = *std::localtime(&calculated_time);
	std::wstringstream wss;
	wss << std::put_time(&calculated_tm, L"%d-%m-%Y");
    //return temp_loan_date_issue;
	return wss.str();
}

std::wstring Loan::getLoanDateDue(){
	//std::wstring temp_loan_date_due = std::to_wstring(this->loan_date_due->tm_mday) + L"/" + std::to_wstring(this->loan_date_due->tm_mon + 1) + L"/" + std::to_wstring(this->loan_date_due->tm_year);
	time_t calculated_time = std::mktime(&this->loan_date_due);
	std::tm calculated_tm = *std::localtime(&calculated_time);
	std::wstringstream wss;
	wss << std::put_time(&calculated_tm, L"%d-%m-%Y");
    //return temp_loan_date_due;
	return wss.str();
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
	std::wistringstream ss{ date_issue };
	std::tm temporary_tm = {0};
	ss >> std::get_time(&temporary_tm, this->dateFormat.c_str());
	this->loan_date_issue = temporary_tm;
}

void Loan::setLoanDateDue(){
	std::tm temp_tm = this->loan_date_issue;
	temp_tm.tm_mday += 15;
	this->loan_date_due = temp_tm;
}

void Loan::setLoanDateDue(std::wstring date_due){
	std::wistringstream ss{ date_due };
	std::tm temporary_tm = {0};
	ss >> std::get_time(&temporary_tm, this->dateFormat.c_str());
	this->loan_date_due = temporary_tm;
}

void Loan::extendDateDue(){
	this->loan_date_due.tm_mday += 15;
}

void Loan::prepForLoanReturn(){
	book_dto->dataobj.changeAvailValue(1);
    patron_dto->dataobj.decrementNumBorrowed();
}
