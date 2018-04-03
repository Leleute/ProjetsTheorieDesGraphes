#ifndef ARETE_H
#define ARETE_H
#include <iostream>
#include <vector>
#include "Sommet.h"
using namespace std;


class Arete
{
      public:
            Arete();
            Arete(string s1, float taille1,string s2,float taille2, float val);
            virtual ~Arete();

            Sommet Gets1() { return m_s1; }
            void Sets1(Sommet val) { m_s1 = val; }
            Sommet Gets2() { return m_s2; }
            void Sets2(Sommet val) { m_s2 = val; }
            float Getpoids() { return m_poids; }
            void Setpoids(float val) { m_poids = val; }

      protected:

      private:
            Sommet m_s1;
            Sommet m_s2;
            float m_poids;
};

#endif // ARETE_H
