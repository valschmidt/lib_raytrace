//
//  regular_ssp.cpp
//  raytrace
//
//  Created by Eric Keilty on 8/4/15.
//  Copyright (c) 2015 Assembly. All rights reserved.
//

#include "regular_ssp.h"
#include <math.h>

vector< vector<double> > regular_ssp::raytrace(double z0, double x0, double theta0, double owtt)
{
    
    //z and c are member variables so I would rather keep them constant
    vector<double> z2 = z;
    vector<double> c2 = c;
    
    //calulating all the gradients
    vector<double> gradient(z2.size() - 1);
    vector<double> dz(z2.size() - 1);
    vector<double> dc(z2.size() - 1);
    
    for (int i = 0; i < gradient.size(); i++)
    {
        gradient[i] = (c2[i] - c2[i+1])/(z2[i] - z2[i+1]);
        dz[i] = z2[i + 1] - z2[i]; //do we want dz to be positive or negative
        dc[i] = c2[i + 1] - c2[i]; //same here...prolly positive
    }
    
    double min_z = fabs(z2[0] - z0);
    int q = 0;
    for (int i = 0; i < z2.size(); i++)
    {
        if (fabs(z2[i] - z0) < min_z)
        {
            min_z = z2[i];
            q = i; //q is the index of the ssp closes to z0
        }
    }
    int q_start = q;
    
    //initializing variables
    vector<double> theta(dz.size()); //ray angle
    theta[q] = fabs(theta0); //fabs(theta0) * M_PI/180;
    vector<double> x(z2.size()); //distance of ray path
    x[q] = x0; //where does x0 come from? cuz he didn't have me pass it as an input
    vector<double> dx(dz.size()); //change in distance of the ray path
    vector<double> ddd(z2.size());
    //vector<double> z2(z.size());
    
    double t = 0; //cumulative travel time
    double d = 0; //cumulative distance
    vector<double> ttt(z2.size()); //vector of the travel times between each layer
    ttt[0] = t;
    
    double dd = 0;
    double dt = 0;
    
    //check if t is suppose to be less than owtt --> translates to tt in matlab code
    while (t < owtt) {
        
        double Rc;
        
        if (theta[q] > M_PI/2 || theta[q] < -M_PI/2)
        {
            break;
        }
        
        if (q == gradient.size())
        {
            gradient.resize(q+1);
            gradient[q] = -0.017;
            
            x.resize(q+2);
            dx.resize(q+1);
            
            theta.resize(q+2);
            
            ddd.resize(q+2);
            
            ttt.resize(q+2);
            
            z2.resize(q+1);
            dz.resize(q+1);
            
            dz[q] = dz[q-1];
            z2[q] = z2[q-1] + dz[q-1];
            
            c2.resize(q+1);
            dc.resize(q+1);
            
            dc[q] = dc[q-1];
            c2[q] = c2[q-1];
            
            //cout << "true" << '\t' << q << endl;
            /*
             for (int i = 0; i < z2.size(); i++)
             {
             cout << z2[i] << '\t' << c2[i] << endl;
             }
             cout << endl;
             */
            break;
        }
        
        if (gradient[q] == 0)
        {
            theta[q + 1] = theta[q]; //no gradient change
            
            if (theta[q] == 0)
            {
                dx[q] = fabs(dz[q]); //horizontal ray
            }
            else
            {
                dx[q] = fabs(dz[q] / tan(theta[q]));
            }
            
            dd = sqrt(pow(dx[q], 2) + pow(dz[q], 2));
            dt = dd/c2[q];
        }
        else
        {
            Rc = (-1/gradient[q]) * (c2[q]/cos(theta[q]));
            theta[q + 1] = acos( cos(theta[q]) - (dz[q]/Rc) );
            
            //cout << theta[q+1] << '\t' << Rc << '\t' << c2[q] << endl;
            
            //if x > 1 or x < -1, then acos(x) will give a complex number
            //that way is faster than doing fabs( ... ) > 1
            if (( cos(theta[q]) - (dz[q]/Rc) ) < -1 || ( cos(theta[q]) - (dz[q]/Rc) ) > 1)
            {
                theta[q + 1] = -theta[q];
                //cout << "true" << endl;
                
                //can probably take out z_flipped
                /*
                 double min_tmp = fabs(z_flipped[q+1] - z_flipped[q]);
                 int tmp = 0;
                 for (int i = (q+2); i < q + 2*c2.size(); i++) //check this
                 {
                 if (z_flipped[i] == 0 && z_flipped.size() < i + 1)
                 {
                 break;
                 }
                 
                 if (fabs(z_flipped[i] - z_flipped[q]) < min_tmp)
                 {
                 min_tmp = fabs(z_flipped[i] - z_flipped[q]);
                 tmp = i;
                 }
                 }
                 */
                double min_tmp = fabs(z2[q+1] - z2[q]);
                int tmp = 0;
                for (int i = (q+2); i < q + 2*z2.size(); i++) //check this
                {
                    if (z2[i] == 0 && z2.size() < i + 1)
                    {
                        break;
                    }
                    
                    if (fabs(z2[i] - z2[q]) < min_tmp)
                    {
                        min_tmp = fabs(z2[i] - z2[q]);
                        tmp = i;
                    }
                }
                
                //we are skipping the values in certain vectors from q to q + tmp
                vector<double> z_new(z2.size());
                vector<double> c_new(c2.size());
                double zshift = z2[q + tmp + 1] - z2[q];
                for (int i = 0; i < q + 1; i++)
                {
                    z_new[i] = z2[i];
                    c_new[i] = c2[i];
                    //z2[i] = z_flipped[i];
                }
                
                for (int i = q + tmp; i < z2.size(); i++)
                {
                    z_new[i] = z2[i] - zshift;
                    c_new[i] = c2[i];
                    //z2[i] = z_flipped[i];
                }
                
                for (int i = 0; i < z_new.size(); i++)
                {
                    dz[i] = z_new[i+1] - z_new[i];
                    dc[i] = c_new[i+1] - c_new[i];
                    gradient[i] = (c_new[i] - c_new[i+1])/(z_new[i] - z_new[i+1]);
                }
                
                dx[q] = 0;
                dt = 0;
                dd = 0;
            }
            else
            {
                if (theta[q] > 0)
                {
                    dx[q] = Rc * (sin(theta[q+1]) - sin(theta[q]));
                    dt = (-2/gradient[q]) * ( atanh(tan(theta[q+1]/2)) - atanh(tan(theta[q]/2)) );
                }
                else
                {
                    dx[q] = fabs(Rc * -( sin(theta[q+1]) - sin(theta[q]) ));
                    dt = (-2/gradient[q]) * ( atanh(tan(theta[q+1]/2)) - atanh(tan(theta[q]/2)) );
                }
                
                dd = dt * (c2[q] + gradient[q]/2);
            }
        }
        
        t += dt;
        ttt[q+1] = t;
        x[q+1] = (x[q] + dx[q]);
        d += dd;
        ddd[q+1] = d;
        q++;
        
        //cout << q << "\t" << x.size() << endl;
    }
    
    //this would take values off the end of the vector, We proabably want the values to come off the begining
    
    x.erase(x.begin(), x.begin() + q_start);
    z2.erase(z2.begin(), z2.begin() + q_start);
    ddd.erase(ddd.begin(), ddd.begin() + q_start);
    ttt.erase(ttt.begin(), ttt.begin() + q_start);
    
    x.resize(q - q_start + 1);
    z2.resize(q - q_start + 1);
    ddd.resize(q - q_start + 1);
    ttt.resize(q - q_start + 1);
    
    //correcting the raytrace
    double corrector = (owtt - (t-dt))/dt;
    x[q-q_start] = (x[q-q_start - 1] + corrector*(x[q-q_start] - x[q-q_start - 1]));
    z2[q-q_start] = (z2[q-q_start - 1] + corrector*(z2[q-q_start] - z2[q-q_start - 1]));
    t = ((t-dt) + dt*corrector);
    ttt[q-q_start] = t;
    
    vector< vector<double> > outputs;
    
    outputs.resize(4);
    outputs[0].resize(x.size());
    outputs[1].resize(z2.size());
    outputs[2].resize(ddd.size());
    outputs[3].resize(ttt.size());
    
    for (int i = 0; i < x.size(); i++)
    {
        outputs[0][i] = x[i];
        outputs[1][i] = z2[i];
        outputs[2][i] = ddd[i];
        outputs[3][i] = ttt[i];
    }
    
    return outputs; //[ [x1, x2, ...], [z1, z2, ...], [ddd1, ddd2, ...], [ttt1, ttt2, ...] ]
}