#include <cstring>
#include <fstream>
#include <iostream>
// TODO: Error Handling, Code testing

using namespace std;

class myMatrix
{
private:
  int **matr, nrow, ncol;

public:
  // Constructors
  myMatrix()
  {
    matr = nullptr;
    nrow = ncol = 0;
  }

  myMatrix(int r, int c, int val = 0)
  {
    nrow = r;
    ncol = c;
    matr = new int *[r];
    for (int i = 0; i < r; i++)
    {
      matr[i] = new int[c];
      for (int j = 0; j < c; j++)
        matr[i][j] = val;
    }
  }

  myMatrix(const myMatrix &obj)
  {
    matr = new int *[obj.nrow];
    for (int i = 0; i < obj.nrow; i++)
    {
      matr[i] = new int[obj.ncol];
      for (int j = 0; j < obj.ncol; j++)
        matr[i][j] = obj.matr[i][j];
    }
  }

  // Methods

  myMatrix add(const myMatrix &obj)
  {
    // TODO: If rows and columns are equal, do addition
    myMatrix output(*this);
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] += obj.matr[i][j];
    return output;
  }

  myMatrix mul(const myMatrix &obj)
  {
    // TODO: Check if number is 0?
    // TODO: If rows and columns are equal, do multiplication
    myMatrix output(*this);
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] *= obj.matr[i][j];
    return output;
  }

  myMatrix mul(int scalar)
  {
    // TODO: If rows and columns are equal, do multiplication
    myMatrix output(*this);
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] *= scalar;
    return output;
  }

  const myMatrix &mulAndUpdate(int scalar)
  {
    // TODO: If rows and columns are equal, do multiplication
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j] *= scalar;
    return *this;
  }

  const myMatrix pre_increment()
  {
    myMatrix output(*this);
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        ++output.matr[i][j];
    return output;
  }

  myMatrix post_increment()
  {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j]++;
    return *this;
  }

  const myMatrix &negate()
  {
    // TODO: No need to multiply with -1, if the entry is 0
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j] *= -1;
    return *this;
  }

  const myMatrix &transpose()
  {
    // TODO: order check
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if (i != j)
          swap(matr[i][j], matr[j][j]);

    return *this;
  }

  const myMatrix &assign(const myMatrix &obj)
  {
    this->matr = obj.matr;
    this->nrow = obj.nrow;
    this->ncol = obj.ncol;
    return *this;
  }

  // TODO: Implementation
  bool submatrix(const myMatrix &obj);

  bool isIdentity()
  {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if ((matr[i][j] != 1) && (matr[j][i] != 0))
          return 0;
    return 1;
  }

  // Getters and Setters
  int getRows() { return nrow; }
  int getCols() { return ncol; }
  int getElement(int r, int c)
  {
    if (matr[r][c])
      return matr[r][c];
    return 0;
  }

  // TODO: Element within indices (rows and columns)?
  void setElement(int r, int c, int val) { matr[r][c] = val; }
  // Destructor

  ~myMatrix()
  {

    for (int i = 0; i < nrow; i++)
      if (matr[i])
        delete[] matr[i];

    if (matr)
    {
      delete[] matr;
      matr = nullptr;
    }
  }
};

myMatrix readMatrix(char filename[])
{
  ifstream fin(filename);
  int r, c, rc, cc;
  rc = cc = 0;
  fin >> r;
  fin >> c;
  fin.ignore();

  myMatrix obj(r, c, 0);
  // cout << "Row Count: " << obj.getRows();
  char temp[200];
  int num;

  while (fin.getline(temp, 200))
  {
    for (int i = 0; temp[i] != 0; i++)
    {
      if (temp[i] != ' ' && temp[i] != '\n')
      {
        num = temp[i] - 48;
        obj.setElement(rc, cc++, num);
      }
    }
    cc = 0; // Reset Column Count
    rc++;   // New line indicates a new row
  }
  return obj;
}

void printMatrix(myMatrix &obj)
{
  cout << "Matrix is : \n\n";
  int r = obj.getRows(), c = obj.getCols();
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
      cout << " " << obj.getElement(i, j) << "\t";
    cout << "\n";
  }
}

int main()
{
  char fn[] = "test.txt";
  myMatrix stream = readMatrix(fn);
  printMatrix(stream);
}