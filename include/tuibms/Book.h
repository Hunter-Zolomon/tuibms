#include <string>

#ifndef BOOK_H_
#define BOOK_H_

class Book{
    std::wstring    book_isbn,      book_title, 
                    book_author,    book_year, 
                    book_category,  book_genre;
    unsigned int    num_available,  num_total_books;
    public:
        Book();
        Book(std::wstring isbn, std::wstring title, std::wstring author,
             std::wstring year, std::wstring category,std::wstring genre, int num_available);

        std::wstring getIsbn();
        std::wstring getTitle();
        std::wstring getAuthor();
        std::wstring getYear();
        std::wstring getCategory();
        std::wstring getGenre();
        unsigned int getNumAvailable();
        unsigned int getNumTotal();
        
        std::wstring getMenuEntry();

        void changeAvailValue(int amount);
        void setIsbn(std::wstring isbn);
        void setTitle(std::wstring title);
        void setAuthor(std::wstring author);
        void setYear(std::wstring year);
        void setCategory(std::wstring category);
        void setGenre(std::wstring genre);
        void setTotal(unsigned int total);

};

#endif
