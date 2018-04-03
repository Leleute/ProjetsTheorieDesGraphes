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
    bool valide1 = false;
    bool valide2 = false;
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

            for(int j = 0; j < m_sommets.size(); j++)
            {
                if(s1 == m_sommets[j].Getnom())
                {
                    valide1 = true;
                }
                if(s2 == m_sommets[j].Getnom())
                {
                    valide2 = true;
                }
            }
            if(valide1 == false)
            {
                Sommet s(s1, taille1);
                m_sommets.push_back(s);
            }
            if(valide2 == false)
            {
                Sommet s(s2, taille2);
                m_sommets.push_back(s);
            }
            valide1 = false;
            valide2 = false;

        }
    }
}

Graphe::~Graphe()
{
    //dtor
}
