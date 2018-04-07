#include "grman/grman.h"
#include <iostream>

#include "GraphList.h"
#include "graph.h"

int main()
{
///
    grman::init();
    grman::set_pictures_path("pics");


    /// Un exemple de graphe
    GraphList g;
    g.Setforteconnexite();
    g.Getgraphes().front().AfficherForteConnexite();

        Graph gr;
//g.animaux();
////g.niveau1();
//g.niveau2();
bool test = true;

    while ( !key[KEY_ESC] )
    {
          if(test == true)
          {
                test = false;
                  gr.niveau2();
          }
          if(test == false)
          {
                gr.niveau1();
                test = true;
          }
        gr.update();
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();
      return 0;
}
END_OF_MAIN();


