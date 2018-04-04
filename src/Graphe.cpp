#include "Graphe.h"
#include <queue>

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
        for(unsigned int i = 0; i<m_nbaretes; i++)
        {
            fp>>s1;
            fp>>taille1;
            fp>>s2;
            fp>>taille2;
            fp>>poids;

            for(unsigned int j = 0; j < m_sommets.size(); j++)
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

            Arete arete(s1, taille1, s2,taille2, poids) ;
            m_aretes.push_back(arete);
        }
        Initialisation();
    }
}

void Graphe::Initialisation()
{
    ///On initialise les indices des sommeet
    for(unsigned int i = 0; i<m_ordre; i++)
    {
        m_sommets[i].Setindice(i);
        m_sommets[i].Setmarque(false);

    }
    ///On mets les sommets des aretes a egalite de ces derniers
    for(unsigned int i = 0; i<m_aretes.size(); i ++)
    {
        for(unsigned int j = 0; j<m_ordre; j++)
        {
            if(m_aretes[i].Gets1().Getnom() == m_sommets[j].Getnom())
                m_aretes[i].Sets1(&m_sommets[j]);
            if(m_aretes[i].Gets2().Getnom() == m_sommets[j].Getnom())
                m_aretes[i].Sets2(&m_sommets[j]);
        }
    }


}

Graphe::~Graphe()
{
    //dtor
}

///A revoir
void Graphe::Setmatriceadja()
{
    vector<int> sav;
    for(unsigned int i= 0; i<m_ordre*m_ordre; i++)
    {

        m_matriceadja.push_back(0);
    }

    for(unsigned int i = 0; i<m_ordre; i++)
    {
        for(unsigned int j = 0; j<m_ordre; j++)
        {
            for(unsigned int k = 0; k<m_aretes.size(); k++)
            {
                if(m_sommets[i].Getnom() == m_aretes[k].Gets1().Getnom() && m_sommets[j].Getnom() == m_aretes[k].Gets2().Getnom())
                {
                    m_matriceadja[(i + j*m_ordre)] = m_aretes[k].Getpoids();
                }
            }

        }
    }
}


void Graphe::AfficherMatriceAdj()
{
    for(unsigned int i = 0 ; i<m_sommets.size(); i++)
    {
        cout<<m_sommets[i].Getnom()<<endl;
    }
    for(unsigned int i= 0; i<m_ordre; i++)
    {
        for(unsigned int j = 0; j<m_ordre; j++)
        {
            cout<<m_matriceadja[i + j * m_ordre]<<" ";
        }
        cout<<endl;
    }

    for(unsigned int i = 0; i<m_ordre; i++)
    {
        cout<<m_sommets[i].Getnom()<<" "<<m_sommets[i].Getindice()<<endl;
    }
}

void Graphe::ForteConnexite()
{
    queue<int> file;
    ///On initialise les indices des sommets
    ///On fait la boucle pour les comporantes fortement connexe pour les sommets 1 a 1
    for(unsigned int i = 0; i<m_ordre; i++)
    {
        ///Composantes fortement connexte partant de x (via vecteur d'arrete)

        ///On initialise le marquage a faux
        Initialisation();
        ///On ajoute le sommets de debut
        file.push(i);
        ///On le marque
        m_sommets[i].Setmarque(true);
        ///On crée le vecteur qui va recuperer les arretes utilisés
        vector<Sommet> compoconnexe;
        while(file.size() != 0)
        {
            for(unsigned int j = 0; j<m_aretes.size(); j++)
            {
                ///Si le sommets cible et le sommet 1 d'une arete on le meme nom
                if(m_sommets[file.front()].Getnom() == m_aretes[j].Gets1().Getnom() && m_sommets[m_aretes[j].Gets2().Getindice()].Getmarque() == false)
                {
                    ///Si le sommets 2 de l'arete n'est pas marquer, on le marque et on l'ajoute a la file
                    file.push(m_aretes[j].Gets2().Getindice());
                    ///On le marque
                    m_sommets[m_aretes[j].Gets2().Getindice()].Setmarque(true);
                }
            }
            file.pop();
        }
        cout<<m_sommets[i].Getnom()<<endl;
        for(unsigned int j = 0; j<m_ordre; j++)
        {
            if(m_sommets[j].Getmarque() == true)
            {
                ///On recuperer les sommets de la compo connexe dans le sens positif
                cout<<m_sommets[j].Getnom()<<endl;
                compoconnexe.push_back(m_sommets[j]);
            }
        }
        cout<<endl<<endl;

        ///Composantes fortement connexte en sens inverse partant de x (via vecteur d'arrete)

        ///On initialise le marquage a faux
        Initialisation();
        ///On ajoute le sommets de debut
        file.push(i);
        ///On le marque
        m_sommets[i].Setmarque(true);
        ///On crée le vecteur qui va recuperer les arretes utilisés
        vector<Sommet> compoconnexeinverse;
        while(file.size() != 0)
        {
            for(unsigned int j = 0; j<m_aretes.size(); j++)
            {
                ///Si le sommets cible et le sommet 1 d'une arete on le meme nom
                if(m_sommets[file.front()].Getnom() == m_aretes[j].Gets2().Getnom() && m_sommets[m_aretes[j].Gets1().Getindice()].Getmarque() == false)
                {
                    ///Si le sommets 2 de l'arete n'est pas marquer, on le marque et on l'ajoute a la file
                    file.push(m_aretes[j].Gets1().Getindice());
                    ///On le marque
                    m_sommets[m_aretes[j].Gets1().Getindice()].Setmarque(true);
                }
            }
            file.pop();
        }
        cout<<m_sommets[i].Getnom()<<endl;
        for(unsigned int j = 0; j<m_ordre; j++)
        {
            if(m_sommets[j].Getmarque() == true)
            {
                ///On recuperer les sommets de la compo connexe dans le sens positif
                cout<<m_sommets[j].Getnom()<<endl;
                compoconnexeinverse.push_back(m_sommets[j]);
            }
        }

        cout<<endl<<endl;
        for(unsigned int j = 0; j<compoconnexe.size();j++)
        {
            for(unsigned int k = 0; k<compoconnexeinverse.size(); k++)
            {
                if(compoconnexe[j].Getnom()==compoconnexeinverse[k].Getnom())
                {
                    m_sommets[compoconnexe[j].Getindice()].Setcouleur(i);
                }
            }
        }
    }
}

void Graphe::AfficherForteConnexite()
{
    for(unsigned int i = 0; i<m_ordre; i++)
    {
        for(unsigned int j = 0; j<m_sommets[i].Getcouleur().size(); j++)
        {
            cout<<m_sommets[i].Getcouleur()[j]<<endl;
        }
        cout<<endl;
    }
}
