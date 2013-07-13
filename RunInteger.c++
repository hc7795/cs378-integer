// -------------------------------
// projects/integer/RunInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Integer.c++ RunInteger.c++ -o RunInteger
    % valgrind RunInteger > RunInteger.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <deque>    // deque
#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <math.h> 
#include <algorithm> 


#include "Integer.h"
#include <time.h>
// ----
// main
// ----

int main () {
    using namespace std;
    clock_t t1;
    cout << "RunInteger.c++" << endl << endl;

    // less than 300 ms without valgrind
    // less than  15  s with    valgrind
    cout << "*** 20th Mersenne prime: 1,332 digits ***" << endl << endl;
    t1 = clock();
    {
    const Integer<int> n = Integer<int>(2).pow(4423)-1;
    cout << "2^4423 - 1 = " << n << endl << endl;
    }
    t1 = clock() - t1;
    cout<<"Time For 20th Mersenne using Vector =  " << ((float)t1)/CLOCKS_PER_SEC << " seconds "<<endl;
    cout<<endl;
    return 0;}
