#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cmath>
#include<bits/stdc++.h> 
#include<chrono>

template<typename T>
static std::vector<T> final_pair(4);//for storing the closest pair of: 2 points so 4 co-ordinates
static double delta;//setting the "strip" and storing the distance calculated using divide and conquer method
static double min{99999.0};//storing the distance calculated using Brute-force method
// **************************************************
//returns the distance between the given 2 points
template<typename T>
using coord=std::vector<std::vector<T>>;
template<typename T>
double distance(T x1,T y1,T x2, T y2)
{
    return(sqrt(pow((x1-x2),2)+pow((y1-y2),2)));
}
// **************************************************
//for base case where the subproblem has 3 points, so calculate minimum distance manually
template<typename T>
std::vector<T> minDist(coord<T> pointList,int low,int high)
{
    //3 possible cases. either 1st and 2nd, 1st and 3rd or 1st and 2nd points
    double d12=distance(pointList[low][0],pointList[low][1],pointList[low+1][0],pointList[low+1][1]);
    double d13=distance(pointList[low][0],pointList[low][1],pointList[high][0],pointList[high][1]);
    double d23=distance(pointList[low+1][0],pointList[low+1][1],pointList[high][0],pointList[high][1]);
    double x=std::min(std::min(d12,d13),d23);
    /*if this is the firsts ever recursive call to calculate disance, check global delta value and 
    set it accordingly*/
    //store minimum of them in final_pair and retur
    if(x<=delta||delta==0.0){
        if(x=d12)
        {
            final_pair<T>[0]=pointList[low][0];
            final_pair<T>[1]=pointList[low][1];
            final_pair<T>[2]=pointList[low+1][0];
            final_pair<T>[3]=pointList[low+1][1];
            
        }
        else if(x==d13)
        {
            final_pair<T>[0]=pointList[low][0];
            final_pair<T>[1]=pointList[low][1];
            final_pair<T>[2]=pointList[high][0];
            final_pair<T>[3]=pointList[high][1];
        }
        else
        {
            final_pair<T>[0]=pointList[low+1][0];
            final_pair<T>[1]=pointList[low+1][1];
            final_pair<T>[2]=pointList[high][0];
            final_pair<T>[3]=pointList[high][1];
        }
    }
    delta=x;
    final_pair<T>.resize(4);
    return final_pair<T>;
}

// **************************************************
    
template<typename T>
std::vector<T> closestSplitPair(coord<T> pointList, int n, int low, int mid, int high, double &delta)
{
    //set delta to mid or rightmost of left sub-array
    
    T x_mean=pointList[mid][0];
    coord<T> sub_y;

    //filter points based on their ditance from the "strip"/delta
    //push into array sub_y 
    for(int i=0;i<n;i++)
    {
        if(abs(x_mean-pointList[i][0])<=delta)
        {
            std::vector<T> temp{pointList[i][0],pointList[i][1]};
            sub_y.push_back(temp);
        }
    }
    //casting size to int to prevent type-compatibility issues with size()
    int ySize=static_cast<int>(sub_y.size());
    //check min within the sub_y array
    double final_distance;
    for(int i=0;i<ySize-1;i++)
    {   
        for(int j=i+1;j<std::min(7,ySize-i);j++)
        {
            double temp_distance=distance(sub_y[i][0],sub_y[i][1],sub_y[j][0],sub_y[j][1]);
            if(temp_distance<=delta)//if found,set delta and final pair vector
            {   delta=temp_distance;
                final_pair<T>[0]=sub_y[i][0];
                final_pair<T>[1]=sub_y[i][1];
                final_pair<T>[2]=sub_y[j][0];
                final_pair<T>[3]=sub_y[j][1];
            }
        }
    }
    final_pair<T>.resize(4); 
    return final_pair<T>;
}
 
