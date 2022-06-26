import re
import string
import os

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def openFile(s):
    if(os.path.exists(s)):
        f = open(s , r)
    return 0

#p2
def readFile(s):#counts each item in a txt document
    times=0
    s = os.getcwd()+ '\\' + s
    if(os.path.exists(s)):#check if the file exists
        f = open(s, "r")#open file for reading
        item = f.readlines()#make list of all items
        leng = len(item)
        itemList = []#displays item, to be used with times list
        timesList = []#the amount of times an item was counted int the list
        removeList = []
        temp=item[-1]#used to make sure the last item is read like all the others with a new line at the end
        temp += '\n'
        item[-1] = temp
        while(leng!=0):#until the list is empty
            removeList = []
            itemOne=item[0]#the item being counted for this go of the while loop
            count = 0 #count the item
            for i in item:#goes through each item in the list, able to be used for checking if an item is the same as itemOne 
                if(itemOne == i):#checks if itemone and the item in the list are the same, if it is add item's place to remove list to be removed later and count
                    removeList.append(count)
                    times = times + 1
                count = count + 1
            removeCount = 0
            for i in removeList:#remove already counted items
                item.pop(i - removeCount)
                removeCount = removeCount + 1
            itemTwo = itemOne.replace('\n',' ')
            itemList.append(itemTwo)
            timesList.append(times)
            leng = len(item)
            times = 0
        count = 0
        for i in itemList:
            print(itemList[count] + str(timesList[count]))
            count = count + 1
    return times

def specItem(sItem):#count specificic item
    times = 0
    #    s='C:/Users/Erik/source/repos/Project6/items.txt'#address of txt file being read
    s='items.txt'#address of txt file being read
    s = os.getcwd() + '\\' + s
    if(os.path.exists(s)):#check if exists
        f = open(s, "r")#open for reading
        item = f.readlines()#list of all items
        temp = item[-1]
        temp += '\n'
        item[-1] = temp
        itemOne = sItem
        itemOne += '\n'
        for i in item:#goes through each item in the list, able to be used for checking if an item is te same as itemOne abs
            if(itemOne == i):
                times = times + 1#times++ doesnt work
    return times

def makeFile(dat):#makes a dat file based on data able to be obtained from the first choice
    times = 0
#    s='C:/Users/Erik/source/repos/Project6/items.txt'#address of txt file being read
    s = 'items.txt'#address of txt file being read
    s = os.getcwd() + '\\' + s
    if(os.path.exists(s)):
        f = open(s, "r")
        item = f.readlines()#list of all items
        leng = len(item)
        itemList = []
        timesList = []
        removeList = []
        temp = item[-1]
        temp += '\n'
        item[-1] = temp
        while(leng != 0):
            removeList = []
            itemOne = item[0]
            count = 0 
            for i in item:#goes through each item in the list, able to be used for checking if an item is te same as itemOne abs
                if(itemOne == i):
                    removeList.append(count)
                    times = times + 1#times++ doesnt work
                count = count + 1
            removeCount = 0
            for i in removeList:
                item.pop(i - removeCount)
                removeCount = removeCount + 1
            itemTwo = itemOne.replace('\n',' ')
            itemList.append(itemTwo)
            timesList.append(times)
            leng = len(item)
            times = 0
        count = 0
        fptr = open(dat, "w")#make a file to write to
        for i in itemList:#write to file for each item
            l = [itemList[count],str(timesList[count]),'\n']#the line to be put into dat file with item and number
            fptr.writelines(l)#write l to dat file
            count = count + 1#count to print right amount of lines when back in c++
        fptr.close()#close the data file
    return count
