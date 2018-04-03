#include "Sommet.h"

Sommet::Sommet()
{
      //ctor
}

Sommet::Sommet(string nom, float taille)
{
    m_nom = nom;
    m_actif = true;
    m_taille = taille;
}

Sommet::~Sommet()
{
      //dtor
}
