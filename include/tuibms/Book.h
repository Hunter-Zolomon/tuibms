#include <string>

class Book{
    std::wstring    book_isbn,      book_title, 
                    book_author,    book_year, 
                    book_category,  book_genre;
    bool book_isAvailable;
    public:
        Book(std::wstring isbn, std::wstring title, std::wstring author,
             std::wstring year, std::wstring category,std::wstring genre, bool isAvailable);

        bool getIsAvailable();
        std::wstring getIsbn();
        std::wstring getTitle();
        std::wstring getAuthor();
        std::wstring getYear();
        std::wstring getCategory();
        std::wstring getGenre();
        
        std::wstring getMenuEntry();

        void setIsAvailable(bool isAvailable);
        void setIsbn(std::wstring isbn);
        void setTitle(std::wstring title);
        void setAuthor(std::wstring author);
        void setYear(std::wstring year);
        void setCategory(std::wstring category);
        void setGenre(std::wstring genre);

};