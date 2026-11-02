// Program to find the inverse of a matrix
// Method: Gauss-Jordan elimination
// Written using a class (Matrix) with separate functions for each step
 
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
class Matrix
{
private:
    int n;                          // size of the matrix (n x n)
    vector<vector<double> > a;      // given matrix A
    vector<vector<double> > aug;    // augmented matrix [A | I]
 
    // swap two rows of the augmented matrix
    void swapRows(int r1, int r2)
    {
        for (int j = 0; j < 2 * n; j++)
        {
            double temp = aug[r1][j];
            aug[r1][j] = aug[r2][j];
            aug[r2][j] = temp;
        }
    }
 
    // build [A | I]
    void buildAugmented()
    {
        aug.assign(n, vector<double>(2 * n, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                aug[i][j] = a[i][j];
            }
            aug[i][i + n] = 1;
        }
    }
 
    // if the diagonal element is zero, swap with a row below that has a non-zero value
    // returns false if no such row exists (matrix is singular)
    bool makePivotNonZero(int i)
    {
        if (aug[i][i] != 0)
        {
            return true;
        }
        for (int k = i + 1; k < n; k++)
        {
            if (aug[k][i] != 0)
            {
                swapRows(i, k);
                return true;
            }
        }
        return false;
    }
 
    // divide row i so that the diagonal element becomes 1
    void normalizeRow(int i)
    {
        double p = aug[i][i];
        for (int j = 0; j < 2 * n; j++)
        {
            aug[i][j] /= p;
        }
    }
 
    // make all other elements of column i equal to 0
    void eliminateColumn(int i)
    {
        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                double f = aug[k][i];
                for (int j = 0; j < 2 * n; j++)
                {
                    aug[k][j] -= f * aug[i][j];
                }
            }
        }
    }
 
public:
    Matrix(int size) : n(size), a(size, vector<double>(size, 0)) {}
 
    // take input of the matrix
    void input()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << "Enter element [" << i + 1 << "][" << j + 1 << "]: ";
                cin >> a[i][j];
            }
        }
    }
 
    // print the given matrix
    void printGiven() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(10) << a[i][j];
            }
            cout << endl;
        }
    }
 
    // Gauss-Jordan elimination; returns false if the inverse does not exist
    bool invert()
    {
        buildAugmented();
        for (int i = 0; i < n; i++)
        {
            if (!makePivotNonZero(i))
            {
                return false;
            }
            normalizeRow(i);
            eliminateColumn(i);
        }
        return true;
    }
 
    // print the inverse (right half of the augmented matrix)
    void printInverse() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = n; j < 2 * n; j++)
            {
                cout << setw(10) << aug[i][j];
            }
            cout << endl;
        }
    }
};
 
int main()
{
    int n;
 
    cout << "Enter the size of the matrix: ";
    cin >> n;
 
    if (n < 1)
    {
        cout << "Invalid size!" << endl;
        return 0;
    }
 
    Matrix m(n);
    m.input();
 
    cout << fixed << setprecision(3);
    cout << endl << "Given matrix:" << endl;
    m.printGiven();
 
    if (m.invert())
    {
        cout << endl << "Inverse matrix:" << endl;
        m.printInverse();
    }
    else
    {
        cout << endl << "Inverse does not exist (matrix is singular)." << endl;
    }
 
    return 0;
}