//
//  regular_ssp.h
//  raytrace
//
//  Created by Eric Keilty on 8/4/15.
//  Copyright (c) 2015 Assembly. All rights reserved.
//

#ifndef __raytrace__regular_ssp__
#define __raytrace__regular_ssp__

#include <stdio.h>
#include <vector>
using namespace std;

class regular_ssp
{
public:
    vector<double> z;
    vector<double> c;
    
    regular_ssp(vector<double> Z, vector<double> C)
    {
        z = Z;
        c = C;
    }
    
    //check is z0 or owtt are actually ints
    vector< vector<double> > raytrace(double z0, double x0, double theta0, double owtt);
};

#endif /* defined(__raytrace__regular_ssp__) */