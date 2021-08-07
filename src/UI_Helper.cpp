#include <vector>
#include <map>
#include <string>
#include <UI_Helper.h>
#include <Book.h>
#include <Patron.h>
#include <Loan.h>
#include <DTO.h>
#include <algorithm>

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
void UI_Helper<T>::populate_book_editor(DTO<Book> dto_book, std::vector<std::wstring*> input_book_content_vector){
    *(input_book_content_vector[0]) = dto_book.dataobj.getIsbn();
    *(input_book_content_vector[1]) = dto_book.dataobj.getTitle();
    *(input_book_content_vector[2]) = dto_book.dataobj.getAuthor();
    *(input_book_content_vector[3]) = dto_book.dataobj.getYear();
    *(input_book_content_vector[4]) = dto_book.dataobj.getCategory();
    *(input_book_content_vector[5]) = dto_book.dataobj.getGenre();
    *(input_book_content_vector[6]) = std::to_wstring(dto_book.dataobj.getNumTotal());
}

template<class T>
void UI_Helper<T>::populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::wstring*> input_patron_content_vector){
    *(input_patron_content_vector[0]) = dto_patron.dataobj.getIsActive() ? L"True" : L"False";
    *(input_patron_content_vector[1]) = dto_patron.dataobj.getName();
    *(input_patron_content_vector[2]) = dto_patron.dataobj.getEmail();
    *(input_patron_content_vector[3]) = dto_patron.dataobj.getAddress();
    *(input_patron_content_vector[4]) = dto_patron.dataobj.getPostcode();
    *(input_patron_content_vector[5]) = dto_patron.dataobj.getPhone();
    *(input_patron_content_vector[6]) = std::to_wstring(dto_patron.dataobj.getNumBorrowed());
}

template<class T>
void UI_Helper<T>::populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::wstring*> input_loan_content_vector){
    *(input_loan_content_vector[0]) = std::to_wstring(dto_loan.dataobj.getBookId());
    *(input_loan_content_vector[1]) = dto_loan.dataobj.getBookIsbn();
    *(input_loan_content_vector[2]) = dto_loan.dataobj.getBookName();
    *(input_loan_content_vector[3]) = std::to_wstring(dto_loan.dataobj.getPatronId());
    *(input_loan_content_vector[4]) = dto_loan.dataobj.getPatronName();
    *(input_loan_content_vector[5]) = dto_loan.dataobj.getLoanDateIssue();
    *(input_loan_content_vector[6]) = dto_loan.dataobj.getLoanDateDue();
}

template<class T>
void UI_Helper<T>::populate_loan_editor_book_info(DTO<Book>* dto_book, std::vector<std::wstring*> input_loan_content_vector){
    *(input_loan_content_vector[0]) = std::to_wstring(dto_book->id);
    *(input_loan_content_vector[1]) = dto_book->dataobj.getIsbn();
    *(input_loan_content_vector[2]) = dto_book->dataobj.getTitle();
}

