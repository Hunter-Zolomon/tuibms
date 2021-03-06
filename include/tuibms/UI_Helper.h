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
        static std::vector<std::wstring> split_string_by_delimiter(const std::wstring str, const std::wstring regex_str);
		static bool validate_isbn(std::wstring isbn_string, std::vector<std::wstring> display_vector);
		static void grab_all_populate(std::vector<DTO<T>*> dto_vector, std::vector<std::wstring>& display_vector);
        static void search_vector(std::wstring search_string, std::vector<std::wstring>& display_vector);
        static void search_vector(std::wstring search_string, std::vector<std::wstring>& display_vector, std::wstring num_borrowing);
        static void add_to_vector(std::vector<std::wstring>* vec, std::wstring search_string);
        static bool del_from_vector(std::vector<std::wstring>* vec);
        static unsigned int  get_id_from_wstring(std::wstring menu_entry);
        static std::wstring ui_dto_entry_string(DTO<T>* dto);
        static void populate_book_editor(DTO<Book> dto_book, std::vector<std::wstring*> input_book_content_vector);
        static void populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::wstring*> input_patron_content_vector);
        static void populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::wstring*> input_loan_content_vector);
        static void populate_loan_editor_book_info(DTO<Book>* dto_book, std::vector<std::wstring*> input_loan_content_vector);
        static void populate_loan_editor_patron_info(DTO<Patron>* dto_patron, std::vector<std::wstring*> input_loan_content_vector);
        static void clear_editor(std::vector<std::wstring*> input_editor_vector);
        static void save_book_changes(DTO<Book>* dto_book, std::vector<std::wstring*> input_book_content_vector);
        static void save_patron_changes(DTO<Patron>* dto_patron, std::vector<std::wstring*> input_patron_content_vector);
        static void save_loan_changes(DTO<Loan>* dto_loan, std::vector<std::wstring*> input_loan_content_vector);
        static bool is_editor_empty(std::vector<std::wstring*> input_loan_content_vector);
        static void display_dialog_message(int* dialog_to_show, std::wstring* message, int error_code);
        static void display_last_borrowed(std::vector<std::wstring> last_borrowed, std::vector<std::wstring>& display_vector);
        static void display_currently_borrowing(std::vector<std::wstring> last_borrowed, std::vector<std::wstring>& display_vector);
        static bool bool_of_wstring(std::wstring line);
        static bool is_valid_date(std::wstring date);
        static bool is_valid_int(std::wstring num_wstring);
        static bool is_total_books_valid(std::wstring num_input, DTO<Book>* dto_book);
};

#endif
