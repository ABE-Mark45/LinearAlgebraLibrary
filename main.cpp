#include <bits/stdc++.h>

using namespace std;


class Matrix
{
public:
    double **arr;
public:
    int m, n;
    Matrix(int m, int n): m(m), n(n)
    {
        arr = new double*[m];
        for(int i = 0;i < m;i++)
            arr[i] = new double[n];
        for(int i = 0;i < m;i++)
            for(int j = 0;j < n;j++)
                arr[i][j] = 0.0f;
    }
    Matrix()
    {
        arr = NULL;
        m = 0, n=0;
    }

    Matrix(const Matrix &a)
    {
        m = a.m;
        n = a.n;
        this->arr = new

        double*[a.m];
        for(int i = 0;i < m;i++)
            arr[i] = new
            double[a.n];
        for(int i = 0;i < m;i++)
            for(int j = 0;j < n;j++)
                arr[i][j] = a.arr[i][j];
    }

    Matrix add(const Matrix &b) const
    {
        if(m != b.m || n != b.n)
        {
            cout << "Dimensions Error\n";
            return Matrix();
        }
        Matrix sum = Matrix(m, n);
        for(int i = 0;i < m;i++)
            for(int j = 0;j < n;j++)
                sum.arr[i][j] = arr[i][j] + b.arr[i][j];
        return sum;
    }

    Matrix subtract(const Matrix &b) const
    {
        if(m != b.m || n != b.n)
        {
            cout << "Dimensions Error\n";
            return Matrix();
        }
        Matrix sum = Matrix(m, n);
        for(int i = 0;i < m;i++)
            for(int j = 0;j < n;j++)
                sum.arr[i][j] = arr[i][j] - b.arr[i][j];
        return sum;
    }


    Matrix multiply(const Matrix &b) const
    {
        if(n != b.m)
        {
            cout << "Dimensions error\n";
            return Matrix();
        }
        Matrix sum = Matrix(m, b.n);
        for(int i = 0;i < sum.m;i++)
        {
            for(int j = 0;j < sum.n; j++)
            {
                double cell = 0;
                for(int k = 0;k < n;k++)
                    cell+= arr[i][k] * b.arr[k][j];
                sum.arr[i][j] = cell;
            }
        }
        return sum;
    }
    Matrix transpose() const
    {
        Matrix t = Matrix(n, m);
        for(int i = 0; i < m;i++)
            for(int j = 0; j < n;j++)
                t.arr[j][i] = arr[i][j];
        return t;
    }

    Matrix operator*(const Matrix &b)const
    {
        return multiply(b);
    }

    Matrix operator*(double num)const
    {
        Matrix a = *this;
        for(int i = 0;i < m;i++)
            for(int j = 0; j < n;j++)
                a.arr[i][j] *= num;
        return a;
    }


    Matrix operator+(const Matrix &b)const
    {
        return add(b);
    }

    Matrix operator-(const Matrix &b)const
    {
        return subtract(b);
    }

    friend ostream& operator<<(ostream &os, const Matrix &a)
    {
        for(int i = 0;i < a.m;i++)
        {
            for(int j = 0;j < a.n;j++)
                os << a.arr[i][j] << '\t';
            os << endl;
        }
        return os;
    }

    double trace()const
    {
        if(m != n)
        {
            cout << "Dimensions error: matrix must be square" << endl;
            return -1;
        }

        double sum = 1;
        for(int i = 0; i < n;i++)
            sum *= arr[i][i];
        return sum;
    }

    double determinant()const
    {
        Matrix a = *this;
        if(m != n)
        {
            cout << "Dimensions error: matrix must be square" << endl;
            return -1;
        }
        for(int i = 0;i < n;i++)
            for(int j = i+1;j < n;j++)
            {
                double tmp = a.arr[j][i];
                if(abs(arr[i][i]) > 1e-7)
                    for(int k = i;k < n;k++)
                        a.arr[j][k] = a.arr[j][k] - a.arr[i][k] * tmp / a.arr[i][i];
            }
        return a.trace();
    }

    Matrix GaussianElimination() const
    {
        Matrix a = *this;
        int limit = min(m, n);
        for(int i = 0;i < limit-1;i++)
            for(int j = i+1;j < limit;j++)
            {
                double tmp = a.arr[j][i];
                if(abs(a.arr[i][i]) > 1e-7)
                    for(int k = i;k < n;k++)
                        a.arr[j][k] = a.arr[j][k] - a.arr[i][k] * tmp / a.arr[i][i];
                else
                {
                    for(int k = 0; k < n;k++)
                        swap(a.arr[i][k], a.arr[i+1][k]);
                    j--;
                }
            }
        for(int i = 0;i < m;i++)
        {
            double tmp_ratio = a.arr[i][i];
            if(abs(tmp_ratio) > 1e-7)
                for(int j = i;j < n;j++)
                    a.arr[i][j] /= tmp_ratio;
        }
        return a;
    }

