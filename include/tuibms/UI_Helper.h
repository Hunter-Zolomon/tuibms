#include <vector>
#include <string>
#include <algorithm>

template<class T>
class UI_Helper{
    public:
        static void grab_all_populate(std::vector<T> instance_vector, std::vector<std::wstring>& display_vector);
        static void search_vector(std::vector<std::wstring>* vec, std::wstring search_string);
        static void add_to_vector(std::vector<std::wstring>* vec, std::wstring search_string);
        static bool del_from_vector(std::vector<std::wstring>* vec);
        static int  get_id_from_wstring(std::wstring menu_entry);
        static bool populate_book_editor(int instance_id, std::vector<T> instance_vector, std::vector<std::wstring> input_book_content_vector);
};