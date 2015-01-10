//
//  main.cpp
//  01KnapsackProblem
//
//  Created by Lu Kuan-Yin on 12/25/14.
//  Copyright (c) 2014 NTU. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include "usingFunction.h"
using namespace std;

class compareUpperBound {
public:
    bool operator()(TreeNode& node1, TreeNode& node2) // Returns true if n1 is larger than n2
    {
        if (node1.upperBound > node2.upperBound) return true;
        return false;
    }
};


int main(int argc, const char * argv[]) {
    vector<int> weights;
    vector<int> values;
    int bagConstrain;
    
    readFile(weights, values, bagConstrain);
    
    vector<Item> x(weights.size());
    
    // calculate the price per weight
    initializeItems(x, weights, values);
    int numItem = (int) x.size();
    // x must have to sort by x[i].pricePerWeight
    
    priority_queue<TreeNode, vector<TreeNode>, compareUpperBound> tree;
    
    TreeNode root(numItem);
    root.nextItem = 0; // that is x[0]
    root.upperBound = calaulateUpperBound(root, x, bagConstrain);
    
    tree.push(root);
    
//    printf("Upper Bound: %f\n", root.upperBound);
    
#ifdef DEBUG
    for (int i=0; i<numItem; i++) {
        printf("State : %d\n", root.allItemState[i]);
    }
#endif
    
    tree.push(root);
    while ( !tree.empty() )
    {
        // pop the root of the tree of priority_queue
        TreeNode topNode = tree.top(); tree.pop();
        
        
        // if( u.b. < l.b ) 不展開
        // else 對nextItem 展開兩點（take nextItem or not）
        // Initialize the 2 nodes, including setting the nextItem and UpperBound
        
    }
    
    
    
    
    return 0;
}
