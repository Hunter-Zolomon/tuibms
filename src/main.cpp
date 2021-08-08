#include <functional>  // for ref, reference_wrapper, function
#include <string>      // for wstring, basic_string, operator+, to_wstring
#include <thread>      // for sleep_for, thread
#include <vector>      // for vector
#include <time.h>

#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, Tab, Toggle
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/component/component_options.hpp> //for MenuOption
#include <ftxui/component/event.hpp>           // for Event, Event::Custom
#include <ftxui/component/mouse.hpp> // for Mouse
#include <ftxui/component/receiver.hpp> // for Receivers
#include <ftxui/component/screen_interactive.hpp>  // for Component, ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for text, operator|, color, bgcolor, Element, filler, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
#include <ftxui/screen/color.hpp>  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::Ggg, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default

#include <HashTable.h> //for HashTable<T> & HTO<T>
#include <AVLTree.h> //for AVL<T>
#include <DTO.h> //for DTO<T>
#include <Book.h> //for Book class
#include <Patron.h> //for Patron class
#include <Loan.h> //for Loan class
#include <UI_Helper.h> //for UI assist functionality

using namespace ftxui;

int main(int argc, char* argv[]) {

	srand(time(NULL)); //To further seed rand for DTO id generation

	HashTable<Book> hash_table_book(1000); //For testing
	HashTable<Patron> hash_table_patron(1000); //For testing
	HashTable<Loan> hash_table_loan(1000); //For testing

	// Title
	const auto title = [&] () {
		return vbox({
			text(L" "),
			text(L"######## ##     ## #### ########  ##     ##  ###### ") | bold | hcenter | color(Color::GreenLight),
			text(L"   ##    ##     ##  ##  ##     ## ###   ### ##    ##") | bold | hcenter | color(Color::Cyan),
			text(L"   ##    ##     ##  ##  ##     ## #### #### ##      ") | bold | hcenter | color(Color::YellowLight),
			text(L"   ##    ##     ##  ##  ########  ## ### ##  ###### ") | bold | hcenter | color(Color::Magenta),
			text(L"   ##    ##     ##  ##  ##     ## ##     ##       ##") | bold | hcenter | color(Color::MagentaLight),
			text(L"   ##    ##     ##  ##  ##     ## ##     ## ##    ##") | bold | hcenter | color(Color::BlueLight),
			text(L"   ##     #######  #### ########  ##     ##  ###### ") | bold | hcenter | color(Color::Green),
			text(L" ")
		});
	};

	//0 - None		1 - Book Dialog		2 - Patron Dialog		3 - Loan Dialog
	int dialog_to_show = 0; 

	//Janky but I need it here to populate last 10 borrows & force a tab switch
	int selected_tab = 0;
	// Loan Menu 
	std::vector<std::wstring> loan_menu_entries = 	{};	

	// ---------------------------------------- Error Dialog ---------------------------------------- 
	std::wstring error_dialog_error_string;
	ButtonOption error_dialog_button_ok_option;
	auto error_dialog_button_ok = Button(L"Continue", [&]{ 
		dialog_to_show = 0; 
	}, &error_dialog_button_ok_option);


	auto error_dialog_renderer = Renderer(error_dialog_button_ok, [&]{
		return vbox({
			vbox({ 	text(error_dialog_error_string), separator(),	}),
			error_dialog_button_ok->Render() | center
		}) | border | color(Color::Red);
	});
	
	#pragma region Book Tab
	// ---------------------------------------- Book Tab ---------------------------------------- 
	//Book Editing
	int book_editing_id = -1;
	int book_editing_index = -1;

	//Book Loaning Variables
	int book_loaning_id = -1;
	int patron_loaning_id = -1; // Move this line down to patron/ Bring all global stuff above Book Tab pragma

	//Book Search
	std::wstring book_user_search_text = L""; //Book search string text
	InputOption book_user_search_input_option;
	auto book_user_search_input = Input(&book_user_search_text, L"Search books", &book_user_search_input_option); //Input for Book Search 

	// Book Menu
	std::vector<std::wstring> book_menu_entries = {}; //UI Display Vector that displays Books
	int book_menu_entries_selectedidx = 0; //Selected book 
	MenuOption book_menu_option;
	
	auto book_menu = Menu(&book_menu_entries, &book_menu_entries_selectedidx, &book_menu_option); //Menu containing books

	// Book Menu - Searching Functionality
	book_user_search_input_option.on_change = [&](){
		std::vector<DTO<Book>*> all_books = hash_table_book.getAllElements();
		UI_Helper<Book>::grab_all_populate(all_books, book_menu_entries);
		UI_Helper<Book>::search_vector(book_user_search_text, book_menu_entries);
	};


	book_menu_option.on_enter = [&](){ dialog_to_show = 1; }; //Triggered when Enter is pressed on a selected menu entry 

	// Book Editor - Inputs
	std::wstring 	input_book_isbn_content, 
					input_book_title_content,	input_book_author_content, 
					input_book_year_content,	input_book_category_content, 
					input_book_genre_content, 	input_book_available_content;


	// Book Editor - InputOptions
	InputOption 	input_book_isbn_content_option,	
					input_book_title_content_option, 	input_book_author_content_option,	
					input_book_year_content_option, 	input_book_category_content_option,
					input_book_genre_content_option, 	input_book_available_content_option;


	auto input_book_isbn = 		Input(&input_book_isbn_content, 	L"", &input_book_isbn_content_option);
	auto input_book_title = 	Input(&input_book_title_content, 	L"", &input_book_title_content_option);
	auto input_book_author = 	Input(&input_book_author_content, 	L"", &input_book_author_content_option);
	auto input_book_year = 		Input(&input_book_year_content, 	L"", &input_book_year_content_option);
	auto input_book_category = 	Input(&input_book_category_content, L"", &input_book_category_content_option);
	auto input_book_genre = 	Input(&input_book_genre_content, 	L"", &input_book_genre_content_option);
	auto input_book_available = Input(&input_book_available_content,L"", &input_book_available_content_option);
	

	// Book Editor - Container
	auto book_editor_section_input = Container::Vertical({
		input_book_isbn,
		input_book_title,
		input_book_author,
		input_book_year,	
		input_book_category,
		input_book_genre,
		input_book_available
	});

	// Book Editor - Vector of Input Strings. TODO - Implement for Patron & Loan
	std::vector<std::wstring*> book_editor_input_vector{	&input_book_isbn_content, 
															&input_book_title_content,	&input_book_author_content, 
															&input_book_year_content,	&input_book_category_content, 
															&input_book_genre_content, 	&input_book_available_content};


	// Book Editor - Render Function
	auto book_editor_section = [&]() {
		return vbox({
				hbox({ text(L"ISBN      :")	 | bold, input_book_isbn->Render() }),
				hbox({ text(L"TITLE     :")  | bold, input_book_title->Render() }),
				hbox({ text(L"AUTHOR    :")  | bold, input_book_author->Render() }),
				hbox({ text(L"YEAR      :")  | bold, input_book_year->Render() }),
				hbox({ text(L"CATEGORY  :")  | bold, input_book_category->Render() }),
				hbox({ text(L"GENRE     :")  | bold, input_book_genre->Render() }),
				hbox({ text(L"AVAILABLE :")  | bold, input_book_available->Render() }),
				});
	};

	// Book Editor - Buttons
	ButtonOption book_button_editor_option;

auto book_button_add 	= Button(L"Add New",[&](){
	if (!UI_Helper<Book>::is_editor_empty(book_editor_input_vector)){
		if (!UI_Helper<Book>::is_valid_int(input_book_available_content))
			UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 106);
		else{
			Book book_line_content(	input_book_isbn_content, input_book_title_content, input_book_author_content, 
									input_book_year_content, input_book_category_content, input_book_genre_content, 
									std::stoi(input_book_available_content)); 
			DTO<Book>* temp_dto_book = hash_table_book(new DTO<Book>(book_line_content));
			if (nullptr != temp_dto_book) {
				std::wstring book_line_content_menu_entry = UI_Helper<Book>::ui_dto_entry_string(temp_dto_book);
				book_menu_entries.push_back(book_line_content_menu_entry);
				UI_Helper<Book>::clear_editor(book_editor_input_vector);
			} 
			else
				UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 101);
			book_editing_id = -1;
			book_editing_index = -1;			
		}
	} 
	else
		UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 100);

}, &book_button_editor_option);

	auto book_button_save 	= Button(L"Save Changes",[&](){
		if (book_editing_id >= 0 && book_editing_index >= 0){
			DTO<Book>* temp_selected_book = hash_table_book[book_editing_id];
			if (nullptr != temp_selected_book) {
				if (!UI_Helper<Book>::is_valid_int(input_book_available_content))
					UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 106);
				if (!UI_Helper<Book>::is_total_books_valid(input_book_available_content, temp_selected_book))
					UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 107);
				else{
					UI_Helper<Book>::save_book_changes(temp_selected_book, book_editor_input_vector);
					book_menu_entries[book_editing_index] = UI_Helper<Book>::ui_dto_entry_string(temp_selected_book);
					UI_Helper<Book>::clear_editor(book_editor_input_vector);
					book_editing_id = -1;
					book_editing_index = -1;
				}
			} 
			else
				UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
		} 
		else
			UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 102);
	}, &book_button_editor_option);

	auto book_button_cancel = Button(L"Cancel", [&](){
		UI_Helper<Book>::clear_editor(book_editor_input_vector);
		book_editing_id = -1;
		book_editing_index = -1;
	}, &book_button_editor_option);

	// Book Editor - Button Container
	auto book_button_container = Container::Horizontal({
		book_button_add, 	
		book_button_save,
		book_button_cancel
	});

	// Book Editor - Editor & Button Container
	auto book_editor_button_container = Container::Vertical({
		book_editor_section_input,
		book_button_container
	});

	// Book Editor - Book Section Stuff
	auto book_content_container = Container::Horizontal({
		book_menu,
		book_editor_button_container
	});

	// Book Editor - Book Section Stuff & Search Field
	auto book_tab_container = Container::Vertical({
		book_user_search_input,
		book_content_container
	});
	
	// Book - Dialog Box 
	std::vector<std::wstring> book_dialog_entries = {
		L"Loan", L"Edit Book", L"Delete Book", L"Exit",
	};

	ButtonOption book_dialog_button_option;

	auto book_dialog_button_loan = Button(&book_dialog_entries[0], [&] {
		unsigned int id = UI_Helper<Book>::get_id_from_wstring(book_menu_entries[book_menu_entries_selectedidx]);
		book_loaning_id = id;
		dialog_to_show = 0;
	}, &book_dialog_button_option);

	auto book_dialog_button_edit = Button(&book_dialog_entries[1], [&] {
		dialog_to_show = 0;
		unsigned int id = UI_Helper<Book>::get_id_from_wstring(book_menu_entries[book_menu_entries_selectedidx]);
		book_editing_id = id;
		book_editing_index = book_menu_entries_selectedidx;
		DTO<Book>* temp_selected_book = hash_table_book[id];
		if (nullptr!=temp_selected_book)
			UI_Helper<Book>::populate_book_editor(*temp_selected_book, book_editor_input_vector);
		else
			UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
	}, &book_dialog_button_option);

	auto book_dialog_button_delete = Button(&book_dialog_entries[2], [&] {
		unsigned int id = UI_Helper<Book>::get_id_from_wstring(book_menu_entries[book_menu_entries_selectedidx]);
		DTO<Book>* temp_selected_book = hash_table_book[id];
		if (temp_selected_book->dataobj.getNumAvailable()==temp_selected_book->dataobj.getNumTotal()){
			if (hash_table_book.removeFromTable(id)){
				book_menu_entries.erase(book_menu_entries.begin()+book_menu_entries_selectedidx);
				dialog_to_show = 0;
			}
			else
				UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 105);			
		}
		else
			UI_Helper<Book>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 201);
		book_editing_id = -1;
		book_editing_index = -1;
			
	}, &book_dialog_button_option);


	auto book_dialog_button_exit = Button(&book_dialog_entries[3], [&] {dialog_to_show = 0;}, &book_dialog_button_option);

	auto book_dialog_container = Container::Horizontal({
		book_dialog_button_loan,
		book_dialog_button_edit,
		book_dialog_button_delete,
		book_dialog_button_exit
	});

	auto book_dialog_renderer = Renderer(book_dialog_container, [&]{
		return vbox({
				text(L"Select a book menu option") | center,
				separator(),
				hbox(book_dialog_container->Render())  | center,
		}) | border | color(Color::GrayLight);
	});

	// Book - Tab Render Function
	auto book_tab = [&](std::wstring left_window_text, std::wstring right_window_text) {
		return vbox({
				separator(),
				book_user_search_input->Render() | flex,
				separator(),
				hbox({
					window(	text(left_window_text), 
							vbox({
								book_menu->Render()			| frame | size(HEIGHT, LESS_THAN, 10)
						})) | flex,
					vbox({ 
						window(	text(right_window_text), 
								vbox({
									book_editor_section()
								})), 
							hbox({
								book_button_add->	Render()| flex,
								book_button_save->	Render()| flex,
								book_button_cancel->Render()| flex
								})
						})
					})
				});
	};


	// Book - Main Renderer 
	auto book_tab_renderer = Renderer(book_tab_container, [&]() { 
			return book_tab(L"BOOKS", L"BOOK EDITOR") | color(Color::DarkGoldenrod);
	}) ;


	#pragma endregion 

	#pragma region Patron Tab

	// ---------------------------------------- Patron Tab ---------------------------------------- 
	//Patron Editing 
	int patron_editing_id = -1;
	int patron_editing_index = -1;
	
	// Patron Search
	std::wstring patron_user_search_text = L"";
	InputOption patron_user_search_input_option;
	auto patron_user_search_input = Input(&patron_user_search_text, L"Search patrons", &patron_user_search_input_option);

	// Patron Menu
	std::vector<std::wstring> patron_menu_entries = {}; // UI Display Vector that displays Patrons
	int patron_menu_entries_selectedidx = 0; // Selected patron
	MenuOption patron_menu_option;
	auto patron_menu = Menu(&patron_menu_entries, &patron_menu_entries_selectedidx, &patron_menu_option);

	// Patron Menu - Searching Functionality 
	patron_user_search_input_option.on_change = [&](){
		std::vector<DTO<Patron>*> all_patrons = hash_table_patron.getAllElements();
		UI_Helper<Patron>::grab_all_populate(all_patrons, patron_menu_entries);
		UI_Helper<Patron>::search_vector(patron_user_search_text, patron_menu_entries);
	};
	
	patron_menu_option.on_enter = [&](){ dialog_to_show = 2; };

	// Patron Editor - Inputs
	std::wstring 	input_patron_active_content, 	
					input_patron_name_content, 		input_patron_email_content,
					input_patron_address_content, 	input_patron_postcode_content, 
					input_patron_phone_content, 	input_patron_num_borrowed_content;
					
	// Patron Editor - InputOptions
	InputOption	 	input_patron_active_content_option,		
					input_patron_name_content_option, 		input_patron_email_content_option,
					input_patron_address_content_option, 	input_patron_postcode_content_option, 
					input_patron_phone_content_option, 	input_patron_num_borrowed_content_option;

	auto input_patron_active = 		Input(&input_patron_active_content, 		L"", &input_patron_active_content_option);
	auto input_patron_name = 		Input(&input_patron_name_content, 			L"", &input_patron_name_content_option);
	auto input_patron_email = 		Input(&input_patron_email_content, 			L"", &input_patron_email_content_option);
	auto input_patron_address = 	Input(&input_patron_address_content, 		L"", &input_patron_address_content_option);
	auto input_patron_postcode = 	Input(&input_patron_postcode_content, 		L"", &input_patron_postcode_content_option);
	auto input_patron_phone 	= 	Input(&input_patron_phone_content, 			L"", &input_patron_phone_content_option);

	// Patron Editor - Container
	auto patron_editor_section_input = Container::Vertical({
		input_patron_active,
		input_patron_name,
		input_patron_email,
		input_patron_address,
		input_patron_postcode,
		input_patron_phone,
	});

	// Patron Editor - Vector of Input Strings
	std::vector<std::wstring*> patron_editor_input_vector{	&input_patron_active_content, 
															&input_patron_name_content, 	&input_patron_email_content, 
															&input_patron_address_content, 	&input_patron_postcode_content,  
															&input_patron_phone_content,	&input_patron_num_borrowed_content};
	
	// Patron Editor - Render Function
	auto patron_editor_section = [&]() {
		return vbox({
				hbox({ text(L"ACTIVE     :") | bold, input_patron_active->Render() }),
				hbox({ text(L"NAME       :") | bold, input_patron_name->Render() }),
				hbox({ text(L"EMAIL      :") | bold, input_patron_email->Render() }),
				hbox({ text(L"ADDRESS    :") | bold, input_patron_address->Render() }),
				hbox({ text(L"POST CODE  :") | bold, input_patron_postcode->Render() }),
				hbox({ text(L"CONTACT NO :") | bold, input_patron_phone->Render() }),
				hbox({ text(L"BORROWING  :") | bold, text(input_patron_num_borrowed_content) })
				});
	};

	// Patron Editor - Buttons
	ButtonOption patron_button_editor_option;
	auto patron_button_add = 	Button(L"Add New",[&](){
		if (!UI_Helper<Patron>::is_editor_empty({patron_editor_input_vector.begin(), patron_editor_input_vector.end() - 1})){
			Patron patron_line_content(UI_Helper<Book>::bool_of_wstring(input_patron_active_content), input_patron_name_content, input_patron_email_content, input_patron_address_content,input_patron_postcode_content,input_patron_phone_content);
			DTO<Patron>* temp_dto_patron = hash_table_patron(new DTO<Patron>(patron_line_content));
			if (nullptr != temp_dto_patron){
				std::wstring patron_line_content_menu_entry = UI_Helper<Patron>::ui_dto_entry_string(temp_dto_patron);
				patron_menu_entries.push_back(patron_line_content_menu_entry);
				UI_Helper<Patron>::clear_editor(patron_editor_input_vector);
			} 	
			else
				UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 101);
			patron_editing_id = -1;
			patron_editing_index = -1;
		} 
		else
			UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 100);
	}, &patron_button_editor_option);

	auto patron_button_save = 	Button(L"Save Changes", [&](){
		if (patron_editing_id >=0 && patron_editing_index >=0){
			DTO<Patron>* temp_selected_patron = hash_table_patron[patron_editing_id];
			if (nullptr!=temp_selected_patron){
				UI_Helper<Patron>::save_patron_changes(temp_selected_patron, patron_editor_input_vector);
				patron_menu_entries[patron_editing_index] = UI_Helper<Patron>::ui_dto_entry_string(temp_selected_patron);
				UI_Helper<Patron>::clear_editor(patron_editor_input_vector);
				patron_editing_id = -1;
				patron_editing_index = -1;
			} 
			else
				UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
		} 
		else
			UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 102);
	}, &patron_button_editor_option);

	auto patron_button_cancel = Button(L"Cancel", 		[&](){
		UI_Helper<Patron>::clear_editor(patron_editor_input_vector);
		patron_editing_id = -1;
		patron_editing_index = -1;
	}, &patron_button_editor_option);

	// Patron Editor - Button Container
	auto patron_button_container = Container::Horizontal({
		patron_button_add, 
		patron_button_save,
		patron_button_cancel
	});

	// Patron - Editor & Button Container
	auto patron_editor_button_container = Container::Vertical({
		patron_editor_section_input,
		patron_button_container
	});

	// Patron - Patron Section Stuff
	auto patron_patrons_container = Container::Horizontal({
		patron_menu,
		patron_editor_button_container
	});

	// Patron - Patron Section Stuff & Search Field
	auto patron_tab_container = Container::Vertical({
		patron_user_search_input,
		patron_patrons_container
	});

	// Patron - Dialog Box
	std::vector<std::wstring> patron_dialog_entries = { L"Loan", L"Edit Patron", L"Delete Patron", L"View Borrows",  L"Cancel" };

	ButtonOption patron_dialog_button_option;

	auto patron_dialog_button_loan = 	Button(	&patron_dialog_entries[0], [&]{
		unsigned int id = UI_Helper<Book>::get_id_from_wstring(patron_menu_entries[patron_menu_entries_selectedidx]);
		patron_loaning_id = id;
		dialog_to_show = 0;
	}, &patron_dialog_button_option);

	auto patron_dialog_button_edit = 	Button(	&patron_dialog_entries[1], [&]{
		dialog_to_show = 0;
		unsigned int id = UI_Helper<Patron>::get_id_from_wstring(patron_menu_entries[patron_menu_entries_selectedidx]);
		patron_editing_id = id;
		patron_editing_index = patron_menu_entries_selectedidx;
		DTO<Patron>* temp_selected_patron = hash_table_patron[id];
		if (nullptr!=temp_selected_patron)
			UI_Helper<Book>::populate_patron_editor(*temp_selected_patron, patron_editor_input_vector);
		else
			UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
	}, &patron_dialog_button_option);

	auto patron_dialog_button_delete = 	Button(	&patron_dialog_entries[2], [&]{
		unsigned int id = UI_Helper<Loan>::get_id_from_wstring(patron_menu_entries[patron_menu_entries_selectedidx]);
		DTO<Patron>* temp_selected_patron = hash_table_patron[id];
		if (0==temp_selected_patron->dataobj.getNumBorrowed()){
			if (hash_table_patron.removeFromTable(id)){
				patron_menu_entries.erase(patron_menu_entries.begin()+patron_menu_entries_selectedidx);
				dialog_to_show = 0;
			}
			else
				UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 105);
		}
		else
			UI_Helper<Patron>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 202);
		patron_editing_id = -1;
		patron_editing_index = -1;
	}, &patron_dialog_button_option);

	auto patron_dialog_button_view = 	Button(	&patron_dialog_entries[3], [&]{ dialog_to_show = 5; }, &patron_dialog_button_option);

	auto patron_dialog_button_exit = 	Button(	&patron_dialog_entries[4], [&]{ dialog_to_show = 0; }, &patron_dialog_button_option);

	auto patron_dialog_container = Container::Horizontal({
		patron_dialog_button_loan,
		patron_dialog_button_edit,
		patron_dialog_button_delete,
		patron_dialog_button_view,
		patron_dialog_button_exit
	});

	auto patron_dialog_renderer = Renderer(patron_dialog_container, [&]{
		return vbox({
			text(L"Select a patron menu option") | center,
			separator(),
			hbox(patron_dialog_container->Render()) | center,  
		}) | border;
	});

	// Patron - Menu Display Dialog Box
	std::vector<std::wstring> patron_menu_display_dialog_menu_entries;

	MenuOption patron_menu_display_dialog_menu_option;
	patron_menu_display_dialog_menu_option.style_focused = nothing;
	patron_menu_display_dialog_menu_option.style_normal = nothing;
	patron_menu_display_dialog_menu_option.style_selected = nothing;
	patron_menu_display_dialog_menu_option.style_selected_focused = nothing;
	int patron_menu_display_dialog_menu_selectedidx = -1;

	auto patron_menu_display_dialog_menu = Menu(&patron_menu_display_dialog_menu_entries, &patron_menu_display_dialog_menu_selectedidx, &patron_menu_display_dialog_menu_option);

	ButtonOption patron_menu_display_dialog_button_lastthree_option, patron_menu_display_dialog_button_lastten_option, patron_menu_display_dialog_button_exit_option;

	auto patron_menu_display_dialog_button_lastthree = Button(L"Current Borrows", [&] {
		unsigned int id = UI_Helper<Patron>::get_id_from_wstring(patron_menu_entries[patron_menu_entries_selectedidx]);
		DTO<Patron>* temp_selected_patron = hash_table_patron[id];
		UI_Helper<Patron>::display_currently_borrowing(temp_selected_patron->dataobj.getCurrentBorrows(), patron_menu_display_dialog_menu_entries);
	}, &patron_menu_display_dialog_button_lastthree_option); 

	auto patron_menu_display_dialog_button_lastten = Button(L"Last 10 Books Borrowed", [&] {
		unsigned int id = UI_Helper<Loan>::get_id_from_wstring(patron_menu_entries[patron_menu_entries_selectedidx]);
		DTO<Patron>* temp_selected_patron = hash_table_patron[id];
		UI_Helper<Patron>::display_last_borrowed(temp_selected_patron->dataobj.getLastBorrowed(), patron_menu_display_dialog_menu_entries);
	}, &patron_menu_display_dialog_button_lastten_option); 
	
	auto patron_menu_display_dialog_button_exit = Button(L"Exit", [&] {
		patron_menu_display_dialog_menu_entries.clear();
		dialog_to_show = 0;
	}, &patron_menu_display_dialog_button_exit_option); 

	auto patron_menu_display_dialog_container = Container::Horizontal({
		patron_menu_display_dialog_button_lastthree,
		patron_menu_display_dialog_button_lastten,
		patron_menu_display_dialog_button_exit 
	});

	auto patron_menu_display_dialog_renderer = Renderer(patron_menu_display_dialog_container, [&]{
		return vbox({
			text(L"Patron Borrow Display") | center,
			separator(), 
			hbox({patron_menu_display_dialog_button_lastthree->Render() | flex, patron_menu_display_dialog_button_lastten->Render() | flex, patron_menu_display_dialog_button_exit->Render() | flex}) | center,
			separator(),
			patron_menu_display_dialog_menu->Render() | size(HEIGHT, LESS_THAN, 10)
			}) | border;
	});

	// Patron - Tab Render Function
	auto patron_tab = [&](std::wstring left_window_text, std::wstring right_window_text) {
		return vbox({
				separator(),
				patron_user_search_input->Render() | flex,
				separator(),
				hbox({
					window(	text(left_window_text), 
							vbox({
								patron_menu->Render()	| frame | size(HEIGHT, LESS_THAN, 10)
							})) | flex,
					vbox({ 
						window(	text(right_window_text), 
							vbox({
								patron_editor_section()
							})),
							hbox({
								patron_button_add->		Render() | flex,
								patron_button_save->	Render() | flex,
								patron_button_cancel->	Render() | flex
								}),
						})
					})
				});
	};

	// Patron - Main Renderer 
	auto patron_tab_renderer = Renderer(patron_tab_container, [&]() { 
			return patron_tab(L"PATRONS", L"PATRON EDITOR") | color(Color::BlueLight);
		}
	);


	#pragma endregion

	#pragma region Loan Tab

	// ---------------------------------------- Loan Tab ---------------------------------------- 
	//Patron Editing 
	int loan_editing_id = -1;
	int loan_editing_index = -1;
	
	// Loan Search
	std::wstring loan_user_search_text = L"";
	InputOption loan_user_search_input_option;
	auto loan_user_search_input = Input(&loan_user_search_text, L"Search loans", &loan_user_search_input_option);


	// Loan Menu - Searching Functionality
	loan_user_search_input_option.on_change = [&](){
		std::vector<DTO<Loan>*> all_loans = hash_table_loan.getAllElements();
		UI_Helper<Loan>::grab_all_populate(all_loans, loan_menu_entries);
		UI_Helper<Loan>::search_vector(loan_user_search_text, loan_menu_entries);
	};

	int loan_menu_entries_selectedidx = 0;
	MenuOption loan_menu_option;
	auto loan_menu = Menu(&loan_menu_entries, &loan_menu_entries_selectedidx, &loan_menu_option);

	loan_menu_option.on_enter = [&](){ 
		if (!(loan_menu_entries.empty()))
			dialog_to_show = 3; 
	};

	// Loan Editor - Inputs
	std::wstring 	input_loan_book_id_content, 
					input_loan_book_isbn_content, 	input_loan_book_name_content,
					input_loan_patron_id_content, 	input_loan_patron_name_content,
					input_loan_date_issue_content,  input_loan_date_due_content;

	// Loan Editor - InputOptions
	InputOption		input_loan_date_issue_option;

	auto input_loan_date_issue  =	Input(&input_loan_date_issue_content, 	L"", &input_loan_date_issue_option);

	// Loan Editor - Container
	auto loan_editor_section_input = Container::Vertical({
		input_loan_date_issue
	});

	// Loan Editor - Vector of Input Strings
	std::vector<std::wstring*> loan_editor_input_vector{	&input_loan_book_id_content, 
															&input_loan_book_isbn_content, 	&input_loan_book_name_content,
															&input_loan_patron_id_content, 	&input_loan_patron_name_content,
															&input_loan_date_issue_content, &input_loan_date_due_content};

	// Loan Editor - Render Function
	auto loan_editor_section = [&](){
		return vbox({
				hbox({ text(L"BOOK ID     :") 	| bold, text(input_loan_book_id_content)}),
				hbox({ text(L"BOOK ISBN   :") 	| bold, text(input_loan_book_isbn_content)}),
				hbox({ text(L"BOOK NAME   :") 	| bold, text(input_loan_book_name_content)}),
				hbox({ text(L"PATRON ID   :") 	| bold, text(input_loan_patron_id_content)}),
				hbox({ text(L"PATRON NAME :") 	| bold, text(input_loan_patron_name_content)}),				
				hbox({ text(L"ISSUE DATE  :") 	| bold, input_loan_date_issue->Render()}),
				hbox({ text(L"DUE DATE    :") 	| bold,	text(input_loan_date_due_content)}),
				});
	};

	// Loan Editor - Buttons
	ButtonOption loan_button_editor_option;

	auto loan_button_add 	= Button(L"Add New", 		[&](){
		bool reset_id = false;
		if (book_loaning_id >=0 && patron_loaning_id >=0 ){
			DTO<Book>* temp_selected_book = hash_table_book[book_loaning_id];
			DTO<Patron>* temp_selected_patron = hash_table_patron[patron_loaning_id];
			if (nullptr != temp_selected_book && nullptr != temp_selected_patron){
				if (temp_selected_book->dataobj.getNumAvailable() < 1)
					UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 203);
				else if (temp_selected_patron->dataobj.getNumBorrowed() >= 3)
					UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 204);
				else if (!temp_selected_patron->dataobj.getIsActive())
					UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 206);
				else if (!UI_Helper<Loan>::is_valid_date(input_loan_date_issue_content)){
					UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 207);
					reset_id = true;
				}
				else{
					Loan loan_line_contents(temp_selected_book, temp_selected_patron, input_loan_date_issue_content, input_loan_date_due_content);
					DTO<Loan>* temp_dto_loan = hash_table_loan(new DTO<Loan>(loan_line_contents));
					std::wstring loan_line_content_menu_entry = UI_Helper<Loan>::ui_dto_entry_string(temp_dto_loan);
					temp_selected_patron->dataobj.addToCurrentBorrows(temp_selected_book->dataobj.getMenuEntry());
					loan_menu_entries.push_back(loan_line_content_menu_entry);
					UI_Helper<Loan>::clear_editor(loan_editor_input_vector);
				}
			}
			else
				UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
			if (!reset_id){
				book_loaning_id = -1;
				patron_loaning_id = -1; 
			}
		}
		else
			UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 100);
	}, &loan_button_editor_option);

	auto loan_button_save 	= Button(L"Save Changes", 	[&](){
		if (loan_editing_id  >=0 && loan_editing_index >= 0){
			DTO<Loan>* temp_selected_loan = hash_table_loan[loan_editing_id];
			if (nullptr != temp_selected_loan){
				UI_Helper<Loan>::save_loan_changes(temp_selected_loan, loan_editor_input_vector);
				loan_menu_entries[loan_editing_index] = UI_Helper<Loan>::ui_dto_entry_string(temp_selected_loan);
				UI_Helper<Loan>::clear_editor(loan_editor_input_vector);
				loan_editing_id = -1;
				loan_editing_index = -1;
			}
			else
				UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
		}
		else
			UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 102);
	}, &loan_button_editor_option);


	auto loan_button_cancel = Button(L"Cancel", 		[&](){
		UI_Helper<Loan>::clear_editor(loan_editor_input_vector);
		book_loaning_id = -1;
		patron_loaning_id = -1;
	}, &loan_button_editor_option);

	// Loan Editor - Button Container
	auto loan_button_container = Container::Horizontal({
		loan_button_add,
		loan_button_save,
		loan_button_cancel
	});

	// Loan Editor- Editor & Button Container
	auto loan_editor_button_container = Container::Vertical({
		loan_editor_section_input,
		loan_button_container
	});

	// Loan Editor - Loan Section Stuff
	auto loan_content_container = Container::Horizontal({
		loan_menu,
		loan_editor_button_container
	});

	// Loan Editor - Loan Section Stuff & Search Field
	auto loan_tab_container = Container::Vertical({
		loan_user_search_input,
		loan_content_container
	});
	
	// Loan - Dialog Box
	std::vector<std::wstring> loan_dialog_entries = {
		L"Extend Loan", L"Return Loan", L"Cancel",
	};

	ButtonOption loan_button_dialog_option;

	auto loan_button_dialog_extend = 	Button(&loan_dialog_entries[0], [&]{
		unsigned int id = UI_Helper<Loan>::get_id_from_wstring(loan_menu_entries[loan_menu_entries_selectedidx]);
		DTO<Loan>* temp_selected_loan = hash_table_loan[id];
		temp_selected_loan->dataobj.extendDateDue();
		loan_menu_entries[loan_menu_entries_selectedidx] = UI_Helper<Loan>::ui_dto_entry_string(temp_selected_loan);
		dialog_to_show = 0;
	}, &loan_button_dialog_option);


	auto loan_button_dialog_return = 	Button(&loan_dialog_entries[1], [&]{
		unsigned int id = UI_Helper<Loan>::get_id_from_wstring(loan_menu_entries[loan_menu_entries_selectedidx]);
		DTO<Loan>* temp_selected_loan = hash_table_loan[id];
		if (nullptr!=temp_selected_loan){
			temp_selected_loan->dataobj.patron_dto->dataobj.addToLastBorrowed(temp_selected_loan->dataobj.book_dto->dataobj.getMenuEntry());
			temp_selected_loan->dataobj.prepForLoanReturn();
			if (hash_table_loan.removeFromTable(id)){
				loan_menu_entries.erase(loan_menu_entries.begin()+loan_menu_entries_selectedidx);
				dialog_to_show = 0;
			}		
			else
				UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 205);
		}
		else
			UI_Helper<Loan>::display_dialog_message(&dialog_to_show, &error_dialog_error_string, 104);
		loan_editing_id = -1;
		loan_editing_index = -1;
	}, &loan_button_dialog_option);

	auto loan_button_dialog_exit = 		Button(&loan_dialog_entries[2], [&]{ dialog_to_show = 0; }, &loan_button_dialog_option);

	auto loan_dialog_container = Container::Horizontal({
		loan_button_dialog_extend,
		loan_button_dialog_return,
		loan_button_dialog_exit
	});

	auto loan_dialog_renderer = Renderer(loan_dialog_container, [&]{
		return vbox({
			text(L"Select a loan menu option") | center,
			separator(), 
			hbox(loan_dialog_container->Render())  | center,
		}) | border ;
	});


	//Loan - Tab Render Function
	auto loan_tab = [&](std::wstring left_window_text, std::wstring right_window_text){
		return vbox({
				separator(),
				loan_user_search_input->Render() | flex, 
				separator(),
				hbox({
					window(text(left_window_text),
						vbox({
							loan_menu -> Render()			| frame | size(HEIGHT, LESS_THAN, 10)
						})) | flex,
					vbox({
						window(text(right_window_text),
							vbox({
								loan_editor_section(),
							})),
							hbox({
								loan_button_add->Render()| flex,
								loan_button_save->Render()| flex,
								loan_button_cancel->Render()| flex
							}) 								
					})
				})
			});
	};

	//Loan - Main Renderer
	auto loan_tab_renderer = Renderer(loan_tab_container, [&]() { 
				return loan_tab(L"LOANS", L"LOAN EDITOR") | color(Color::MagentaLight);
			}
		);
	
	#pragma endregion

	#pragma region Navigation Tab & Tab Container 

	std::vector<std::wstring> tab_values {
		L"BOOKS",
		L"PATRONS",
		L"LOANS"
	};

	ToggleOption tab_toggle_option;
	auto tab_toggle = Toggle(&tab_values, &selected_tab, &tab_toggle_option);

	tab_toggle_option.on_change = [&](){
		if (0==selected_tab){
			std::vector<DTO<Book>*> all_books = hash_table_book.getAllElements();
			UI_Helper<Book>::grab_all_populate(all_books, book_menu_entries);
		}
		else if (1==selected_tab){
			std::vector<DTO<Patron>*> all_patrons = hash_table_patron.getAllElements();
			UI_Helper<Patron>::grab_all_populate(all_patrons, patron_menu_entries);
		}
		else if (2==selected_tab){
			std::vector<DTO<Loan>*> all_loans = hash_table_loan.getAllElements();
			UI_Helper<Loan>::grab_all_populate(all_loans, loan_menu_entries);
			if (book_loaning_id>=0){
				DTO<Book>* temp_dto_book = hash_table_book[book_loaning_id];
				if (nullptr != temp_dto_book)
					UI_Helper<Loan>::populate_loan_editor_book_info(temp_dto_book, loan_editor_input_vector);
			}
			if (patron_loaning_id>=0){
				DTO<Patron>* temp_dto_patron = hash_table_patron[patron_loaning_id];
				if (nullptr != temp_dto_patron)
					UI_Helper<Loan>::populate_loan_editor_patron_info(temp_dto_patron, loan_editor_input_vector);
			}
			if (book_loaning_id>=0 && patron_loaning_id>=0){
				std::time_t time_now = std::time(0);
				std::tm struct_time_now = *(std::localtime(&time_now));
				std::wstringstream wss;
				wss << std::put_time(&struct_time_now, L"%d-%m-%Y");
				input_loan_date_issue_content = wss.str();
			}
			else
				UI_Helper<Loan>::clear_editor(loan_editor_input_vector);
		}
	};

	auto tab_container = Container::Tab(
		{
			book_tab_renderer,
			patron_tab_renderer,
			loan_tab_renderer,
		},
		&selected_tab);

	#pragma endregion

	#pragma region Main Container

	auto main_container = Container::Vertical({
		tab_toggle,
		tab_container
	});

	auto main_renderer = Renderer(main_container, [&] {
		return vbox({
					tab_toggle->Render() | hcenter | border,
					tab_container->Render() 
					});
	});

	// Gotta be a better way
	auto final_container = Container::Tab({
		main_renderer, //0
		book_dialog_renderer, //1
		patron_dialog_renderer, //2
		loan_dialog_renderer, //3
		error_dialog_renderer, //4
		patron_menu_display_dialog_renderer //5
	}, &dialog_to_show);

	auto final_renderer = Renderer(final_container, [&]{
		Element document = main_renderer->Render() | color(Color::Green);

		if (dialog_to_show==1){
			document = dbox({
				document, 
				book_dialog_renderer->Render() | clear_under | center
			});
		}
		if (dialog_to_show==2){
			document = dbox({
				document,
				patron_dialog_renderer->Render() | clear_under | center
			});
		} 
		if (dialog_to_show==3){
			document = dbox({
				document, 
				loan_dialog_renderer->Render() | clear_under | center
			});
		}
		if (dialog_to_show==4){
			document = dbox({
				document,
				error_dialog_renderer->Render() | clear_under | center
			});
		}
		if (dialog_to_show==5){
			document = dbox({
				document,
				patron_menu_display_dialog_renderer->Render() | clear_under | center
			});
		}
		return vbox({
			title(),
			document
		});
	});

	auto screen = ScreenInteractive::TerminalOutput();
	final_renderer = CatchEvent(final_renderer, [&](Event event) {
		if (event == Event::Escape) {
			screen.Clear();
			screen.ExitLoopClosure();
			return true;
		}
		return false;
	});
	screen.Loop(final_renderer);
	#pragma endregion

	return EXIT_SUCCESS;
}
