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
    /// Un exemple de graphe
    GraphList g;
    g.Setforteconnexite();
    g.Getgraphes().front().AfficherForteConnexite();
                    std::string nomGraph;
    Graph gr;

//g.animaux();
//g.niveau1();
//g.niveau2();
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
            for(unsigned int i = 0; i<g.Getgraphes().size(); i++)
                    {
                        if(g.Getgraphes()[i].Getactif() == true) std::cout<<g.Getgraphes()[i].Getsommets().size()<<" "<<g.Getgraphes()[i].Getaretes().size()<<endl;
                    }

            std::cout<<"Voici les actions possible : "<<std::endl;
            std::cout<<"1 : Changer de graph actif"<<std::endl;
            std::cout<<"2 : Voir les composantes fortement connexe du graph"<<std::endl;
            std::cout<<"3 : Supprimer un sommet"<<std::endl;
            std::cout<<"4 : Ajouter un sommet"<<std::endl;
            std::cout<<"5 : Voir la K-Sommet-Connexite du graph"<<std::endl;
            std::cout<<"6 : Voir la K-Arete-Connexite du graph"<<std::endl;
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
                    break;

                case 9 :
                    menu = false;
                    break;
                }

        }

        gr.update();
        grman::mettre_a_jour();
    }
    //g.SauvegarderFichier();

    grman::fermer_allegro();
      return 0;
}
END_OF_MAIN();


