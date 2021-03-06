#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

def MyFunction(x, y, i, j): 
  print("x",str(x))
  print("y",str(y))
  print("i",str(i))
  print("j",str(j))

def main():
  x, y = np.random.random(size=(2,5))
  i, j = np.random.random(size=(2,5))
  MyFunction(x, y, i, j)

if __name__ == "__main__":
    main()