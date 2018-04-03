#ifndef MATRICEADJA_H
#define MATRICEADJA_H
#include <vector>
using namespace std;

class MatriceAdja
{
    public:
        /** Default constructor */
        MatriceAdja(vector<int> val);
        /** Default destructor */
        virtual ~MatriceAdja();
        vector<int> Getmatriceadj() {return m_matriceadj; }
    protected:

    private:
        vector<int> m_matriceadj;
};

#endif // MATRICEADJA_H
