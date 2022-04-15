#include "Loader.h"
#include "Sorter.h"

int main() {
    Sorter sor;
    Matrix m1(1, 2, 2);
    Matrix m2(2, 2, 2);
    Matrix m3(3, 2, 2);
    Matrix m4(4, 2, 2);
    Matrix* m;
    m = new Matrix[4];
    m[0] = m3;
    m[1] = m2;
    m[2] = m4;
    m[3] = m1;
    sor.shellSort(m, 4);
    delete [] m;
    return 0;
}
