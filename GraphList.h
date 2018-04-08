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
    vector<Graph> GetgraphesSave()
    {
        return m_graphesSave;
    }
    void SetgraphesSave(vector<Graph> val)
    {
        m_graphesSave = val;
    }
    void AffichageGraphe();
    void Setmatriceajd();
    void Setforteconnexite();
    void SauvegarderFichier();
    void SupprimerSommet();
    void AjouterSommet();
    void SetGrapheActif(int i){ m_graphes[i].Setactif(true); }
    void SetGrapheNonActif(int i){ m_graphes[i].Setactif(false); }
    void ModifierTaille();

        void croissance();
protected:

private:
    vector<Graph> m_graphes;
    vector<Graph> m_graphesSave;
    vector<string> m_listnoms;

};

#endif // GRAPHLIST_H

