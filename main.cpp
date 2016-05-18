#include <iostream>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//class Iterator
//{
//private:
//    int index;
//}
//class Iterator
//{
//private:
//    friend Matrix;
//public:
//    Iterator()
//    {
//        ptr = nullptr;
//    }
//    Iterator(int *pv)
//    {
//        ptr = pv;
//    }
//    int operator *() const
//    {
//        return *ptr;
//    }
//    Iterator operator ++(int)
//    {
//        int *temp = ptr;
//        return ++temp;
//    }
//};

class Error  //exist but not used
{
private:
    int code;
public:
    Error(int i) : code(i){};
    ~Error(){};
};
//template <class T>

class Complex
{
    //private:
public:
    double re, im;
    Complex ()
    {
        re = 0;
        im = 0;
    };
    //only Rez
    Complex (double r)
    {
        re = r;
        im = 0;
    }
    //Rez & Imz
    Complex (double r, double i)
    {
        re = r;
        im = i;
    }
    
    void show ()
    {
        cout<<re<<endl;
        cout<<im<<endl;
    }
    
    //copy ctor
    Complex (const Complex &c)
    {
        re = c.re;
        im = c.im;
    }
    
    ~Complex ()
    {
    }
    
    //OVERLOADs
    
    Complex& operator += (Complex &c)
    {
        re += c.re;
        im += c.im;
        return *this;
    }
    
    Complex operator + (const Complex &c)
    {
        return Complex (re + c.re, im + c.im);
    }
    
    Complex operator - (const Complex &c)
    {
        return Complex(re - c.re, im - c.im);
    }
    
    Complex operator * (const Complex &c)
    {
        return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
    }
    
    
    
    //friends
    friend ostream & operator<< (ostream &, const Complex &);
    friend istream & operator>> (istream &, Complex &);
    
};

// overload <<
ostream& operator<< (ostream &out, const Complex &c)
{
    out << "(" << c.re << ", " << c.im << ")";
    return out;
}


// overload >>
istream& operator>> (istream &in, Complex &c)
{
    in >> c.re >> c.im;
    return in;
}

//Complex null (0,0);
//int zero=0;
//template <class U>
template <class T>
class Matrix
{
private:
    int line, column;
    T** ptr;
    friend Complex;
    T null;
    // friend Iterator;
public:
    //    typedef Matrix<int> iterator;
    //    typedef Matrix<const int> const_iterator;
    class Iterator : public std::iterator<std::input_iterator_tag, T>
    {
    private:
        T** DAT;
        size_t nCount;
        size_t mCount;
        size_t indx;
    public:
        
        Iterator(T** data, size_t n, size_t m, size_t index) :DAT(data), nCount(n), mCount(m), indx(index) { }
        Iterator(const Iterator& it) : DAT(it.DAT), nCount(it.nCount), mCount(it.mCount), indx(it.indx) { }
        bool operator==(const Iterator& it) const
        {
            return indx == it.indx;
        }
        bool operator!=(const Iterator& it) const
        {
            return !(*this == it);
        }
        Iterator& operator++()
        {
            ++indx; return *this;
        }
        Iterator& operator++(int)
        {
            indx++; return *this;
        }
        Iterator operator+(size_t ind)
        {
            if (indx + ind >= nCount*mCount)
                throw std::out_of_range("out_of_range");
            indx += ind;
            return *this;
        }
        T& operator*() const
        {
            if (indx >= nCount*mCount)
                throw std::out_of_range("out_of_range");;
            return DAT[indx / mCount][indx % mCount];
        }
        
    };
    Iterator begin() { return Iterator(ptr, line, column, 0); }
    Iterator end() { return Iterator(ptr, line, column, line*column); }
    size_t get_line() const { return line; }
    size_t get_column() const { return column; }
    T** getMatrix() const { return ptr; }
    T operator()(size_t npos, size_t mpos) const;
    
