#include <flens/flens.cxx>
#include <iostream>

using namespace flens;
using namespace std;

int
main()
{
    GeMatrix<FullStorage<double> >   A(3, 3);
    DenseVector<Array<double> >      b(3);

///
/// Setup the raw data.
///
    A = 2, 0, 0,
        1, 2, 0,
        0, 1, 2;

    b = 1,
        2,
        3;

///
/// $S$ is a symmetric matrix view constructed from the lower triangular
/// part of $A$.  Note that $S$ only references data from $A$.
///
    auto S = A.lower().symmetric();

    cout << "S = " << S << endl;
    cout << "b = " << b << endl;

///
/// Computes the Cholesky factorization $S = L L^T$ where $L$ is lower
/// triangular.  Matrix $S$ (i.e. the lower triangular part of $A$) gets
/// overwritten with $L$.
///
    int info = lapack::potrf(S);

    if (info!=0) {
        cerr << "S is singular" << endl;
        return info;
    }

///
/// Solve $L u = b$
///
    lapack::trs(NoTrans, A.lower(), b);

///
/// Solve $L^T x = u$
///
    lapack::trs(Trans, A.lower(), b);

    cout << "x = inv(S)*b = " << b << endl;

    return 0;
}

