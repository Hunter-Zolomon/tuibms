#include <vector>
#include <string>
#include <Book.h>
#include <Patron.h>
#include <Loan.h>
#include <DTO.h>

#ifndef UI_HELPER_H_
#define UI_HELPER_H_

template<class T>
class UI_Helper{
    public:
        static void grab_all_populate(std::vector<DTO<T>*> dto_vector, std::vector<std::wstring>& display_vector);
        static void search_vector(std::wstring search_string, std::vector<std::wstring>& display_vector);
        static void add_to_vector(std::vector<std::wstring>* vec, std::wstring search_string);
        static bool del_from_vector(std::vector<std::wstring>* vec);
        static unsigned int  get_id_from_wstring(std::wstring menu_entry);
        static std::wstring ui_dto_entry_string(DTO<T>* dto);
        static bool populate_book_editor(DTO<Book> dto_book, std::vector<std::wstring*> input_book_content_vector);
        static bool populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::wstring*> input_patron_content_vector);
        static bool populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::wstring*> input_loan_content_vector);
        static void clear_editor(std::vector<std::wstring*> input_editor_vector);
};

#endif
