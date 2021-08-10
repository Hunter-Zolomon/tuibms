#include <vector>
#include <map>
#include <string>
#include <Book.h>
#include <Patron.h>
#include <Loan.h>
#include <DTO.h>
#include <algorithm>
#include <ctime>
#include <regex>
#include <rapidfuzz/fuzz.hpp>

#ifndef UI_HELPER_H_
#define UI_HELPER_H_

template<class T>
class UI_Helper{
    public:
        static std::vector<std::string> split_string_by_delimiter(const std::string str, const std::string regex_str);
		static bool validate_isbn(std::string isbn_string, std::vector<std::string> display_vector);
		static void grab_all_populate(std::vector<DTO<T>*> dto_vector, std::vector<std::string>& display_vector);
        static void search_vector(std::string search_string, std::vector<std::string>& display_vector);
        static void search_vector(std::string search_string, std::vector<std::string>& display_vector, std::string num_borrowing);
        static void add_to_vector(std::vector<std::string>* vec, std::string search_string);
        static bool del_from_vector(std::vector<std::string>* vec);
        static unsigned int  get_id_from_string(std::string menu_entry);
        static std::string ui_dto_entry_string(DTO<T>* dto);
        static void populate_book_editor(DTO<Book> dto_book, std::vector<std::string*> input_book_content_vector);
        static void populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::string*> input_patron_content_vector);
        static void populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::string*> input_loan_content_vector);
        static void populate_loan_editor_book_info(DTO<Book>* dto_book, std::vector<std::string*> input_loan_content_vector);
        static void populate_loan_editor_patron_info(DTO<Patron>* dto_patron, std::vector<std::string*> input_loan_content_vector);
        static void clear_editor(std::vector<std::string*> input_editor_vector);
        static void save_book_changes(DTO<Book>* dto_book, std::vector<std::string*> input_book_content_vector);
        static void save_patron_changes(DTO<Patron>* dto_patron, std::vector<std::string*> input_patron_content_vector);
        static void save_loan_changes(DTO<Loan>* dto_loan, std::vector<std::string*> input_loan_content_vector);
        static bool is_editor_empty(std::vector<std::string*> input_loan_content_vector);
        static void display_dialog_message(int* dialog_to_show, std::string* message, int error_code);
        static void display_last_borrowed(std::vector<std::string> last_borrowed, std::vector<std::string>& display_vector);
        static void display_currently_borrowing(std::vector<std::string> last_borrowed, std::vector<std::string>& display_vector);
        static bool bool_of_string(std::string line);
        static bool is_valid_date(std::string date);
        static bool is_valid_int(std::string num_string);
        static bool is_total_books_valid(std::string num_input, DTO<Book>* dto_book);
};

#endif
