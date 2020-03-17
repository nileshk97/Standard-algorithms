#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<vector>

template<typename T>
void sink(T a[],int i,int n)
{
    while((2*i)<=n)
    {
        int j=2*i;
        if((j<n)&&(a[j]<a[j+1]))
            j++;
        if(a[i]>=a[j])
            break;
        std::swap(a[i],a[j]);
        i=j;
    }
}

template<typename T>
void deleteMax(T a[],int i,int n)
{



}

template<typename T>
const void MS_merge(T a[],T aux[],int low,int mid, int high)
{

    for(int i=low;i<=high;i++)
    {
        aux[i]=a[i];
    }
    int i=low,j=mid+1;

    for(int k=low;k<=high;k++)
    {
        if(aux[mid]<aux[mid+1])
            return; 
        else if(i>mid)
            a[k]=aux[j++];
        else if(j>high)
            a[k]=aux[i++];
        else if(aux[i]<aux[j])
            a[k]=aux[i++];
        else
            a[k]=aux[j++];

    }    
}

template<typename T>
const void MS_sort(T a[],T aux[],int low, int high)
{
    if(high<=low)
        return;
    int mid=low+(high-low)/2;
    MS_sort(a,aux,low,mid);
    MS_sort(a,aux,mid+1,high);
    MS_merge(a,aux,low,mid,high);

}

template<typename T>
void shuffleArray(T a[],int n)
{
    int index=0;
    for (int i=0;i<n;i++)
    {
        index=(std::rand()%(i+1));
        std::swap(a[i],a[index]);
    }

}

template<typename T>
int partition(T a[],int low,int high)
{
    int i=low,j=high+1;
    //T pivot =a[0];
    while(1)
    {
        while(a[++i]<a[low])
        {
            if(i>=high)
                break;
        }
        while(a[--j]>a[low])
        {
            if(j<=low)
                break;
        }

        if(i>=j)
            break;
        
        std::swap(a[i],a[j]);

    }
    std::swap(a[j],a[low]);

    return j;
}
