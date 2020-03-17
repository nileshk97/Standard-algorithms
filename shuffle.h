#ifndef SHUFFLE_H
#define SHUFFLE_H
#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<vector>


template<typename T>
void shuffleArray(T a[],int n);

template<typename T>
int partition(T a[],int low,int high);

template<typename T>
const void MS_merge(T a[],T aux[],int low,int mid, int high);

template<typename T>
const void MS_sort(T a[],T aux[],int low, int high);

#include "shuffle.cpp"

#endif