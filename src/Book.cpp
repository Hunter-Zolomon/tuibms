#include <Book.h>

Book::Book(){};

Book::Book( std::string isbn, 
            std::string title, std::string author, std::string year, 
            std::string category, std::string genre, int available) {
                setIsbn(isbn);
                setTitle(title);
                setAuthor(author);
                setYear(year);
                setCategory(category);
                setGenre(genre);
                num_available = available;
                num_total_books = available;
}

// Book - Getters

std::string Book::getIsbn(){
    return book_isbn;
}

std::string Book::getTitle(){
    return book_title;
}

std::string Book::getAuthor(){
    return book_author;
}

std::string Book::getYear(){
    return book_year;
}

std::string Book::getCategory(){
    return book_category;
}

std::string Book::getGenre(){
    return book_genre;
}

std::string Book::getMenuEntry(){
    return  book_isbn   + " - " + 
            book_title  + " - " + 
            book_author + " - " + 
            book_year   + " - " + 
            book_category+ " - " + 
            book_genre  + " - " + 
            std::to_string(num_available);
}

unsigned int Book::getNumAvailable(){
    return num_available;
}

unsigned int Book::getNumTotal(){
    return num_total_books;
}

// Book - Setters

void Book::setIsbn(std::string isbn){
    book_isbn = isbn;
}
void Book::setTitle(std::string title){
    book_title = title;
}

void Book::setAuthor(std::string author){
    book_author = author;
}

void Book::setYear(std::string year){
    book_year = year;
}

void Book::setCategory(std::string category){
    book_category = category;
}

void Book::setGenre(std::string genre){
    book_genre = genre;
}

void Book::changeAvailValue(int amount){
    num_available += amount;
}

void Book::setTotal(unsigned int total){
    num_available += (total-num_total_books);
    num_total_books = total;
}
    

