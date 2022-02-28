# Object Storage

Object storage provides facilities to manage data in the form of objects in a cost-efficient manner. These systems allow the user to store and access a huge amount of data. Different data structures provide object-based storage, and it is mainly used in databases, filesystems, etc.

This project includes analysis and implementation of the following data structures, which can be used for object storage:
- B tree
- B+tree
- B<sup>ε</sup>-tree

### Time Complexity:
| Data Structure     | Write                             |  Read             |
| ------------------ | ----------------------------------|-------------------|
| B tree             | log<sub>B</sub>N                  |log<sub>B</sub>N   |
| B+ tree            | log<sub>B</sub>N                  |log<sub>B</sub>N   |
| B<sup>ε</sup> tree | log<sub>B</sub>N/εB<sup>1-ε</sup> |log<sub>B</sub>N/ε |

*The above table shows the asymptotic time complexity for read-write I/O operation. B denotes the order of the tree, and N is the node size that can be selected in multiples of block size. ε is deciding factor for space allocation for pivots and child pointer (≈ Bε) and buffer (≈ B − Bε).*

> It is interesting to note that though the time complexity looks the same for the B tree and B+ tree, the overall ratio log<sub>B</sub>N is less for the B+ tree.
> As the B+ tree does not require to store values at internal nodes, it can accommodate more keys which increases the order of the tree (i. e. factor B). Thus, it reduces the height of the B+ tree and thereby the cost to load nodes as compared to the B tree.

### Performance Analysis:
As B-tree stores values along with key and child pointers, it causes to increase the height and load more number of blocks for I/O operation as compared to B+ tree and B-epsilon. However, as values are present along with the keys, in some cases, the operation can be completed in constant time, providing better read I/O performance over the B+ tree.  

In the case of the B+ tree, the values will be present at the leaf node, and the internal node holds keys and pointers to the child nodes. Thus, it is always required to traverse to the leaf and load log<sub>B</sub>N nodes for I/O operation. At the same time, as the B+ tree can hold more keys, overall, it requires loading fewer nodes as compared to the B tree.

B-epsilon tree provides better performance as compared to B-tree and B-plus tree, particularly for write and update operation due to addition of buffer storage along with keys and node pointers.Thus, it does not require traversing the leaf for every operation and stores the newly inserted data near the root.

> Each data structure has its pros and cons. Therefore, selecting the data structure for object storage is also depends on the use cases and requirements.

> This project provides the general implementation of Btree, B+ tree, b-epsioln tree. However there are different variant can be made depending on usage and user cases which can optimize the performance.

