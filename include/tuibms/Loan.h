#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <DTO.h>
#include <Book.h>
#include <Patron.h>

#ifndef LOAN_H_
#define LOAN_H_

class Loan{
	private:
		static inline const std::string dateFormat {"%d-%m-%Y"};
    public:
        DTO<Book>* book_dto;
        DTO<Patron>* patron_dto;
        Loan();
        Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::string loan_date_issue, std::string loan_date_due);

		std::tm loan_date_issue, loan_date_due;

        unsigned int getBookId();
        unsigned int getPatronId();

        std::string getBookIsbn();
        std::string getBookName();
        std::string getBookAuthor();
        std::string getPatronName();
        std::string getLoanDateIssue();
        std::string getLoanDateDue();

        std::string getMenuEntry();

        void setBook(DTO<Book>* book);
        void setPatron(DTO<Patron>* patron);
        void setLoanDateIssue(std::string date_issue);
        void setLoanDateDue(std::string date_due);
		void setLoanDateDue();
		void extendDateDue();

        void prepForLoanReturn();

};

#endif
