//
//  Stats.h
//  raytrace
//
//  Created by Eric Keilty on 7/30/15.
//  Copyright (c) 2015 Assembly. All rights reserved.
//

#ifndef __raytrace__Stats__
#define __raytrace__Stats__

#include <stdio.h>
#include <vector>
using namespace std;

class Stats
{
public:
    Stats()
    {
    }
    
    vector<double> basic(vector<double> data);
};


#endif /* defined(__raytrace__Stats__) */