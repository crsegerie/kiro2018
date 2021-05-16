#include "traitement_fichier.h"
#include "graphe.h"

void write_solution(string file_path, const graphe& G, vector<int>* historique_avion) {
    ofstream file(file_path.c_str(),ios::out);
    if(file) {
        for (int i=0; i<G.info[2]; i++) {
            file<<"p "<<i+1<<" v";
            for (int j=0; j<historique_avion[i].size(); j++) {
                file<<" "<<historique_avion[i][j]+1;
            }
            file<<endl;
        }
        file.close();
    }
    else
        cout<<"Error while loading file to write"<<endl;
}

int prix(vector<int>* historique_avion,const graphe&G,int &prix){
    int c=0;
    int* nombre_de_passage = new int[G.info[0]];
    for (int p=0;p<G.info[2];p++){
        for (int j=0;j<historique_avion[p].size();j++){
            c+=G.cost[historique_avion[p][j] + G.info[2]*p];
            nombre_de_passage[historique_avion[p][j]]+=1;
        }
    }
    for (int v=0;v<G.info[0];v++){
        c+=G.info[5]*abs(nombre_de_passage[v]-1);
    }
    int couttot=0;
    for (int p=0;p<G.info[2];p++){
        for (int i=0;i<historique_avion[p].size()-1;i++){

            if (G.t[historique_avion[p][i]+G.info[0]*historique_avion[p][i+1]].maintenance==false){
                int indi=i;
                int coutprov=G.t[historique_avion[p][i]+(G.info[0]*historique_avion[p][i+1])].temps;
                while ((G.t[historique_avion[p][indi]+G.info[0]*historique_avion[p][indi]].maintenance==false) && (indi<historique_avion[p].size()-1)){
                    indi+=1;
                    coutprov+=G.t[historique_avion[p][indi]+(G.info[0]*historique_avion[p][indi+1])].temps;
                    if (coutprov>5){
                        couttot+=1;
                }
                }
            }
        }
    }

    return c+(G.info[5]*couttot);
}

void une_solution(vector<int>* historique_avion,const graphe & G){
    int V=G.info[0];
    int A=G.info[1];
    int P=G.info[2];
    int B=G.info[3];
    int K=G.info[4];
    bool deja_traites[V];
    for (int i=0;i<V;i++){
        deja_traites[i]=false;
    }
    int avion=0;
    for (avion=0;avion<P;avion++){
        int v=0;
        while (v<V && ((G.tab_delta_plus[v].size() == 0) || (deja_traites[v] == true))){
            v++;
        }
        vector<int> Les_indices;
        for(int indic=0; indic<G.tab_delta_plus[v].size();indic++){
            if ((deja_traites[G.tab_delta_plus[v][indic]]==true)){
            Les_indices.push_back(indic);
            }
        }
        int indice = 0;
        if (Les_indices.size()!=0) {
            int k=rand()%Les_indices.size();
            int indice=k;
        }
        int v_suivant=G.tab_delta_plus[v][indice];
        deja_traites[v]=true;
        deja_traites[v_suivant]=true;
        historique_avion[avion].push_back(v);
        historique_avion[avion].push_back(v_suivant);
        bool cont=true;
        indice=0;
        while(cont){
            cont = false;
            v = v_suivant;
            vector<int> Les_indices;
            for(int indic=0; indic<G.tab_delta_plus[v].size();indic++){
                if ((deja_traites[G.tab_delta_plus[v][indic]]==true)){
                Les_indices.push_back(indic);
                }
            }
            int indice = 0;
            if (Les_indices.size()!=0) {
                int k=rand()%Les_indices.size();
                int indice=k;
            }
            if (G.tab_delta_plus[v].size()!=0 && deja_traites[G.tab_delta_plus[v][indice]]==false){
                cont=true;
                v_suivant=G.tab_delta_plus[v][indice];
                deja_traites[v_suivant]=true;
                historique_avion[avion].push_back(v_suivant);
            }
        }
    }
}
int main() {
    srand((unsigned int)time(0));   // Initialisation aleatoire
    graphe G("../instances/instance_exemple.in");
    vector<int>* historique_avion=new vector<int>[G.info[2]];
    vector<int>* historique_avion_best=new vector<int>[G.info[2]];
    int best_prix=-1;
    for (int i=0;i<1000;i++){
        une_solution(historique_avion, G);
        int a;
        prix(historique_avion,G,a);
        if((best_prix=-1)||(a<best_prix)){
            best_prix=a;
            for(int j=0;j<G.info[2];j++){
                historique_avion_best[j]=historique_avion[j];
            }
        }
    }

    write_solution("../solutions/solution_exemple_2.in", G, historique_avion);
    return 0;
}
