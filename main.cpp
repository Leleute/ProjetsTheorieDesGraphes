#include "grman/grman.h"
#include <iostream>

#include "GraphList.h"
#include "graph.h"

int main()
{
///
    grman::init();
    grman::set_pictures_path("pics");

bool reussite;
int cpt = 0;
    /// Un exemple de graphe
    GraphList g;
    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
    {
        if(g.Getgraphes()[i].Getactif()== true)
        {
        for(unsigned int j = 0; j<g.Getgraphes()[i].Getsommets().size(); j++)
        {
            cout<<g.Getgraphes()[i].Getsommets()[j].Getnom()<<" "<<g.Getgraphes()[i].Getsommets()[j].Gettaille()<<" "<<g.Getgraphes()[i].Getsommets()[j].getRythme()<<endl;
        }
        cout<<endl;

        for(unsigned int j = 0; j<g.Getgraphes()[i].Getaretes().size(); j++)
        {
            cout<<g.Getgraphes()[i].Getaretes()[j].Gets1().Getnom()<<" "<<g.Getgraphes()[i].Getaretes()[j].Gets1().Gettaille()<<" "<<g.Getgraphes()[i].Getaretes()[j].Gets1().getRythme()<<endl;
            cout<<g.Getgraphes()[i].Getaretes()[j].Gets2().Getnom()<<" "<<g.Getgraphes()[i].Getaretes()[j].Gets2().Gettaille()<<" "<<g.Getgraphes()[i].Getaretes()[j].Gets2().getRythme()<<endl;
            cout<<g.Getgraphes()[i].Getaretes()[j].Getpoids()<<endl;
        }
        }
    }
    std::string nomGraph;
    Graph gr;
bool menu = false;
int menuChoix = 10;
bool lancementboucle = true;

    while ( !key[KEY_ESC] )
    {

        if(lancementboucle == true)
        {
            if(g.Getgraphes()[0].Getactif() == true) gr.animaux();
            if(g.Getgraphes()[1].Getactif() == true) gr.niveau1();
            if(g.Getgraphes()[2].Getactif() == true) gr.niveau2();
            lancementboucle = false;
        }
        if(key[KEY_P])
        {
            menu = true;
        }
        while(menu == true)
        {

            std::cout<<"Voici les actions possibles : "<<std::endl;
            std::cout<<"1 : Changer de graphe actif"<<std::endl;
            std::cout<<"2 : Voir les composantes fortement connexes du graphe"<<std::endl;
            std::cout<<"3 : Supprimer un sommet"<<std::endl;
            std::cout<<"4 : Ajouter un sommet"<<std::endl;
            std::cout<<"5 : Voir la K-Sommet-Connexite du graphe"<<std::endl;
            std::cout<<"6 : Voir la K-Arete-Connexite du graphe"<<std::endl;
            std::cout<<"7 : Voir la Matrice d'adjacence"<<std::endl;
            std::cout<<"8 : Modifier la population d'un sommet"<<std::endl;
            std::cout<<"9 : Revenir au defilement Temporel"<<std::endl;
            std::cin>>menuChoix;
                switch(menuChoix)
                {
                case 1 :
                    reussite = false;
                    while(reussite == false)
                    {
                    std::cout<<"Quel graph voulez vous voir actif"<<std::endl;
                    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        std::cout<<g.Getgraphes()[i].Getnom()<<std::endl;
                    }
                    cin>>nomGraph;
                    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        if(nomGraph == g.Getgraphes()[i].Getnom())
                        {
                            reussite = true,
                                g.SetGrapheActif(i);
                        }
                        if(nomGraph != g.Getgraphes()[i].Getnom()) g.SetGrapheNonActif(i);
                    }
                    }


                    if(g.Getgraphes()[0].Getactif() == true) gr.animaux();
                    if(g.Getgraphes()[1].Getactif() == true) gr.niveau1();
                    if(g.Getgraphes()[2].Getactif() == true) gr.niveau2();
                    menu = false;
                    break;

                case 2 :
                    g.Setforteconnexite();
                    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        if(g.Getgraphes()[i].Getactif() == true) g.Getgraphes()[i].AfficherForteConnexite();
                    }
                    break;

                case 3 :
                    g.SupprimerSommet();
                    break;

                case 4 :
                    g.AjouterSommet();
                    break;

                case 5 :
                    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        if(g.Getgraphes()[i].Getactif() == true)
                        {
                            g.Getgraphes()[i].KconnexiteSommet();
                        }
                    }
                    break;

                case 6 :
                    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        if(g.Getgraphes()[i].Getactif() == true) g.Getgraphes()[i].KconnexiteArete();
                    }
                    break;

                case 7 :
                    g.Setmatriceajd();
                    for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        if(g.Getgraphes()[i].Getactif() == true) g.Getgraphes()[i].AfficherMatriceAdj();
                    }
                    break;

                case 8 :
                    g.ModifierTaille();
                    g.AffichageGraphe();
                    break;

                case 9 :
                    menu = false;
                    break;
                }

        }

         if(cpt >= 100)
        {

              cpt=0;
            g.croissance();
            g.AffichageGraphe();

        }
        gr.update();
        grman::mettre_a_jour();

        cpt++;
    }
    g.SauvegarderFichier();

    grman::fermer_allegro();
      return 0;
}
END_OF_MAIN();


