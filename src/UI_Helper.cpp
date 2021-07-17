#include <vector>
#include <string>
#include <UI_Helper.h>
#include <Book.h>
#include <Patron.h>
#include <Loan.h>

template<class T>
void UI_Helper<T>::grab_all_populate(std::vector<T> instance_vector, std::vector<std::wstring>& display_vector){
    display_vector.clear();
    for (T instance: instance_vector){
        display_vector.push_back(instance.getMenuEntry());
        // (std::wstring)instance.id + instance.dataobj.getMenuEntry
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
            




template class UI_Helper<Book>;
template class UI_Helper<Patron>;
template class UI_Helper<Loan>;
