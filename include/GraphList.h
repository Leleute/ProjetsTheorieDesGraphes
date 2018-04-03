#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include "Graphe.h"



class GraphList
{
    public:

        GraphList();

        virtual ~GraphList();
        vector<Graphe> Getgraphes() { return m_graphes; }
        void Setgraphes(vector<Graphe> val) { m_graphes = val; }
        void AffichageGraphe();
    protected:

    private:
        vector<Graphe> m_graphes;
        vector<string> m_listnoms;

};

#endif // GRAPHLIST_H