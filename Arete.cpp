#include "Arete.h"

Arete::Arete()
{
      //ctor
}

Arete::Arete(string s1, float taille1, string s2, float taille2, float val)
{
    Sommet sommet1(s1,taille1);
    Sommet sommet2(s2, taille2);
    m_s1 = sommet1;
    m_s2 = sommet2;
    m_poids = val;
}

Arete::~Arete()
{
      //dtor
}
/*
void Arete::Sets1(Sommet* val)
{
    m_s1.Setnom(val->Getnom());
    m_s1.Setmarque(val->Getmarque());
    m_s1.Setindice(val->Getindice());
}

void Arete::Sets2(Sommet* val)
{
    m_s2.Setnom(val->Getnom());
    m_s2.Setmarque(val->Getmarque());
    m_s2.Setindice(val->Getindice());
}*/

