#include "GraphList.h"

GraphList::GraphList()
{
    ifstream fp { ("GrapheList.txt")} ; // On essaye d'ouvrir le fichier;
    if(fp) // On teste si tout est OK
    {
        string ligne;
        while(getline(fp,ligne))
        {
            m_listnoms.push_back(ligne);
        }
        for(unsigned int i=0; i<m_listnoms.size(); i++)
        {
            Graph graph(m_listnoms[i]);
            Graph graphSave(m_listnoms[i] + "Save");
            m_graphes.push_back(graph);
            m_graphesSave.push_back(graphSave);
        }
        fp.close();
        string nomgraph;
        bool valide = false;
        while(!valide)
        {
            cout<<"Quel graph voulez vous voir actif en premier ?"<<endl;
            for(unsigned int i = 0; i<m_graphes.size(); i++)
            {
                cout<<m_graphes[i].Getnom()<<endl;
            }
            cin>>nomgraph;
            for(unsigned int i = 0; i<m_graphes.size(); i++)
            {
                if(nomgraph == m_graphes[i].Getnom())
                {
                    m_graphes[i].Setactif(true);
                    valide = true;
                }
                else if(nomgraph != m_graphes[i].Getnom())
                {
                    m_graphes[i].Setactif(false);
                }
            }
        }
    }
    else if(!fp)
    {
        cout<<"Erreur"<<endl;
    }
}


GraphList::~GraphList()
{
    //dtor
}

void GraphList::SupprimerSommet()
{
    string sommetsuppr;
    bool valide = false;
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif() == true )
        {
            while(valide == false)
            {
                cout<<"choisissez le sommet que vous voulez supprimer"<<endl;
                cin>>sommetsuppr;
                for(unsigned int j = 0; j<m_graphes[i].Getsommets().size(); j++)
                {

                    if(sommetsuppr == m_graphes[i].Getsommets()[j].Getnom())
                        valide = true;
                }
            }
            m_graphes[i].SupprimerSommet(sommetsuppr);
            m_graphes[i].Initialisation();
        }
    }

}

void GraphList::AjouterSommet()
{
    bool valide = false;
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif() == true )
        {
            m_graphes[i].AjouterSommet(m_graphesSave[i]);
        }
    }
}


void GraphList::Setmatriceajd()
{
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif() == true) m_graphes[i].Setmatriceadja();
    }
}

void GraphList::Setforteconnexite()
{
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif() == true) m_graphes[i].ForteConnexite();
    }
}

void GraphList::AffichageGraphe()
{
    for(int i=0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif()==true)
        {
        for(int j = 0; j<m_graphes[i].Getsommets().size(); j++)
        {
            cout<<m_graphes[i].Getsommets()[j].Getnom()<<" a une population de "<<m_graphes[i].Getsommets()[j].Gettaille()<<endl;
        }
        cout<<endl;
        }

    }
}

void GraphList::ModifierTaille()
{
    for(int i=0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif()==true)
        {
            m_graphes[i].ModifierTailleSommet();
        }
    }

}

void GraphList::SauvegarderFichier()
{
    ofstream fp {("GrapheList.txt"), ios::out};
    if (fp)
    {
        for(unsigned int i = 0; i<m_graphes.size(); i++)
        {
            fp<<m_graphes[i].Getnom()<<endl;
            m_graphes[i].SauvegarderGraphe();
        }
    }
    else
    {
        cout<<"Erreur"<<endl;
    }

}


void GraphList::croissance()
{
          for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif() == true )
        {
            m_graphes[i].croissance();
        }
    }
}