// **************************************************
template<typename T>
std::vector<T> closestPair(coord<T> pointList,int n,int low,int high)
{
    //1st base: calculates and return distance minimum manually if call gets only 3 points 
    if(high-low==2)
    {
        return minDist(pointList,low,high);
    }
    //2nd base case: for 2 points returns distance between them
    if(high-low==1)
    {
        final_pair<T>[0]=pointList[low][0];
        final_pair<T>[1]=pointList[low][1];
        final_pair<T>[2]=pointList[high][0];
        final_pair<T>[3]=pointList[high][1];
        return final_pair<T>;
    }
    //for storing min distance co-ordinates returned from left, right and split case respectively
    std::vector<T> leftPoints(4); 
    std::vector<T> rightPoints(4);
    std::vector<T> splitPoints(4);

    int mid=low+(high-low)/2;
    leftPoints=closestPair(pointList,n,low,mid);         
    rightPoints=closestPair(pointList,n,mid+1,high);

    double distance_left=distance(leftPoints[0],leftPoints[1],leftPoints[2],leftPoints[3]);
    double distance_right=distance(rightPoints[0],rightPoints[1],rightPoints[2],rightPoints[3]);

    //set delta to min to construct the "strip" for filtering further
    if(delta==0||std::min(distance_left,distance_right)<delta)
        delta=std::min(distance_left,distance_right);
    //call to check split case, where one point is in left sub-array dn other in right
    splitPoints=closestSplitPair(pointList,n,low,mid,high,delta);

    //indicates first ever recursive call
    //coming back to this means work is done and final co-ordinates can be returned
    if((high==n-1)&&(low==0))
    {
        final_pair<T>.resize(4);
        return final_pair<T>;
    }
    else//or else return the minimum found from either left, right or combined(split) array
    {
        double distance_split=distance(splitPoints[0],splitPoints[1],splitPoints[2],splitPoints[3]);
        double x=std::min(std::min(distance_left,distance_right),distance_split);//minimum distance
        if(x==distance_split)
        {
           return splitPoints;
        }
        else if(x=distance_left)
        {
            return leftPoints;
        }
        else
        {
           return rightPoints;
        }
    }
    
}
//*************************************************************
template<typename T>
std::vector<T> bruteForceClosestPair(coord<T> pointlist,int n,int low,int high)
{
     double a; std::vector<T> pairs(4);
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {  
            a=distance(pointlist[i][0],pointlist[i][1],pointlist[j][0],pointlist[j][1]);
            if(a<min)
            {
                min=a;
                pairs[0]=pointlist[i][0];
                pairs[1]=pointlist[i][1];
                pairs[2]=pointlist[j][0];
                pairs[3]=pointlist[j][1];
            }
        }
    }
    return pairs;
}
int main()
{
    //create a 2-D vector to store all co-ordinates 
    std::vector<std::vector<int>> pointList{
                                            {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}
                                            };

    // std::vector<std::vector<int>> pointList;std::vector<int> a(2);
    // for(int i=0;i<1002;i++)
    // {
    //     a[0]=std::rand()%1000;
    //     a[1]=std::rand()%1000;
    //     pointList.push_back(a);
    // }

    std::sort(pointList.begin(),pointList.end());//sort the cooridiantes by their x-values
    auto start=std::chrono::steady_clock::now();
    //calls divide and conquer algorithm
    std::vector<int> points=closestPair(pointList,pointList.size(),0,pointList.size()-1);
    auto end = std::chrono::steady_clock::now();

    std::cout<<"\nClosest pairs using Divide and Conquer algorithm:";
    std::cout<<"("<<points[0]<<","<<points[1]<<")--("<<points[2]<<","<<points[3]<<")"<<"\n";
    std::cout<<"The distance between them: "<<delta;
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "\nElapsed time: " << elapsed_seconds.count() << "s\n";

    start=std::chrono::steady_clock::now();
    points=bruteForceClosestPair(pointList,pointList.size(),0,pointList.size()-1);
    end= std::chrono::steady_clock::now();

    std::cout<<"\nClosest pairs using Brute-Force algorithm:";
    std::cout<<"("<<points[0]<<","<<points[1]<<")--("<<points[2]<<","<<points[3]<<")"<<"\n";
    std::cout<<"The distance between them: "<<min;
    elapsed_seconds = end-start;
    std::cout << "\nElapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}