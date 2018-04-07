#include "graph.h"
#include <queue>
#include "fstream"
#include <algorithm>
/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration.:
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );

    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}

void Vertex::croissance()
{
    if(m_taille > 0)
    {
        m_taille += m_rythme*m_taille*(1- m_taille/m_K);
        ///reste à soustraire tous les K
    }
    else if(m_taille <= 0)
    {
        m_taille = 0;
    }
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box); ///Point de départ
    m_top_edge.attach_to(to.m_interface->m_top_box);              ///Point d'arrivée
    m_top_edge.reset_arrow_with_bullet();                                           ///la fleche et le point de l'arete

    // Une boite pour englober les widgets de réglage associés
    ///Toute la boîte
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    ///=bouton poussoir des box edge
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    ///= le nombre de représentants de l'espece
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider

    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs

    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}
void Graph::animaux()
{
    m_vertices.clear();
    m_edges.clear();
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    add_interfaced_vertex(0,1.0f, 150,150,"algue.bmp");
    add_interfaced_vertex(1,1.0f, 150,400,"herbeMarine.bmp");
    add_interfaced_vertex(2,1.0f, 350,50,"crevette.bmp");
    add_interfaced_vertex(3,1.0f, 350,200,"carpe.bmp");
    add_interfaced_vertex(4,1.0f, 350,350,"mouche.bmp");
    add_interfaced_vertex(5,1.0f, 350,480,"limace.bmp");
    add_interfaced_vertex(6,1.0f, 550,50,"truite.bmp");
    add_interfaced_vertex(7,1.0f, 550,300,"libellule.bmp");
    add_interfaced_vertex(8,1.0f, 550,480,"tortue.bmp");
    add_interfaced_vertex(9,1.0f, 750,50,"martinPecheur.bmp");
    add_interfaced_vertex(10,1.0f, 750,300,"grenouille.bmp");
    add_interfaced_vertex(11,1.0f, 750,480,"serpent.bmp");

    add_interfaced_edge(0, 0, 2, 1);
    add_interfaced_edge(1, 0, 3, 1);
    add_interfaced_edge(2, 0, 5, 1);
    add_interfaced_edge(3, 1, 2, 1);
    add_interfaced_edge(4, 1, 3, 1);
    add_interfaced_edge(5, 1, 4, 1);
    add_interfaced_edge(6, 1, 5, 1);
    add_interfaced_edge(7, 1, 8, 1);
    add_interfaced_edge(8, 2, 6, 1);
    add_interfaced_edge(9, 3, 6, 1);
    add_interfaced_edge(10, 3, 9, 1);
    add_interfaced_edge(11, 6, 9, 1);
    add_interfaced_edge(12, 4, 7, 1);
    add_interfaced_edge(13, 4, 8, 1);
    add_interfaced_edge(14, 4, 10, 1);
    add_interfaced_edge(15, 5, 8, 1);
    add_interfaced_edge(16, 7, 10, 1);
    add_interfaced_edge(17, 10, 9, 1);
    add_interfaced_edge(18, 10, 11, 1);

}

void Graph::niveau1()
{
    m_vertices.clear();
    m_edges.clear();
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    add_interfaced_vertex(0,1.0f, 150,400,"boeuf.bmp");
    add_interfaced_vertex(1,1.0f, 500,400,"graines.bmp");
    add_interfaced_vertex(2,1.0f, 300,200,"homme.bmp");
    add_interfaced_vertex(3,1.0f, 450,100,"mouton.bmp");
    add_interfaced_vertex(4,1.0f, 700,100,"herbe.bmp");

    add_interfaced_edge(0, 0, 2, 1);
    add_interfaced_edge(1, 1, 0, 1);
    add_interfaced_edge(2, 2, 1, 1);
    add_interfaced_edge(3, 3, 2, 1);
    add_interfaced_edge(4, 4, 3, 1);
}
void Graph::niveau2()
{
    m_vertices.clear();
    m_edges.clear();
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    add_interfaced_vertex(0,1.0f, 150,100,"cachalot.bmp");
    add_interfaced_vertex(1,1.0f, 500,70,"calamar.bmp");
    add_interfaced_vertex(2,1.0f, 600,300,"ecrevisse.bmp");
    add_interfaced_vertex(3,1.0f, 400,420,"zooplancton.bmp");
    add_interfaced_vertex(4,1.0f, 680,480,"phytoplancton.bmp");
    add_interfaced_vertex(5,1.0f, 150,300,"thon.bmp");

    add_interfaced_edge(0, 1, 0, 1);
    add_interfaced_edge(1, 5, 0, 1);
    add_interfaced_edge(2, 5, 2, 1);
    add_interfaced_edge(3, 3, 2, 1);
    add_interfaced_edge(4, 3, 5, 1);
    add_interfaced_edge(5, 2, 1, 1);
    add_interfaced_edge(6, 4, 3, 1);
}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
}



