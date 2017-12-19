// n2vDataMiningTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <numeric>
#include <sstream>

using namespace std;

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
		lMinId = (lMin < lMax)?lMin:lMax;
		lMaxId = (lMin > lMax)?lMin:lMax;
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
		return ( (lMinId >= 0 ) && (lMaxId >= 0) && (lMinId != lMaxId) );
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


// Computes the distance between two std::vectors
template <typename T>
double	manhattan_distance(const std::vector<T>& a, const std::vector<T>& b)
{
	std::vector<double>	auxiliary;

	std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),//
		[](T element1, T element2) {return abs(element1 - element2); });

	auxiliary.shrink_to_fit();

	return  (std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
} // end template vectors_distance


  // Computes the distance between two std::vectors
template <typename T>
double	euclidean_distance(const std::vector<T>& a, const std::vector<T>& b)
{
	std::vector<double>	auxiliary;

	std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),//
		[](T element1, T element2) {return pow((element1 - element2), 2); });

	auxiliary.shrink_to_fit();

	return  sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
} // end template vectors_distance


bool loadEmbGraph(std::map<int, std::vector<double>> &outDataFrame, const std::string& filename);

void printDataFrame(const std::map<int, std::vector<double>> &mapDataFrame);

void computeDistance(std::map<string, double> &outDis, const std::map<int, std::vector<double>> &mapDataFrame);


#define OUTPUT_RESULT

int main()
{
	////std::vector<double> v1 = { 0.1,0.3,0.4 };
	////std::vector<double> v2 = { -0.1,-0.3,-0.4 };

	std::vector<double> v1 = { 1,4 };
	std::vector<double> v2 = { 4,2 };

	//std::cout << euclidean_distance(v1, v2) << "\n";

	std::cout << manhattan_distance(v2, v1) << "\n";
	
	return 0;

	std::map<int, std::vector<double>> mapDataFrame;
	string fileName("./emb/karate.emb");

	if (!loadEmbGraph(mapDataFrame, fileName))
	{
		std::cout << "loadEmbGraph fail ." << "\n";

		return 0;
	}

	//printDataFrame(mapDataFrame);

	//std::cout <<"euclidean_distance of node[0] & node[1]: " << euclidean_distance(mapDataFrame[0], mapDataFrame[1]) << "\n";

	std::map<std::string, double> mapDistance;

	computeDistance(mapDistance, mapDataFrame);


    return 0;
}

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
			vector<double> vecDimValue;

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

		std::cout << endl;

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

			if(pair.isValid())
			{
				double dis = euclidean_distance(it->second, it2->second);
				outDis[pair.toString()] = dis;
				//std::cout << pair.toString() <<"\t"<< dis << endl;

#ifdef OUTPUT_RESULT
				ofs << pair.toString() << "\t" << dis << endl;
#endif // end OUTPUT_RESULT

			}

			++it2;
		}

		++it;
	}

	std::cout << "node pair size: " << outDis.size() << endl;

#ifdef OUTPUT_RESULT
	ofs.close();
#endif // end OUTPUT_RESULT

}