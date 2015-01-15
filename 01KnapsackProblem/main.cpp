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
#include <math.h>
#include "usingFunction.h"
using namespace std;

class compareUpperBound {
public:
    bool operator()(TreeNode& node1, TreeNode& node2) {
        if (node1.upperBound < node2.upperBound) return true;
        return false;
    }
};


int main(int argc, const char * argv[]) {
    vector<int> weights;
    vector<int> values;
    int bagConstrain;
    int lowerBound = 0;
    
    readFile(weights, values, bagConstrain);
    
    vector<Item> x(weights.size());
    initializeItems(x, weights, values);
    int numItem = (int) x.size();
    
    
    priority_queue<TreeNode, vector<TreeNode>, compareUpperBound> tree;
    
    TreeNode optimalNode(numItem);
    TreeNode root(numItem);
    root.nextItem = 0; // that is x[0]
    root.upperBound = calaulateUpperBound(root, x, bagConstrain);
    tree.push(root);
    int expandingNodeNum = 1;
    
    while ( !tree.empty() )
    {
        TreeNode topNode = tree.top();
        tree.pop();
        
        // if topNode.upperBound < lowerBound, then don't expand
        if (topNode.upperBound < lowerBound)
            continue;
        // if( leaf ) update the lowerBound and continue
        else if (topNode.nextItem == x.size()) {
            int lb = calculateLowerBound(topNode.allItemState, x, bagConstrain);
            
            if (lb!=INFEASIBLE && lb>lowerBound) {
                lowerBound = lb;
                optimalNode = topNode;
            }
            continue;
        }
        else {
            TreeNode take(topNode), nonTake(topNode);
            int thisLevelItemNumber = topNode.nextItem;
            
            take.nextItem = thisLevelItemNumber + 1;
            take.allItemState[thisLevelItemNumber] = SELECT;
            take.upperBound = calaulateUpperBound(take, x, bagConstrain);
            tree.push(take);
            
            nonTake.nextItem = thisLevelItemNumber + 1;
            nonTake.allItemState[thisLevelItemNumber] = NON_SELECTED;
            nonTake.upperBound = calaulateUpperBound(nonTake, x, bagConstrain);
            tree.push(nonTake);
            
            expandingNodeNum += 2;
        }
    }
    
    printf("The optimal solution: %d\n", lowerBound);
    for (int i=0; i<optimalNode.allItemState.size(); i++) {
        printf("x%d=%d", i+1, optimalNode.allItemState[i]);
        
        if (i < optimalNode.allItemState.size() -1)
            cout<< ", ";
        else
            cout<<"\n";
    }

    cout<< "ratio = " << 1 - ((expandingNodeNum*1.0)/(pow(2, numItem+1)-1))<<endl;
    
    return 0;
}