Graph::Graph(std::string nomfichier)
{
    std::ifstream fp { (nomfichier+".txt").c_str() };
    std::string s1, s2;
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
                Vertex s(s1, taille1);
                m_sommets.push_back(s);
            }
            if(valide2 == false)
            {
                Vertex s(s2, taille2);
                m_sommets.push_back(s);
            }
            valide1 = false;
            valide2 = false;

            Edge arete(s1, taille1, s2,taille2, poids) ;
            m_aretes.push_back(arete);
        }
        Initialisation();
    }
}


void Graph::Initialisation()
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
        for(unsigned int j = 0; j<m_sommets.size(); j++)
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

void Graph::AjouterSommet(Graph grapheSave)
{
    bool newSommet;
    std::vector<std::string> listNewSommet;
    std::string sommetAjout;
    int tailleNewSommet;
    std::cout<<"Voici la liste des sommets possible a ajouter : "<<std::endl;
    for(unsigned int i = 0; i<grapheSave.Getsommets().size(); i++)
    {
        newSommet = true;
        for(unsigned int j = 0; j<m_sommets.size(); j++)
        {
            if(grapheSave.Getsommets()[i].Getnom() == m_sommets[j].Getnom())
                newSommet = false;
        }
        if(newSommet == true)
        {
            listNewSommet.push_back(grapheSave.Getsommets()[i].Getnom());
            std::cout<<grapheSave.Getsommets()[i].Getnom()<<" ,"<<std::endl;
        }
    }
    if(listNewSommet.size() == 0 )
        std::cout<<"Le graphe est deja complet"<<std::endl;
    if(listNewSommet.size() != 0 )
        std::cin>>sommetAjout;
    std::vector<Edge> newArete;
    for(unsigned int i = 0; i<listNewSommet.size(); i++)
    {
        ///On ajoute le sommet et les aretes
        if(sommetAjout == listNewSommet[i])
        {
            for(unsigned int j = 0; j<grapheSave.Getaretes().size(); j++)
            {
                if(grapheSave.Getaretes()[j].Gets1().Getnom() == listNewSommet[i] || grapheSave.Getaretes()[j].Gets2().Getnom() == listNewSommet[i])
                {
                    Edge newEdgeCrea(grapheSave.Getaretes()[j].Gets1().Getnom(),grapheSave.Getaretes()[j].Gets1().Gettaille(),grapheSave.Getaretes()[j].Gets2().Getnom(),grapheSave.Getaretes()[j].Gets2().Gettaille(),grapheSave.Getaretes()[j].Getpoids());
                    newArete.push_back(newEdgeCrea);
                }
            }
        }
    }
    bool aRajouter;
    std::cout<<"Test"<<std::endl;
    for(unsigned int i = 0; i<newArete.size(); i++)
    {
        aRajouter = false;
        for(unsigned int j = 0; j<m_sommets.size(); j++)
        {
            if(newArete[i].Gets1().Getnom() == m_sommets[j].Getnom() ||newArete[i].Gets2().Getnom() == m_sommets[j].Getnom())
            {
                aRajouter = true;
            }
        }
        if(aRajouter == true)
            m_aretes.push_back(newArete[i]);

    }
    for(unsigned int i = 0; i<listNewSommet.size(); i++)
    {
        ///On ajoute le sommet et les aretes
        if(sommetAjout == listNewSommet[i])
        {
            std::cout<<"Veuillez rentrer l'ordre du nouveau sommet"<<std::endl;
            std::cin>>tailleNewSommet;
            Vertex newSommetCrea(sommetAjout,tailleNewSommet);
            m_sommets.push_back(newSommetCrea);
        }
    }
    Initialisation();
    std::cout<<m_nbaretes<<std::endl;
}


