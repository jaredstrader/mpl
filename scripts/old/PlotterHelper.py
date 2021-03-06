#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

def plotRoadmap(x, y, tail, head):
  # print("x=")
  # print(x)
  # print("y=")
  # print(y)
  print("tail=",str(tail))
  print("head=",str(head))


  #
  fig = plt.figure()
  ax = plt.gca()
  ax.grid(color='lightgrey', linestyle='-', linewidth='0.5')
  ax.grid(True)

  plt.gca().set_aspect('equal', adjustable='box')

  #
  counter=0
  for t, h in zip(tail, head):
    print("t=",str(t))
    print("h=",str(h))
    print("counter = ", str(counter))
    plt.plot([ x[t], x[h] ], [ y[t], y[h] ], 'k-')
    plt.plot([ x[t], x[h] ], [ y[t], y[h] ], 'b.')
    # print(counter)
    counter = counter + 1

  #
  plt.show()
  plt.pause()

# def plotRoadmap(points, edges):
#   #
#   fig = plt.figure()
#   ax = plt.gca()
#   ax.grid(color='lightgrey', linestyle='-', linewidth='0.5')
#   ax.grid(True)

#   plt.gca().set_aspect('equal', adjustable='box')

#   #
#   for edge in edges:
#     plt.plot([ points[edge[0]][0], points[edge[1]][0] ], [ points[edge[0]][1], points[edge[1]][1] ], 'k-') #
#     plt.plot([ points[edge[0]][0], points[edge[1]][0] ], [ points[edge[0]][1], points[edge[1]][1] ], 'b.')

#   #
#   plt.show()

def main():
  #points
  x, y = np.random.random(size=(2,5))

  #edges
  edges = []
  edges.append((0,1));
  edges.append((1,2));
  edges.append((2,3));
  edges.append((3,4));
  edges.append((4,0));
  print(edges)

  #plot
  plotRoadmap(x, y,  edges)

if __name__ == "__main__":
    main()