    friend std::ostream & operator<<(std::ostream & out, Matrix<T> & matr)
    {
        for (int i = 0; i < matr.line; i++)
        {
            for (int j = 0; j < matr.column; j++)
                out << matr.ptr[i][j] << "  ";
            out << "\n";
        }
        return out;
    }
    //Matrix(const Matrix<T>& matr);
    //  T** ptr;
    //    class Iterat
    //    {
    //        T**& ptr;
    //    public:
    //        //        Iterator()
    //        //        {
    //        //            //ptr = nullptr;
    //        //        }
    //        Iterat(T**& pv)
    //        {
    //            ptr = pv;
    //        }
    //        int operator *() const
    //        {
    //            return *ptr;
    //        }
    //        Iterat operator ++(int)
    //        {
    //            int *temp = ptr;
    //            return ++temp;
    //        }
    //    };
    
    Matrix (int n, int m)
    {
        line = m;
        column = n;
        ptr = new T *[n];
        for (int i = 0; i < n; ++i)
            ptr[i] = new T[m];
    }
    Matrix ()
    {
        line = 2;
        column = 2;
        ptr = new T *[line];
        for (int i = 0; i < line; ++i)
            ptr[i] = new T[column];
    }
    Matrix(const Matrix& matr)
    {
        ptr= new T*[matr.line];
        for (int i = 0; i < matr.line; i++)
            ptr[i] = new T[matr.column];
        line = matr.line;
        column = matr.column;
        for (int i = 0; i < line; i++)
            for (int j = 0; j < column; j++)
                ptr[i][j] = matr.ptr[i][j];
    }
    Matrix(T** matr, size_t lines, size_t columns)
    {
        ptr = new T*[lines];
        for (int i = 0; i < lines; i++)
            ptr[i] = new T[columns];
        for (int i = 0; i < lines; i++)
            for (int j = 0; j < columns; j++)
                ptr[i][j] = matr[i][j];
        line = lines;
        column = columns;
    }
    //    Matrix(const Matrix& matr)
    //    {
    //        ptr = new T*[matr.getRows()];
    //        for (int i = 0; i < matr.getRows(); i++)
    //            ptr[i] = new T[matr.getColumns()];
    //        line = matr.getRows();
    //        column = matr.getColumns();
    //        for (int i = 0; i < _rows; i++)
    //            for (int j = 0; j < _columns; j++)
    //                ptr[i][j] = static_cast<T>(matr.getMatrix()[i][j]);
    //    }
    
    
    //    Matrix()
    //    {
    //        ptr =0; line = 0; column = 0;
    //    }
    // copy ctor
    //    Matrix (const Matrix &obj)
    //    {
    //        ptr = new T*[obj.line];
    //
    //        for (int i=0;i<line;i++)
    //        {
    //            ptr[i] = new T[obj.column];
    //            for(int j=0;j<column;j++)
    //                ptr[i][j]=obj.ptr[i][j];
    //        }
    //    }
    
    void setNull(T nul)
    {
        null = nul;
    }
    Matrix operator|(const Matrix/*<T>*/ & matr) const
    {
        if (line != matr.line)
            throw std::logic_error("Error in concatenation of matrixes.");
        Matrix<T> result(line, column + matr.column, null);
        int j;
        for (int i = 0; i < line; i++)
        {
            for (j = 0; j < column; j++)
                result.ptr[i][j] = ptr[i][j];
            for (int k = 0; k < matr.columns; k++)
                result.ptr[i][k + j] = matr.ptr[i][k];
        }
        return result;
    }
    
