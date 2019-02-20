#include <fstream>
#include <iostream>

// TODO: Error Handling, Code testing

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
    matr = new int *[r];
    for (i = 0; i < r; i++)
    {
      matr[i] = new int[c];
      for (j = 0; j < c; j++)
        matr[i][j] = val;
    }
  }

  myMatrix(const myMatrix &obj)
  {
    matr = new int[obj.r];
    for (i = 0; i < obj.r; i++)
    {
      matr[i] = new int[obj.c];
      for (j = 0; j < obj.c; j++)
        matr[i][j] = obj.matr[i][j];
    }
  }

  // Methods

  myMatrix add(const myMatrix &obj)
  {
    // TODO: If rows and columns are equal, do addition
    myMatrix output(this);
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        output.matr[i][j] += obj.matr[i][j];
    return output;
  }

  myMatrix mul(const myMatrix &obj)
  {
    // TODO: Check if number is 0?
    // TODO: If rows and columns are equal, do multiplication
    myMatrix output(this);
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        output.matr[i][j] *= obj.matr[i][j];
    return output;
  }

  myMatrix mul(int scalar)
  {
    // TODO: If rows and columns are equal, do multiplication
    myMatrix output(this);
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        output[i][j] *= scalar;
    return output;
  }

  const myMatrix &mulAndUpdate(int scalar)
  {
    // TODO: If rows and columns are equal, do multiplication
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        matr[i][j] *= scalar;
    return matr;
  }

  const myMatrix &pre_increment()
  {
    myMatrix output(this);
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        ++output[i][j];
    return output;
  }

  myMatrix post_increment()
  {
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        matr[i][j]++;
    return matr;
  }

  const myMatrix &negate()
  {
    // TODO: No need to multiply with -1, if the entry is 0
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        mat[i][j] *= -1;
    return mat;
  }

  const myMatrix &transpose()
  {
    // TODO: order check
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        if (i != j)
          swap(mat[i][j], mat[j][j]);

    return mat;
  }

  const myMatrix &assign(const myMatrix &obj)
  {
    this->matr = obj.matr;
    this->nrows = obj.nrows;
    this->ncols = obj.ncols;
    return this;
  }

  // TODO: Implementation
  bool submatrix(const myMatrix &obj);

  bool isIdentity()
  {
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        if ((mat[i][j] != 1) && (mat[j][i] != 0))
          return 0;
    return 1;
  }

  // Getters and Setters
  int getRows() { return nrows; }
  int getCols() { return ncols; }
  int getElement(int r, int c)
  {
    if (matr[r][c])
      return matr[r][c];
    return 0;
  }

  // TODO: Element within indices (rows and columns)?
  int setElement(int r, int c, int val) { mat[r][c] = val; }

  // Destructor
  ~myMatrix()
  {

    for (i = 0; i < nrows; i++)
      if (mat[i])
        delete[] mat[i];

    if (mat)
    {
      delete[] mat;
      mat = nullptr;
    }
  }
};

myMatrix readMatrix(char filename[]) { ifstream fin(filename); }

void printMatrix(const myMatrix &obj)
{
  cout << "\n Matrix is : \n\n";
  for (int i = 0; i < obj.nrows; i++)
  {
    for (int j = 0; j < obj.ncols; j++)
      cout << " " << a[i][j] << "\t";
    cout << "\n";
  }
}