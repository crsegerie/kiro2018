#include "graphe.h"

graphe::graphe(string file_path) {
    ifstream file(file_path.c_str(),ios::in);
    if(file) {
        string letter;
        int number;

        //// info //// OK
        for (int i=0; i<6; i++) {
            file>>letter>>info[i]; // Première ligne
        }

        //// cost //// OK
        cost = new int[info[0]*info[2]];    // V*P
        for (int i=0; i<info[0]; i++) {
            file>>letter>>number>>letter>>cost[3*i]>>cost[3*i+1]>>cost[3*i+2];
        }

        //// t //// OK
        t = new arrete[info[0]*info[0]];    // V*V
        for (int i=0; i<info[0]; i++) {
            for (int j=0; j<info[0]; j++) {
                t[i+info[0]*j].correspondance = false;
                t[i+info[0]*j].maintenance = false;
                t[i+info[0]*j].temps = 0;
            }
        }
        for (int i=0; i<info[1]; i++) {
            file>>letter>>number>>letter;
            int o, d;   // o to d
            file>>o>>letter>>d>>letter;
            t[(o-1)+(d-1)*info[0]].correspondance = true;
            file>>t[(o-1)+(d-1)*info[0]].maintenance>>letter>>t[(o-1)+(d-1)*info[0]].temps;
        }
        file.close();

        /*while(getline(file, line))  // Lit toutes les lignes de file
            cout<<line<<endl;
        char character;
        file.get(character);    // Stocke le prochain caractere dans character
        int number;
        file >> number; // Stocke le prochain mot dans number
        file.clear();   // Revient au début du fichier*/
    }
    else
        cout<<"Error while loading file to read"<<endl;

    //// delta_plus ////
    tab_delta_plus = new vector<int>[info[0]];
    for (int i=0; i<info[0]; i++){
        for (int j=0; j<info[0]; j++){
            if (t[i+info[0]*j].correspondance == true){
                tab_delta_plus[i].push_back(j);
            }
        }
        /*int k = 0;
        while (k < tab_delta_plus[i].size()){
            cout<<tab_delta_plus[i][k]<<" ";
            k += 1;
        }
        cout<<endl;*/
    }
}
graphe::~graphe() {
    delete[] t;
    delete[] tab_delta_plus;
}
