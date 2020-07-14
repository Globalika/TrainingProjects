#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void fillMatrix(int**& matrix, string name, int &n, int &m)
{
    ifstream fin(name);

    fin >> n;
    fin >> m;
    int num;

    matrix = new int*[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            fin >> num;
            matrix[i][j] = num;
        }
    }

    fin.close();

}

void printMatrix(int** matrix,int n,int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

void deleteMatrix(int**& matrix,int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void sadleFinder(int** matrix, int n, int m)
{
    if (n > m) m = n;
    int* arr = new int[m];
    int k = 0;
    int max;
	int imax, jmax;
    int ex;

    for (int i = 0 ; i < n; i++)
    {
    	
        bool y = false;
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] > matrix[i][j + 1])
            {
                max = matrix[i][j]; imax = i; jmax = j;
            }
            else if (matrix[i][j] < matrix[i][j + 1])
            {
                max = matrix[i][j + 1]; imax = i; jmax = j + 1;
            }
		    else
            {
                break;
            }
        	
            if (j == m - 1)
            {
                y = true;
                break;
            }
        }
        if (y)
        {
            for (int t = 0; t < n; t++)
            {
                if(imax == t)
                    continue;
                else
                {

                    if (max < matrix[t][jmax]) 
                    {
                        if (t == n - 1)
                        {
                            arr[k] = max;
                            k++;
                        }
                    }
                        else 
                        {
                            break;
                        }

                }
            }
        }
    }

	
    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << endl;
    }
	
}


int main()
{
    int** matrix1;
//    int** matrix2;
    string mx1 = "input1.txt";
//	string mx2 = "input2.txt";
    int n1, n2;
    int m1, m2;

    fillMatrix(matrix1, mx1, n1, m1);
//    fillMatrix(matrix2, mx2, n2, m2);
    printMatrix(matrix1, n1, m1);
    cout << endl;
//    printMatrix(matrix2, n2, m2);


    sadleFinder(matrix1, n1, m1);


	
    deleteMatrix(matrix1, n1);
//    deleteMatrix(matrix2, n2);


	
    system("pause");
    return 0;
}