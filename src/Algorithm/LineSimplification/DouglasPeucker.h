#ifndef DOUGLASPUECKER_H
#define DOUGLASPUECKER_H

#include <vector>
#include <algorithm>

#include "../../Utility/Point.h"
#include "../../Utility/Number.h"

/*
T must be Point or the derived class of Point
*/

#include <map>
#include <iostream>

// analytics
inline bool isExist(std::vector<int> map, int id)
{
    for(int i=0; i<map.size(); ++i)
    {
        if(map[i] == id)
            return true;
    }
    return false;
}
static std::vector<int> elPair;
// analytics

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

		// analytics
        for(int l=i+1; l<j; ++l)
        {
            //if(l != f)
            {
                tmp_dist = Number::pointToLineDistance(vLineIn[i].getX(), vLineIn[i].getY(), vLineIn[i].getZ(),
                                                       vLineIn[j].getX(), vLineIn[j].getY(), vLineIn[j].getZ(),
                                                       vLineIn[l].getX(), vLineIn[l].getY(), vLineIn[l].getZ());
                int id= vLineIn[l].id;
                if(!isExist(elPair, id))
                {
                    elPair.push_back(vLineIn[l].id);
                    std::cout << "id= " << vLineIn[l].id << " " << vLineIn[l].getLatitude() << ", " << vLineIn[l].getLongitude() << " d from line: " << tmp_dist << " m \n";
                }
            }
        }
		// analytics
    }
}

// tolerance is in meters
template <typename T>
std::vector<T> dpSimplify(std::vector<T> &vLineIn, double tolerance)
{
	if(tolerance > 5000)
		DebugInfo("Tolerance >5 km will give lost of accuracy", DebugInfo::Warning);
    std::vector<T> vLineOut;

    dpReduceRecursive<T>(vLineIn, vLineOut, 0, vLineIn.size()-1, tolerance);
    vLineOut.push_back(vLineIn.back()); // must, dp doens't evaluate to the last node

    std::cout << "size = " << elPair.size() << std::endl; //analytics

    return vLineOut;
}

#endif // DOUGLASPUECKER_H