///A revoir
void Graph::Setmatriceadja()
{
    ///On reinitialise la matrice
    while(m_matriceadja.size() != 0)
    {
        m_matriceadja.pop_back();
    }
    std::cout<<"ordre : "<<m_ordre<<std::endl;
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


void Graph::AfficherMatriceAdj()
{
    for(unsigned int i = 0 ; i<m_sommets.size(); i++)
    {
        std::cout<<m_sommets[i].Getnom()<<std::endl;
    }
    for(unsigned int i= 0; i<m_ordre; i++)
    {
        for(unsigned int j = 0; j<m_ordre; j++)
        {
            std::cout<<m_matriceadja[i + j * m_ordre]<<" ";
        }
        std::cout<<std::endl;
    }

    for(unsigned int i = 0; i<m_ordre; i++)
    {
        std::cout<<m_sommets[i].Getnom()<<" "<<m_sommets[i].Getindice()<<std::endl;
    }
}

void Graph::ForteConnexite()
{
    for(unsigned int k = 0; k<m_sommets.size(); k++)
                {
                    m_sommets[k].CleanColor();
                }
    std::queue<int> file;
    std::vector<Vertex> vecForteConnexite;
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
            std::vector<Vertex> compoconnexe;
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

            ///Composantes fortement connexte en sens inverse partant de x (via vecteur d'arrete)

            ///On initialise le marquage a faux
            Initialisation();
            ///On ajoute le sommets de debut
            file.push(i);
            ///On le marque
            m_sommets[i].Setmarque(true);
            ///On crée le vecteur qui va recuperer les arretes utilisés
            std::vector<Vertex> compoconnexeinverse;
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
            ///On regarde les si les points d'intersection entre la composante connexe inverse et celle dans le sens positif
            for(unsigned int j = 0; j<compoconnexe.size(); j++)
            {
                for(unsigned int k = 0; k<compoconnexeinverse.size(); k++)
                {
                    if(compoconnexe[j].Getnom() == compoconnexeinverse[k].Getnom())
                    {

                        m_sommets[compoconnexe[j].Getindice()].Setcouleur(i);
                        std::cout<<m_sommets[compoconnexe[j].Getindice()].Getcouleur().front()<<std::endl;
                    }
                }
            }
        }
    }
}

void Graph::AfficherForteConnexite()
{
    int nbcolor = 0;
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        for(unsigned int j = 0; j<m_sommets[i].Getcouleur().size(); j++)
        {
            if(m_sommets[i].Getcouleur()[j] >= nbcolor ) nbcolor=m_sommets[i].Getcouleur()[j] + 1;
        }

    }
    std::cout<<"il y a "<<nbcolor<<" composante(s) connexe(s) : "<<std::endl;
    for(unsigned int i = 0; i<nbcolor; i++)
    {
        std::cout<<"Composante Connexe numero "<<i<<std::endl;
        for(unsigned int j= 0; j<m_sommets.size(); j++)
        {
            for(unsigned int k = 0; k<m_sommets[j].Getcouleur().size(); k++)
            {
                if(m_sommets[j].Getcouleur()[k] == i) std::cout<<m_sommets[j].Getnom()<<std::endl;
            }
        }
        std::cout<<std::endl;
    }
}

void Graph::SauvegarderGraphe()
{
    std::ofstream fp {(m_nom+".txt").c_str(), std::ios::out};
    if (fp)
    {
        fp<<m_sommets.size()<<std::endl;
        fp<<m_aretes.size()<<std::endl;
        for(unsigned int i = 0; i<m_nbaretes; i++)
        {
            fp<<m_aretes[i].Gets1().Getnom()<<" "<<m_aretes[i].Gets1().Gettaille()<<" "<<m_aretes[i].Gets2().Getnom()<<" "<<m_aretes[i].Gets2().Gettaille()<<" "<<m_aretes[i].Getpoids()<<std::endl;
        }
    }
    else
    {
        std::cout<<"Erreur"<<std::endl;
    }
}

void Graph::SupprimerSommet(std::string sommetsupr)
{
    std::vector<Edge> newArete;
    std::vector<Vertex> newSommet;
    ///Pour les sommets
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        ///On ajoute tous les sommets sauf celui a supprimer
        if(sommetsupr != m_sommets[i].Getnom())
            newSommet.push_back(m_sommets[i]);
    }
    ///On met a jour les sommets
    m_sommets = newSommet;

    ///Mise a jour des aretes
    for(unsigned int i = 0; i<m_aretes.size(); i++)
    {
        if(m_aretes[i].Gets1().Getnom() != sommetsupr && m_aretes[i].Gets2().Getnom() != sommetsupr)
            newArete.push_back(m_aretes[i]);
    }

    m_aretes = newArete;
    bool sommetExiste;
    for(unsigned int i = 0; i<m_sommets.size(); i++ )
    {
        sommetExiste = false;
        for(unsigned int j = 0; j<m_aretes.size(); j++ )
        {
            if(m_sommets[i].Getnom() == m_aretes[j].Gets1().Getnom() || m_sommets[i].Getnom() == m_aretes[j].Gets2().Getnom())
            {
                sommetExiste = true;
            }
        }
        if(sommetExiste == false) SupprimerSommet(Getsommets()[i].Getnom());
    }
}