    Matrix GaussJordan() const
    {
        Matrix a = *this;
        int limit = min(m, n);
        for(int i = 0;i < limit;i++)
            for(int j = i+1;j < limit;j++)
            {
                double tmp = a.arr[j][i];
                if(abs(a.arr[i][i]) > 1e-7)
                    for(int k = i;k < n;k++)
                        a.arr[j][k] = a.arr[j][k] - a.arr[i][k] * tmp / a.arr[i][i];
                else
                {
                    for(int k = 0; k < n;k++)
                        swap(a.arr[i][k], a.arr[i+1][k]);
                    j--;
                }

            }

        for(int i = limit-1;i >= 0;i--)
            for(int j = i-1;j >= 0;j--)
            {
                double tmp = a.arr[j][i];
                if(abs(a.arr[i][i]) > 1e-7)
                    for(int k = n-1;k >= 0;k--)
                        a.arr[j][k] = a.arr[j][k] - a.arr[i][k] * tmp / a.arr[i][i];
            }


        for(int i = 0;i < m;i++)
        {
            double tmp_ratio = a.arr[i][i];
            if(abs(a.arr[i][i]) > 1e-7)
                for(int j = i;j < n;j++)
                    a.arr[i][j] /= tmp_ratio;
        }
        return a;
    }

    Matrix identity(int n)
    {
        Matrix a = Matrix(n, n);
        for(int i = 0; i < n;i++)
            a.arr[i][i] = 1;
        return a;
    }

    Matrix inverse() const
    {
        if(m != n)
        {
            cout << "Dimensions error: matrix must be square" << endl;
            return Matrix();
        }
        if(!this->determinant())
        {
            cout << "Error: the matrix is non-invertible" << endl;
            return Matrix();
        }

        Matrix a = Matrix(n, n*2);
        Matrix ones = a.identity(n);
        for(int i = 0; i < n;i++)
            for(int j = 0;j < n;j++)
                a.arr[i][j] = arr[i][j];

        for(int i = 0; i < n;i++)
            for(int j = n; j < n*2; j++)
                a.arr[i][j] = ones.arr[i][j-n];
        a = a.GaussJordan();
        for(int i = 0; i < n;i++)
            for(int j = n; j < n*2; j++)
                ones.arr[i][j-n] = a.arr[i][j];
        return ones;
    }

    pair<Matrix, Matrix> LUFactorization() const
    {
        Matrix a = *this;
        Matrix L = a.identity(m);
        int limit = min(m, n);
        for(int i = 0;i < limit;i++)
            for(int j = i+1;j < limit;j++)
            {
                double tmp = a.arr[j][i];
                L.arr[j][i] = tmp / a.arr[i][i];
                if(abs(a.arr[i][i]) > 1e-7)
                    for(int k = i;k < n;k++)
                        a.arr[j][k] -= a.arr[i][k] * tmp / a.arr[i][i];
                else
                {
                    for(int k = 0; k < n;k++)
                        swap(a.arr[i][k], a.arr[i+1][k]);
                    j--;
                }
            }
        pair<Matrix, Matrix> out = make_pair(L, a);
        return out;
    }

    string soln(){
        Matrix a = *this;
        Matrix z();
        if(m != n-1){
            return "Enter N*(N+1) Dimensions Please" ;

        }
        Matrix solutions = a.GaussJordan();
        a = a.GaussJordan();
        int v1= a.arr[m-1][m-1],v2=a.arr[m-1][m];


        if(v1 == 0 && v2 == 0){
            return "infinite number of solns \n";

        }
        else if (v1 == 0 && v2 != 0 ){
            return "no soln\n";
         //   return 0;
        }

        cout << "soln is:\n";
        for(int i=0; i<m; i++){
            cout << solutions.arr[i][n-1] <<" ";
        }
        return "\n";
    }

};

/*
1 2 3 4
5 6 7 8
9 10 11 12
*/

/*
 1 2 3 1
 -3 -2 -1 2
 4 4 4 3

 NO SOLN
*/


/*
    2 -1 3 5
    2 2 3 7
    -2 3 0 -3

    2.5,2/3,2/9
*/
int main()
{
    int n,m;
    cin >> n >> m;
    Matrix a = Matrix(3, 2);
    Matrix b = Matrix(2, 2);
    Matrix c = Matrix(n, m);
    for(int i = 0;i < n;i++)
        for(int j = 0; j < m;j++)
            cin >> c.arr[i][j];
    //a.arr[0][0] = 2, a.arr[0][1] = 3, a.arr[1][0] = 5, a.arr[1][1] = 4, a.arr[2][0] = 9, a.arr[2][1] = 10;

    b.arr[0][0] = 5, b.arr[0][1] = 4, b.arr[1][0] = 1, b.arr[1][1] = 0;
    //cout << endl << c << endl;
    //cout << c.GaussJordan() << endl;
    //cout << c.inverse() << endl;

    //pair<Matrix, Matrix> out = c.LUFactorization();
    cout << c.soln() << endl;

    //cout << out.first * out.second << endl << c << endl;;

    return 0;
}