    Matrix transp() {
        Matrix matr(line, column);
        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                matr.ptr[i][j] = ptr[j][i];
            }
        }
        return matr;
    }
    
    
    
    T & operator () (unsigned int m, unsigned  int n)
    {
        try
        {
            if ((m > line) && (n > column))
                throw 123;
        }
        catch (int i)
        {
            if (i == 123)
                cout<<"EGGOG №" << i << " going beyond the area of matrix indexes " << endl;
        }
        return (ptr[m][n]);
    }
    
    
    Matrix operator + (const Matrix& m) const
    {
        
        try
        {
            if ((m.line != line) && (m.column!= column))
                throw 666;
        }
        catch (int i)
        {
            if (i == 666)
                cout<<"EGGOG №" << i << " Matrices of different sizes " << endl;
        }
        
        Matrix matr (m.line, m.column);
        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                matr.ptr[i][j] = ptr[i][j] + m.ptr[i][j];
            }
        }
        return matr;
    }
    
    Matrix operator * (const Matrix& m) const
    {
        
        
        try
        {
            if ((line != m.column))
                throw 13;
        }
        catch (int i)
        {
            if (i == 13)
                cout<<"EGGOG №" << i << " Matrices can not multiplied " << endl;
        }
        
        Matrix matr(line, m.column);
        //if (typeid(matr.ptr[0][0])==typeid(Complex))
        
        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            { matr.ptr[i][j]=0; }
        };
        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                for (int k = 0; k < column; ++k)
                {
                    matr.ptr[i][j] = matr.ptr[i][j] + ptr[i][k] * m.ptr[k][j];
                }
            }
        }
        
        
        return matr;
    }
    
    //    Matrix operator| (Matrix matrix2)
    //    {
    //        //if (_countof(matrix1) != _countof(matrix2.matrix1)) return NULL;
    //
    //
    //
    //
    //        T **sum = new T *[line];
    //        for (int i = 0; i < line; i++)
    //        {
    //            sum[i] = new T[column+matrix2.column];
    //        }
    //
    //
    //
    //
    //        for (int i = 0; i < line; i++)
    //        {
    //            for (int j = 0; j < column; j++)
    //            {
    //
    //                sum[i][j] = ptr[i][j];
    //
    //            }
    //
    //            for (int j = 3; j < column+matrix2.column; j++)
    //            {
    //
    //                sum[i][j] = matrix2.ptr[i][j-column];
    //
    //            }
    //
    //
    //        }
    //
    //
    //        Matrix m;
    //        m.setplus(sum, matrix2.m);
    //        return m;
    //    }
    

    void printme()
    {
        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                cout << "(" << ptr[i][j].re << "," << ptr[i][j].im << ")" << "     ";
            }
            cout << endl;
        }
    }
    void printmee()
    {
        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                cout << "(" << ptr[i][j] << ")" << "     ";
            }
            cout << endl;
        }
    }
    //    iterator begin()
    //    {
    //    //return iterator(data.get());
    //    }
    //    iterator end();
    //
    //    const_iterator begin() const;
    //    const_iterator end() const;
    ~Matrix ()
    {
        for (int i=0;i<line;i++)
            delete[] (ptr[i]);
        delete[] (ptr);
    }
    
};

using namespace std;
using namespace placeholders;

void add_Num(int& num, int j)
{
    num += j;
}
void add_Indx(int& number, int& indx)
{
    number += indx++;
}

bool less_than(int number, int granica)
{
    return number < granica;
}

