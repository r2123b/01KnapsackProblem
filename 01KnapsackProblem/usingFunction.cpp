//
//  usingFunction.cpp
//  01KnapsackProblem
//
//  Created by Lu Kuan-Yin on 1/7/15.
//  Copyright (c) 2015 NTU. All rights reserved.
//

#include "usingFunction.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

bool readFile(vector<int> &weights, vector<int> &values, int &constrain)
{
    // the file is supposed to put in the same direction with .out
    ifstream infile("testData.txt"); // input file stream
    //    ofstream outfile("outData.txt"); // output file stream
    
    if (!infile) {
        cout<<"file doesn't open!!\n";
        return false;
    }
    
    int iteration = 1; // used to distinguish input lines
    while (!infile.eof()) {
        string line; // temp variable
        int num;     // temp variable
        
        getline(infile, line);
        stringstream ss(line);  //save to special data type(here is int)
        while (ss >> num) {
            if (iteration == 1) {
                values.push_back(num);
            }
            else if (iteration == 2) {
                weights.push_back(num);
            }
            else
                constrain = num;
        }
        iteration++;
    }
//    //Test the input:
//    cout<<"w: ";
//    for (int i=0; i<values.size(); i++) {
//        cout<<weights[i] <<" ";}
    
    infile.close();
    return true;
}

void initializeItems(vector<Item> &x, const vector<int> &weights, const vector<int> &values)
{
    for (int i =0 ; i< x.size(); i++) {
        x[i].weight = weights[i];
        x[i].value = values[i];
        x[i].pricePerWeight = values[i]*1.0 / weights[i];
        x[i].isChosen = false;
    }
    
//    //Test the pricePerWeight
//    for (int i = 0; i<x.size(); i++) {
//        cout << x[i].pricePerWeight<<endl;
//    }
}


// calculate the fraction knapsack
float calaulateUpperBound(TreeNode &n, const vector<Item> &x, const int bagConstrain)
{
    float upperBound = 0;
    int remainWeight = bagConstrain;
    vector<ItemState> state(n.allItemState);
    
    for (int i=0; i<x.size(); i++) {
        if (state[i] == NON_SELECTED)
            continue;
        
        else if (state[i] == SELECT) {
            if (x[i].weight <= remainWeight) {
                // take all and continue
                upperBound += x[i].value;
                remainWeight -= x[i].weight;
                continue;
            }
            else {
                // take fration and return u.b.
                upperBound += remainWeight * x[i].pricePerWeight;
                return upperBound;
            }
        }
        
        else // if(state[i] == CONSIDERING)
        {
            if (x[i].weight <= remainWeight) {
                // take all and continue
                upperBound += x[i].value;
                remainWeight -= x[i].weight;
                continue;
            }
            else {
                // take fration and return u.b.
                upperBound += remainWeight * x[i].pricePerWeight;
                return upperBound;
            }
        }
    }
    
    return upperBound;
}

// calculate the 0/1 knapsack
int calculateLowerBound(const vector<ItemState> &allItemState, const vector<Item> &x, const int bagConstrain) {
    int nowConstrain = bagConstrain;
    int totalValue = 0;
    
    for (int i=0; i<x.size(); i++) {
        if (nowConstrain < x[i].weight && allItemState[i] == SELECT) {
            return INFEASIBLE;
        }
        
        if (allItemState[i] == SELECT) {
            nowConstrain -= x[i].weight;
            totalValue += x[i].value;
        }
    }
    return totalValue;
}
