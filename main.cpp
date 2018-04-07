#include "grman/grman.h"
#include <iostream>

#include "GraphList.h"
#include "graph.h"

int main()
{

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
//g.animaux();
////g.niveau1();
//g.niveau2();
bool test = true;
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
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

        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();
    return 0;
}
END_OF_MAIN();


