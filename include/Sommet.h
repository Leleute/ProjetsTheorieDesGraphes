#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>
#include <vector>
using namespace std;

class Sommet
{
      public:
            Sommet();
            Sommet(string nom, float taille);
            virtual ~Sommet();

            string Getnom() { return m_nom; }
            void Setnom(string val) { m_nom = val; }
            int Gettaille() { return m_taille; }
            void Settaille(int val) { m_taille = val; }
            bool Getactif() { return m_actif; }
            void Setactif(bool val) { m_actif = val; }

            vector<int> Getcouleur() { return m_couleur; }
            void Setcouleur(int val) { m_couleur.push_back(val); }

            int Getindice() { return m_indice; }
            void Setindice(int val) { m_indice = val;}

            bool Getmarque() { return m_marque; }
            bool Setmarque(bool val) {m_marque = val;}

      protected:

      private:
            string m_nom;
            int m_taille;
            bool m_actif;
            vector<int> m_couleur;
            int m_indice;

            bool m_marque;
};

#endif // SOMMET_H
