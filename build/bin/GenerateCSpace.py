#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

#define polygons in configuration space representing obstacles
#xmin: minimum x of configuration space
#xmax: maximum x of configuration space
#ymin: minimum y of configuration space
#ymax: maximum y of configuration space
def definePolygons(xmin, xmax, ymin, ymax):
  #create figure for selecting points
  fig = plt.figure()

  ax = plt.gca()
  ax.grid(color='lightgrey', linestyle='-', linewidth='0.5')
  ax.grid(True)
  ax.set_xlim(xmin,xmax)
  ax.set_ylim(ymin,ymax)

  plt.gca().set_aspect('equal', adjustable='box')

  #select polygons
  print('')
  print('CLICK LEFT...............add vertex for polygon.')
  print('CLICK MIDDLE.............remove most recent added point.')
  print('CLICK RIGHT..............stop input for current polygon. To stop selecting polygons, right click without adding vertices.\n')

  polygons = []
  i=0
  while 1:
    print("Selecting points for obstacle " + str(i))
    i=i+1

    #select points
    pts = plt.ginput(0, mouse_add=1, mouse_pop=2, mouse_stop=3) #1 is left, 2 is middle, 3 is right

    #if no points selected, break
    print(str(len(pts)) + " points selected...")
    if len(pts) < 3: #if less than 3 points selected, terminate selection process
      print("Terminating with " + str(len(pts)) + " points selected...")
      break

    ##add obstacle to list
    polygons.append(pts)
    # print("Number of polygons is " + str(len(polygons)))

    #show created obstacle
    temp = pts[:]
    temp.append(temp[0])
    x, y = zip(*temp)
    plt.plot(x,y) 
    plt.draw()

  #close current figure
  plt.close()

  #return list of polygons
  return polygons

#define configuration space and obstacles
def defineConfigurationSpaceAndObstacles():
  print('The obstacles are represented as polygons. Enter the range for x and y axes for the configuration space and select points defining the polygons.\n')

  #range for x-axis and y-axis for user input
  xmin = input("Enter minimum for x-axis:")
  xmax = input("Enter maximum for x-axis:")
  ymin = input("Enter minimum for y-axis:")
  ymax = input("Enter maximum for y-axis:")

  #create obstacles from user inputs
  obstacles = definePolygons(xmin, xmax, ymin, ymax)

  #write configuration space to file
  f = open("configuration_space.txt", "w")
  f.write(str(xmin) + " " + str(xmax) + " " + str(ymin) + " " + str(ymax) )
  f.close()

  #write obstacles to file
  f = open("obstacles.txt", "w")
  for obs in obstacles:
    for pt in obs:
      f.write(str(pt[0]) + " " + str(pt[1]) + " ")
    f.write("\n")
  f.close()

  return 0

#plot configuration space with obstacles
#xmin: minimum x of configuration space
#xmax: maximum x of configuration space
#ymin: minimum y of configuration space
#ymax: maximum y of configuration space
#obstacles: list of obstacles where each obstacle is a list of tuples
def plotConfigurationSpaceAndObstacles(xmin, xmax, ymin, ymax, obstacles):
  #create figure
  fig = plt.figure()

  ax = plt.gca()
  ax.grid(color='lightgrey', linestyle='-', linewidth='0.5')
  ax.grid(True)
  ax.set_xlim(xmin,xmax)
  ax.set_ylim(ymin,ymax)

  plt.gca().set_aspect('equal', adjustable='box')

  #plot obstacles
  for obs in obstacles:
    temp = obs[:]
    temp.append(temp[0])
    print('temp')
    print(temp)
    x, y = zip(*temp)
    plt.plot(x,y)
    plt.draw()

  plt.waitforbuttonpress()

#select point in configuration space and return the point
#xmin: minimum x of configuration space
#xmax: maximum x of configuration space
#ymin: minimum y of configuration space
#ymax: maximum y of configuration space
#obstacles: list of obstacles where each obstacle is a list of tuples
def selectConfiguration(xmin, xmax, ymin, ymax, obstacles):
  #create figure
  fig = plt.figure()

  ax = plt.gca()
  ax.grid(color='lightgrey', linestyle='-', linewidth='0.5')
  ax.grid(True)
  ax.set_xlim(xmin,xmax)
  ax.set_ylim(ymin,ymax)

  plt.gca().set_aspect('equal', adjustable='box')

  #plot obstacles
  for obs in obstacles:
    temp = obs[:]
    temp.append(temp[0])
    x, y = zip(*temp)
    plt.plot(x,y)
    plt.draw()

  #select point
  pts = plt.ginput(1)

  return pts[0]

def main():
  defineConfigurationSpaceAndObstacles()

if __name__ == "__main__":
    main()