#include <cstdlib>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <functional>
#include <time.h>
#define standard 10000

using namespace std;
class Pessoa
{
  public:
    unsigned long long id;
    string nome;
    string endereco;
    Pessoa()
    {
      id=NULL;
      nome='HARRY JAMES POTTER, THE BOY WHO LIVED';
      endereco='THE CUPBOARD UNDER THE STAIRS, NUMBER 4, PRIVET DRIVE, LITTLE WHINING, SURREY';
    }
    bool operator < (const Pessoa &x) const
    {
      return id < x.id;
    };
    bool operator <= (const Pessoa &x) const
    {
      return id <= x.id;
    };
    bool operator > (const Pessoa &x) const
    {
      return id > x.id;
    };
    Pessoa& operator =(const Pessoa &x)
    {
      id=x.id;
    };
};



template<class T>
class Vectorx
{
    int capacityx;
    int sizex;
    T* vet;
    //Comp comparator;

public:
    typedef T * iterator;
    Vectorx()
    {
        vet=NULL;
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
            //else newvet[i] = NULL;
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
    void swap(int i,int j)
    {
      T aux;
      aux=vet[i];
      vet[i]=vet[j];
      vet[j]=aux;

    };
    void InsertionSort()
    {
      int i,j,k;
      for(i=1;i < size();i++)
      {
        j=0;
        while(vet[j] < vet[i] && j<i)
        {
          j++;
        };
        for(k=i;k>j;k--)
        {
          swap(k,k-1);
        }
      }
    };
    void BubbleSort()
    {
      int i,j;
      for(i=size()-1;i > -1;i--)
      {
        for(j=0;j < i;j++)
        {
          if(vet[j] > vet[j+1])
          {
            swap(j,j+1);
          }
        }
      }
    };
    void SelectionSort()
    {
      int i,j,k;
      for(i=0;i<size();i++)
      {
        k=i;
        for(j= i+1;j<size();j++)
        {
          if(vet[j] < vet[k])
            k=j;
        }
        if(k != i)
          swap(k,i);
      }
    };
    void Sort(int left,int right)
    {
      int i=left,j=right;
      T aux,pivot;
      pivot= vet[left];
      while(i <= j)
      {
          while(vet[i] < pivot)
                i++;
          while(vet[j] > pivot)
                j--;
          if(i <= j)
          {
            swap(i,j);
            i++;
            j--;
          }
      };
      if(left < j)
        Sort(left,j);
      if(right > i)
        Sort(i,right);
    };
    void QuickSort()
    {
      Sort(0,size()-1);
    };
    void Merge(T* aux,int begin,int end)
    {
      int left,right,middle,i;
      if(begin == end)
        return;
      middle=(end+begin)/2;
      Merge(aux,begin,middle);
      Merge(aux,middle+1,end);
      left=begin;
      right=middle+1;
      for(i=begin;i<=end;i++)
      {
        if(right > end || (left <= middle && vet[left] <= vet[right]))
                {
                        aux[i] = vet[left];
                        left++;
                }
                else
                {
                        aux[i] = vet[right];
                        right++;
                }
      }
      for(i = begin;i <= end;i++)
                vet[i] = aux[i];
    };
    void MergeSort()
    {
      T* aux;
      aux= new T[size()];
      Merge(aux,0,size()-1);
      delete []aux;
    };
    void Heap(int root,int bottom)
    {
      int done,max;
      done = 0;
      while ((root*2 <= bottom) && (!done))
      {
        if (root*2 == bottom)
          max = root * 2;
        else if (vet[root * 2] > vet[root * 2 + 1])
              max = root * 2;
            else
              max = root * 2 + 1;
        if (vet[root] < vet[max])
        {
          swap(root,max);
          root = max;
        }
        else
        done = 1;
      }
    };
    void HeapSort()
    {
      for(int i = ((size()/2)-1);i >= 0;i--)
      {
        Heap(i,size()-1);
      }
      for(int i = size()-1;i >= 1;i--)
      {
        swap(0,i);
        Heap(0,i-1);
      }
    }

};

