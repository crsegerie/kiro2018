#include "traitement_fichier.h"

void read_file(string file_path) {
    ifstream file(file_path.c_str(),ios::in);
    if(file) {
        string line;
        while(getline(file, line))  // Lit toutes les lignes de file
            cout<<line<<endl;
        /*char character;
        file.get(character);    // Stocke le prochain caractere dans character
        int number;
        file >> number; // Stocke le prochain mot dans number
        file.clear();   // Revient au début du fichier*/
        file.close();
    }
    else
        cout<<"Error while loading file to read"<<endl;
}

void write_in_file(string file_path) {
    ofstream file(file_path.c_str(),ios::out);
    if(file) {

        file<<"Hello world"<<endl;
        file.close();
    }
    else
        cout<<"Error while loading file to write"<<endl;
}
