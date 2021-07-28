#include <string>
#include <DTO.h>
#include <Book.h>
#include <Patron.h>

#ifndef LOAN_H_
#define LOAN_H_


class Loan{
    DTO<Book>* book_dto;
    DTO<Patron>* patron_dto;
    std::wstring loan_date_issue ,loan_date_due;

    public:
        Loan();
        Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::wstring loan_date_issue, std::wstring loan_date_due);

        unsigned int getBookId();
        unsigned int getPatronId();

        std::wstring getBookIsbn();
        std::wstring getBookName();
        std::wstring getPatronName();
        std::wstring getLoanDateIssue();
        std::wstring getLoanDateDue();

        std::wstring getMenuEntry();

        void setBook(DTO<Book>* book);
        void setPatron(DTO<Patron>* patron);
        void setLoanDateIssue(std::wstring date_issue);
        void setLoanDateDue(std::wstring date_due);
};

#endif
