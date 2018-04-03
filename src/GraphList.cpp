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
    }
    else if(!fp)
    {
    }
}


GraphList::~GraphList()
{
    //dtor
}

void GraphList::AffichageGraphe()
{
    for(int i=0;i<m_listnoms.size();i++)
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
    }
}


