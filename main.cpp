#include "grman/grman.h"
#include <iostream>

#include "GraphList.h"
#include "graph.h"

int main()
{


    /// Un exemple de graphe
<<<<<<< HEAD
    GraphList g;
    g.AjouterSommet();
    g.SauvegarderFichier();


=======
    Graph g;
//g.animaux();
////g.niveau1();
//g.niveau2();
bool test = true;
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
          if(test == true)
          {
                test = false;
                  g.niveau2();
          }
          if(test == false)
          {
                g.niveau1();
                test = true;
          }

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();
    return 0;
>>>>>>> ebef66f0849355c30cc139e1543d927bdd53d2cb
}
END_OF_MAIN();


