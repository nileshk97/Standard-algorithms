import math
import copy
import random as rd
import time

def distance(co1,co2):
    return (co1[0]-co2[0])**2+(co1[1]-co2[1])**2

def splitPair(points, delta_DQ, low, mid, high):
    mean=points[mid][0]
    sub_y=[]
    for i in points:
        if abs(mean-i[0]<=delta_DQ):
            sub_y.append(i)

    sub_y.sort(key=lambda x: x[1])
    pair_DQ=[]
    for i in range(len(sub_y)-1):
        for j in range(i+1,min(7,len(sub_y)-i)):
            temp_distance=distance(points[i],points[j])
            if(temp_distance<delta_DQ):
                delta_DQ=temp_distance
                pair_DQ=[points[i],points[j]]

    return(pair_DQ, delta_DQ)

def closetPair(points, delta_DQ, low, high):
    if high-low==2:
        # print("base case 1--->")
        # print(points[low],points[high]) 
        temp_points=[points[low],points[low+1],points[high]]
        result=bruteForceCP(temp_points, delta_DQ,)
        #print(result)
        return result

    elif high-low==1:
        # print("base case 2--->")
        # print(points[low],points[high])
        # print(delta_DQ)
        temp_points=[points[low],points[high]]
        ####result=bruteForceCP(temp_points, delta_DQ,) #check later
        #print(result)
        return (temp_points,distance(points[low],points[high]))

    else:
        mid=low+(high-low)//2
        # print("left recursion--->")
        # print(points[low],points[mid])
        result_left=closetPair(points, delta_DQ, low, mid)
        # print("After left recursion:_____")
        # print(result_left)


        # print("right recursion--->")
        # print(points[mid+1],points[high])
        result_right=closetPair(points, delta_DQ, mid+1, high)
        # print("After right recursion:_____")
        # print(result_right)

        if(min(result_left[1],result_right[1])<delta_DQ):
            delta_DQ=min(result_left[1],result_right[1])

        result_split=splitPair(points, delta_DQ, low, mid, high)
        pair_DQ=[]
        if(delta_DQ==result_left[1]):
            pair_DQ=result_left[0]
        elif(delta_DQ==result_right[1]):
            pair_DQ=result_right[0]
        elif(delta_DQ==result_split[1]):
            pair_DQ=result_split[0]

        return (pair_DQ, delta_DQ)

def bruteForceCP(points, delta_DQ,):
    pair_DQ=[]
    for i in range(len(points)-1):
        for j in range(i+1,len(points)):
            dist=distance(points[i],points[j])
            if dist<delta_DQ:
                delta_DQ=dist
                pair_DQ=[points[i],points[j]]

    return (pair_DQ, delta_DQ)

if __name__ == "__main__":
    delta_DQ=999999.0
    points=[]
    # for _ in range(50):
    #     points.append(rd.sample(range(0,50),2))
    points=[[0,0], [-2,0], [4,0], [1,1], [3, 3], [-2,2],[5,2]]
    points.sort(key=lambda x: x[0])
    #rint(points)
    
    start_t=time.perf_counter()
    result=closetPair(points, delta_DQ,0,len(points)-1)
    end_t=time.perf_counter()
    print("time using divide and conquer: "+str(end_t-start_t))
    
    print(result[0])
    print(math.sqrt(result[1]))
    delta_DQ=999999.0
    points2=[]
    for _ in range(50):
        points2.append(rd.sample(range(0,50),2))
    t1=time.perf_counter()
    result2=bruteForceCP(points, delta_DQ)
    t2=time.perf_counter()
    print("time using brute force: "+str(t2-t1))
    print(result2[0])
    print(math.sqrt(result2[1]))
    #pair=closestPair(points,0,int(len(points)-1))