#include <UI_Helper.h>

template<class T>
std::vector<std::string> UI_Helper<T>::split_string_by_delimiter(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1), std::sregex_token_iterator());
    return list;
}

template<class T>
bool UI_Helper<T>::validate_isbn(std::string isbn_string, std::vector<std::string> display_vector){
	for (std::string entry : display_vector)
		if (split_string_by_delimiter(entry, " - ")[1] == isbn_string)
			return true;
	return false;
}

template<class T>
void UI_Helper<T>::grab_all_populate(std::vector<DTO<T>*> dto_vector, std::vector<std::string>& display_vector){
    display_vector.clear();
    for (DTO<T>* instance : dto_vector){
        std::string line = ui_dto_entry_string(instance);
        display_vector.push_back(line);
    }
}

template<class T>
void UI_Helper<T>::search_vector(std::string search_string, std::vector<std::string>& display_vector){
    std::vector<std::string> search_display_vector;
	if (search_string != ""){
		for (std::string line : display_vector){
			if (rapidfuzz::fuzz::partial_token_ratio(line, search_string) >= 65.0)
				search_display_vector.push_back(line);
		}
		display_vector = search_display_vector;
	}
}

template<class T>
void UI_Helper<T>::search_vector(std::string search_string, std::vector<std::string>& display_vector, std::string num_borrowing){
    std::vector<std::string> search_display_vector;
    if (is_valid_int(num_borrowing.substr(3)))
        num_borrowing = num_borrowing.substr(3);
    else
        num_borrowing = "0";
    for (std::string line : display_vector){
        if (line.back() == *num_borrowing.c_str()){
            search_display_vector.push_back(line);
        }       
    }
    display_vector = search_display_vector;
}

template<class T>
unsigned int UI_Helper<T>::get_id_from_string(std::string menu_entry){
	unsigned int id = std::stoul(menu_entry.substr(0, 10));
    return id;
}

template<class T>
void UI_Helper<T>::populate_book_editor(DTO<Book> dto_book, std::vector<std::string*> input_book_content_vector){
    *(input_book_content_vector[0]) = dto_book.dataobj.getIsbn();
    *(input_book_content_vector[1]) = dto_book.dataobj.getTitle();
    *(input_book_content_vector[2]) = dto_book.dataobj.getAuthor();
    *(input_book_content_vector[3]) = dto_book.dataobj.getYear();
    *(input_book_content_vector[4]) = dto_book.dataobj.getCategory();
    *(input_book_content_vector[5]) = dto_book.dataobj.getGenre();
    *(input_book_content_vector[6]) = std::to_string(dto_book.dataobj.getNumTotal());
}

template<class T>
void UI_Helper<T>::populate_patron_editor(DTO<Patron> dto_patron, std::vector<std::string*> input_patron_content_vector){
    *(input_patron_content_vector[0]) = dto_patron.dataobj.getIsActive() ? "True" : "False";
    *(input_patron_content_vector[1]) = dto_patron.dataobj.getName();
    *(input_patron_content_vector[2]) = dto_patron.dataobj.getEmail();
    *(input_patron_content_vector[3]) = dto_patron.dataobj.getAddress();
    *(input_patron_content_vector[4]) = dto_patron.dataobj.getPostcode();
    *(input_patron_content_vector[5]) = dto_patron.dataobj.getPhone();
    *(input_patron_content_vector[6]) = std::to_string(dto_patron.dataobj.getNumBorrowed());
}

template<class T>
void UI_Helper<T>::populate_loan_editor(DTO<Loan> dto_loan, std::vector<std::string*> input_loan_content_vector){
    *(input_loan_content_vector[0]) = std::to_string(dto_loan.dataobj.getBookId());
    *(input_loan_content_vector[1]) = dto_loan.dataobj.getBookIsbn();
    *(input_loan_content_vector[2]) = dto_loan.dataobj.getBookName();
    *(input_loan_content_vector[3]) = std::to_string(dto_loan.dataobj.getPatronId());
    *(input_loan_content_vector[4]) = dto_loan.dataobj.getPatronName();
    *(input_loan_content_vector[5]) = dto_loan.dataobj.getLoanDateIssue();
    *(input_loan_content_vector[6]) = dto_loan.dataobj.getLoanDateDue();
}

template<class T>
void UI_Helper<T>::populate_loan_editor_book_info(DTO<Book>* dto_book, std::vector<std::string*> input_loan_content_vector){
    *(input_loan_content_vector[0]) = std::to_string(dto_book->id);
    *(input_loan_content_vector[1]) = dto_book->dataobj.getIsbn();
    *(input_loan_content_vector[2]) = dto_book->dataobj.getTitle();
}

template<class T>
void UI_Helper<T>::populate_loan_editor_patron_info(DTO<Patron>* dto_patron, std::vector<std::string*> input_loan_content_vector){
    *(input_loan_content_vector[3]) = std::to_string(dto_patron->id);
    *(input_loan_content_vector[4]) = dto_patron->dataobj.getName();
}

