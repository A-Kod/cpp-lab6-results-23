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
private:
    
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
template <class T>
class Matrix
{
private:
    int line, column;
    
    friend Complex;
   // friend Iterator;
public:
    
//    typedef Matrix<int> iterator;
//    typedef Matrix<const int> const_iterator;
    T** ptr;
    class Iterator
    {
        T**& ptr;
    public:
//        Iterator()
//        {
//            //ptr = nullptr;
//        }
        Iterator(T**& pv)
        {
            ptr = pv;
        }
        int operator *() const
        {
            return *ptr;
        }
        Iterator operator ++(int)
        {
            int *temp = ptr;
            return ++temp;
        }
    };

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

    // copy ctor
    Matrix (const Matrix &obj)
    {
        ptr = new T*[obj.line];
        
        for (int i=0;i<line;i++)
        {
            ptr[i] = new T[obj.column];
            for(int j=0;j<column;j++)
                ptr[i][j]=obj.ptr[i][j];
        }
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
    
    ~Matrix ()
    {
        for (int i=0;i<line;i++)
            delete[] (ptr[i]);
        delete[] (ptr);
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
    
    Matrix operator| (Matrix matrix2)
    {
        //if (_countof(matrix1) != _countof(matrix2.matrix1)) return NULL;
        
        
        
        
        T **sum = new T *[line];
        for (int i = 0; i < line; i++)
        {
            sum[i] = new T[column+matrix2.column];
        }
        
        
        
        
        for (int i = 0; i < line; i++)
        {
            for (int j = 0; j < column; j++)
            {
                
                sum[i][j] = ptr[i][j];
                
            }
            
            for (int j = 3; j < column+matrix2.column; j++)
            {
                
                sum[i][j] = matrix2.ptr[i][j-column];
                
            }
            
            
        }
        
        
        Matrix m;
        m.setplus(sum, matrix2.m);
        return m;
    }
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
};


int main(int argc, const char * argv[])
{
    Complex a (5, 2);
    Complex b (3, -3);
    cout << "a = " << a << "; b =" << b << endl;
    cout << "a+=b: "<< endl;
    a += b;
    cout << "a = " << a << "; b =" << b << endl;
    Complex c = a + b;
    Complex d = c * b;
    cout << "d = c * b" << d << endl;
    cout << "c=" << c << endl;
    cout << "a + b" << a + b << endl;
    cout << "a * b" << a * b << endl;
    cout << endl << "first  = " << endl;
    Matrix <Complex>first (2,2);
    first.ptr[0][0] = a;
    first.ptr[0][1] = b;
    first.ptr[1][0] = c;
    first.ptr[1][1] = d;
    first.printme();
    cout << endl << "second = " << endl;
    Matrix <Complex>second(2, 2);
    second.ptr[0][0] = d;
    second.ptr[0][1] = c;
    second.ptr[1][0] = b;
    second.ptr[1][1] = a;
    second.printme();
    cout << endl << "sum = " << endl;
    Matrix <Complex>sum = first + second;
    sum.printme();
    cout <<endl <<endl << "proizvedenie = "<<endl;
    Matrix <Complex>proizvedenie = first * second;
    proizvedenie.printme();
    cout << endl << endl << "transposition sum " <<endl;
    Matrix <Complex>transpon = sum.transp();
    transpon.printme();
    cout << endl << endl << endl;
    Matrix <Complex>third (3,3);
    third.ptr[0][0] = a;
    third.ptr[0][1] = b;
    third.ptr[0][2] = c;
    third.ptr[1][0] = d;
    third.ptr[1][1] = a;
    third.ptr[1][2] = b;
    third.ptr[2][0] = c;
    third.ptr[2][1] = d;
    third.ptr[2][2] = d;
    cout<<"exceptions!"<<endl<<endl;
    Matrix <Complex>sum2 = first + third;
    Matrix <Complex>proizvedenie2 = first * third;
    Matrix <int> proba;
    cout<<"------------"<<endl;
    proba.ptr[0][0] = 1;
    proba.ptr[0][1] = 2;
    proba.ptr[1][0] = 3;
    proba.ptr[1][1] = 4;
    proba.printmee();
    Matrix <int> test;
    cout<<"------------"<<endl;
    test.ptr[0][0] = 5;
    test.ptr[0][1] = 6;
    test.ptr[1][0] = 7;
    test.ptr[1][1] = 8;
    test.printmee();
    Matrix <int> probrproisv = proba*test;
    cout<<"--------";
    probrproisv.printmee();
    return 0;
}