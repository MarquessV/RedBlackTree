# RedBlackTree
This is an implementation of the red black tree data structure in C++. I did this as an educational exercise and as an opportunity to try out Google Test. It works and supports all the methods you would expect. However, the C++ standard library includes red black tree based implementations of set, multiset, map, and multimap that would probably be more appropriate choices for serious projects. Still, this code can be used as a reference if you are having trouble understanding red black trees.

## Usage

Make sure to include red_black_tree.hpp

To create an empty tree of type T you can write:
```C++
red_black_tree<T> tree;
```
Or, to initialize the tree with a list of data, you can write:
```C++
vector<T> data = {a1, a2, a3, ..., an};
red_black_tree<T> tree(data);
```
NOTE: This implementation uses the data as the key, so type T must have less than, greater than, and equal to operators defined.

Items can be inserted or removed with:

```C++
tree.insert(x);
tree.remove(x);
```

insert(x) returns false if x was already in the tree and true otherwise. Similarly, remove(x) returns false if x wasn't in the tree and true otherwise.

You can check if x is in the tree with:
```C++
tree.find(x);
```
which returns true if x was found and false otherwise.

You can check how many elements are in the tree with:
```C++
tree.size();
```

Finally you can dump the tree with:
```C++
tree.dump();
```
which returns a vector<pair<T, bool>> containing a preorder list of the data in the nodes where the bool is true if that node was black and false if it was red.
