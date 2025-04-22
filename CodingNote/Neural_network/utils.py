import matplotlib.pyplot as plt
import numpy as np
import math
import random
import matplotlib.pyplot as plot

# generate dataset
NUM_OF_DATA = 1000
def create_data(n):
    entry_list = []
    for i in range(n):
        x = random.uniform(-2,2)
        y = random.uniform(-2,2)
        entry_list.append([x,y,tag_entry(x,y)])
    return np.array(entry_list)

def tag_entry(x,y):
    if x**2 + y**2 < 1:
        tag = 0
    else:
        tag = 1
    return tag

def show(data,title):
    color = []
    for i in data[:,2]:
        if i == 0:
            color.append("orange")
        else:
            color.append("blue")
    plt.scatter(data[:,0],data[:,1],c=color)
    plt.title(title)
    plt.show()


if __name__ == "__main__":
    show(create_data(NUM_OF_DATA),"data")