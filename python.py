import networkx as nx
import matplotlib
from numpy import split  
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

ufile = open("Urban.txt", "r")
ux = []
uy = []
l1 = ufile.readlines()
for ul in l1:
    plt.scatter(int(ul.split()[0]), int(ul.split()[1]), color = 'red')
ufile.close()

rfile = open("Rural.txt", "r")
rx = []
ry = []
l2 = rfile.readlines()
for rl in l2:
    plt.scatter(int(rl.split()[0]), int(rl.split()[1]), color = 'green')

rfile.close()

nfile = open("Neighbor.txt", "r")
lines = nfile.readlines()

for line in lines:
    x1=line.split()[0] 
    y1=line.split()[1]
    x2=line.split()[2]
    y2=line.split()[3]
    plt.plot([int(x1),int(x2)],[int(y1),int(y2)], color = 'black')
plt.show()
