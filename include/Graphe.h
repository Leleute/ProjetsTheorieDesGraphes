#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include <iostream>
#include "Arete.h"
#include "Graphe.h"



class Graphe
{
    public:
        Graphe();
        virtual ~Graphe();

        vector<Sommet*> Getsommets() { return m_sommets; }
        void Setsommets(vector<Sommet*> val) { m_sommets = val; }

        vector<Arete*> Getaretes() { return m_aretes; }
        void Setarete(vector<Arete*> val) { m_aretes = val; }

    protected:

    private:
        vector<Sommet*> m_sommets;
        vector<Arete*> m_aretes;
};

#endif // GRAPHE_H
