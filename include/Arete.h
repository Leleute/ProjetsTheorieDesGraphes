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
            virtual ~Arete();

            Sommet* Gets1() { return m_s1; }
            void Sets1(Sommet* val) { m_s1 = val; }
            Sommet* Gets2() { return m_s2; }
            void Sets2(Sommet* val) { m_s2 = val; }
            int Getpoids() { return m_poids; }
            void Setpoids(int val) { m_poids = val; }

      protected:

      private:
            Sommet* m_s1;
            Sommet* m_s2;
            int m_poids;
};

#endif // ARETE_H
