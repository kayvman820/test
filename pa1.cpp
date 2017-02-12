#include <iostream>
#include "pa1.h"
using namespace std;

bool check(float n);
int** rotateArray(int **a, int n);
int** magicsquare(int n);
void sumSq(int **array, int n);


int main() {
    bool pass;
    float N;
    int n;
    do {
        cout << "INPUT>> Enter the size of the magic square: ";
        cin >> N;
        pass = check(N); //calling on check function making sure its 3,5,7,9,11,13,15
    } while (pass != true);

    n = (int) N; //cast type double to type int
    cout << endl;

    int **magic = magicsquare(n); //creating magicsquare
    int **magic1 = magicsquare(n);



//printing first magicsquare
    cout << "OUTPUT>> Magic Square #1 is:" << endl;
    for (int k = 0; k < n; k++) {
        for (int d = 0; d < n; d++) {
            cout << magic[k][d] << ' ';
        }
        cout << '\n';
    }
    sumSq(magic, n); //summing first magic square

    cout << endl;

    cout << "OUTPUT>> Magic Square #2 is:" << endl;
    magic1 = rotateArray(magic, n); //rotating first magic square
    for (int k = 0; k < n; k++) {
        for (int d = 0; d < n; d++) {
            cout << magic1[k][d] << ' ';
        }
        cout << '\n';
    }
    sumSq(magic1, n);


    cout << endl;

    cout << "OUTPUT>> Magic Square #3 is:" << endl;
    magic1 = rotateArray(rotateArray(magic, n), n); //rotating second time
    for (int k = 0; k < n; k++) {
        for (int d = 0; d < n; d++) {
            cout << magic1[k][d] << ' ';
        }
        cout << '\n';
    }
    sumSq(magic1, n);

    cout << endl;

    cout << "OUTPUT>> Magic Square #4 is:" << endl;
    magic1 = rotateArray(rotateArray(rotateArray(magic, n), n) ,n); //rotating third time
    for (int k = 0; k < n; k++) {
        for (int d = 0; d < n; d++) {
            cout << magic1[k][d] << ' ';
        }
        cout << '\n';
    }
    sumSq(magic1, n);
    return 0;
}


bool check(float N){
    bool check = false;

    if (cin.fail())
    {
        cin.clear();
        cout << "You need to enter an odd integer between 3 and 15" << endl;
    }
    else
    {
        int n = (int) N; //cast type float N to type int n
        if (n == N)
        {
            if (n == 3 || n == 5 || n == 7 || n == 9 || n == 11 || n == 13 || n == 15 )
            {
              //if input is 3,5,7,9,11,13,15 then return true and proceed to construct
                check = true;
            }
            else
            {
                cout << "You need to enter an odd integer between 3 and 15" << endl;
            }
        }
    //never gets here, probably dont need
//        else
//        {
//            cout << "You entered a float, you need an odd integer" << endl;
//        }
    }
    cin.ignore(1000, '\n');
    return check;

}

int** rotateArray(int **a, int n)
{
    int **array = new int*[15];
    for (int i = 0; i < n; i++) {
        array[i] = new int[15];
    }

    int **newarray = new int*[15];

    for (int i = 0; i < n; i++) {
        newarray[i] = new int[15];
        }

    for (int a = 0; a < n; a++) {
        for (int c = 0; c < n; c++) {
            newarray[a][c] = 0;
        }
    }

    newarray = a;

    for (int a = 0; a < n; a++){
        for (int c = 0; c < n; c++){
            array[a][c] = newarray[n - c - 1][a];
        }
    }
    return array;

}

int** magicsquare(int n){
    int **magic = new int*[n];

    for (int i = 0; i < n; i++)
    {
        magic[i] = new int[n];
    }
    //magic square constructor equation found on wikipedia
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            magic[i - 1][j - 1] = n * ((i + j - 1 + (n / 2)) % n) + ((i + (2 * j) - 2) % n) + 1;
        }
    }
    return magic;
}

void sumSq(int **array, int n){
  int sumRows;
  int sumCols;
  int sumDiag1 = 0;
  int sumDiag2 = 0;

  cout << "OUTPUT<< Checking the sum of every row: ";
  for (int i = 0; i<n; i++){
    sumRows = 0;
    for (int j = 0; j<n; j++){
      sumRows+= array[i][j];
    }
    cout << sumRows << " ";
  }
  cout << endl;

  cout << "OUTPUT<< Checking the sum of every column: ";
  for(int j = 0; j<n; j++){
    sumCols = 0;
    for (int i = 0; i<n; i++){
      sumCols += array[i][j];
    }
    cout << sumCols << " ";
  }
  cout << endl;

  cout << "OUTPUT<< Checking the sum of every diagonal: ";
  for (int i=0, j=0; i<n; i++, j++){
    sumDiag1 += array[i][j];
  }

  for (int i=0, j=n-1; i<n; i++, j--){
    sumDiag2 += array[i][j];
  }
  cout << sumDiag1 << " " << sumDiag2 << endl;
}
