#include <string>

#ifndef BOOK_H_
#define BOOK_H_

class Book{
	private:
		std::string    book_isbn,      book_title, 
						book_author,    book_year, 
						book_category,  book_genre;
		unsigned int    num_available,  num_total_books;
    public:
        Book();
        Book(std::string isbn, std::string title, std::string author,
             std::string year, std::string category,std::string genre, int num_available);

        std::string getIsbn();
        std::string getTitle();
        std::string getAuthor();
        std::string getYear();
        std::string getCategory();
        std::string getGenre();
        unsigned int getNumAvailable();
        unsigned int getNumTotal();
        
        std::string getMenuEntry();

        void changeAvailValue(int amount);
        void setIsbn(std::string isbn);
        void setTitle(std::string title);
        void setAuthor(std::string author);
        void setYear(std::string year);
        void setCategory(std::string category);
        void setGenre(std::string genre);
        void setTotal(unsigned int total);

};

#endif
