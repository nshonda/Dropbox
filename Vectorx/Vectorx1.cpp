#include <cstdlib>
#include <iostream>
#include <exception>
#include <stdexcept>
#define standard 20

using namespace std;
template <class T>
class Vectorx
{
    int capacityx;
    int sizex;
    T* vet;
public:
    typedef T * iterator;
    Vectorx()
    {
        capacityx=0;
        sizex=0;
        reserve(standard);
    };
    Vectorx& operator=(Vectorx& other)
    {
        T* oldvet;
        oldvet=vet;
        delete[] oldvet;
        vet= new T[other.capacity()];
        for(int i=0;i<other.capacity();i++)
        {
            vet[i]=other.vet[i];
        }
        capacityx=other.capacityx;
        sizex=other.sizex;
    };
    T operator[](int n)
    {
        return vet[n];
    };
    iterator begin()
    {
        return vet;
    };
    iterator end()
    {
        return vet+size();
    };
    int size()
    {
        return sizex;
    };
    int capacity()
    {
        return capacityx;
    };
    bool empty()
    {
        if(size() == 0)
            return 1;
        else
            return 0;
    };
    void reserve(int n)
    {
        T* oldvet = vet;
        int oldsize;
        if(oldvet == NULL)
        {
            oldsize=0;
        }
        else oldsize= capacityx;
        T* newvet = new T[oldsize + n];
        int newsize = oldsize + n;
        for(int i=0; i < newsize; i++)
        {
            if(i < oldsize)
            {
                newvet[i] = oldvet[i];
            }
            else newvet[i] = NULL;
        }
        if (oldvet != NULL) {
            delete[] oldvet;
        }
        capacityx = newsize;
        vet = newvet;
    };
    T at(int n)
    {
        try
        {
            if(n >= size())
                throw std::out_of_range ("out_of_range");
            return vet[n];
        }
        catch(std::out_of_range oor)
        {
            cout<<"exception "<<oor.what()<<" occured \n";
        };
    };
    T& front()
    {
        return vet[0];
    };
    T& back()
    {
        int i = size();
        i--;
        return vet[i];
    };
    void push_back(const T& x)
    {
        if(size() == capacity())
        {
            reserve(standard);
        }
        T* p = &back();
        p++;
        *p = x;
        sizex++;

    };
    void pop_back()
    {
        if(size() != 0)
        {
            T* p = &back();
            *p = NULL;
            sizex--;
        }
        else cout<<"empty vector\n";
    };
    void clear()
    {
        delete[] vet;
        vet = NULL;
        capacityx=0;
        sizex=0;
        reserve(standard);
    };
    void pop_front()
    {
        if(size() != 0)
        {
            for(int i=1;i<size()+1;i++)
            {
                vet[i-1] = vet[i];
            }
            sizex--;
        }
        else cout<<"empty vector\n";
    };
    void insertAt(int n,const T& x)
    {
        if(size() == capacity())
        {
            reserve(standard);
        }
        if(vet[n]!= NULL)
        {
            for(int i = size();i>n-1;i--)
            {
                vet[i+1] = vet[i];
            }
            vet[n] = x;
        }
        else vet[n] = x;
        sizex++;
    };
};

 int main(int argc, char *argv[])
{
    Vectorx<int> Y;
    Vectorx<int> Z;
    Vectorx<int>::iterator it;
    int j=0,k=0;
    for(int i=0;i<20;i++)
    {
        j=j+5;
        k++;
        Y.push_back(i+j+k);
    }
    for(int i=0;i<10;i++)
        Z.push_back(i);
    cout<<"Vector Y:";
    for(it = Y.begin(); it != Y.end(); it++)
    {
        cout<<" "<<*it<<" ";
    }
    cout << "\nSize(Y): "<< Y.size();
    cout << "\nCapacity(Y): "<< Y.capacity();
    cout << "\n";
    cout<<"Vector Z:";
    for(it = Z.begin(); it != Z.end(); it++)
    {
        cout<<" "<<*it<<" ";
    }
    cout << "\nSize(Z): "<<Z.size();
    cout << "\nCapacity(Z): "<<Z.capacity();
    cout << "\n";
    Z=Y;
    cout<<"Z = Y";
    cout<<"Vector Z:";
    for(it = Z.begin(); it != Z.end(); it++)
    {
        cout<<" "<<*it<<" ";
    }
    cout << "\nSize(Z): "<<Z.size();
    cout << "\nCapacity(Y): "<<Z.capacity();
    cout << "\n";
    cout << "Clear Z: ";
    Z.clear();
    if(Z.empty()==1)
        cout << "Empty";
    cout << "\nY[0]: " << Y[0] << "\nY[15]:" << Y[15];
    cout << "\nY.at(0): " << Y.at(0) << "\nY.at(15):" << Y.at(15);
    cout << "\nY.reserve(50)";
    Y.reserve(50);
    cout << "\nSize(Y): "<< Y.size();
    cout << "\nCapacity(Y): "<< Y.capacity();
    cout << "\n";
    for(int i=0;i<10;i++)
    {
        Y.push_back(i);
    }
    for(it = Y.begin(); it != Y.end(); it++)
    {
        cout<<" "<<*it<<" ";
    }
    cout << "\n" << "Front: " << Y.front();
    cout << "\n" << "Back: " << Y.back();
    cout << "\n" << "Pop_Back Pop_Front\n";
    Y.pop_front();
    Y.pop_back();
    cout<<"Vector Y:";
    for(it = Y.begin(); it != Y.end(); it++)
    {
        cout<<" "<<*it<<" ";
    }
    cout << "\nInsertAt(4,60):\n";
    Y.insertAt(4,60);
    cout<<"Vector Y:";
    for(it = Y.begin(); it != Y.end(); it++)
    {
        cout<<" "<<*it<<" ";
    }
    Y.clear();
    system("PAUSE");
    return EXIT_SUCCESS;
}
