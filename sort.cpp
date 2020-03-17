#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include "shuffle.h"
#include<chrono>

template<typename T>
const void quickSort(T a[], int n, int low, int high)
{   
    if(high-low==n-1)
        shuffleArray(a,n);
    if (high<=low)
        return;
    int mid=partition(a,low,high);//defined in another file
    quickSort(a,n,low,mid-1);
    quickSort(a,n,mid+1,high);

}

template<typename T>
void heapSort(T a[],int n)
{
    T aux[n+1];
    for (int i=0;i<n;i++)
        aux[i+1]=a[i];

    
    for(int i=n/2;i>=1;i--)//create heap tree
        sink(aux,i,n);

    int x=n;
    while (x>1)
    {
        std::swap(aux[1],aux[x--]);
        sink(aux,1,x);
    }
    
    for(int i=1;i<=n;i++)//copies tree back into array
        a[i-1]=aux[i];

}

template <typename T>
//caller func for actual merge sort so we can use only one aux array here
const void mergeSort(T a[], int n)
{
    T aux[n];
    MS_sort(a,aux,0,n-1);

}


template <typename T>
const void insertionSort(T a[], int n)
{   
    int j;
    T key;
    for(int i=0; i<n-1; i++)
    {
        j=i+1;
        key=a[j];
        while((key<a[i])&&(i>=0))
        {   
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=key;

    }

}
template <typename T>
const void shellSort(T a[], int n)
{   
    int h=1;
    while (h<(n/3))
    {
        h=3*h+1;
    }
    
    while(h>=1)
    {
        for (int i = h; i < n; i++)
        {
            for (int j = i; (j>=h)&&(a[j]<a[j-h]); j=j-h)
            {
                std::swap(a[j],a[j-h]);
            }
            
        }
        h=h/3;
        
    }

}

template <typename T>
const void selectionSort(T a[], int n)
{
    int smallestPos;
    for(int i=0; i<n-1; i++)
    {
        smallestPos=i;
        for(int j=i+1; j<n; j++)
        {
            if (a[j]<a[smallestPos])
            {
                smallestPos=j;
            }
        
        }
        std::swap(a[i],a[smallestPos]);
    }

}


int main()
{
     int a[5]{3,2,5,2,4};
    //"nilesh","bhushan","aakash","nikhil","aasfdfsd"
    auto start=std::chrono::steady_clock::now();
    quickSort(a,5,0,4);
    auto end = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end-start;
     
    for(auto i: a)
        std::cout<<i<<" ";
    std::cout<<"\nusing quicksort, time elapsed= "<<elapsed_seconds.count() << "s\n";

    int b[5]{3,2,5,2,4};

    start=std::chrono::steady_clock::now();
    mergeSort(b,5);
    end = std::chrono::steady_clock::now();
    
    elapsed_seconds = end-start;
     
    for(auto i: a)
        std::cout<<i<<" ";
    std::cout<<"\nusing mergesort, time elapsed= "<<elapsed_seconds.count() << "s\n";

    return 0;
}