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
            //Graphe* graph = new Graphe(m_listnoms[i]);
            Graphe graph(m_listnoms[i]);
            m_graphes.push_back(graph);
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
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        if(m_graphes[i].Getactif() == true )
        {
            m_graphes[i].SupprimerSommet();
        }
    }
}

void GraphList::Setmatriceajd()
{
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        m_graphes[i].Setmatriceadja();
    }
}

void GraphList::Setforteconnexite()
{
    for(unsigned int i = 0; i<m_graphes.size(); i++)
    {
        m_graphes[i].ForteConnexite();
    }
}

void GraphList::AffichageGraphe()
{
    for(int i=0; i<m_listnoms.size(); i++)
    {
        cout<<"Graphe numero "<<i+1<<endl;
        cout<<this->Getgraphes()[i].Getnom()<<endl;
        for(int j = 0; j<m_graphes[i].Getaretes().size(); j++)
        {
            cout<<m_graphes[i].Getaretes()[j].Gets1().Getnom()<<endl;
            cout<<m_graphes[i].Getaretes()[j].Gets1().Gettaille()<<endl;

            cout<<m_graphes[i].Getaretes()[j].Gets2().Getnom()<<endl;
            cout<<m_graphes[i].Getaretes()[j].Gets2().Gettaille()<<endl;
            cout<<m_graphes[i].Getaretes()[j].Getpoids()<<endl;
            cout<<endl;
        }
        cout<<m_graphes[i].Getsommets().size()<<endl<<endl;
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


