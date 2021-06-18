#include <array>       // for array
#include <chrono>      // for operator""s, chrono_literals
#include <cmath>       // for sin
#include <functional>  // for ref, reference_wrapper, function
#include <memory>      // for allocator, shared_ptr, __shared_ptr_access
#include <string>      // for wstring, basic_string, operator+, to_wstring
#include <thread>      // for sleep_for, thread
#include <utility>     // for move
#include <vector>      // for vector
 
#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, Tab, Toggle
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/component/event.hpp>           // for Event, Event::Custom
#include <ftxui/component/input.hpp>           // for InputBase
#include <ftxui/component/screen_interactive.hpp>  // for Component, ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for text, operator|, color, bgcolor, Element, filler, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
#include <ftxui/screen/color.hpp>  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default
#include <ftxui/component/menu.hpp>

using namespace ftxui;

int main(int argc, char* argv[]) {

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

	std::wstring user_search_input = L"";

	int dialog_to_show = 0; //0 - None		1 - Book Dialog		2 - Patron Dialog		3 - Loan Dialog

	#pragma region Book Tab

	// ---------------------------------------- Book Tab ---------------------------------------- 
	//Book Search
	auto book_user_search_input = Input(&user_search_input, L"Search books");

	// Book Menu
	std::vector<std::wstring> book_menu_entries = 	{	
		L"11 - 978-3-640123-07-8 - The C Programming Language - Keninghan, B.  - 1978 - Non-Fiction - Reference - 1", 
		L"12 - 978-3-452323-08-8 - Requirements Engineering - Wiegers, K. & Beatty, J.  - 2013 - Non-Fiction - Reference - 1",
		L"13 - 978-3-640123-05-8 - The Da Vinci Code - Brown, D.  - 2003 - Fiction - Mystery - 1",

													};
	int book_menu_entries_selectedidx = 0;
	auto book_menu = Menu(&book_menu_entries, &book_menu_entries_selectedidx);

	MenuBase::From(book_menu)->on_enter = [&](){
		dialog_to_show = 1;
	};

	// Book Editor - Inputs
	std::wstring 	input_book_id_content, 		input_book_isbn_content, 
					input_book_title_content,	input_book_author_content, 
					input_book_year_content,	input_book_category_content, 
					input_book_genre_content, 	input_book_available_content;
					
	auto input_book_id = 		Input(&input_book_id_content, 		L"");
	auto input_book_isbn = 		Input(&input_book_isbn_content, 	L"");
	auto input_book_title = 	Input(&input_book_title_content, 	L"");
	auto input_book_author = 	Input(&input_book_author_content, 	L"");
	auto input_book_year = 		Input(&input_book_year_content, 	L"");
	auto input_book_category = 	Input(&input_book_category_content, L"");
	auto input_book_genre = 	Input(&input_book_genre_content, 	L"");
	auto input_book_available = Input(&input_book_available_content,L"");
	
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
	auto book_button_add 	= Button(L"Add New", 		[&](){
		std::wstring book_line_content = 	input_book_id_content + L" - " +
											input_book_isbn_content + L" - " +
											input_book_title_content + L" - " +
											input_book_author_content + L" - " +
											input_book_year_content + L" - " +	
											input_book_category_content + L" - " +
											input_book_genre_content + L" - " + 
											input_book_available_content;

		book_menu_entries.push_back(book_line_content);
	}, true);

	auto book_button_save 	= Button(L"Save Changes", 	[](){
		// 
	}, true);

	auto book_button_cancel = Button(L"Cancel", 		[](){

	}, true);

	// Book Editor - Button Container
	auto book_button_container = Container::Horizontal({
		book_button_add, 	
		book_button_save,
		book_button_cancel
	});

	// Book - Search & Menu Container
	auto book_books_container = Container::Vertical({
		book_user_search_input,
		book_menu
	});

	// Book - Main Content Container 
	auto book_content_container = Container::Horizontal({
		book_books_container,
		book_editor_section_input,
		book_button_container
	});


	// Book - Dialog Box 
	std::vector<std::wstring> book_dialog_entries = {
		L"Edit Book", L"Delete Book", L"Loan", L"Exit",
	};

	auto book_dialog_container = Container::Horizontal({
		Button(&book_dialog_entries[0], [&] {
			
		}),
		Button(&book_dialog_entries[1], [&] {
				book_menu_entries.erase(book_menu_entries.begin() + book_menu_entries_selectedidx);
				//delete somewhere else
				dialog_to_show = 0;
			
		}),

		Button(&book_dialog_entries[2], [&] {
			// LOAN BOOK BTN DIALOG CODE
			// Grab the book details, tab user into Loan & Fill the Editor ??
		}),

		Button(&book_dialog_entries[3], [&] {
			dialog_to_show = 0;
		}),
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
								})), 
							hbox({
								book_button_add->	Render() | flex,
								book_button_save->	Render() | flex,
								book_button_cancel->Render() | flex
								}) 							| color(Color::GreenLight)
						})
					})
				});
	};


	// Book - Main Renderer 
	auto book_tab_renderer = Renderer(book_content_container, [&]() { 
			return book_tab(L"BOOKS", L"BOOK EDITOR");
	});

	#pragma endregion

	#pragma region Patron Tab

	// ---------------------------------------- Patron Tab ---------------------------------------- 

	// Patron Search
	auto patron_user_search_input = Input(&user_search_input, L"Search patrons");

	// Patron Menu
	std::vector<std::wstring> patron_menu_entries = { 
		L"56 - Active - John Doe - Bukit Jalil  - 50430 - 0126985741 - 1", 
		L"87 - Barred - Bruce Wayne - Sri Petaling  - 69420 - 0178547963 - 3",
		L"69 - Active - Phillip Fry - Chow Kit  - 50480 - 0143369852 - 2",
		};

	int patron_menu_entries_selectedidx = 0;
	auto patron_menu = Menu(&patron_menu_entries, &patron_menu_entries_selectedidx);

	MenuBase::From(patron_menu)->on_enter = [&](){
		dialog_to_show = 2;
	};

	// Patron Editor - Inputs
	std::wstring 	input_patron_id_content, 		input_patron_status_content, 
					input_patron_fname_content, 	input_patron_lname_content, 
					input_patron_address_content, 	input_patron_postcode_content, 
					input_patron_contact_content, 	input_patron_num_borrowed_content;
					
	auto input_patron_id = 			Input(&input_patron_id_content, 			L"");
	auto input_patron_status = 		Input(&input_patron_status_content, 		L"");
	auto input_patron_fname = 		Input(&input_patron_fname_content, 			L"");
	auto input_patron_lname = 		Input(&input_patron_lname_content, 			L"");
	auto input_patron_address = 	Input(&input_patron_address_content, 		L"");
	auto input_patron_postcode = 	Input(&input_patron_postcode_content, 		L"");
	auto input_patron_contact = 	Input(&input_patron_contact_content, 		L"");
	auto input_patron_num_borrowed =Input(&input_patron_num_borrowed_content,	L"");

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
	auto patron_button_add = 	Button(L"Add New", 		[&](){
		// 
	}, true);
	auto patron_button_save = 	Button(L"Save Changes", [](){}, true);
	auto patron_button_cancel = Button(L"Cancel", 		[](){}, true);

	// Patron Editor - Button Container
	auto patron_button_container = Container::Horizontal({
		patron_button_add, 
		patron_button_save,
		patron_button_cancel
	});

	// Patron - Search & Menu Container
	auto patron_patrons_container = Container::Vertical({
		patron_user_search_input,
		patron_menu
	});

	// Patron - Main Content Container 
	auto patron_content_container = Container::Horizontal({
		patron_patrons_container,
		patron_editor_section_input,
		patron_button_container
	});

	// Patron - Dialog Box
	std::vector<std::wstring> patron_dialog_entries = {
		L"Edit Patron", L"Delete Patron", L"View Borrows", L"Cancel"
	};

	auto patron_dialog_container = Container::Horizontal({
		Button(&patron_dialog_entries[0], [&]{
			// Edit Patron
		}),
		Button(&patron_dialog_entries[1], [&]{
			// Delete Patron 
		}),
		Button(&patron_dialog_entries[2], [&]{
			// View Borrows
		}),
		Button(&patron_dialog_entries[3], [&]{
			dialog_to_show = 0;
		}),
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
				patron_user_search_input->Render() | flex,
				separator(),
				hbox({
					window(	text(left_window_text) | 		color(Color::BlueLight), 
							vbox({
								patron_menu->Render() 
							})) | flex | 					color(Color::BlueLight),
					vbox({ 
						window(	text(right_window_text)	| 	color(Color::BlueLight), 
							vbox({
								patron_editor_section() | 	color(Color::BlueLight)
							})),
							hbox({
								patron_button_add->		Render() | flex,
								patron_button_save->	Render() | flex,
								patron_button_cancel->	Render() | flex
								}) ,
						})
					})
				});
	};

	// Patron - Main Renderer 
	auto patron_tab_renderer = Renderer(patron_content_container, [&]() { 
			return patron_tab(L"PATRONS", L"PATRON EDITOR");
		}
	);

	#pragma endregion

	#pragma region Loan Tab

	// ---------------------------------------- Loan Tab ---------------------------------------- 

	// Loan Search
	auto loan_user_search_input = Input(&user_search_input, L"Search loans");
	
	// Loan Menu
	std::vector<std::wstring> loan_menu_entries = 	{	
		L"69 - 42 - Mein Kampf  01 - Julie Doe - 978-3-640123-07-8 - April 20", 
		L"74 - 18 - Science of Sleep - 03 - Beff Jazos - 978-3-452323-08-8 - April 03",
		L"51 - 79 - Animal Farm - 54  - Norman Bates - 978-3-640123-05-8 - March 21",
													};	

	int loan_menu_entries_selectedidx = 0;

	auto loan_menu = Menu(&loan_menu_entries, &loan_menu_entries_selectedidx);

	MenuBase::From(loan_menu)->on_enter = [&](){
		dialog_to_show = 3;
	};

	// Loan Editor - Inputs
	std::wstring 	input_loan_id_content, 			input_loan_book_id_content, 
					input_loan_book_isbn_content, 	input_loan_book_name_content,
					input_loan_patron_id_content, 	input_loan_patron_name_content,
					input_loan_day_content, 		input_loan_month_content;

	auto input_loan_id 		  = 	Input(&input_loan_id_content, 			L"");
	auto input_loan_book_id   = 	Input(&input_loan_book_id_content, 		L"");
	auto input_loan_book_isbn =		Input(&input_loan_book_isbn_content, 	L"");
	auto input_loan_book_name = 	Input(&input_loan_book_name_content,	L"");
	auto input_loan_patron_id=		Input(&input_loan_patron_id_content,	L"");
	auto input_loan_patron_name =	Input(&input_loan_patron_name_content,	L"");
	auto input_loan_day  	  =		Input(&input_loan_day_content, 			L"");
	auto input_loan_month 	  =		Input(&input_loan_month_content, 		L"");

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
	auto loan_button_loan 	= Button(L"Add New", [&](){
		//
	}, true);

	auto loan_button_extend = Button(L"Save Changes", [](){
			
	}, true);

	auto loan_button_return = Button(L"Cancel", [](){

	}, true);

	// Loan Editor - Button Container
	auto loan_button_container = Container::Horizontal({
		loan_button_loan,
		loan_button_extend,
		loan_button_return
	});

	// Loan - Search & Menu Container
	auto loan_loans_container = Container::Vertical({
		loan_user_search_input,
		loan_menu
	});

	// Loan - Main Content Container
	auto loan_content_container = Container::Horizontal({
		loan_loans_container,
		loan_editor_section_input,
		loan_button_container
	});

	// Loan - Dialog Box
	std::vector<std::wstring> loan_dialog_entries = {
		L"Edit Loan", L"Extend Loan", L"Return Loan", L"Cancel",
	};

	auto loan_dialog_container = Container::Horizontal({
		Button(&loan_dialog_entries[0], [&]{
			// Edit Loan functionality
		}),
		Button(&loan_dialog_entries[1], [&]{
			// Extend Loan functionality
		}),
		Button(&loan_dialog_entries[2], [&]{
			// Return Loan functionality
		}),
		Button(&loan_dialog_entries[3], [&]{
			dialog_to_show = 0;
		}),
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
						})),
						hbox({
							loan_button_loan->	Render() | flex,
							loan_button_extend->Render() | flex,
							loan_button_return->Render() | flex
						}) 								| color(Color::CyanLight)
				})
			})
		});
	};

	//Loan - Main Renderer
	auto loan_tab_renderer = Renderer(loan_content_container, [&]() { 
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
	auto tab_toggle = ftxui::Toggle(&tab_values, &selected_tab);

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