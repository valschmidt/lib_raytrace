//
//  Stats.cpp
//  raytrace
//
//  Created by Eric Keilty on 7/30/15.
//  Copyright (c) 2015 Assembly. All rights reserved.
//

#include "Stats.h"
#include <math.h>

vector<double> Stats::basic(vector<double> data)
{
    
    unsigned long n = data.size();
    
    double sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    
    double mean = sum/n;
    
    double t = 0;
    for (int i = 0; i < data.size(); i++)
    {
        t += pow(data[i] - mean, 2);
    }
    
    double StdDev = sqrt(t/(n-1));
    
    vector<double> output(3);
    output[0] = mean;
    output[1] = StdDev;
    output[2] = n;
    
    return output;
}