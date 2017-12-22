#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
//#include <algorithm>
//#include <vector>
//#include <map>
//#include <functional>
//#include <cmath>
//#include <numeric>
#include <sstream>

#include "dm.hpp"

//using namespace std;

typedef long zqyInsideIdType;

template <class T>
std::string convert2str(T &t)
{
	std::string s;
	std::stringstream ss(s);
	ss << t;
	return ss.str();
}

struct SNodePair
{
	SNodePair(zqyInsideIdType lMin, zqyInsideIdType lMax)
	{
		lMinId = (lMin < lMax) ? lMin : lMax;
		lMaxId = (lMin > lMax) ? lMin : lMax;
	}

	inline bool operator < (const SNodePair &other) const
	{
		if (other.lMinId < this->lMinId)
		{
			return true;
		}

		if (other.lMaxId < this->lMaxId)
		{
			return true;
		}

		return false;
	}

	inline bool operator > (const SNodePair &other) const
	{
		if (other.lMinId > this->lMinId)
		{
			return true;
		}

		if (other.lMaxId > this->lMaxId)
		{
			return true;
		}

		return false;
	}

	inline bool operator == (const SNodePair &other) const
	{
		return ((other.lMinId == this->lMinId)
			&& (other.lMaxId == this->lMaxId));
	}

	inline bool operator != (const SNodePair &other) const
	{
		if (other.lMinId != this->lMinId)
		{
			return true;
		}

		if (other.lMaxId != this->lMaxId)
		{
			return true;
		}

		return false;
	}

	inline bool isValid() const
	{
		return ((lMinId >= 0) && (lMaxId >= 0) && (lMinId != lMaxId));
	}

	std::string toString() const
	{
		std::string str(convert2str(lMinId));
		str.append("-");
		str.append(convert2str(lMaxId));
		return str;
	}

	zqyInsideIdType lMinId;
	zqyInsideIdType lMaxId;
};



bool loadEmbGraph(std::map<int, std::vector<double>> &outDataFrame, const std::string& filename)
{
	if (filename.rfind(".emb") == (filename.length() - 4) || filename.rfind(".EMB") == (filename.length() - 4))
	{
		std::ifstream is;
		is.open(filename.c_str());

		//check
		if (!is.good())
		{
			std::cout << "File failed to load: " << filename << std::endl;
			return false;
		}

		// read first line   NumberOfNodes NumberOfDimensions
		int iNumNodes, iNumDim;

		is >> iNumNodes >> iNumDim;

		std::cout << "NumberOfNodes: " << iNumNodes << ", NumberOfDimensions: " << iNumDim << std::endl;

		if (iNumNodes < 1 || iNumDim < 1)
		{
			std::cout << "NumberOfNodes or NumberOfDimensions is error." << std::endl;
			return false;
		}

		do
		{
			int iIndex;
			std::vector<double> vecDimValue;

			is >> iIndex;

			for (int i = 0; i < iNumDim; ++i)
			{
				double value;
				is >> value;

				vecDimValue.push_back(value);
			}

			outDataFrame[iIndex] = vecDimValue;

		} while (!is.eof());


		// check result
		if (outDataFrame.size() != iNumNodes)
		{
			std::cout << "NumberOfNodes is error." << outDataFrame.size() << std::endl;
			return false;
		}
		//if (outDataFrame.size() != iNumNodes)
		//{
		//	std::cout << "NumberOfNodes or NumberOfDimensions is error." << std::endl;
		//	return false;
		//}

		is.close();
	}

	return true;
}

void printDataFrame(const std::map<int, std::vector<double>> &mapDataFrame)
{
	std::map<int, std::vector<double>>::const_iterator it = mapDataFrame.cbegin();

	while (it != mapDataFrame.cend())
	{
		std::cout << it->first;
		std::vector<double> dimV = it->second;

		for (size_t t = 0; t < dimV.size(); ++t)
		{
			std::cout << " " << dimV[t];
		}

		std::cout << std::endl;

		++it;
	}
}


void computeDistance(std::map<std::string, double> &outDis, const std::map<int, std::vector<double>> &mapDataFrame)
{

#ifdef OUTPUT_RESULT
	std::ofstream ofs("euclidean_distance.txt");
	//ofs << "euclidean_distance:" << std::endl;
#endif

	// generate node-pair
	std::map<int, std::vector<double>>::const_iterator it = mapDataFrame.cbegin();

	while (it != mapDataFrame.cend())
	{
		std::map<int, std::vector<double>>::const_iterator tmp = it;
		std::map<int, std::vector<double>>::const_iterator it2 = ++tmp;

		while (it2 != mapDataFrame.cend())
		{
			SNodePair pair(it->first, it2->first);
			//std::cout << pair.toString() <<",";

			if (pair.isValid())
			{
				double dis = euclidean_distance(it->second, it2->second);
				outDis[pair.toString()] = dis;
				//std::cout << pair.toString() <<"\t"<< dis << endl;

#ifdef OUTPUT_RESULT
				ofs << pair.toString() << "\t" << dis << std::endl;
#endif // end OUTPUT_RESULT

			}

			++it2;
		}

		++it;
	}

	std::cout << "node pair size: " << outDis.size() << std::endl;

#ifdef OUTPUT_RESULT
	ofs.close();
#endif // end OUTPUT_RESULT

}