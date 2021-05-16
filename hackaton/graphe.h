#pragma once
#include <iostream>
#include <cmath>
#include "traitement_fichier.h"
#include "vector"
using namespace std;
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;
struct arrete{
    bool correspondance;
    bool maintenance;
    int temps;
};
class graphe
{
public:
    int info[6];
    int* cost;
    arrete* t;
    vector<int>* tab_delta_plus;
    graphe(string file_path);
    ~graphe();
};
