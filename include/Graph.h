#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include "Sommet.h"
#include "Arete.h"

using namespace std;

class Graph
{
    public:
        Graph();
        virtual ~Graph();

        vector<Arete*> Getaretes() { return m_aretes; }
        void Setarretes(vector<Arrete*> val) { m_aretes = val; }

         vector<Sommet*> Getsommets() { return m_sommets; }
        void Setsommets(vector<Sommet*> val) { m_sommets = val; }

    protected:

    private:
        vector<Arete*> m_aretes;
        vector<Sommet*> m_sommets;
};

#endif // GRAPH_H
