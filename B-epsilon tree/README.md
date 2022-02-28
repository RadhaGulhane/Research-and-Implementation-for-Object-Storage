# B epsilon-tree (Bε tree)

## Introduction
Bε-tree  is a data structure which  can be used to organized on disk storage for application such as databases or file system. Bε tree uses key-value pair as similar to B tree but provides better performance, particularly for inserts, range queries, and key-value updates. It is composition of  B tree and buffered repository tree where B tree favors query operation and a bu?ered repository tree favors insertion.  

## Node structure
### B<sup>ε</sup>-tree
<img alt="B<sup>ε</sup>-tree node structure" src="./diagrams/B_epsilon_tree_node_structure_1.PNG" height="200"/>

## Source Code
Source code include implementation of B epsilon-tree. Code provide functionality to perform operations such as insertion, deletion, search. 
Code can be optimized and modalized in later version to increase the performance.