template<class T>
std::string UI_Helper<T>::ui_dto_entry_string(DTO<T>* dto){
    return std::to_string(dto->id) + " - " + dto->dataobj.getMenuEntry();
}

template<class T>
void UI_Helper<T>::clear_editor(std::vector<std::string*> input_editor_vector){
    for (std::string* entry : input_editor_vector){
        *entry="";
    }
}

template<class T>
void UI_Helper<T>::save_book_changes(DTO<Book>* dto_book, std::vector<std::string*> input_book_content_vector){
    dto_book->dataobj.setIsbn(*(input_book_content_vector[0]));
    dto_book->dataobj.setTitle(*(input_book_content_vector[1]));
    dto_book->dataobj.setAuthor(*(input_book_content_vector[2]));
    dto_book->dataobj.setYear(*(input_book_content_vector[3]));
    dto_book->dataobj.setCategory(*(input_book_content_vector[4]));
    dto_book->dataobj.setGenre(*(input_book_content_vector[5]));
    dto_book->dataobj.setTotal(std::stoi(*(input_book_content_vector[6])));
}

template<class T>
void UI_Helper<T>::save_patron_changes(DTO<Patron>* dto_patron, std::vector<std::string*> input_patron_content_vector){
    dto_patron->dataobj.setIsActive(bool_of_string(*(input_patron_content_vector[0]))); 
    dto_patron->dataobj.setName(*(input_patron_content_vector[1])); 
    dto_patron->dataobj.setEmail(*(input_patron_content_vector[2])); 
    dto_patron->dataobj.setAddress(*(input_patron_content_vector[3])); 
    dto_patron->dataobj.setPostcode(*(input_patron_content_vector[4]));
    dto_patron->dataobj.setPhone(*(input_patron_content_vector[5])); 
}

template<class T>
void UI_Helper<T>::save_loan_changes(DTO<Loan>* dto_loan, std::vector<std::string*> input_loan_content_vector){
    dto_loan->dataobj.setLoanDateIssue(*(input_loan_content_vector[5]));
    dto_loan->dataobj.setLoanDateDue(*(input_loan_content_vector[6]));
}

template<class T>
bool UI_Helper<T>::is_editor_empty(std::vector<std::string*> input_loan_content_vector){
    for (std::string* line : input_loan_content_vector){
        if (line->empty())
            return true;
    }
    return false;
}

template<class T>
void UI_Helper<T>::display_dialog_message(int* dialog_to_show, std::string* message, int error_code){
    std::map<int, std::string> error_codes {
        //General
        {100, "All fields must be filled. Please try again"},
        {101, "Failed to add. Please try again"},
        {102, "Nothing to save. Please select an entry to edit"},
        {103, "Failed to save changes. Please try again"},
        {104, "Failed to locate object(s). Please try again"},
        {105, "Failed to delete object. Please try again"},
        {106, "Failed to create book. Invalid number of books or Existing ISBN"},
        {107, "Total can't be less than currently loaned books."},
        //Loan related
        {201, "Can't delete a book with an existing loan"},
        {202, "Can't delete a patron with an existing loan"},
        {203, "Failed to create loan. Book is unavailable!"},
        {204, "Failed to create loan. Patron is borrowing maximum books"},
        {205, "Failed to return loan. Please try again"},
        {206, "Failed to create loan. Patron is not active"},
        {207, "Failed to create loan. Date is invalid"},
    };
    *dialog_to_show = 4;
    *message = error_codes[error_code];
}

template<class T>
void UI_Helper<T>::display_last_borrowed(std::vector<std::string> last_borrowed, std::vector<std::string>& display_vector){
    display_vector.clear();
    for (std::string line : last_borrowed){
        display_vector.push_back(line);
    }
}

template<class T>
void UI_Helper<T>::display_currently_borrowing(std::vector<std::string> current_loans, std::vector<std::string>& display_vector){
    display_vector.clear();
    for (std::string loan : current_loans){
        display_vector.push_back(loan);
    }
}

template<class T>
bool UI_Helper<T>::bool_of_string(std::string line){
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return ((line == "true" || line == "1" || line == "t") ? true : false);
}

template<class T>
bool UI_Helper<T>::is_valid_date(std::string date){
    std::string temp_string(date.begin(), date.end());
    int day, month, year;
    sscanf((char*)(temp_string.c_str()), "%2d-%2d-%4d", &day, &month, &year);
    if ((day<32 && day>0) && (month<13 && month>0) && (year>1995 && year<2025)){
        return true;
    }
    return false;
}

template<class T>
bool UI_Helper<T>::is_valid_int(std::string num_string){
    if (!num_string.empty()){
        for (char const &i : num_string){
            if (std::isdigit(i)==0)
                return false;
        } 
        return true;
    }
    return false;
}
template<class T>
bool UI_Helper<T>::is_total_books_valid(std::string num_input, DTO<Book>* dto_book){
    if (std::stoi(num_input) < (dto_book->dataobj.getNumTotal()-dto_book->dataobj.getNumAvailable()))
        return false;
    return true;
}

template class UI_Helper<Book>;
template class UI_Helper<Patron>;
template class UI_Helper<Loan>;
