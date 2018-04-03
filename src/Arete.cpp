#include "Arete.h"

Arete::Arete()
{
      //ctor
}

Arete::Arete(string s1, float taille1, string s2, float taille2, float val)
{
    Sommet sommet1(s1,taille1);
    Sommet sommet2(s2,taille2);
    m_s1 = sommet1;
    m_s2 = sommet2;
    m_poids = val;
}

Arete::~Arete()
{
      //dtor
}
