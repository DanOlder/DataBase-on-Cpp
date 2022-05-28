#include "BigHeader.hpp"

Database::Database(){

    album_created = false;
    band_created = false;
    concert_created = false;
    member_created = false;
    place_created = false;
    recordlabel_created = false;
    song_created = false;
}

void Database::addInfo(int table_num){

    //user selects a table to add info to it

    switch (table_num)
    {
        case A: {//album
          
            AddInfoTemplate<Album_strc, FormFillA>
                (&album_created, band_created, "You need to create a band first", &album);
            break;
        }
        case B: {//band

            AddInfoTemplate<Band_strc, FormFillB>
                (&band_created, recordlabel_created, "You need to create a label first", &band);
            break;
        }
        case C: {//concert

            AddInfoTemplate<Concert_strc, FormFillC>
                (&concert_created, (band_created && place_created), "You need to create a band and a place first", &concert);
            break;
        }
        case M: {//member

            AddInfoTemplate<Member_strc, FormFillM>
                (&member_created, (band_created && place_created), "You need to create a band and a place first", &member);
            break;
        }
        case P: {//place

            AddInfoTemplate<Place_strc, FormFillP>
                (&place_created, 1, " ", &place);
            break;
        }
        case R: {//recordlabel

            AddInfoTemplate<RecordLabel_strc, FormFillR>
                (&recordlabel_created, 1, " ", &recordlabel);
            break;
        }
        case S: {//song

            AddInfoTemplate<Song_strc, FormFillS>
                (&song_created, album_created, "You need to create an album first", &song);
            break;
        }
    }
}

void Database::saveInFile()
{
    //queue:
    //recordlabel -> place -> band -> album -> song -> member -> concert

    std::ofstream fout("txts/db.txt");
    std::string delimiter = "--";

    if (recordlabel_created) {
        fout << "R\n";

        RecordLabel* temp;
        for (temp = &(this->recordlabel); temp != NULL; temp = temp->next) {
            RecordLabel_strc* data = &(temp->data);

            fout << data->name;
            fout << delimiter;
            fout << data->year_of_found;
            fout << "\n";
        }
        fout << "\n";
    }
    if (place_created) {
        fout << "P\n";

        Place* temp;
        for (temp = &(this->place); temp != NULL; temp = temp->next) {
            Place_strc* data = &(temp->data);

            fout << data->country;
            fout << delimiter;
            fout << data->region;
            fout << delimiter;
            fout << data->name;
            fout << "\n";
        }
        fout << "\n";
    }
    if (band_created) {
        fout << "B\n";

        Band* temp;
        for (temp = &(this->band); temp != NULL; temp = temp->next) {
            Band_strc* data = &(temp->data);

            fout << data->recordLabel_id;
            fout << delimiter;
            fout << data->name;
            fout << delimiter;
            fout << data->year_of_forming;
            fout << "\n";
        }
        fout << "\n";
    }
    if (album_created) {
        fout << "A\n";

        Album* temp;
        for (temp = &(this->album); temp != NULL; temp = temp->next) {
            Album_strc* data = &(temp->data);

            fout << data->band_id;
            fout << delimiter;
            fout << data->name;
            fout << delimiter;
            fout << data->release_year;
            fout << delimiter;
            fout << data->number_of_songs;
            fout << "\n";
        }
        fout << "\n";
    }
    if (song_created) {
        fout << "S\n";

        Song* temp;
        for (temp = &(this->song); temp != NULL; temp = temp->next) {
            Song_strc* data = &(temp->data);

            fout << data->album_id;
            fout << delimiter;
            fout << data->name;
            fout << delimiter;
            fout << data->genre;
            fout << delimiter;
            fout << data->is_single;
            fout << "\n";
        }
        fout << "\n";
    }
    if (member_created) {
        fout << "M\n";

        Member* temp;
        for (temp = &(this->member); temp != NULL; temp = temp->next) {
            Member_strc* data = &(temp->data);

            fout << data->band_id;
            fout << delimiter;
            fout << data->place_id;
            fout << delimiter;
            fout << data->birth_date;
            fout << delimiter;
            fout << data->name;
            fout << delimiter;
            fout << data->lastname;
            fout << delimiter;
            fout << data->is_frontman;
            fout << "\n";
        }
        fout << "\n";
    }
    if (concert_created) {
        fout << "C\n";

        Concert* temp;
        for (temp = &(this->concert); temp != NULL; temp = temp->next) {
            Concert_strc* data = &(temp->data);

            fout << data->band_id;
            fout << delimiter;
            fout << data->place_id;
            fout << delimiter;
            fout << data->concert_date;
            fout << "\n";
        }
        fout << "\n";
    }

    fout.close();
}

