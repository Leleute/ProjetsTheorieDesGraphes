#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include "Graphe.h"
#include "graph.h"


class GraphList
{
public:

    GraphList();

    virtual ~GraphList();
    vector<Graph> Getgraphes()
    {
        return m_graphes;
    }
    void Setgraphes(vector<Graph> val)
    {
        m_graphes = val;
    }
    void AffichageGraphe();
    void Setmatriceajd();
    void Setforteconnexite();
    void SauvegarderFichier();
    void SupprimerSommet();
protected:

private:
    vector<Graph> m_graphes;
    vector<string> m_listnoms;

};

#endif // GRAPHLIST_H

