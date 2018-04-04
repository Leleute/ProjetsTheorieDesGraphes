#include <iostream>
#include "GraphList.h"

using namespace std;
int main()
{
    GraphList* test = new GraphList;
    test->Setmatriceajd();
    test->Getgraphes().front().AfficherMatriceAdj();
    test->SupprimerSommet();
    test->Setmatriceajd();
    test->Getgraphes().front().AfficherMatriceAdj();
    test->SauvegarderFichier();
}

 // ok
