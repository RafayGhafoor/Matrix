#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

class myMatrix {
private:
  int **matr, nrow, ncol;

public:
  // Constructors

  // Default Constructor
  myMatrix() {
    matr = nullptr;
    nrow = ncol = 0;
  }

  // Parametric Constructor
  myMatrix(int r, int c, int val = 0) {
    nrow = r;
    ncol = c;
    matr = new int *[r];

    for (int i = 0; i < r; i++) {
      matr[i] = new int[c];
      for (int j = 0; j < c; j++)
        matr[i][j] = val;
    }
  }

  // Deep Copy Constructor
  myMatrix(const myMatrix &obj) {
    matr = new int *[obj.nrow];
    for (int i = 0; i < obj.nrow; i++) {
      matr[i] = new int[obj.ncol];
      for (int j = 0; j < obj.ncol; j++)
        matr[i][j] = obj.matr[i][j];
    }
  }

  // Methods
  myMatrix add(const myMatrix &obj) {
    // When the order (rows * columns) of the parametric object is not equal to
    // instance's order.
    if ((this->nrow != obj.nrow) || (this->ncol != obj.ncol))
      return *this;

    myMatrix output(*this);

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] += obj.matr[i][j];

    return output;
  }

  myMatrix mul(const myMatrix &obj) {
    if ((this->nrow != obj.nrow) || (this->ncol != obj.ncol))
      return *this;

    myMatrix output(*this);

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] *= obj.matr[i][j];

    return output;
  }

  myMatrix mul(int scalar) {
    myMatrix output(*this);

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] *= scalar;

    return output;
  }

  const myMatrix &mulAndUpdate(int scalar) {
    if (!scalar) {
      for (int i = 0; i < nrow; i++)
        matr[i] = {0};
      return *this;
    }

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j] *= scalar;

    return *this;
  }

  const myMatrix pre_increment() {
    myMatrix output(*this);

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        ++output.matr[i][j];

    return output;
  }

  myMatrix post_increment() {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j]++;

    return *this;
  }

  const myMatrix &negate() {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if (matr[i][j] != 0)
          matr[i][j] *= -1;

    return *this;
  }

  const myMatrix &transpose() {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if (i != j)
          swap(matr[i][j], matr[j][j]);

    return *this;
  }

  const myMatrix &assign(const myMatrix &obj) {
    this->matr = obj.matr;
    this->nrow = obj.nrow;
    this->ncol = obj.ncol;
    return *this;
  }

  // TODO: Implementation
  // https://youtu.be/KvzS03KB2X8
  bool submatrix(const myMatrix &obj) {
    /* Sample test cases:
    O:  1 2 3          M: 2 3 | M: 1 2 3 | M: 4 5 6
        4 5 6             5 6

    */

    if (obj.getRows() > nrow || obj.getCols() > ncols) // object is super-matrix
      return 0;
  }

  bool isIdentity() {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if ((matr[i][j] != 1) && (matr[j][i] != 0))
          return 0;
    return 1;
  }

  // Getters and Setters
  int getRows() { return nrow; }

  int getCols() { return ncol; }

  int getElement(int r, int c) {
    if ((matr[r][c] && r < this->nrow) && (c < this->ncol))
      return matr[r][c];

    return 0;
  }

  void setElement(int r, int c, int val) {
    if ((r < this->nrow) &&
        (c < this->ncol)) // bound check for rows and columns for matrix
      matr[r][c] = val;
  }

  // Destructor
  ~myMatrix() {

    for (int i = 0; i < nrow; i++)
      if (matr[i])
        delete[] matr[i];

    if (matr) {
      delete[] matr;
      matr = nullptr;
    }
  }
};

myMatrix readMatrix(char filename[]) {
  ifstream fin(filename);
  int r, c, rc, cc;
  rc = cc = 0;
  fin >> r;
  fin >> c;
  fin.ignore();

  myMatrix obj(r, c, 0);
  int n;

  while (fin >> n) {
    obj.setElement(rc, cc++, n);
    if (cc == c) // When temp column count (cc) becomes equal to pre-defined
                 // column count (c)
    {
      cc = 0; // Reset Column Count
      rc++;   // New line indicates a new row
    }
  }

  return obj;
}

void printMatrix(myMatrix &obj) {
  cout << "Matrix is : \n\n";
  int r = obj.getRows(), c = obj.getCols();

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++)
      cout << " " << obj.getElement(i, j) << "\t";
    cout << "\n";
  }
}

int main() {
  char fn[] = "test.txt";
  myMatrix stream = readMatrix(fn);
  printMatrix(stream);
}