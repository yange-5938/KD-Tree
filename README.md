# kd-tree

## what's a kd-tree?
[kd-tree](https://en.wikipedia.org/wiki/K-d_tree) is like a normal tree, but it's kd.

## How to build

```console
$ g++ -o <name-you-want-to-give> kd-tree.cpp
$ ./myprogram
```

we use input.csv as a input file, currently it only works with 2-dimensional points.

## How to use

This program now services only demonstration purpose, it's not yet meant for production but merely to demonstrate all of the functions.

Once the program is excuted, it will read all the points from the csv file in same directory, and construct a kd-tree accordingly. It will then print the tree to terminal and also print the mininum vector of each dimension. Then the program asks user to type in a vector to delete, it only deletes when input is valide, when the input is not valide it may cause your computer to crash. Once the vector is deleted, the tree will be printed again and then the program terminates.
