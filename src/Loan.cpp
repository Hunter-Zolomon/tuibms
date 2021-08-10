#include <Loan.h>

Loan::Loan(){}

Loan::Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::string user_loan_date_issue, std::string user_loan_date_due){
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

std::string Loan::getBookIsbn(){
    return book_dto->dataobj.getIsbn();
}

std::string Loan::getBookName(){
    return book_dto->dataobj.getTitle();
}

std::string Loan::getBookAuthor(){
    return book_dto->dataobj.getAuthor();
}

std::string Loan::getPatronName(){
    return patron_dto->dataobj.getName();
}

std::string Loan::getLoanDateIssue(){
	time_t calculated_time = std::mktime(&this->loan_date_issue);
	std::tm calculated_tm = *std::localtime(&calculated_time);
	std::stringstream wss;
	wss << std::put_time(&calculated_tm, "%d-%m-%Y");
	return wss.str();
}

std::string Loan::getLoanDateDue(){
	time_t calculated_time = std::mktime(&this->loan_date_due);
	std::tm calculated_tm = *std::localtime(&calculated_time);
	std::stringstream wss;
	wss << std::put_time(&calculated_tm, "%d-%m-%Y");
	return wss.str();
}


std::string Loan::getMenuEntry(){
    return  std::to_string(getBookId())     + " - " +
            getBookName()   + " - " + 
            getBookAuthor() + " - " + 
            getPatronName() + " - " + 
            getLoanDateIssue() + " - " + 
            getLoanDateDue(); 
}


// Loan - Setters 
void Loan::setBook(DTO<Book>* book){
    book_dto = book;
}
void Loan::setPatron(DTO<Patron>* patron){
    patron_dto = patron;
}

void Loan::setLoanDateIssue(std::string date_issue){
	std::istringstream ss{ date_issue };
	std::tm temporary_tm = {0};
	ss >> std::get_time(&temporary_tm, this->dateFormat.c_str());
	this->loan_date_issue = temporary_tm;
}

void Loan::setLoanDateDue(){
	std::tm temp_tm = this->loan_date_issue;
	temp_tm.tm_mday += 15;
	this->loan_date_due = temp_tm;
}

void Loan::setLoanDateDue(std::string date_due){
	std::istringstream ss{ date_due };
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