void Graph::SupprimerSommets(std::vector<std::string> sommetsuppr)
{
    ///On parcourt le vecteur
    ///Pour chaque, on regarde si il est dans la liste, si il n'y est pas on l'ajoute
    std::vector<Edge> newArete;
    std::vector<Vertex> newSommet;
    bool aSupprimer = false;
    bool aGarder = false;
    ///Pour les sommets
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        aSupprimer = false;
        ///On ajoute toutes les aretes sauf celle a supprimer
        for(unsigned int j = 0; j<sommetsuppr.size(); j++)
        {
            if(sommetsuppr[j] == m_sommets[i].Getnom())
            {
                aSupprimer = true;
            }
        }
        if(aSupprimer == false)
            newSommet.push_back(m_sommets[i]);
    }
    ///On met a jour les aretes
    m_sommets = newSommet;
    for(unsigned int i = 0; i<m_aretes.size(); i++)
    {
        for(unsigned int j = 0; j<sommetsuppr.size(); j++)
        {
            aGarder = true;
            if(m_aretes[i].Gets1().Getnom() == sommetsuppr[j] || m_aretes[i].Gets2().Getnom() == sommetsuppr[j])
            {
                aGarder = false;
            }
        }
        if(aGarder == true)
            newArete.push_back(m_aretes[i]);
    }
    m_aretes = newArete;

    ///On reinitiallise le graphe
    //Initialisation();
}


void Graph::SupprimerArete(int aretesuppr)
{
    std::vector<Edge> newArete;
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
    //Initialisation();
}


void Graph::SupprimerAretes(std::vector<int> aretesuppr)
{
    ///On parcourt le vecteur
    ///Pour chaque, on regarde si il est dans la liste, si il n'y est pas on l'ajoute
    std::vector<Edge> newArete;
    bool aSupprimer = false;
    ///Pour les sommets
    for(unsigned int i = 0; i<m_aretes.size(); i++)
    {
        aSupprimer = false;
        ///On ajoute toutes les aretes sauf celle a supprimer
        for(unsigned int j = 0; j<aretesuppr.size(); j++)
        {
            if(aretesuppr[j] == m_aretes[i].Getindice())
            {
                aSupprimer = true;
            }
        }
        if(aSupprimer == false)
            newArete.push_back(m_aretes[i]);
    }
    ///On met a jour les sommets

    m_aretes = newArete;

    ///On reinitiallise le graphe
    //Initialisation();
}


bool Graph::IsConnexe()
{
    std::queue<int> file;
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
        return true;
    }

    if(nombreSommetMarque != m_sommets.size())
    {
        return false;
    }
}

void Graph::KconnexiteArete()
{
    Initialisation();
    int nombreAreteThisRound;
    int kAreteConnexite = m_aretes.size();
    ///On copie le graphe pour pouvoir le modifier sans affecter tout l'affichage, etc ...
    Graph copie = *this;
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        for(unsigned int j = 0; j<m_sommets.size(); j++)
        {
            if(i != j)
            {
                nombreAreteThisRound = BFSSuppressionArete(j, i);
                if(nombreAreteThisRound < kAreteConnexite)
                    kAreteConnexite = nombreAreteThisRound;
            }
            *this = copie;

        }
    }
    std::cout<<"Le graphe est "<<kAreteConnexite<<" K-Arete-Connexe"<<std::endl;

}