void Database::loadFromFile()
{
    //recordlabel -> place -> band -> album -> song -> member -> concert

    char switchVar;

    std::ifstream fin("txts/db.txt");
    std::string str;
    std::string delimiter = "--";

    while (getline(fin, str)) {

        if (str.length() == 1) {
            char tempChar = str[0];
            switch (tempChar)
            {
                case 'R': {
                    switchVar = 'R';
                    break;
                }
                case 'P': {
                    switchVar = 'P';
                    break;
                }
                case 'B': {
                    switchVar = 'B';
                    break;
                }
                case 'A': {
                    switchVar = 'A';
                    break;
                }
                case 'S': {
                    switchVar = 'S';
                    break;
                }
                case 'M': {
                    switchVar = 'M';
                    break;
                }
                case 'C': {
                    switchVar = 'C';
                    break;
                }
            }
        }
        else {
            if (str.length() == 0) continue;
            switch (switchVar)
            {
                case 'R': {
                    RecordLabel_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (recordlabel_created) {
                        data = recordlabel.add_node();


                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());
                        
                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->year_of_found = stoi(token);
                        str.erase(0, pos + delimiter.length());


                    }
                    else {
                        data = recordlabel.fill_first_node();
                        if (data == NULL) return;

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->year_of_found = stoi(token);
                        str.erase(0, pos + delimiter.length());


                        recordlabel_created = true;
                    }
                    break;
                }
                case 'P': {
                    Place_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (place_created) {
                        data = place.add_node();

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->country = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->region = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());

                    }
                    else {
                        data = place.fill_first_node();
                        if (data == NULL) return;


                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->country = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->region = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());


                        place_created = true;
                    }
                    break;
                }
                case 'B': {
                    Band_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (band_created) {

                        data = band.add_node();


                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->recordLabel_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->year_of_forming = stoi(token);
                        str.erase(0, pos + delimiter.length());

                    }
                    else {
                        if (recordlabel_created) {
                            data = band.fill_first_node();
                            if (data == NULL) return;


                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->recordLabel_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->name = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->year_of_forming = stoi(token);
                            str.erase(0, pos + delimiter.length());


                            band_created = true;
                        }
                        else {
                            MessageBox::Show("You need to create a label first", "Error");
                            return;
                        }
                    }
                    break;
                }
                case 'A': {
                    Album_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (album_created) {

                        data = album.add_node();


                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->band_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->release_year = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->number_of_songs = stoi(token);
                        str.erase(0, pos + delimiter.length());


                    }
                    else {
                        if (band_created) {

                            data = album.fill_first_node();
                            if (data == NULL) return;


                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->band_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->name = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->release_year = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->number_of_songs = stoi(token);
                            str.erase(0, pos + delimiter.length());


                            album_created = true;
                        }
                        else {
                            MessageBox::Show("You need to create a band first", "Error");
                        }
                    }
                    break;
                }
                case 'S': {
                    Song_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (song_created) {

                        data = song.add_node();


                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->album_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->genre = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->is_single = token;
                        str.erase(0, pos + delimiter.length());

                    }
                    else {
                        if (album_created) {
                            data = song.fill_first_node();
                            if (data == NULL) return;


                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->album_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->name = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->genre = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->is_single = token;
                            str.erase(0, pos + delimiter.length());


                            song_created = true;
                        }
                        else {
                            MessageBox::Show("You need to create an album first", "Error");
                        }
                    }
                    break;
                }
                case 'M': {
                    Member_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (member_created) {

                        data = member.add_node();

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->band_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->place_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->birth_date = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->name = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->lastname = token;
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->is_frontman = token;
                        str.erase(0, pos + delimiter.length());

                    }
                    else {
                        if (band_created && place_created) {
                            data = member.fill_first_node();
                            if (data == NULL) return;

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->band_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->place_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->birth_date = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->name = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->lastname = token;
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->is_frontman = token;
                            str.erase(0, pos + delimiter.length());

                            member_created = true;
                        }
                        else {
                            MessageBox::Show("You need to create a band and a place first", "Error");
                        }
                    }
                    break;
                }
                case 'C': {
                    Concert_strc* data;
                    std::string token;
                    size_t pos = 0;

                    if (concert_created) {

                        data = concert.add_node();

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->band_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->place_id = stoi(token);
                        str.erase(0, pos + delimiter.length());

                        pos = str.find(delimiter);
                        token = str.substr(0, pos);
                        data->concert_date = token;
                        str.erase(0, pos + delimiter.length());

                    }
                    else {
                        if (band_created && place_created) {
                            data = concert.fill_first_node();
                            if (data == NULL) return;

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->band_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->place_id = stoi(token);
                            str.erase(0, pos + delimiter.length());

                            pos = str.find(delimiter);
                            token = str.substr(0, pos);
                            data->concert_date = token;
                            str.erase(0, pos + delimiter.length());

                            concert_created = true;
                        }
                        else {
                            MessageBox::Show("You need to create a band and a place first", "Error");
                        }
                    }
                    break;
                }
            }
        }

    }

    fin.close();
}
