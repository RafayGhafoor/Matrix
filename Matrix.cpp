#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

class myMatrix
{

private:
  int **matr, nrow, ncol;

public:
  // ***Constructors***

  // *Default Constructor
  myMatrix()
  {
    matr = nullptr;
    nrow = ncol = 0;
  }

  // *Parametric Constructor
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

  // *Deep Copy Constructor
  myMatrix(const myMatrix &obj)
  {
    nrow = obj.nrow;
    ncol = obj.ncol;

    matr = new int *[obj.nrow];

    for (int i = 0; i < obj.nrow; i++)
    {
      matr[i] = new int[obj.ncol];
      for (int j = 0; j < obj.ncol; j++)
        matr[i][j] = obj.matr[i][j];
    }
  }

  // *Methods
  const myMatrix add(const myMatrix &obj)
  {
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

  myMatrix mul(const myMatrix &obj)
  {
    if ((this->nrow != obj.nrow) || (this->ncol != obj.ncol))
      return *this;

    // 4 12
    // 12 24
    myMatrix output(nrow, ncol, 0);
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)

        for (int k = i; k < obj.nrow; k++)
          output.matr[i][j] += this->matr[i][j] * obj.matr[k][i];

    return output;
  }

  myMatrix mul(int scalar)
  {
    myMatrix output(*this);

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        output.matr[i][j] *= scalar;

    return output;
  }

  const myMatrix &mulAndUpdate(int scalar)
  {
    if (!scalar)
    {
      for (int i = 0; i < nrow; i++)
        matr[i] = {0};
      return *this;
    }

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j] *= scalar;

    return *this;
  }

  const myMatrix &pre_increment()
  {

    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j] += 1;

    return *this;
  }

  const myMatrix post_increment()
  {
    myMatrix temp(*this);
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        matr[i][j]++;

    return temp;
  }

  const myMatrix &negate()
  {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if (matr[i][j] != 0)
          matr[i][j] *= -1;

    return *this;
  }

  const myMatrix &transpose()
  {
    myMatrix temp(ncol, nrow, 0);
    for (int i = 0; i < ncol; i++)
      for (int j = 0; j < nrow; j++)
        temp.matr[i][j] = matr[j][i];
    assign(temp);
    return *this;
  }

  const myMatrix &assign(const myMatrix &obj)
  {
    this->matr = new int *[obj.nrow];

    for (int i = 0; i < obj.nrow; i++)
    {
      this->matr[i] = new int[obj.ncol];
      for (int j = 0; j < obj.ncol; j++)
        this->matr[i][j] = obj.matr[i][j];
    }

    this->nrow = obj.nrow;
    this->ncol = obj.ncol;

    return *this;
  }

  bool submatrix(const myMatrix &obj)
  {
    int s_row, s_col,
        match_count = 0; // Declaration of start row and start column

    if ((obj.nrow > nrow) ||
        (obj.ncol > ncol)) // object is super - matrix (not a submatrix)
      return 0;

    for (int i = 0, j = 0, x = 0, y = 0; i < nrow && j < ncol; i++, j++)
    {
      if (obj.matr[x][y++] == matr[i][j])
        return 0;
      y = 0;
    }
    return 1;
  }

  bool isIdentity()
  {
    for (int i = 0; i < nrow; i++)
      for (int j = 0; j < ncol; j++)
        if ((matr[i][j] != 1) && (matr[j][i] != 0))
          return 0;

    return 1;
  }

  // Getters and Setters
  int getRows() const { return nrow; }

  int getCols() const { return ncol; }

  int getElement(int r, int c) const
  {
    if ((matr[r][c] && r < this->nrow) && (c < this->ncol))
      return matr[r][c];

    return 0;
  }

  void setElement(int r, int c, int val)
  {
    if ((r < this->nrow) &&
        (c < this->ncol)) // bound check for rows and columns for matrix
      matr[r][c] = val;
  }

  // Destructor
  ~myMatrix()
  {
    if (matr)
    {
      for (int i = 0; i < nrow; i++)
        if (matr[i])
          delete[] matr[i];

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
  int n;

  while (fin >> n)
  {
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

void printMatrix(const myMatrix &obj)
{
  cout << "Matrix is : \n\n";
  int r = obj.getRows(), c = obj.getCols();

  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
      cout << " " << obj.getElement(i, j);
    cout << "\n";
  }
}

int main()
{
  char name[] = "test.txt";
  myMatrix *a = new myMatrix();
  myMatrix *b = new myMatrix(3, 3, 3);
  myMatrix *c = new myMatrix(readMatrix(name));
  myMatrix *d = new myMatrix(3, 3, 1);

  cout << "Matrix B:\n";
  printMatrix(*b);
  cout << "\n\n"
       << endl;

  cout << "Matrix C:\n";
  printMatrix(*c);
  cout << "\n\n"
       << endl;

  cout << "B add C:\n";
  printMatrix(b->add(*c));

  cout << "B mul 2:\n";
  printMatrix((b->mul(2)));

  cout << "B mul C:\n";
  printMatrix((b->mul(*c)));

  cout << "B mul and update 2:\n";
  printMatrix(b->mulAndUpdate(2));

  cout << "D Pre, post increment:\n";
  d->pre_increment();
  printMatrix(*d);
  d->post_increment();
  printMatrix(*d);

  cout << "D is ID:\n";
  cout << d->isIdentity();

  cout << "\nD negate:\n";
  printMatrix(d->negate());

  cout << "D transpose:\n";
  printMatrix(d->transpose());

  // check assign manually

  // cout << "SubMatrix:\n";
  // cout << d->submatrix(*a);

  cout << "getRows:";
  cout << d->getRows() << endl;

  cout << "getCols:";
  cout << d->getCols() << endl;

  cout << "getElement:";
  cout << d->getElement(1, 1) << endl;

  cout << "setElement:";
  d->setElement(1, 1, -5);
}