#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include <iostream>
#include "Arete.h"
#include "Graphe.h"
#include"fstream"

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
        void SupprimerSommet();

        void MiseEnPlaceMatriceAdj(vector<int> test);

        void Initialisation();

    protected:

    private:
        vector<Sommet> m_sommets;
        vector<Arete> m_aretes;
        int m_ordre;
        int m_nbaretes;
        string m_nom;
        vector<int> m_matriceadja;
        bool m_actif;
};

#endif // GRAPHE_H

