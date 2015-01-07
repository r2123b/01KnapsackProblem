//
//  main.cpp
//  01KnapsackProblem
//
//  Created by Lu Kuan-Yin on 12/25/14.
//  Copyright (c) 2014 NTU. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
bool ReadFile(vector<int> &weights, vector<int> &values, int &constrain)
{
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
    //Test the input:
    cout<<"w: ";
    for (int i=0; i<values.size(); i++) {
        cout<<weights[i] <<" ";
    }
    infile.close();
    return true;
}

int main(int argc, const char * argv[]) {
    vector<int> weights;
    vector<int> values;
    int bagConstrain;
    
    ReadFile(weights, values, bagConstrain);
    
    // calculate the price per weight
    
    // calculate the first upper bound
    
    return 0;
}
