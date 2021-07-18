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
void UI_Helper<T>::search_vector(std::vector<std::wstring>* vec, std::wstring search_string){
    //vec.clear();
    // loop thru each menu element
    // if substring match, push to vec
}

template<class T>
unsigned int UI_Helper<T>::get_id_from_wstring(std::wstring menu_entry){
	unsigned int id = std::stoul(menu_entry.substr(0, 10));
    return id;
}

template<class T>
bool UI_Helper<T>::populate_book_editor(DTO<Book> dto_book, std::vector<std::wstring*> input_book_content_vector){
    *(input_book_content_vector[0]) = std::to_wstring(dto_book.id);
    *(input_book_content_vector[1]) = dto_book.dataobj.getIsbn();
    *(input_book_content_vector[2]) = dto_book.dataobj.getTitle();
    *(input_book_content_vector[3]) = dto_book.dataobj.getAuthor();
    *(input_book_content_vector[4]) = dto_book.dataobj.getYear();
    *(input_book_content_vector[5]) = dto_book.dataobj.getCategory();
    *(input_book_content_vector[6]) = dto_book.dataobj.getGenre();
    *(input_book_content_vector[7]) = dto_book.dataobj.getIsAvailable() ? L"True" : L"False";
    return true;
}

template<class T>
bool UI_Helper<T>::populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::wstring*> input_patron_content_vector){
    *(input_patron_content_vector[0]) = std::to_wstring(dto_patron.id);
    *(input_patron_content_vector[1]) = dto_patron.dataobj.getIsActive() ? L"True" : L"False";
    *(input_patron_content_vector[2]) = dto_patron.dataobj.getFname();
    *(input_patron_content_vector[3]) = dto_patron.dataobj.getLname();
    *(input_patron_content_vector[4]) = dto_patron.dataobj.getAddress();
    *(input_patron_content_vector[5]) = dto_patron.dataobj.getPostcode();
    *(input_patron_content_vector[6]) = dto_patron.dataobj.getContact();
    *(input_patron_content_vector[7]) = std::to_wstring(dto_patron.dataobj.getNumBorrowed());
    return true;
}

template<class T>
bool UI_Helper<T>::populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::wstring*> input_loan_content_vector){
    *(input_loan_content_vector[0]) = std::to_wstring(dto_loan.id);
    *(input_loan_content_vector[1]) = std::to_wstring(dto_loan.dataobj.getBookId());
    *(input_loan_content_vector[2]) = dto_loan.dataobj.getBookIsbn();
    *(input_loan_content_vector[3]) = dto_loan.dataobj.getBookName();
    *(input_loan_content_vector[4]) = std::to_wstring(dto_loan.dataobj.getPatronId());
    *(input_loan_content_vector[5]) = dto_loan.dataobj.getPatronName();
    *(input_loan_content_vector[6]) = dto_loan.dataobj.getLoanDay();
    *(input_loan_content_vector[7]) = dto_loan.dataobj.getLoanMonth();
    return true;
}

template<class T>
std::wstring UI_Helper<T>::ui_dto_entry_string(DTO<T>* dto){
    return std::to_wstring(dto->id) + L" - " + dto->dataobj.getMenuEntry();
}




template class UI_Helper<Book>;
template class UI_Helper<Patron>;
template class UI_Helper<Loan>;