 int main(int argc, char *argv[])
{
    Vectorx<class Pessoa> Z;
    Vectorx<class Pessoa>:: iterator it;
    Pessoa a;
    int N,S;
    double time1,time2;
    bool menu=false;
    bool sort=false;
    bool sort2=false;
    bool size=false;
    while(!menu)
    {
        system("cls");
        if(!sort)
        {
          if(sort2)
          {
            cout<<"\t Vector Z Is Sorted\n";
          }
          else cout<<"\t Size Of Vector Z Not Specified\n"<<"\t Please Input 1 To Choose Size\n";
        }
        else cout<<"\t Vector Z Created With A Size Of "<<Z.size()<<"\n";
        cout<<"\t MENU\n"<<"\t 1 - Size Of Vector Z\n"<<"\t 2 - Insertion Sort\n"<<"\t 3 - Bubble Sort\n";
        cout<<"\t 4 - Selection Sort\n"<<"\t 5 - Quick Sort\n"<<"\t 6 - Merge Sort\n";
        cout<<"\t 7 - Heap Sort\n"<<"\t 8 - Print Vector\n"<<"\t 9 - Exit\n";
        cin>>S;
        switch(S)
        {
          case 1:
                  system("cls");
                  Z.clear();
                  sort=true;
                  cout<<"\t Choose the size of Vector Z:\n"<<"\t 1 - 10.000\n";
                  cout<<"\t 2 - 100.000\n"<<"\t 3 - 1.000.000\n"<<"\t 4 - 10.000.000\n"<<"\t 5 - Exit\n";
                  cin>>N;
                  switch(N)
                  {
                        case 1:for(int i=10000;i>0;i--)
                                {
                                  a.id=(rand()%10000);
                                  Z.push_back(a);
                                }
                                size=false;
                                cout<<"Vector Z created with size "<<Z.size()<<"\n";
                                break;
                        case 2:for(int i=100000;i>0;i--)
                                {
                                  a.id=(rand()%100000);
                                  Z.push_back(a);
                                }
                                size=false;
                                cout<<"Vector Z created with size "<<Z.size()<<"\n";
                                break;
                        case 3:for(int i=1000000;i>0;i--)
                                {
                                  a.id=(rand()%1000000);
                                  Z.push_back(a);
                                }
                                size=true;
                                cout<<"Vector Z created with size "<<Z.size()<<"\n";
                                break;
                        case 4:for(int i=10000000;i>0;i--)
                                {
                                  a.id=(rand()%1000000);
                                  Z.push_back(a);
                                }
                                size=true;
                                cout<<"Vector Z created with size "<<Z.size()<<"\n";
                                break;
                        case 5:sort=false;break;
                        default:system("cls");cout << "\nInvalid Input";break;
                  }
                  system("PAUSE");
                  system("cls");
                  break;
          case 2:
                sort=false;
                sort2=true;
                if(size)
                {
                  cout<<"\t Size Of Vector Z Is Too Big\n";
                }
                else
                {
                  time1=clock();
                  Z.InsertionSort();
                  time2=clock()-time1;
                  cout<<"\t Vector Z Insertion Sorted";
                  cout<<" Execution Time: "<<time2/CLOCKS_PER_SEC<<" seconds\n";
                }
                break;
          case 3:
                sort=false;
                sort2=true;
                if(size)
                {
                  cout<<"\t Size Of Vector Z Is Too Big\n";
                }
                else
                {
                  time1=clock();
                  Z.BubbleSort();
                  time2=clock()-time1;
                  cout<<"\t Vector Z Bubble Sorted";
                  cout<<" Execution Time: "<<time2/CLOCKS_PER_SEC<<" seconds\n";
                }
                break;
          case 4:
                sort=false;
                sort2=true;
                if(size)
                {
                  cout<<"\t Size Of Vector Z Is Too Big\n";
                }
                else
                {
                  time1=clock();
                  Z.SelectionSort();
                  time2=clock()-time1;
                  cout<<"\t Vector Z Selection Sorted";
                  cout<<" Execution Time: "<<time2/CLOCKS_PER_SEC<<" seconds\n";
                }
                break;
          case 5:
                sort=false;
                sort2=true;
                time1=clock();
                Z.QuickSort();
                time2=clock()-time1;
                cout<<"\t Vector Z Quick Sorted";
                cout<<" Execution Time: "<<time2/CLOCKS_PER_SEC<<" seconds\n";
                break;
          case 6:
                sort=false;
                sort2=true;
                time1=clock();
                Z.MergeSort();
                time2=clock()-time1;
                cout<<"\t Vector Z Merge Sorted";
                cout<<" Execution Time: "<<time2/CLOCKS_PER_SEC<<" seconds\n";
                break;
          case 7:
                sort=false;
                sort2=true;
                time1=clock();
                Z.HeapSort();
                time2=clock()-time1;
                cout<<"\t Vector Z Heap Sorted";
                cout<<" Execution Time: "<<time2/CLOCKS_PER_SEC<<" seconds\n";
                break;
          case 8:
                cout<<"\t Vector Z:\n";
                for(it=Z.begin();it!=Z.end();it++)
                {
                  a=*it;
                  cout<<" "<<a.id;
                }
                cout<<"\n";
                break;
          case 9: menu=true;break;
      }
      system("PAUSE");
    };
    return EXIT_SUCCESS;
}
