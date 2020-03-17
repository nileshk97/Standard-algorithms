#/mnt/C216CEC416CEB925/Udemy Tutorials/Python 3.5
import os
import sys
import re


mylist=[]
os.system(r"cd /mnt/C216CEC416CEB925/Udemy\ Tutorials/Python\ 3.5;touch /home/nilesh/code/f.txt;ls -tr>/home/nilesh/code/f.txt")
fp=open("f.txt",'r+')
dirList=str(fp.read())
dirList=dirList.split('\n')
#print(dirList)
fp.seek(0)
fp.truncate()

cnt=1
j=0
for i in dirList:
    match=re.search(r'.txt\b',i)
    if match:
        continue
    else:
        i=str(cnt)+". "+i
        cnt+=1
        
        mylist.append(i.replace(' The Complete Python 3 Course- Go from Beginner to Advanced! - Udemy.MP4',''))
#finalList=[]
'''
for i in mylist:
    i=str(cnt)+". "+i
    cnt+=1
    finalList.append'''
for i in mylist:
    print(i.split(r' +'))

for i in mylist:
    fp.write(i+"\n")

fp.close()