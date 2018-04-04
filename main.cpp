#include <iostream>
#include "GraphList.h"

using namespace std;
int main()
{
    GraphList* test = new GraphList;
    test->Setmatriceajd();
    test->Getgraphes()[0].AfficherMatriceAdj();
    test->Setforteconnexite();
    test->Getgraphes()[0].AfficherForteConnexite();

}

 // ok
