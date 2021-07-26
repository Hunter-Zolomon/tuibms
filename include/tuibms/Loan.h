#include <string>
#include <DTO.h>
#include <Book.h>
#include <Patron.h>

#ifndef LOAN_H_
#define LOAN_H_


class Loan{
    DTO<Book>* book_dto;
    DTO<Patron>* patron_dto;
    std::wstring loan_day,loan_month;

    public:
        Loan();
        Loan(DTO<Book>* book_dto, DTO<Patron>* patron_dto, std::wstring loan_day, std::wstring loan_month);

        unsigned int getBookId();
        unsigned int getPatronId();

        std::wstring getBookIsbn();
        std::wstring getBookName();
        std::wstring getPatronName();
        std::wstring getLoanDay();
        std::wstring getLoanMonth();

        std::wstring getMenuEntry();

        void setBook(DTO<Book>* book);
        void setPatron(DTO<Patron>* patron);
        void setLoanDay(std::wstring day);
        void setLoanMonth(std::wstring month);
};

#endif
