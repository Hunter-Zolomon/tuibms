#include <string>
#include <Book.h>

Book::Book(){};

Book::Book( std::wstring isbn, 
            std::wstring title, std::wstring author, std::wstring year, 
            std::wstring category, std::wstring genre,bool isAvailable) {
                setIsbn(isbn);
                setTitle(title);
                setAuthor(author);
                setYear(year);
                setCategory(category);
                setGenre(genre);
                setIsAvailable(isAvailable);
}

// Book - Getters

std::wstring Book::getIsbn(){
    return book_isbn;
}

std::wstring Book::getTitle(){
    return book_title;
}

std::wstring Book::getAuthor(){
    return book_author;
}

std::wstring Book::getYear(){
    return book_year;
}

std::wstring Book::getCategory(){
    return book_category;
}

std::wstring Book::getGenre(){
    return book_genre;
}

std::wstring Book::getMenuEntry(){
    return  book_isbn   + L" - " + 
            book_title  + L" - " + 
            book_author + L" - " + 
            book_year   + L" - " + 
            book_category+ L" - " + 
            book_genre  + L" - " + 
            std::to_wstring(book_isAvailable);
}

bool Book::getIsAvailable(){
    return book_isAvailable;
}

// Book - Setters

void Book::setIsbn(std::wstring isbn){
    book_isbn = isbn;
}
void Book::setTitle(std::wstring title){
    book_title = title;
}

void Book::setAuthor(std::wstring author){
    book_author = author;
}

void Book::setYear(std::wstring year){
    book_year = year;
}

void Book::setCategory(std::wstring category){
    book_category = category;
}

void Book::setGenre(std::wstring genre){
    book_genre = genre;
}

void Book::setIsAvailable(bool isAvailable){
    book_isAvailable = isAvailable;
}


