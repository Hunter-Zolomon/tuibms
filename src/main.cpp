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
using namespace ftxui;

int main(int argc, char* argv[]) {
	std::wstring input_book_id_content, input_isbn_content, input_subject_content,  input_book_name_content, input_author_content, input_publisher_content, input_edition_content, input_num_copies_content, input_cost_content;
	auto input_book_id = Input(&input_book_id_content, L"");
	auto input_isbn = Input(&input_isbn_content, L"");
	auto input_subject = Input(&input_subject_content, L"");
	auto input_book_name = Input(&input_book_name_content, L"");
	auto input_author = Input(&input_author_content, L"");
	auto input_publisher = Input(&input_publisher_content, L"");
	auto input_edition = Input(&input_edition_content, L"");
	auto input_num_copies = Input(&input_num_copies_content, L"");
	auto input_cost = Input(&input_cost_content, L"");
	
	auto editorsectioninputs = Container::Vertical({
		input_book_id,
		input_isbn,
		input_subject,
		input_book_name,
		input_author,
		input_publisher,
		input_edition,
		input_num_copies,
		input_cost
	});

	auto bookeditorsection = [&]() {
		return vbox({
				hbox({ text(L"Book ID: "), input_book_id->Render() }),
				hbox({ text(L"ISBN Number: "), input_isbn->Render() }),
				hbox({ text(L"Subject: "), input_subject->Render() }),
				hbox({ text(L"Name: "), input_book_name->Render() }),
				hbox({ text(L"Author: "), input_author->Render() }),
				hbox({ text(L"Publisher: "), input_publisher->Render() }),
				hbox({ text(L"Edition: "), input_edition->Render() }),
				hbox({ text(L"Copies: "), input_num_copies->Render() }),
				hbox({ text(L"Cost: "), input_cost->Render() })
				});
	};

	std::wstring input_patron_id_content, input_patron_type_content, input_patron_first_content, input_patron_last_content, input_patron_address_content, input_patron_postcode_content, input_patron_contact_content, input_patron_nobooksbor_content;
	auto input_patron_id = Input(&input_patron_id_content, L"");
	auto input_patron_type = Input(&input_patron_type_content, L"");
	auto input_patron_first = Input(&input_patron_first_content, L"");
	auto input_patron_last = Input(&input_patron_last_content, L"");
	auto input_patron_address = Input(&input_patron_address_content, L"");
	auto input_patron_postcode = Input(&input_patron_postcode_content, L"");
	auto input_patron_contact = Input(&input_patron_contact_content, L"");
	auto input_patron_nobooksbor = Input(&input_patron_nobooksbor_content, L"");

	auto patroneditorsectioninputs = Container::Vertical({
		input_patron_id,
		input_patron_type,
		input_patron_first,
		input_patron_last,
		input_patron_address,
		input_patron_postcode,
		input_patron_contact,
		input_patron_nobooksbor
	});

	auto patroneditorsection = [&]() {
		return vbox({
				hbox({ text(L"Patron ID: "), input_patron_id->Render() }),
				hbox({ text(L"Patron Type: "), input_patron_type->Render() }),
				hbox({ text(L"First Name: "), input_patron_first->Render() }),
				hbox({ text(L"Last/Surname: "), input_patron_last->Render() }),
				hbox({ text(L"Address: "), input_patron_address->Render() }),
				hbox({ text(L"Post Code: "), input_patron_postcode->Render() }),
				hbox({ text(L"Contact No: "), input_patron_contact->Render() }),
				hbox({ text(L"No Of Books Borrowed: "), input_patron_nobooksbor->Render() })
				});
	};
	
	std::vector<std::wstring> book_menu_entries;
	int book_menu_entries_selectedidx = 0;

	auto book_menu = Menu(&book_menu_entries, &book_menu_entries_selectedidx);

	std::wstring user_search_input = L"";

	auto book_user_search_input = Input(&user_search_input, L"Search for a book");
	auto book_button1 = Button(L"Button 1", [](){}, true);
	auto book_button2 = Button(L"Button 2", [](){}, true);
	auto book_button3 = Button(L"Button 3", [](){}, true);

	auto book_buttonscontainer = Container::Horizontal({
		book_button1, 
		book_button2,
		book_button3
	});

	auto book_bookscontainer = Container::Vertical({
		book_user_search_input,
		book_menu
	});

	auto book_contentcontainer = Container::Horizontal({
		book_bookscontainer,
		editorsectioninputs,
		book_buttonscontainer
	});

	auto booktab = [&](std::wstring leftwindowtext, std::wstring rightwindowstring) {
		return vbox({
				book_user_search_input->Render() | flex,
				hbox({
					window(text(leftwindowtext), vbox({
								book_menu->Render()
								})),
					vbox({ 
						window(text(rightwindowstring), vbox({
									bookeditorsection()
									})), 
						hbox({
							book_button1->Render() | flex,
							book_button2->Render() | flex,
							book_button3->Render() | flex
							})
						})
					})
				});
	};

	auto booktab_renderer = Renderer(book_contentcontainer, [&]() { return booktab(L"Books", L"Book Editor"); });

	std::vector<std::wstring> patron_menu_entries;
	int patron_menu_entries_selectedidx = 0;

	auto patron_menu = Menu(&patron_menu_entries, &patron_menu_entries_selectedidx);

	auto patron_user_search_input = Input(&user_search_input, L"Search for a patron");
	auto patron_button1 = Button(L"Button 1", [](){}, true);
	auto patron_button2 = Button(L"Button 2", [](){}, true);
	auto patron_button3 = Button(L"Button 3", [](){}, true);

	auto patron_buttonscontainer = Container::Horizontal({
		patron_button1, 
		patron_button2,
		patron_button3
	});

	auto patron_patronscontainer = Container::Vertical({
		patron_user_search_input,
		patron_menu
	});

	auto patron_contentcontainer = Container::Horizontal({
		patron_patronscontainer,
		patroneditorsectioninputs,
		patron_buttonscontainer
	});

	auto patrontab = [&](std::wstring leftwindowtext, std::wstring rightwindowstring) {
		return vbox({
				patron_user_search_input->Render() | flex,
				hbox({
					window(text(leftwindowtext), vbox({
								patron_menu->Render()
								})),
					vbox({ 
						window(text(rightwindowstring), vbox({
									patroneditorsection()
									})), 
						hbox({
							patron_button1->Render() | flex,
							patron_button2->Render() | flex,
							patron_button3->Render() | flex
							})
						})
					})
				});
	};

	auto patrontab_renderer = Renderer(patron_contentcontainer, [&]() { return patrontab(L"Patrons", L"Patron Editor"); });

	auto borrowtab_renderer = Renderer([&]() { return text(L"PLACEHOLDER"); });

	std::vector<std::wstring> tab_values {
		L"Books",
		L"Patrons",
		L"Borrow/Return"
	};
	int selectedtab = 0;
	auto tabtoggle = ftxui::Toggle(&tab_values, &selectedtab);

	auto tab_content = ftxui::Container::Tab(
		{
			booktab_renderer,
			patrontab_renderer,
			borrowtab_renderer
		},
		&selectedtab);

	auto container = ftxui::Container::Vertical({
		tabtoggle,
		tab_content
	});

	auto main_renderer = ftxui::Renderer(container, [&] {
			return ftxui::vbox({
					tabtoggle->Render(),
					ftxui::separator(),
					tab_content->Render()
					}) |
			ftxui::border;
	});

	auto screen = ftxui::ScreenInteractive::TerminalOutput();
	screen.Loop(main_renderer);

	return EXIT_SUCCESS;
}
