# lib_raytrace

A library and command-line utility for acoustic raytracing.

Val Schmidt
Eric Keilty
Center for Coastal and Ocean Mapping
University of New Hamphshire
Copyright 2015-2019

lib_raytrace is a C++ library and command-line utility for acoustic ray-tracing. It is based on MATLAB code written by Val, which uses the gradient-based approximation to Snell's law, and coded in C++ by Eric (as a high-school student) during a 2015 summer internship at the Center. 

To build try the following:

    git clone lib_raytrace
    cd lib_raytrace
    mkdir build
    cd build
    cmake ../
    make

To give it a go, try:

    ./src/app/main -ssp ../test_data/depths_svp.txt -angle ../test_data/theta_tt.txt
    0.000000  0.000000  0.000000  0.000000
    113.463051  20.000000  115.211168  0.082294
    250.902004  45.000000  255.039142  0.182167
    331.009553  60.000000  336.534133  0.240447
    357.464722  65.000000  363.465897  0.259712
    383.668251  70.000000  390.141066  0.278806
    409.650205  75.000000  416.607259  0.297750
    435.303474  80.000000  442.745411  0.316472
    461.078432  85.000000  468.995079  0.335277
    1368.636245  270.276931  4552.740129  1.000000

    0.000000  0.000000  0.000000  0.000000
    54.954218  20.000000  58.479924  0.041772
    123.073196  45.000000  131.111359  0.093649
    163.623280  60.000000  174.344312  0.124566
    177.104219  65.000000  188.727029  0.134855
    190.548376  70.000000  203.070247  0.145122
    203.959231  75.000000  217.386934  0.155369
    217.319895  80.000000  231.653711  0.165588
    230.699277  85.000000  245.933703  0.175818
    2376.903489  900.000000  2546.901420  1.823332
    2513.095240  950.000000  2691.084433  1.925773
    2609.435625  988.713933  15122.903920  2.000000

Here `depths_svp.txt` is space delimited text file with two columns of depth (m) and sound speed (m/s), and `theta_tt.txt` is a space delimited text file with two columns of launch angles and one-way travel times (in seconds). 

The results consist of a table (one for each raytrace of input angle/travel time pair), in which the first two columns provide the horizontal and vertical coordinates of each step along the traced ray, the third column gives the cumulative distance traveled and fourth gives the cumulative one-way travel time. The number of entries in the table is equal to the number of entries in the input sound speed profile.




> Written with [StackEdit](https://stackedit.io/).
