#include <vector>
#include <string>
#include <UI_Helper.h>
#include <Book.h>
#include <Patron.h>
#include <Loan.h>
#include <DTO.h>

template<class T>
void UI_Helper<T>::grab_all_populate(std::vector<DTO<T>*> dto_vector, std::vector<std::wstring>& display_vector){
    display_vector.clear();
    for (DTO<T>* instance: dto_vector){
        std::wstring line = ui_dto_entry_string(instance);
        display_vector.push_back(line);
    }
}


template<class T>
void UI_Helper<T>::search_vector(std::wstring search_string, std::vector<std::wstring>& display_vector){
    std::vector<std::wstring> search_display_vector;
    for (std::wstring line: display_vector){
        if (line.find(search_string) != std::wstring::npos){
            search_display_vector.push_back(line);
        }       
    }
    display_vector = search_display_vector;
}

template<class T>
unsigned int UI_Helper<T>::get_id_from_wstring(std::wstring menu_entry){
	unsigned int id = std::stoul(menu_entry.substr(0, 10));
    return id;
}

template<class T>
bool UI_Helper<T>::populate_book_editor(DTO<Book> dto_book, std::vector<std::wstring*> input_book_content_vector){
    *(input_book_content_vector[0]) = dto_book.dataobj.getIsbn();
    *(input_book_content_vector[1]) = dto_book.dataobj.getTitle();
    *(input_book_content_vector[2]) = dto_book.dataobj.getAuthor();
    *(input_book_content_vector[3]) = dto_book.dataobj.getYear();
    *(input_book_content_vector[4]) = dto_book.dataobj.getCategory();
    *(input_book_content_vector[5]) = dto_book.dataobj.getGenre();
    *(input_book_content_vector[6]) = dto_book.dataobj.getIsAvailable() ? L"True" : L"False";
    return true;
}

template<class T>
bool UI_Helper<T>::populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::wstring*> input_patron_content_vector){
    *(input_patron_content_vector[0]) = dto_patron.dataobj.getIsActive() ? L"True" : L"False";
    *(input_patron_content_vector[1]) = dto_patron.dataobj.getFname();
    *(input_patron_content_vector[2]) = dto_patron.dataobj.getLname();
    *(input_patron_content_vector[3]) = dto_patron.dataobj.getAddress();
    *(input_patron_content_vector[4]) = dto_patron.dataobj.getPostcode();
    *(input_patron_content_vector[5]) = dto_patron.dataobj.getContact();
    *(input_patron_content_vector[6]) = std::to_wstring(dto_patron.dataobj.getNumBorrowed());
    return true;
}

template<class T>
bool UI_Helper<T>::populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::wstring*> input_loan_content_vector){
    *(input_loan_content_vector[0]) = std::to_wstring(dto_loan.dataobj.getBookId());
    *(input_loan_content_vector[1]) = dto_loan.dataobj.getBookIsbn();
    *(input_loan_content_vector[2]) = dto_loan.dataobj.getBookName();
    *(input_loan_content_vector[3]) = std::to_wstring(dto_loan.dataobj.getPatronId());
    *(input_loan_content_vector[4]) = dto_loan.dataobj.getPatronName();
    *(input_loan_content_vector[5]) = dto_loan.dataobj.getLoanDay();
    *(input_loan_content_vector[6]) = dto_loan.dataobj.getLoanMonth();
    return true;
}

template<class T>
std::wstring UI_Helper<T>::ui_dto_entry_string(DTO<T>* dto){
    return std::to_wstring(dto->id) + L" - " + dto->dataobj.getMenuEntry();
}

template<class T>
void UI_Helper<T>::clear_editor(std::vector<std::wstring*> input_editor_vector){
    for (std::wstring* entry: input_editor_vector){
        *entry=L"";
    }
}

template<class T>
bool UI_Helper<T>::save_book_changes(DTO<Book>* dto_book, std::vector<std::wstring*> input_book_content_vector){
    dto_book->dataobj.setIsbn(*(input_book_content_vector[0]));
    dto_book->dataobj.setTitle(*(input_book_content_vector[1]));
    dto_book->dataobj.setAuthor(*(input_book_content_vector[2]));
    dto_book->dataobj.setYear(*(input_book_content_vector[3]));
    dto_book->dataobj.setCategory(*(input_book_content_vector[4]));
    dto_book->dataobj.setGenre(*(input_book_content_vector[5]));
    //dto_book.dataobj.setIsAvailable(*(input_book_content_vector[6]));
    return true;
}




template class UI_Helper<Book>;
template class UI_Helper<Patron>;
template class UI_Helper<Loan>;