#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include <iostream>
#include "Arete.h"
#include "Graphe.h"
#include"fstream"
//Copie

class Graphe
{
    public:
        Graphe();
        Graphe(string nomfichier);
        virtual ~Graphe();

        vector<Sommet> Getsommets() { return m_sommets; }
        void Setsommets(vector<Sommet> val) { m_sommets = val; }

        vector<Arete> Getaretes() { return m_aretes; }
        void Setarete(vector<Arete> val) { m_aretes = val; }

        string Getnom() { return m_nom; }

        int Getordre() { return m_ordre; }
        void Setordre(int val) { m_ordre = val; }

        int Getnbarete() { return m_nbaretes; }
        void Setnbarete(int val) {m_nbaretes = val;}

    protected:

    private:
        vector<Sommet> m_sommets;
        vector<Arete> m_aretes;
        int m_ordre;
        int m_nbaretes;
        string m_nom;
};

#endif // GRAPHE_H
