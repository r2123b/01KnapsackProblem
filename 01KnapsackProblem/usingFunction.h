//
//  usingFunction.h
//  01KnapsackProblem
//
//  Created by Lu Kuan-Yin on 1/7/15.
//  Copyright (c) 2015 NTU. All rights reserved.
//

#ifndef ___1KnapsackProblem__usingFunction__
#define ___1KnapsackProblem__usingFunction__

#include <stdio.h>
#include <vector>
#define INFEASIBLE -100

using namespace std;

struct Item {
    int value;
    int weight;
    float pricePerWeight;
    bool isChosen = false;
};

enum ItemState { NON_SELECTED, SELECT, CONSIDERING};

struct TreeNode {
    float upperBound = 0;
    int nextItem =  -1;
    vector<ItemState> allItemState;
    
    //constructor
    TreeNode(int NumItems) {
        allItemState.assign(NumItems, CONSIDERING);
    }
};

bool readFile(vector<int> &weights, vector<int> &values, int &constrain);
void initializeItems(vector<Item> &x, const vector<int> &weights, const vector<int> &values);
float calaulateUpperBound(TreeNode &n, const vector<Item> &x, const int bagConstrain);
int calculateLowerBound(const vector<ItemState> &allItemState, const vector<Item> &x, const int bagConstrain);

#endif /* defined(___1KnapsackProblem__usingFunction__) */
