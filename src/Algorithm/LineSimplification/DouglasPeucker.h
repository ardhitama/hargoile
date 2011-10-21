#ifndef DOUGLASPUECKER_H
#define DOUGLASPUECKER_H

#include <vector>
#include "../../Utility/Point.h"
#include "../../Utility/Number.h"

/*
	T must be Point or the derived class of Point
*/

// might not give accurate result if tolerance > 5km
template <typename T>
void dpReduceRecursive(std::vector<T> &vLineIn, std::vector<T> &vLineOut, const int i, const int j, const double tolerance)
{
	double tmp_dist = -1, dist = -1;
	int f = -1;
	if(i+1 < j)
	{
		for(int k=i+1; k<j; ++k) // find the max point distance from i-j line
		{
			tmp_dist = Number::pointToLineDistance(vLineIn[i].getX(), vLineIn[i].getY(), vLineIn[i].getZ(),
				vLineIn[j].getX(), vLineIn[j].getY(), vLineIn[j].getZ(),
				vLineIn[k].getX(), vLineIn[k].getY(), vLineIn[k].getZ());

			if(tmp_dist > dist) 
			{
				dist = tmp_dist;
				f = k;
			}
		}
	}

	if(dist > tolerance)
	{
		dpReduceRecursive<T>(vLineIn, vLineOut, i, f, tolerance);
		dpReduceRecursive<T>(vLineIn, vLineOut, f, j, tolerance);
	}
	else // if (dist==-1) or this is the last two node left from the divide and conquer
	{
		vLineOut.push_back(vLineIn[i]);
	}
}

// tolerance is in meters
template <typename T>
std::vector<T> dpSimplify(std::vector<T> &vLineIn, double tolerance)
{
	std::vector<T> vLineOut;

	dpReduceRecursive<T>(vLineIn, vLineOut, 0, vLineIn.size()-1, tolerance);
	vLineOut.push_back(vLineIn.back()); // must, dp doens't evaluate to the last node

	return vLineOut;
}


#endif // DOUGLASPUECKER_H
