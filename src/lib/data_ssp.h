//
//  data_ssp.h
//  raytrace
//
//  Created by Eric Keilty on 8/4/15.
//  Copyright (c) 2015 Assembly. All rights reserved.
//

#ifndef __raytrace__data_ssp__
#define __raytrace__data_ssp__

#include <stdio.h>
#include <vector>
using namespace std;

class data_ssp
{
public:
    vector<double> z;
    vector<double> c;
    
    data_ssp(vector<double> Z, vector<double> C)
    {
        z = Z;
        c = C;
    }
    
    //check is z0 or owtt are actually ints
    vector< vector<double> > raytrace(double z0, double x0, double theta0, double owtt);
    vector< vector<double> > raytrace_simple(double z0, double x0, double theta0, double owtt);
    vector< vector<double> > raytrace_angle( vector<double> theta, vector<double> ttt);
};

#endif /* defined(__raytrace__data_ssp__) */