#include "Graphe.h"

Graphe::Graphe()
{
    ///Ouverture du fichier recapitulant le nom de l'ensemble des fichier
}

Graphe::Graphe(string nomfichier)
{
    ifstream fp { (nomfichier+".txt").c_str() };
        string s1, s2;
        float poids, taille1, taille2;

        if(fp)
        {
            m_nom = nomfichier;
            fp>>m_ordre;
            fp>>m_nbaretes;
            for(int i = 0; i<m_nbaretes; i++)
            {
                fp>>s1;
                fp>>taille1;
                fp>>s2;
                fp>>taille2;
                fp>>poids;
                Arete arete(s1, taille1, s2,taille2, poids) ;
                m_aretes.push_back(arete);
            }
        }
}

Graphe::~Graphe()
{
    //dtor
}
