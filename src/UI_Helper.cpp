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
        std::wstring line = ui_book_entry_string(instance);
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
int UI_Helper<T>::get_id_from_wstring(std::wstring menu_entry){
    int id = std::stoi(menu_entry.substr(0,3));
    return id;
}

template<class T>
bool UI_Helper<T>::populate_book_editor(int instance_id, std::vector<T> instance_vector, std::vector<std::wstring> input_book_content_vector){
    return true;
}

template<class T>
std::wstring UI_Helper<T>::ui_book_entry_string(DTO<T>* dto_book){
    return std::to_wstring(dto_book->id) + L" - " + dto_book->dataobj.getMenuEntry();
}




template class UI_Helper<Book>;
template class UI_Helper<Patron>;
template class UI_Helper<Loan>;
//template class UI_Helper<DTO<Book>*>;
//template class UI_Helper<DTO<Patron>*>;
//template class UI_Helper<DTO<Loan>*>;
