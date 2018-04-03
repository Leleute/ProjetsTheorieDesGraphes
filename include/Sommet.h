#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>
#include <vector>
using namespace std;

class Sommet
{
      public:
            Sommet();
            virtual ~Sommet();

            string Getnom() { return m_nom; }
            void Setnom(string val) { m_nom = val; }
            int Gettaille() { return m_taille; }
            void Settaille(int val) { m_taille = val; }
            bool Getactif() { return m_actif; }
            void Setactif(bool val) { m_actif = val; }
            vector<string> Getcouleur() { return m_couleur; }
            void Setcouleur(vector<string> val) { m_couleur = val; }

      protected:

      private:
            string m_nom;
            int m_taille;
            bool m_actif;
            vector<string> m_couleur;
};

#endif // SOMMET_H