void Graph::sommetKConnexite(int k)
{
    int boucle = 0;
    bool actif = true;
    bool sommetDistinct = false;
    std::vector<int> compteur;
    std::vector<std::string> nomEffacer;
    std::vector<std::string> sommetAretirer;
    for(unsigned int i = 0; i<k; i++)
    {
        compteur.push_back(0);
    }
    Graph copie = *this;
    while(actif == true)
    {
        sommetDistinct = true;
        nomEffacer.clear();
        ///On regarde si deux indice on le meme ordre, dans ce cas on ne fera pas les interactions
        for(unsigned int i = 0; i<k; i++)
        {
            for(unsigned int j = 0; j<k; j++)
            {
                if(i != j && compteur[i] == compteur[j])
                    sommetDistinct = false;
            }
        }
        ///On supprime les k sommets a supprimer
        if(sommetDistinct == true)
        {
            for(unsigned int i = 0; i<k; i++)
            {
                nomEffacer.push_back(m_sommets[compteur[i]].Getnom());
                SupprimerSommet(m_sommets[compteur[i]].Getnom());
            }
            if(IsConnexe() == false)
            {
                for(unsigned int i = 0; i<nomEffacer.size(); i++)
                {
                    sommetAretirer.push_back(nomEffacer[i]);
                }
            }
        }
        *this = copie;

        Initialisation();
        ///On augmente le cran du compteur
        compteur[k-1] = compteur[k-1] + 1;

        for(unsigned int i = 0; i<k; i++)
        {
            ///Si on a attent le rang max
            if(compteur[k-i-1] == m_sommets.size())
            {
                if(i == k-1)
                    actif = false;
                if(i < m_sommets.size() - 1 )
                {

                    compteur[k-i-1] = 0;
                    compteur[k-i- 2] = compteur[k-i-2]+1;
                }
            }
        }

    }
    int i = 0;

    std::cout<<"Les couples de sommets a retirer sont donc : "<<std::endl;
    while (i < sommetAretirer.size())
    {
        for(unsigned j = 0; j < k; j++)
        {
            std::cout<<sommetAretirer[i + j]<<" ";
        }
        std::cout<<std::endl;
        i = i+k;
    }
    *this = copie;
}

void Graph::KconnexiteSommet()
{
    Initialisation();
    int nombreSommetThisRound;
    int kSommetConnexite = m_sommets.size();
    ///On copie le graphe pour pouvoir le modifier sans affecter tout l'affichage, etc ...
    Graph copie = *this;
    for(unsigned int i = 0; i<m_sommets.size(); i++)
    {
        for(unsigned int j = 0; j<m_sommets.size(); j++)
        {
            if(i != j)
            {
                nombreSommetThisRound = BFSSuppressionSommet(j, i);
                if(nombreSommetThisRound < kSommetConnexite)
                    kSommetConnexite = nombreSommetThisRound;
            }
            *this = copie;

        }
    }
    std::cout<<"Le graphe est "<<kSommetConnexite<<" K-Sommet-Connexe"<<std::endl;
    sommetKConnexite(kSommetConnexite);

}

int Graph::BFSSuppressionArete(int indice1, int indice2)
{

    int nbchemin = 0;
    std::queue<int> file;
    std::vector<int> areteSupr;
    int sommetselec;
    int sommetsuivant;
    bool reussite;
    do
    {
        Initialisation();
        ///On demarre le BFS au sommet d'incide 1;
        m_sommets[indice1].Setmarque(true);
        file.push(indice1);
        while(!file.empty())
        {
            sommetselec = file.front();
            file.pop();
            for(unsigned int j=0; j< m_aretes.size(); j++)
            {
                reussite = false;
                if(m_sommets[sommetselec].Getnom() == m_aretes[j].Gets1().Getnom())
                {
                    sommetsuivant = m_aretes[j].Gets2().Getindice();
                    reussite = true;
                }
                if(m_sommets[sommetselec].Getnom() == m_aretes[j].Gets2().Getnom())
                {
                    sommetsuivant = m_aretes[j].Gets1().Getindice();
                    reussite = true;
                }
                if(reussite == true)
                {
                    if(!m_sommets[sommetsuivant].Getmarque())
                    {
                        m_sommets[sommetsuivant].Setprede(sommetselec);
                        m_sommets[sommetsuivant].Setmarque(true);
                        file.push(sommetsuivant);
                        if(sommetsuivant == indice2)
                        {
                        }

                    }
                }
            }
        }
        if(m_sommets[indice2].Getmarque() == true)
        {
            sommetselec = indice2;
            areteSupr.clear();
            while(sommetselec != indice1)
            {
                for(unsigned int j = 0; j<m_aretes.size(); j++)
                {
                    if((m_aretes[j].Gets1().Getindice() == m_sommets[sommetselec].Getindice() && m_aretes[j].Gets2().Getindice() == m_sommets[sommetselec].Getprede() )|| (m_aretes[j].Gets2().Getindice() == m_sommets[sommetselec].Getindice() && m_aretes[j].Gets1().Getindice() == m_sommets[sommetselec].Getprede()))
                    {
                        sommetselec = m_sommets[sommetselec].Getprede();
                        areteSupr.push_back(j);
                    }
                }
            }
            std::sort(areteSupr.begin(),areteSupr.end());
            SupprimerAretes(areteSupr);
            nbchemin = nbchemin + 1;
        }
    }
    while(m_sommets[indice2].Getprede() != m_sommets[indice2].Getindice());
    return nbchemin;
}


