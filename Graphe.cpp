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
    ///On met a jour le nombre d'arete et de sommet
    m_nbaretes = m_aretes.size();
    m_ordre = m_sommets.size();
    ///On initialise les indices des sommeet
    for(unsigned int i = 0; i<m_ordre; i++)
    {
        m_sommets[i].Setindice(i);
        m_sommets[i].Setmarque(false);
        m_sommets[i].Setdegre(0);
        m_sommets[i].Setprede(i);

    }
    ///On mets a jour le degré des sommets
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        for(unsigned int j = 0; j<m_aretes.size(); j++)
        {
            if(m_sommets[i].Getnom() == m_aretes[j].Gets1().Getnom() || m_sommets[i].Getnom() == m_aretes[j].Gets2().Getnom())
                m_sommets[i].Setdegre(m_sommets[i].Getdegre() + 1);
        }
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
    ///On mets a jour l'indice des aretes

        for(unsigned int i = 0; i<m_aretes.size(); i++)
        {
            m_aretes[i].Setindice(i);
        }


    this->MapEdge();
    this->MapVertex();
}

Graphe::~Graphe()
{
    //dtor
}

///A revoir
void Graphe::Setmatriceadja()
{
    ///On reinitialise la matrice
    while(m_matriceadja.size() != 0)
    {
        m_matriceadja.pop_back();
    }
    cout<<"ordre : "<<m_ordre<<endl;
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
    vector<Sommet> vecForteConnexite;
    ///On initialise les indices des sommets
    ///On fait la boucle pour les comporantes fortement connexe pour les sommets 1 a 1
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        if(m_sommets[i].Getcouleur().size() == 0)
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
            for(unsigned int j = 0; j<m_ordre; j++)
            {
                if(m_sommets[j].Getmarque() == true)
                {
                    ///On recuperer les sommets de la compo connexe dans le sens positif
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
            for(unsigned int j = 0; j<m_ordre; j++)
            {
                if(m_sommets[j].Getmarque() == true)
                {
                    ///On recuperer les sommets de la compo connexe dans le sens inverse
                    compoconnexeinverse.push_back(m_sommets[j]);
                }
            }

            cout<<endl<<endl;
            ///On regarde les si les points d'intersection entre la composante connexe inverse et celle dans le sens positif
            for(unsigned int j = 0; j<compoconnexe.size(); j++)
            {
                for(unsigned int k = 0; k<compoconnexeinverse.size(); k++)
                {
                    if(compoconnexe[j].Getnom() == compoconnexeinverse[k].Getnom())
                    {
                        m_sommets[compoconnexe[j].Getindice()].Setcouleur(i);
                    }
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

void Graphe::SauvegarderGraphe()
{
    ofstream fp {(m_nom+".txt").c_str(), ios::out};
    if (fp)
    {
        fp<<m_ordre<<endl;
        fp<<m_nbaretes<<endl;
        for(unsigned int i = 0; i<m_nbaretes; i++)
        {
            fp<<m_aretes[i].Gets1().Getnom()<<" "<<m_aretes[i].Gets1().Gettaille()<<" "<<m_aretes[i].Gets2().Getnom()<<" "<<m_aretes[i].Gets2().Gettaille()<<" "<<m_aretes[i].Getpoids()<<endl;
        }
    }
    else
    {
        cout<<"Erreur"<<endl;
    }
}

void Graphe::SupprimerSommet(string sommetsupr)
{
    vector<Arete> newArete;
    vector<Sommet> newSommet;
    ///Pour les sommets
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        ///On ajoute tous les sommets sauf celui a supprimer
        if(sommetsupr != m_sommets[i].Getnom())
            newSommet.push_back(m_sommets[i]);
    }
    ///On met a jour les sommets
    m_sommets = newSommet;

    for(unsigned int i = 0; i<m_aretes.size(); i++)
    {
        if(m_aretes[i].Gets1().Getnom() != sommetsupr && m_aretes[i].Gets2().Getnom() != sommetsupr)
            newArete.push_back(m_aretes[i]);
    }

    m_aretes = newArete;

    ///On reinitiallise le graphe
    Initialisation();
}


void Graphe::SupprimerArete(int aretesuppr)
{
    vector<Arete> newArete;
    ///Pour les sommets
    for(unsigned int i = 0; i<m_aretes.size(); i++)
    {
        ///On ajoute toutes les aretes sauf celui a supprimer
        if(aretesuppr != m_aretes[i].Getindice())
            newArete.push_back(m_aretes[i]);
    }
    ///On met a jour les sommets

    m_aretes = newArete;

    ///On reinitiallise le graphe
    Initialisation();
}


bool Graphe::IsConnexe()
{
    queue<int> file;
    Initialisation();
    ///On ajoute le sommets de debut (il n'a pas d'importance vu qu'on veut juste savoir si le graphe est connexe
    file.push(0);
    ///On le marque
    m_sommets[0].Setmarque(true);
    ///On crée le vecteur qui va recuperer les arretes utilisés
    while(file.size() != 0)
    {
        for(unsigned int j = 0; j<m_aretes.size(); j++)
        {
            ///On recupere les sommets d'arrivée des aretes
            if (m_sommets[file.front()].Getnom() == m_aretes[j].Gets1().Getnom() && m_sommets[m_aretes[j].Gets2().Getindice()].Getmarque() == false)
            {
                ///Si le sommets 2 de l'arete n'est pas marquer, on le marque et on l'ajoute a la file
                file.push(m_aretes[j].Gets2().Getindice());
                ///On le marque
                m_sommets[m_aretes[j].Gets2().Getindice()].Setmarque(true);
            }
            else if( m_sommets[file.front()].Getnom() == m_aretes[j].Gets2().Getnom() && m_sommets[m_aretes[j].Gets1().Getindice()].Getmarque() == false)
            {
                file.push(m_aretes[j].Gets1().Getindice());
                ///On le marque
                m_sommets[m_aretes[j].Gets1().Getindice()].Setmarque(true);
            }
        }
        file.pop();
    }
    int nombreSommetMarque = 0;
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        if (m_sommets[i].Getmarque() == true)
        {
            nombreSommetMarque = nombreSommetMarque + 1;
        }
    }
    if(nombreSommetMarque == m_sommets.size())
    {
        return false;
    }

    if(nombreSommetMarque != m_sommets.size())
    {
        return true;
    }
}

void Graphe::KconnexiteArete()
{
    Initialisation();
    bool cheminValide = true;
    int nombreAreteThisRound;
    int nombreAreteSuppr = m_aretes.size();
    ///On copie le graphe pour pouvoir le modifier sans affecter tout l'affichage, etc ...
    Graphe copie = *this;
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        for(unsigned int j = 0; j<m_sommets.size(); j++)
        {
            //while(cheminValide == true)
            //{
                nombreAreteThisRound = BFSSuppression(i, j);
            //}

        }
    }

}

int Graphe::BFSSuppression(int indice1, int indice2)
{
    Initialisation();
    std::queue<int> file;
    int sommetselec;
    int sommetsuivant;
    ///On demarre le BFS au sommet d'incide 1;
    m_sommets[indice1].Setmarque(true);
    file.push(indice1);
    while(!file.empty())
    {
        sommetselec = file.front();
        file.pop();
        for(unsigned int j=0; j< m_aretes.size(); j++)
        {
            if(m_sommets[sommetselec].Getnom() == m_aretes[j].Gets1().Getnom())
                sommetsuivant = m_aretes[j].Gets2().Getindice();
            if(m_sommets[sommetselec].Getnom() == m_aretes[j].Gets2().Getnom())
                sommetsuivant = m_aretes[j].Gets1().Getindice();
            if(!m_sommets[sommetsuivant].Getmarque())
            {
                m_sommets[sommetsuivant].Setmarque(true);
                file.push(sommetsuivant);
                m_sommets[sommetsuivant].Setprede(sommetselec);
            }
        }
    }
    sommetselec = indice2;
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        cout<<m_sommets[i].Getnom()<<" "<<m_sommets[i].Getindice()<<endl;
    }
    do
    {
        cout<<m_sommets[sommetselec].Getprede()<<endl;
        sommetselec = m_sommets[sommetselec].Getprede();

    }while(sommetselec != 0);
    cout<<endl;
    string mdr;
    cin>>mdr;

}


void Graphe::MapVertex()
{
    m_vertex.clear();
    for(int i = 0; i<m_sommets.size(); i++)
    {
        m_vertex[i] = m_sommets[i];
    }
}

void Graphe::MapEdge()
{
    m_vertex.clear();
    for(int i = 0; i<m_aretes.size(); i++)
    {
        m_edge[i] = m_aretes[i];
    }
}

