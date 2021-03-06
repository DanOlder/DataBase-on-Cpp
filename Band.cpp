#include "BigHeader.hpp"

Band::Band() {

}

Band::Band(int id) {

}

void Band::get_data(int wanted_id) {
    Band* temp = find_with_id(wanted_id);
    Band_strc temp_data = temp->data;

    std::cout << "band id: " << temp->get_id() << std::endl;
    std::cout << "label id for band: " << temp_data.recordLabel_id << std::endl;
    std::cout << "The band name: " << temp_data.band_name << std::endl;
    std::cout << "The band year of found: " << temp_data.year_of_forming << std::endl;
}

void Band::get_all_data() {
    for (int i = 1; i != head->get_id() + 1; i++) {
        get_data(i);
    }
}

Band_strc* Band::fill_first_node() {
    if (this == this->tail) {

        return &data;

    }
    else {
        MessageBox::Show("The first node's already created", "Error");
        return NULL;
    }
}

int Band::find_id(std::string str) {

    Band* temp;
    for (temp = this->tail; temp != NULL; temp = temp->next) {
        if (temp->data.band_name == str) {
            return temp->get_id();
        }
    }
    return -1;
}
