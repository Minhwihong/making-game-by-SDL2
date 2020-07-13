//============================================================================
// Name        : ArcadeApp.cpp
// Author      : Serge Lanisquot
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//======2======================================================================

#include <iostream>
#include "Vec2D.h"

using namespace std;


int main(int argc, const char * argv[])
{
	Vec2D aVec(3,7);

	Vec2D resultVec = 3 * aVec;

	cout << resultVec << endl;

    return 0;
}
