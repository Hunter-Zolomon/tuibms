#include <cmath>       // for sin
#include <functional>  // for ref, reference_wrapper, function
#include <string>      // for wstring, basic_string, operator+, to_wstring
#include <thread>      // for sleep_for, thread
#include <vector>      // for vector

#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, Tab, Toggle
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/component/component_options.hpp> //for MenuOption
#include <ftxui/component/event.hpp>           // for Event, Event::Custom
#include <ftxui/component/mouse.hpp> // for Mouse
#include <ftxui/component/receiver.hpp> // for Receivers
#include <ftxui/component/screen_interactive.hpp>  // for Component, ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for text, operator|, color, bgcolor, Element, filler, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
#include <ftxui/screen/color.hpp>  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default


#include <HashTable.h>
#include <AVLTree.h>
#include <DTO.h>
#include <Book.h>
#include <UI_Helper.h>

using namespace ftxui;

int main(int argc, char* argv[]) {

	HashTable<Book> hash_table_book(1000);
	HashTable<Patron> hash_table_patron(1000);
	HashTable<Loan> hash_table_loan(1000);

	Book bk1(L"45-548", L"C++ Intro", L"Dover, Ben", L"1996", L"Fiction", L"Spirituality", true);
	Book bk2(L"66-892", L"FXTUI Intro", L"Hawk, Mike", L"2005", L"Fiction", L"Self-Improvement", true);
	Book bk3(L"66-892", L"Kamasutra", L"Hawk, Mike", L"2005", L"Fiction", L"Self-Improvement", true);

	DTO<Book> dto_bk1(bk1);
	DTO<Book> dto_bk2(bk2);
	DTO<Book> dto_bk3(bk3);

	hash_table_book(&dto_bk1);
	hash_table_book(&dto_bk2);
	hash_table_book(&dto_bk3);


	Patron pt1(true, L"John", L"Doe", L"Bukit Jalil", L"50430", L"0126985741", 1);
	Patron pt2(false, L"Bruce", L"Wayne", L"Sri Petaling", L"69420", L"017854613", 3);
	Patron pt3(true, L"Phillip", L"Fry", L"Chow Kit", L"50480", L"0143369852", 2);

	DTO<Patron> dto_pt1(pt1);
	DTO<Patron> dto_pt2(pt2);
	DTO<Patron> dto_pt3(pt3);

	hash_table_patron(&dto_pt1);
	hash_table_patron(&dto_pt2);
	hash_table_patron(&dto_pt3);

	Loan ln1(dto_bk1.id, dto_pt1.id, bk1.getIsbn(), bk1.getTitle(), pt1.getFname()+ L" " + pt1.getLname(), L"27", L"Jan");
	Loan ln2(dto_bk2.id, dto_pt2.id, bk2.getIsbn(), bk2.getTitle(), pt2.getFname()+ L" " + pt2.getLname(), L"16", L"Mar");
	Loan ln3(dto_bk3.id, dto_pt3.id, bk3.getIsbn(), bk3.getTitle(), pt3.getFname()+ L" " + pt3.getLname(), L"32", L"Nov");

	DTO<Loan> dto_ln1(ln1);
	DTO<Loan> dto_ln2(ln2);
	DTO<Loan> dto_ln3(ln3);

	hash_table_loan(&dto_ln1);
	hash_table_loan(&dto_ln2);
	hash_table_loan(&dto_ln3);

	const char* title = R"(
	######## ##     ## #### ########  ##     ##  ######  
	   ##    ##     ##  ##  ##     ## ###   ### ##    ## 
	   ##    ##     ##  ##  ##     ## #### #### ##       
	   ##    ##     ##  ##  ########  ## ### ##  ######  
	   ##    ##     ##  ##  ##     ## ##     ##       ## 
	   ##    ##     ##  ##  ##     ## ##     ## ##    ## 
	   ##     #######  #### ########  ##     ##  ######                       
	)"; 

	std::cout << title << std::endl; 

	//0 - None		1 - Book Dialog		2 - Patron Dialog		3 - Loan Dialog
	int dialog_to_show = 0; 

	#pragma region Book Tab
	// ---------------------------------------- Book Tab ---------------------------------------- 
	//Book Search
	std::wstring book_user_search_text = L""; //Book search string text
	InputOption book_user_search_input_option;
	auto book_user_search_input = Input(&book_user_search_text, L"Search books", &book_user_search_input_option); //Input for Book Search 

	// Book Menu
	std::vector<std::wstring> book_menu_entries = {L""}; //UI Display Vector that displays Books
	int book_menu_entries_selectedidx = 0; //Selected book 
	MenuOption book_menu_option;
	auto book_menu = Menu(&book_menu_entries, &book_menu_entries_selectedidx, &book_menu_option); //Menu containing books

	book_menu_option.on_enter = [&](){ dialog_to_show = 1; }; //Triggered when Enter is pressed on a selected menu entry 

	// Book Editor - Inputs
	std::wstring 	input_book_id_content, 		input_book_isbn_content, 
					input_book_title_content,	input_book_author_content, 
					input_book_year_content,	input_book_category_content, 
					input_book_genre_content, 	input_book_available_content;

	InputOption input_book_editor_option; //Options for inputs in Book Editor
	auto input_book_id = 		Input(&input_book_id_content, 		L"", &input_book_editor_option);
	auto input_book_isbn = 		Input(&input_book_isbn_content, 	L"", &input_book_editor_option);
	auto input_book_title = 	Input(&input_book_title_content, 	L"", &input_book_editor_option);
	auto input_book_author = 	Input(&input_book_author_content, 	L"", &input_book_editor_option);
	auto input_book_year = 		Input(&input_book_year_content, 	L"", &input_book_editor_option);
	auto input_book_category = 	Input(&input_book_category_content, L"", &input_book_editor_option);
	auto input_book_genre = 	Input(&input_book_genre_content, 	L"", &input_book_editor_option);
	auto input_book_available = Input(&input_book_available_content,L"", &input_book_editor_option);
	

	// Book Editor - Container
	auto book_editor_section_input = Container::Vertical({
		input_book_id,
		input_book_isbn,
		input_book_title,
		input_book_author,
		input_book_year,	
		input_book_category,
		input_book_genre,
		input_book_available
	});

	// Book Editor - Vector of Input Strings
	std::vector<std::wstring*> book_editor_input_vector{	&input_book_id_content,		&input_book_isbn_content, 
															&input_book_title_content,	&input_book_author_content, 
															&input_book_year_content,	&input_book_category_content, 
															&input_book_genre_content, 	&input_book_available_content};


	// Book Editor - Render Function
	auto book_editor_section = [&]() {
		return vbox({
				hbox({ text(L"BOOK ID   :")  | bold, input_book_id->Render() }),
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
		Book book_line_content(input_book_isbn_content,input_book_title_content,input_book_author_content, input_book_year_content,input_book_category_content, input_book_genre_content,true);
		DTO<Book> dto_temp_new(book_line_content);
		hash_table_book(&dto_temp_new);
		std::wstring book_line_content_menu_entry = UI_Helper<Book>::ui_dto_entry_string(&dto_temp_new);
		book_menu_entries.push_back(book_line_content_menu_entry);
	}, &book_button_editor_option);

	auto book_button_save 	= Button(L"Save Changes",[&](){
		std::vector<DTO<Book>*> all_books = hash_table_book.getAllElements();
		//std::thread do_thread(UI_Helper<Book>::grab_all_populate, all_books, std::ref(book_menu_entries));
		UI_Helper<Book>::grab_all_populate(all_books, book_menu_entries);
		//do_thread.detach();
		//UI_Helper<Book>::grab_all_populate(book_table, book_menu_entries)
	}, &book_button_editor_option);

	auto book_button_cancel = Button(L"Cancel", [&](){
		//TODO
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
		L"Edit Book", L"Delete Book", L"Loan", L"Exit",
	};

	ButtonOption book_dialog_button_option;

	auto book_dialog_button_edit = Button(&book_dialog_entries[0], [&] {
		int id = UI_Helper<Book>::get_id_from_wstring(book_menu_entries[book_menu_entries_selectedidx]);
		DTO<Book> temp_selected_book = hash_table_book[id];
		UI_Helper<Book>::populate_book_editor(temp_selected_book, book_editor_input_vector);
		dialog_to_show = 0;
		
	}, &book_dialog_button_option);

	auto book_dialog_button_delete = Button(&book_dialog_entries[1], [&] {
		int id = UI_Helper<Book>::get_id_from_wstring(book_menu_entries[book_menu_entries_selectedidx]);
		if (hash_table_book.removeFromTable(id)){
			dialog_to_show = 0;
			book_menu_entries.erase(book_menu_entries.begin()+book_menu_entries_selectedidx);
		}
		else{
			book_user_search_text = L"U done fucked up";
		}
			
	}, &book_dialog_button_option);

	auto book_dialog_button_loan = Button(&book_dialog_entries[2], [&] {}, &book_dialog_button_option);
	auto book_dialog_button_exit = Button(&book_dialog_entries[3], [&] {dialog_to_show = 0;}, &book_dialog_button_option);

	auto book_dialog_container = Container::Horizontal({
		book_dialog_button_edit,
		book_dialog_button_delete,
		book_dialog_button_loan,
		book_dialog_button_exit
	});

	auto book_dialog_renderer = Renderer(book_dialog_container, [&]{
		return vbox({
				text(book_menu_entries[book_menu_entries_selectedidx]),
				separator(),
				hbox(book_dialog_container->Render())  | center,
		}) | border;
	});

	// Book - Tab Render Function
	auto book_tab = [&](std::wstring left_window_text, std::wstring right_window_text) {
		return vbox({
				book_user_search_input->Render() | flex,
				separator(),
				hbox({
					window(	text(left_window_text) 			| color(Color::GreenLight), 
							vbox({
								book_menu->Render()
						})) | flex 							| color(Color::GreenLight),
					vbox({ 
						window(	text(right_window_text) 	| color(Color::GreenLight), 
								vbox({
									book_editor_section()	| color(Color::GreenLight)
								}))							| color(Color::GreenLight), 
							hbox({
								book_button_add->	Render()| flex,
								book_button_save->	Render()| flex,
								book_button_cancel->Render()| flex
								}) 							| color(Color::GreenLight)
						})
					})
				});
	};


	// Book - Main Renderer 
	auto book_tab_renderer = Renderer(book_tab_container, [&]() { 
			return book_tab(L"BOOKS", L"BOOK EDITOR");
	});


	#pragma endregion 

	#pragma region Patron Tab

	// ---------------------------------------- Patron Tab ---------------------------------------- 
	// Patron Search
	std::wstring patron_user_search_text = L"";
	InputOption patron_user_search_input_option;
	auto patron_user_search_input = Input(&patron_user_search_text, L"Search patrons", &patron_user_search_input_option);

	// Patron Menu
	std::vector<std::wstring> patron_menu_entries = {};

	int patron_menu_entries_selectedidx = 0;
	MenuOption patron_menu_option;
	auto patron_menu = Menu(&patron_menu_entries, &patron_menu_entries_selectedidx, &patron_menu_option);

	patron_menu_option.on_enter = [&](){ dialog_to_show = 2; };

	// Patron Editor - Inputs
	std::wstring 	input_patron_id_content, 		input_patron_status_content, 
					input_patron_fname_content, 	input_patron_lname_content, 
					input_patron_address_content, 	input_patron_postcode_content, 
					input_patron_contact_content, 	input_patron_num_borrowed_content;
					
	InputOption input_patron_editor_option;
	auto input_patron_id = 			Input(&input_patron_id_content, 			L"", &input_patron_editor_option);
	auto input_patron_status = 		Input(&input_patron_status_content, 		L"", &input_patron_editor_option);
	auto input_patron_fname = 		Input(&input_patron_fname_content, 			L"", &input_patron_editor_option);
	auto input_patron_lname = 		Input(&input_patron_lname_content, 			L"", &input_patron_editor_option);
	auto input_patron_address = 	Input(&input_patron_address_content, 		L"", &input_patron_editor_option);
	auto input_patron_postcode = 	Input(&input_patron_postcode_content, 		L"", &input_patron_editor_option);
	auto input_patron_contact 	= 	Input(&input_patron_contact_content, 		L"", &input_patron_editor_option);
	auto input_patron_num_borrowed =Input(&input_patron_num_borrowed_content,	L"", &input_patron_editor_option);

	// Patron Editor - Container
	auto patron_editor_section_input = Container::Vertical({
		input_patron_id,
		input_patron_status,
		input_patron_fname,
		input_patron_lname,
		input_patron_address,
		input_patron_postcode,
		input_patron_contact,
		input_patron_num_borrowed
	});

	// Patron Editor - Vector of Input Strings
	std::vector<std::wstring*> patron_editor_input_vector{	&input_patron_id_content, 		&input_patron_status_content, 
															&input_patron_fname_content, 	&input_patron_lname_content, 
															&input_patron_address_content, 	&input_patron_postcode_content,  
															&input_patron_contact_content, 	&input_patron_num_borrowed_content};

	
	// Patron Editor - Render Function
	auto patron_editor_section = [&]() {
		return vbox({
				hbox({ text(L"PATRON ID :") | bold, input_patron_id->Render() }),
				hbox({ text(L"STATUS    :") | bold, input_patron_status->Render() }),
				hbox({ text(L"FIRST NAME:") | bold, input_patron_fname->Render() }),
				hbox({ text(L"LAST NAME :") | bold, input_patron_lname->Render() }),
				hbox({ text(L"ADDRESS   :") | bold, input_patron_address->Render() }),
				hbox({ text(L"POST CODE :") | bold, input_patron_postcode->Render() }),
				hbox({ text(L"CONTACT NO:") | bold, input_patron_contact->Render() }),
				hbox({ text(L"BORROWING :") | bold, input_patron_num_borrowed->Render() })
				});
	};

	// Patron Editor - Buttons
	ButtonOption patron_button_editor_option;
	auto patron_button_add = 	Button(L"Add New", 		[&](){}, &patron_button_editor_option);
	auto patron_button_save = 	Button(L"Save Changes", [&](){
		std::vector<DTO<Patron>*> all_patrons = hash_table_patron.getAllElements();
		UI_Helper<Patron>::grab_all_populate(all_patrons, patron_menu_entries);
	}, &patron_button_editor_option);
	auto patron_button_cancel = Button(L"Cancel", 		[&](){}, &patron_button_editor_option);

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
	std::vector<std::wstring> patron_dialog_entries = { L"Edit Patron", L"Delete Patron", L"View Borrows", L"Cancel" };

	ButtonOption patron_dialog_button_option;

	auto patron_dialog_button_edit = 	Button(	&patron_dialog_entries[0], [&]{
		int id = UI_Helper<Patron>::get_id_from_wstring(patron_menu_entries[patron_menu_entries_selectedidx]);
		DTO<Patron> temp_selected_patron = hash_table_patron[id];
		UI_Helper<Book>::populate_patron_editor(temp_selected_patron, patron_editor_input_vector);
		dialog_to_show = 0;
	}, &patron_dialog_button_option);

	auto patron_dialog_button_delete = 	Button(	&patron_dialog_entries[1], [&]{}, &patron_dialog_button_option);
	auto patron_dialog_button_view = 	Button(	&patron_dialog_entries[2], [&]{}, &patron_dialog_button_option);
	auto patron_dialog_button_exit = 	Button(	&patron_dialog_entries[3], [&]{ dialog_to_show = 0;}, &patron_dialog_button_option);

	auto patron_dialog_container = Container::Horizontal({
		patron_dialog_button_edit,
		patron_dialog_button_delete,
		patron_dialog_button_view,
		patron_dialog_button_exit
	});

	auto patron_dialog_renderer = Renderer(patron_dialog_container, [&]{
		return vbox({
			text(patron_menu_entries[patron_menu_entries_selectedidx]),
			separator(),
			hbox(patron_dialog_container->Render()) | center,  
		}) | border;
	});


	// Patron - Tab Render Function
	auto patron_tab = [&](std::wstring left_window_text, std::wstring right_window_text) {
		return vbox({
				patron_user_search_input->Render() 		| flex,
				separator(),
				hbox({
					window(	text(left_window_text) 		|	color(Color::BlueLight), 
							vbox({
								patron_menu->Render() 
							})) | flex 					| 	color(Color::BlueLight),
					vbox({ 
						window(	text(right_window_text)	| 	color(Color::BlueLight), 
							vbox({
								patron_editor_section() | 	color(Color::BlueLight)
							}))							|	color(Color::BlueLight),
							hbox({
								patron_button_add->		Render() | flex,
								patron_button_save->	Render() | flex,
								patron_button_cancel->	Render() | flex
								}) 						|	color(Color::BlueLight),
						})
					})
				});
	};

	// Patron - Main Renderer 
	auto patron_tab_renderer = Renderer(patron_tab_container, [&]() { 
			return patron_tab(L"PATRONS", L"PATRON EDITOR");
		}
	);


	#pragma endregion

	#pragma region Loan Tab

	// ---------------------------------------- Loan Tab ---------------------------------------- 
	// Loan Search
	std::wstring loan_user_seach_text = L"";
	InputOption loan_user_search_input_option;
	auto loan_user_search_input = Input(&loan_user_seach_text, L"Search loans", &loan_user_search_input_option);
	
	// Loan Menu
	std::vector<std::wstring> loan_menu_entries = 	{};	

	int loan_menu_entries_selectedidx = 0;
	MenuOption loan_menu_option;
	auto loan_menu = Menu(&loan_menu_entries, &loan_menu_entries_selectedidx, &loan_menu_option);

	loan_menu_option.on_enter = [&](){ dialog_to_show = 3; };

	// Loan Editor - Inputs
	std::wstring 	input_loan_id_content, 			input_loan_book_id_content, 
					input_loan_book_isbn_content, 	input_loan_book_name_content,
					input_loan_patron_id_content, 	input_loan_patron_name_content,
					input_loan_day_content, 		input_loan_month_content;

	InputOption input_loan_editor_option;

	auto input_loan_id 		  = 	Input(&input_loan_id_content, 			L"", &input_loan_editor_option);
	auto input_loan_book_id   = 	Input(&input_loan_book_id_content, 		L"", &input_loan_editor_option);
	auto input_loan_book_isbn =		Input(&input_loan_book_isbn_content, 	L"", &input_loan_editor_option);
	auto input_loan_book_name = 	Input(&input_loan_book_name_content,	L"", &input_loan_editor_option);
	auto input_loan_patron_id=		Input(&input_loan_patron_id_content,	L"", &input_loan_editor_option);
	auto input_loan_patron_name =	Input(&input_loan_patron_name_content,	L"", &input_loan_editor_option);
	auto input_loan_day  	  =		Input(&input_loan_day_content, 			L"", &input_loan_editor_option);
	auto input_loan_month 	  =		Input(&input_loan_month_content, 		L"", &input_loan_editor_option);

	// Loan Editor - Container
	auto loan_editor_section_input = Container::Vertical({
		input_loan_id,
		input_loan_book_id,
		input_loan_book_isbn,
		input_loan_book_name,
		input_loan_patron_id,
		input_loan_patron_name,
		input_loan_day,
		input_loan_month
	});

	// Loan Editor - Vector of Input Strings
	std::vector<std::wstring*> loan_editor_input_vector{	&input_loan_id_content, 		&input_loan_book_id_content, 
															&input_loan_book_isbn_content, 	&input_loan_book_name_content,
															&input_loan_patron_id_content, 	&input_loan_patron_name_content,
															&input_loan_day_content, 		&input_loan_month_content};

	// Loan Editor - Render Function
	auto loan_editor_section = [&](){
		return vbox({
				hbox({ text(L"LOAN ID    :") 	| bold, input_loan_id->	Render()}),
				hbox({ text(L"BOOK ID    :") 	| bold, input_loan_book_id->Render()}),
				hbox({ text(L"BOOK ISBN  :") 	| bold, input_loan_book_isbn->Render()}),
				hbox({ text(L"BOOK NAME  :") 	| bold, input_loan_book_name->Render()}),
				hbox({ text(L"PATRON ID  :") 	| bold, input_loan_patron_id->Render()}),
				hbox({ text(L"PATRON NAME:") 	| bold, input_loan_patron_name->Render()}),				
				hbox({ text(L"LOAN DAY   :") 	| bold, input_loan_day->Render()}),
				hbox({ text(L"LOAN MONTH :") 	| bold,	input_loan_month->Render()}),
				});
	};

	// Loan Editor - Buttons
	ButtonOption loan_button_editor_option;

	auto loan_button_add 	= Button(L"Add New", 		[&](){}, &loan_button_editor_option);
	auto loan_button_save 	= Button(L"Save Changes", 	[&](){
		std::vector<DTO<Loan>*> all_loans = hash_table_loan.getAllElements();
		UI_Helper<Loan>::grab_all_populate(all_loans, loan_menu_entries);
	}, &loan_button_editor_option);
	auto loan_button_cancel = Button(L"Cancel", 		[&](){}, &loan_button_editor_option);

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
		L"Edit Loan", L"Extend Loan", L"Return Loan", L"Cancel",
	};

	ButtonOption loan_button_dialog_option;

	auto loan_button_dialog_edit = 		Button(&loan_dialog_entries[0], [&]{
		int id = UI_Helper<Loan>::get_id_from_wstring(loan_menu_entries[loan_menu_entries_selectedidx]);
		DTO<Loan> temp_selected_loan = hash_table_loan[id];
		UI_Helper<Loan>::populate_loan_editor(temp_selected_loan, loan_editor_input_vector);
		dialog_to_show = 0;
	}, &loan_button_dialog_option);

	auto loan_button_dialog_extend = 	Button(&loan_dialog_entries[1], [&]{}, &loan_button_dialog_option);
	auto loan_button_dialog_return = 	Button(&loan_dialog_entries[2], [&]{}, &loan_button_dialog_option);
	auto loan_button_dialog_exit = 		Button(&loan_dialog_entries[3], [&]{}, &loan_button_dialog_option);

	auto loan_dialog_container = Container::Horizontal({
		loan_button_dialog_edit,
		loan_button_dialog_extend,
		loan_button_dialog_return,
		loan_button_dialog_exit
	});

	auto loan_dialog_renderer = Renderer(loan_dialog_container, [&]{
		return vbox({
			text(loan_menu_entries[loan_menu_entries_selectedidx]),
			separator(), 
			hbox(loan_dialog_container->Render())  | center,
		}) | border;
	});


	//Loan - Tab Render Function
	auto loan_tab = [&](std::wstring left_window_text, std::wstring right_window_text){
		return vbox({
			loan_user_search_input->Render() | flex, 
			separator(),
			hbox({
				window(text(left_window_text) 			| color(Color::CyanLight), 
					vbox({
						loan_menu -> Render() 
					})) | flex 							| color(Color::CyanLight),

				vbox({
					window(text(right_window_text) 		| color(Color::CyanLight),
						vbox({
							loan_editor_section()  		| color(Color::CyanLight),
						}))								| color(Color::CyanLight),
						hbox({
							loan_button_add->Render()| flex,
							loan_button_save->Render()| flex,
							loan_button_cancel->Render()| flex
						}) 								| color(Color::CyanLight)
				})
			})
		});
	};

	//Loan - Main Renderer
	auto loan_tab_renderer = Renderer(loan_tab_container, [&]() { 
				return loan_tab(L"LOANS", L"LOAN EDITOR");
			}
		);
	
	#pragma endregion

	#pragma region Navigation Tab & Tab Container 

	std::vector<std::wstring> tab_values {
		L"BOOKS",
		L"PATRONS",
		L"LOANS"
	};

	int selected_tab = 0;

	ToggleOption tab_toggle_option;
	auto tab_toggle = ftxui::Toggle(&tab_values, &selected_tab, &tab_toggle_option);

	auto tab_container = ftxui::Container::Tab(
		{
			book_tab_renderer,
			patron_tab_renderer,
			loan_tab_renderer,
		},
		&selected_tab);

	#pragma endregion

	#pragma region Main Container

	auto main_container = ftxui::Container::Vertical({
		tab_toggle,
		tab_container
	});

	auto main_renderer = ftxui::Renderer(main_container, [&] {
		return vbox({
					tab_toggle->Render(),
					ftxui::separator(),
					tab_container->Render() 
					}) |
			ftxui::border;
	});

	// Gotta be a better way
	auto final_container = Container::Tab({
		main_renderer, //0
		book_dialog_renderer, //1
		patron_dialog_renderer, //2
		loan_dialog_renderer, //3
	}, &dialog_to_show);

	auto final_renderer = Renderer(final_container, [&]{
		Element document = main_renderer->Render();

		if (dialog_to_show==1 && !book_menu_entries.empty()){
			document = dbox({
				document, 
				book_dialog_renderer->Render() | clear_under | center,
			});
		}
		if (dialog_to_show==2 && !patron_menu_entries.empty()){
			document = dbox({
				document,
				patron_dialog_renderer->Render() | clear_under | center,
			});
		} 
		if (dialog_to_show==3 && !loan_menu_entries.empty()){
			document = dbox({
				document, 
				loan_dialog_renderer->Render() | clear_under | center,
			});
		}
		return document;
	});


	auto screen = ftxui::ScreenInteractive::TerminalOutput();
	screen.Loop(final_renderer);
	#pragma endregion

	return EXIT_SUCCESS;
}
