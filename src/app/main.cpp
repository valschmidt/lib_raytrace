//
//  main.cpp
//  raytrace
//
//  Created by Eric Keilty and Val Schmit on 7/9/15.
//  Copyright (c) 2015-2019 University of New Hampshire. All rights reserved.
//

#include "ssp.h"
#include "regular_ssp.h"
#include "sparse_ssp.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;


int main(int argc, char* argv[]) {
    
    // FIX: This logic isn't quite right. If one doesn't specify the twtt and launch angle
    // FIX: individually then one must specify a file containing pairs of them. 
    if (argc < 3)
    {
    	printf("\n");
        printf("Error: not enough arguments!\n");
        printf("\n");
        printf("Usage:\n");
        printf("    raytrace -ssp <svp_file.txt> [-a <launch_angle> -t <owtt> | -angle <angle_tt.txt>] \n");
        printf("        [-d decimation_factor]\n");
        printf("\n");
        printf("    svp_file.txt: Space or comma delimited file, containing two columns of \n");
        printf("                  depths in meters and sound speeds in m/s.\n");
        printf("    launch_angle: Launch angle in degrees, down from horizontal.\n");
        printf("    owtt:         One-way travel time in seconds.\n");
        printf("    angle_tt.txt: Optionally, a list of launch angles and one way travel times\n");
        printf("                  may be specified in this space or comma delimited file, \n");
        printf("                  containing two columns of values. [angle twtt] \n");
        printf("    decimation_factor: When specified, the sound speed profile is \n");
        printf("                  decimated by omitting entries whose gradient is larger than \n");
        printf("                  the decimation_factor.\n");
        printf("    launch_angle: Not sure.\n");
        printf("\n");
        return 1;
    }
    
    // Input arguments
    string svp_txt;
    string angle_txt;
    string out_file;
    double decimate = 0;
    double launch_angle = 0;
    double travel_time = 0;
    bool angle_exists = false;
    double default_max_gradient = 0.01;

    
    // Utility variables
    bool out_file_exist = false;
    string line;
    int number_of_lines = 0;
    vector<double> z;   // Depth, m
    vector<double> c;	 // Sound speed, m/s
    vector<double> theta;                // Launch angle, deg
    vector<double> tt;                   // Travel time, sec.

    
    // Parse the input arguments. 
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-ssp") == 0)
        {
            svp_txt = argv[i+1];
        }
        else if (strcmp(argv[i], "-angle") == 0)
        {
            angle_txt = argv[i+1];
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            if (stof(argv[i+1]) == 0)
            {
                decimate = default_max_gradient;
                printf("default minimum gradient change: %0.3f", default_max_gradient);
            }
            else
            {
                decimate = stof(argv[i+1]);
            }
            
        }
        else if (strcmp(argv[i], "-a") == 0)
        {
            launch_angle = stof(argv[i+1]);
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            travel_time = stof(argv[i+1]);
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            out_file = argv[i+1];
        }
    }
    
    // Verifying that the files exist and are readable.

	// output file.    
    ifstream out_file_check(out_file);
    if (getline(out_file_check, line))
    {
        out_file_exist = true;
    }
    out_file_check.close();
    
    // sound speed file
    ifstream svp_file_check(svp_txt);
    if (!getline(svp_file_check, line))
    {
        printf("Usage: svp text file not found\n");
        return 1;
    }
    svp_file_check.close();
    
    // angle twtt file
    ifstream angle_file_check(angle_txt);
    if (!getline(angle_file_check, line))
    {
        if (launch_angle <= 0 || travel_time <= 0)
        {
            printf("Usage: either angle/travel time text file not found or one of them had an input less than or equal to zero\n");
            return 1;
        }
        else if (launch_angle == 90)
        {
            /*special case*/
        }
    }
    else
    {
        angle_exists = true;
    }
    angle_file_check.close();

    //counting number of lines in txt file    
    ifstream svp_file(svp_txt);
    while(getline(svp_file, line))
    {
        ++number_of_lines;
    }
    z.resize(number_of_lines);
    c.resize(number_of_lines);
    
 	// Read the Sound Speed Profile file:
 	// handling either space or comma delimiters...   
    char delim = ',';
    
    // <line> currently has the last line in the file...
    // basically if line.find(delim) is defined properly, then continue
    //else there must be no delimiter, so this method won't work
    //IMPORTANT: this makes the assumption that the last line of the code is
    //the same as the previous thousand
    //if there is some text at the end the whole thing will crash
    //this could be changed to read the first line instead
    //but i figured the last line was easier and safer
    if ( 0 >= line.find(delim) || line.size() <= line.find(delim) ) //check this
    {
        //going back to the top of the txt file
        svp_file.clear();
        svp_file.seekg (0, ios::beg);
        int num_line = 0;
            
        while(getline(svp_file, line))
        {
            //if there is only white space between the numebrs
            //creates a vector that looks like ["num", "num"]
            string buf;
            stringstream ss(line);
            vector<string> tokens;
            while (ss >> buf)
            {
                tokens.push_back(buf);
            }
            //cout << num_line + 1 << ": " << tokens[0] << " " << tokens[1] << endl;
            
            z[num_line] = stof(tokens[0]);
            c[num_line] = stof(tokens[1]);
            
            num_line++;
        }
    }
    else
    {
        //going back to the top of the txt file
        
        svp_file.clear();
        svp_file.seekg (0, ios::beg);
        int num_line = 0;
        
        //splitting txt file into 2 vectors
        while(getline(svp_file, line))
            
        {
            //if there is some delimiter separating the numbers
            line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
            size_t pos = line.find(delim);
            
            z[num_line] = stof(line.substr(0, pos));
            c[num_line] = stof(line.substr(pos + 1));
            
            num_line++;
            
        }
    }
    svp_file.close();

    
    // Read the angle and travel time file:
    if (angle_exists)
    {
        delim = ',';
        number_of_lines = 0;
        ifstream angle_file(angle_txt);
        //counting number of lines in txt file
        while(getline(angle_file, line))
        {
            ++number_of_lines;
        }
        
        theta.resize(number_of_lines);
        tt.resize(number_of_lines);
        
        //basically if line.find(delim) is defined properly, then continue
        //else there must be no delimiter, so this method won't work
        //IMPORTANT: this makes the assumption that the last line of the code is
        //the same as the previous thousand
        //if there is some text at the end the whole thing will crash
        //this could be changed to read the first line instead
        //but i figured the last line was easier and safer
        if ( 0 >= line.find(delim) || line.size() <= line.find(delim) ) //check this
        {
            //going back to the top of the txt file
            angle_file.clear();
            angle_file.seekg (0, ios::beg);
            int num_line = 0;
            
            while(getline(angle_file, line))
            {
                //if there is only white space between the numebrs
                //creates a vector that looks like ["num", "num"]
                string buf;
                stringstream ss(line);
                vector<string> tokens;
                while (ss >> buf)
                {
                    tokens.push_back(buf);
                }
                //cout << num_line + 1 << ": " << tokens[0] << " " << tokens[1] << endl;
                
                theta[num_line] = stof(tokens[0]);
                tt[num_line] = stof(tokens[1]);
                
                num_line++;
            }
        }
        else
        {
            //going back to the top of the txt file
            
            angle_file.clear();
            angle_file.seekg (0, ios::beg);
            int num_line = 0;
            
            //splitting txt file into 2 vectors
            while(getline(angle_file, line))
                
            {
                //if there is some delimiter separating the numbers
                line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
                size_t pos = line.find(delim);
                
                theta[num_line] = stof(line.substr(0, pos));
                tt[num_line] = stof(line.substr(pos + 1));
                
                num_line++;
                
            }
        }
        angle_file.close();
    }
    else
    {
        theta.resize(1);
        tt.resize(1);
        
        theta[0] = launch_angle;
        tt[0] = travel_time;
    }
    
    
    
    //it's not pretty but it's only way to do it that I could come up with
    if (decimate == 0)
    {
        ssp test = ssp(z, c);
        
        for (int i = 0; i < tt.size(); i++)
        {
            //assuming theta is in degrees
            vector< vector<double> > output_vector = test.raytrace(0, 0, (M_PI/180)*theta[i], tt[i]);
            
            if (out_file_exist)
            {
                ofstream out;
                out.open(out_file, std::ios::app);
                
                for (int j = 0; j < output_vector[0].size(); j++)
                    
                {
                    out << output_vector[0][j] << '\t' << output_vector[1][j] << '\t' << output_vector[2][j] << '\t' << output_vector[3][j] << endl;
                }
                out.close();
            }
            else
            {
                for (int j = 0; j < output_vector[0].size(); j++)
                    
                {
                    printf("%f\t%f\t%f\t%f\n", output_vector[0][j], output_vector[1][j], output_vector[2][j], output_vector[3][j]);
                }
            }
            cout << "\n" << endl;
        }
    }
    else
    {
        sparsed_ssp test = sparsed_ssp(z, c);
        
        for (int i = 0; i < tt.size(); i++)
        {
            //assuming theta is in degrees
            vector< vector<double> > output_vector = test.raytrace(0, 0, (M_PI/180)*theta[i], tt[i], decimate);
            
            if (out_file_exist)
            {
                ofstream out;
                out.open(out_file, std::ios::app);
                
                for (int j = 0; j < output_vector[0].size(); j++)
                    
                {
                    out << output_vector[0][j] << '\t' << output_vector[1][j] << '\t' << output_vector[2][j] << '\t' << output_vector[3][j] << endl;
                }
                out.close();
            }
            else
            {
                for (int j = 0; j < output_vector[0].size(); j++)
                    
                {
                    printf("%f\t%f\t%f\t%f\n", output_vector[0][j], output_vector[1][j], output_vector[2][j], output_vector[3][j]);
                }
            }
            cout << "\n" << endl;
        }
    }
    
    return 0;
}