int Graph::BFSSuppressionSommet(int indice1, int indice2)
{
    bool test = true;
    bool connexe = true;
    int nbchemin = 0;
    ///On retire l'arete reliant directement ces 2 sommets (si elle existe)
    for(unsigned int i = 0; i<m_aretes.size(); i++)
    {
        if((m_aretes[i].Gets1().Getindice() == indice1 && m_aretes[i].Gets2().Getindice() == indice2) || (m_aretes[i].Gets1().Getindice() == indice2 && m_aretes[i].Gets2().Getindice() == indice1))
        {
            test = false;
            nbchemin = m_sommets.size() - 1;
        }
    }
    std::queue<int> file;
    std::vector<std::string> SommetSupr;
    int sommetselec;
    int sommetsuivant;
    bool reussite;
    if (test == true)
    {
        do
        {
            ///On demarre le BFS au sommet d'incide 1;
            Initialisation();
            m_sommets[indice1].Setmarque(true);
            file.push(indice1);
            while(!file.empty())
            {
                sommetselec = file.front();
                file.pop();
                for(unsigned int j=0; j< m_aretes.size(); j++)
                {
                    reussite = false;
                    if(m_sommets[sommetselec].Getnom() == m_aretes[j].Gets1().Getnom())
                    {
                        sommetsuivant = m_aretes[j].Gets2().Getindice();
                        reussite = true;
                    }
                    if(m_sommets[sommetselec].Getnom() == m_aretes[j].Gets2().Getnom())
                    {
                        sommetsuivant = m_aretes[j].Gets1().Getindice();
                        reussite = true;
                    }
                    if(reussite == true)
                    {
                        if(!m_sommets[sommetsuivant].Getmarque())
                        {
                            m_sommets[sommetsuivant].Setprede(sommetselec);
                            m_sommets[sommetsuivant].Setmarque(true);
                            file.push(sommetsuivant);
                        }
                    }
                }
            }

            if(m_sommets[indice2].Getmarque() == true)
            {
                sommetselec = indice2;
                SommetSupr.clear();
                while(sommetselec != indice1)
                {
                    for(unsigned int j = 0; j<m_aretes.size(); j++)
                    {
                        if((m_aretes[j].Gets1().Getindice() == m_sommets[sommetselec].Getindice() && m_aretes[j].Gets2().Getindice() == m_sommets[sommetselec].Getprede() )|| (m_aretes[j].Gets2().Getindice() == m_sommets[sommetselec].Getindice() && m_aretes[j].Gets1().Getindice() == m_sommets[sommetselec].Getprede()))
                        {
                            if(sommetselec != indice1 && sommetselec != indice2)
                                SommetSupr.push_back(m_sommets[sommetselec].Getnom());
                            sommetselec = m_sommets[sommetselec].Getprede();

                        }
                    }

                }
                ///On sauvegarde les sommets d'indice 1 et 2
                std::string save1 = m_sommets[indice1].Getnom();
                std::string save2 = m_sommets[indice2].Getnom();
                SupprimerSommets(SommetSupr);
                for(unsigned int i = 0; i<m_sommets.size(); i++)
                {
                    if(m_sommets[i].Getnom() == save1)
                        indice1 = i;
                    if(m_sommets[i].Getnom() == save2)
                        indice2 = i;
                }
                nbchemin = nbchemin + 1;
            }

        }
        while(m_sommets[indice2].Getmarque() == true);
    }
    return nbchemin;
}


void Graph::MapVertex()
{
    m_vertices.clear();
    for(int i = 0; i<m_sommets.size(); i++)
    {
        m_vertices[i] = m_sommets[i];
    }
}

void Graph::MapEdge()
{
    m_edges.clear();
    for(int i = 0; i<m_aretes.size(); i++)
    {
        m_edges[i] = m_aretes[i];
    }
}
