#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include <iostream>
#include "Arete.h"
#include "Graphe.h"
#include"fstream"
#include <map>

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

        bool Getactif() { return m_actif; }
        void Setactif(bool val) { m_actif = val;}

        string Getnom() { return m_nom; }

        int Getordre() { return m_ordre; }
        void Setordre(int val) { m_ordre = val; }

        int Getnbarete() { return m_nbaretes; }
        void Setnbarete(int val) {m_nbaretes = val;}

        vector<int> Getmatriceadja() { return m_matriceadja; }
        void Setmatriceadja();
        void AfficherMatriceAdj();
        void ForteConnexite();
        void AfficherForteConnexite();

        void SauvegarderGraphe();
        void SupprimerSommet(string sommet);
        void SupprimerArete(int arete);
        int BFSSuppression(int indice1, int indice2);

        bool IsConnexe();

        void MiseEnPlaceMatriceAdj(vector<int> test);

        void Initialisation();
        void KconnexiteArete();

        void MapVertex();
        void MapEdge();

    protected:

    private:
        map<int , Arete> m_edge;
        map<int, Sommet> m_vertex;
        vector<Sommet> m_sommets;
        vector<Arete> m_aretes;
        int m_ordre;
        int m_nbaretes;
        string m_nom;
        vector<int> m_matriceadja;
        bool m_actif;
};

#endif // GRAPHE_H

