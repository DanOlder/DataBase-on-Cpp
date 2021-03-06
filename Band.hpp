#pragma once

typedef struct Band_type {
    int recordLabel_id;
    std::string band_name;
    int year_of_forming;
}Band_strc;

class Band : public MyList <Band_strc, Band> {
public:
    Band();
    Band(int id);

    void get_data(int wanted_id);
    void get_all_data();
    Band_strc* fill_first_node();

    int find_id(std::string);
};

