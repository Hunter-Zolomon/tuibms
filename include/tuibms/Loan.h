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
	static inline const std::wstring dateFormat {L"%d-%m-%Y"};
    public:
        DTO<Book>* book_dto;
        DTO<Patron>* patron_dto;
        Loan();
        Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::wstring loan_date_issue, std::wstring loan_date_due);

		std::tm loan_date_issue, loan_date_due;

        unsigned int getBookId();
        unsigned int getPatronId();

        std::wstring getBookIsbn();
        std::wstring getBookName();
        std::wstring getBookAuthor();
        std::wstring getPatronName();
        std::wstring getLoanDateIssue();
        std::wstring getLoanDateDue();

        std::wstring getMenuEntry();

        void setBook(DTO<Book>* book);
        void setPatron(DTO<Patron>* patron);
        void setLoanDateIssue(std::wstring date_issue);
        void setLoanDateDue(std::wstring date_due);
		void setLoanDateDue();
		void extendDateDue();

        void prepForLoanReturn();

};

#endif