template<class T>
void UI_Helper<T>::populate_loan_editor_patron_info(DTO<Patron>* dto_patron, std::vector<std::wstring*> input_loan_content_vector){
    *(input_loan_content_vector[3]) = std::to_wstring(dto_patron->id);
    *(input_loan_content_vector[4]) = dto_patron->dataobj.getName();
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
void UI_Helper<T>::save_book_changes(DTO<Book>* dto_book, std::vector<std::wstring*> input_book_content_vector){
    dto_book->dataobj.setIsbn(*(input_book_content_vector[0]));
    dto_book->dataobj.setTitle(*(input_book_content_vector[1]));
    dto_book->dataobj.setAuthor(*(input_book_content_vector[2]));
    dto_book->dataobj.setYear(*(input_book_content_vector[3]));
    dto_book->dataobj.setCategory(*(input_book_content_vector[4]));
    dto_book->dataobj.setGenre(*(input_book_content_vector[5]));
    dto_book->dataobj.setTotal(std::stoi(*(input_book_content_vector[6])));
}

template<class T>
void UI_Helper<T>::save_patron_changes(DTO<Patron>* dto_patron, std::vector<std::wstring*> input_patron_content_vector){
    dto_patron->dataobj.setIsActive(bool_of_wstring(*(input_patron_content_vector[0]))); 
    dto_patron->dataobj.setName(*(input_patron_content_vector[1])); 
    dto_patron->dataobj.setEmail(*(input_patron_content_vector[2])); 
    dto_patron->dataobj.setAddress(*(input_patron_content_vector[3])); 
    dto_patron->dataobj.setPostcode(*(input_patron_content_vector[4]));
    dto_patron->dataobj.setPhone(*(input_patron_content_vector[5])); 
}

template<class T>
void UI_Helper<T>::save_loan_changes(DTO<Loan>* dto_loan, std::vector<std::wstring*> input_loan_content_vector){
    dto_loan->dataobj.setLoanDateIssue(*(input_loan_content_vector[5]));
    dto_loan->dataobj.setLoanDateDue(*(input_loan_content_vector[6]));
}

template<class T>
bool UI_Helper<T>::is_editor_empty(std::vector<std::wstring*> input_loan_content_vector){
    for (std::wstring* line: input_loan_content_vector){
        if (line->empty())
            return true;
    }
    return false;
}

template<class T>
void UI_Helper<T>::display_dialog_message(int* dialog_to_show, std::wstring* message, int error_code){
    std::map<int, std::wstring> error_codes {
        //General
        {100, L"All fields must be filled. Please try again"},
        {101, L"Failed to add. Please try again"},
        {102, L"Nothing to save. Please select an entry to edit"},
        {103, L"Failed to save changes. Please try again"},
        {104, L"Failed to locate object(s). Please try again"},
        {105, L"Failed to delete object. Please try again"},
        {106, L"Failed to create book. Invalid number of books."},
        //Loan related
        {201, L"Can't delete a book with an existing loan"},
        {202, L"Can't delete a patron with an existing loan"},
        {203, L"Failed to create loan. Book is unavailable!"},
        {204, L"Failed to create loan. Patron is borrowing maximum books"},
        {205, L"Failed to return loan. Please try again"},
        {206, L"Failed to create loan. Patron is not active"},
        {207, L"Failed to create loan. Date is invalid"},
    };
    *dialog_to_show = 4;
    *message = error_codes[error_code];
}

template<class T>
void UI_Helper<T>::display_last_borrowed(std::vector<std::wstring> last_borrowed, std::vector<std::wstring>& display_vector){
    display_vector.clear();
    for (std::wstring line: last_borrowed){
        display_vector.push_back(line);
    }
}

template<class T>
void UI_Helper<T>::display_currently_borrowing(std::vector<std::wstring> current_loans, std::vector<std::wstring>& display_vector){
    display_vector.clear();
    for (std::wstring loan: current_loans){
        display_vector.push_back(loan);
    }
}

template<class T>
bool UI_Helper<T>::bool_of_wstring(std::wstring line){
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return ((line == L"true" || line == L"1" || line == L"t") ? true : false);
}

template<class T>
bool UI_Helper<T>::is_valid_date(std::wstring date){
    std::string temp_string(date.begin(), date.end());
    int day, month, year;
    sscanf((char*)(temp_string.c_str()), "%2d-%2d-%4d", &day, &month, &year);
    if ((day<32 && day>0) && (month<13 && month>0) && (year>1995 && year<2025)){
        return true;
    }
    return false;
}

template<class T>
bool UI_Helper<T>::is_valid_int(std::wstring num_wstring){
    for (char const &i: num_wstring){
        if (std::isdigit(i)==0){
            return false;
        }
    } return true;
}

template class UI_Helper<Book>;
template class UI_Helper<Patron>;
template class UI_Helper<Loan>;