bool square_sol(int x, int a, int b, int c)
{
    return a*x*x + b*x + c == 0;
}
bool linear_sol(int x, int k, int b)
{
    return k*x + b == 0;
}
int main(int argc, const char * argv[])
{
    Complex a_compl (5, 2);
    Complex b_compl (3, -3);
    int** matr1 = new int*[2];
    for (int i = 0; i<2; i++)
        matr1[i] = new int[2];
    int** matr2 = new int*[2];
    for (int i = 0; i<2; i++)
        matr2[i] = new int[1];
    
    matr1[0][0] = -1;
    matr1[0][1] = 0;
    matr1[1][0] = 1;
    matr1[1][1] = 2;
    
    matr2[0][0] = 1;
    matr2[1][0] = 2;
    
    Matrix<int> c_matr1(matr1, 2, 2);
    Matrix<int> c_matr2(matr2, 2, 1);
    cout << "a = " << a_compl << "; b =" << b_compl << endl;
    cout << "a+=b: "<< endl;
    a_compl += b_compl;
    cout << "a = " << a_compl << "; b =" << b_compl << endl;
    Complex c_compl = a_compl + b_compl;
    Complex d_compl = c_compl * b_compl;
    cout << "d = c * b" << d_compl << endl;
    cout << "c=" << c_compl << endl;
    cout << "a + b" << a_compl + b_compl << endl;
    cout << "a * b" << a_compl * b_compl << endl;
    cout << endl << endl << endl;
    //Algorithm
    int granica = 3;
    int y = 1, z = 0;
    int a = 1, b = 0, c = -4, value = 0, num = 3;
    // Складываем каждый элемент матрицы
    for_each(c_matr2.begin(), c_matr2.end(), bind(add_Num, _1, a));
    cout << c_matr2 << endl;
    // Складываем каждый элемент матрицы с порядковым номером
    for_each(c_matr2.begin(), c_matr2.end(), bind(add_Indx, _1, 0));
    cout << c_matr2 << endl;
    // Находим кол-во элементов в матрице, равных заданному числу
    cout << count(c_matr1.begin(), c_matr1.end(), num) << endl;
    //kx + b = 0
       cout << count_if(c_matr1.begin(), c_matr1.end(), bind(linear_sol, _1, y, z)) << endl;
    //Кол-во элементов в матрице меньше числа
    cout << count_if(c_matr1.begin(), c_matr1.end(), bind(less_than, _1, granica)) << endl;
    //ax^2 + bx + c = 0
       cout << *find_if(c_matr1.begin(), c_matr1.end(), bind(square_sol, _1, a, b, c)) << endl;
    //Поиск заданного элемента???
    cout << *find(c_matr1.begin(), c_matr1.end(), value) << endl;
    //   Matrix <Complex>first (2,2);
    //    first.ptr[0][0] = a;
    //    first.ptr[0][1] = b;
    //    first.ptr[1][0] = c;
    //    first.ptr[1][1] = d;
    //    first.printme();
    //    cout << endl << "second = " << endl;
    ///  Matrix <Complex>second(2, 2);
    //    second.ptr[0][0] = d;
    //    second.ptr[0][1] = c;
    //    second.ptr[1][0] = b;
    //    second.ptr[1][1] = a;
    // second.printme();
    //    cout << endl << "sum = " << endl;
    /// Matrix <Complex>sum = first + second;
    // sum.printme();
    //    cout <<endl <<endl << "proizvedenie = "<<endl;
    //    Matrix <Complex>proizvedenie = first * second;
    //    proizvedenie.printme();
    //    cout << endl << endl << "transposition sum " <<endl;
    //    Matrix <Complex>transpon = sum.transp();
    //    transpon.printme();
    //    cout << endl << endl << endl;
    //    Matrix <Complex>third (3,3);
    //    third.ptr[0][0] = a;
    //    third.ptr[0][1] = b;
    //    third.ptr[0][2] = c;
    //    third.ptr[1][0] = d;
    //    third.ptr[1][1] = a;
    //    third.ptr[1][2] = b;
    //    third.ptr[2][0] = c;
    //    third.ptr[2][1] = d;
    //    third.ptr[2][2] = d;
    //    cout<<"exceptions!"<<endl<<endl;
    //    Matrix <Complex>sum2 = first + third;
    //    Matrix <Complex>proizvedenie2 = first * third;
    //    Matrix <int> proba;
    //    cout<<"------------"<<endl;
    //    proba.ptr[0][0] = 1;
    //    proba.ptr[0][1] = 2;
    //    proba.ptr[1][0] = 3;
    //    proba.ptr[1][1] = 4;
    //    proba.printmee();
    //    Matrix <int> test;
    //    cout<<"------------"<<endl;
    //    test.ptr[0][0] = 5;
    //    test.ptr[0][1] = 6;
    //    test.ptr[1][0] = 7;
    //    test.ptr[1][1] = 8;
    //    test.printmee();
    //    Matrix <int> probrproisv = proba*test;
    //    cout<<"--------";
    //    probrproisv.printmee();
    return 0;
}