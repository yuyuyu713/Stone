// n2vDataMiningTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <iterator>
//#include <algorithm>
//#include <vector>
//#include <map>
//#include <functional>
//#include <cmath>
//#include <numeric>
//#include <sstream>


#define OUTPUT_RESULT

#include "n2v_define.hpp"

//using namespace std;

void TEST_n2v();
void TEST_normalizeVector();

int main()
{
	//std::vector<double> v1 = { 4.75,4.5,5.0,4.25,4.0 };
	//std::vector<double> v2 = { 4.0,3.0,5.0,2.0,1.0 };

	std::vector<double> v1 = { 3.5, 2.0, 0.0, 4.5, 5.0, 1.5, 2.5, 2.0};
	std::vector<double> v2 = { 2.0, 3.5, 4.0, 0.0, 2.0, 3.5, 0.0, 3.0};

//"Angelica": {"Blues Traveler": 3.5, "Broken Bells" : 2.0, "Norah Jones" : 4.5, "Phoenix" : 5.0, "Slightly Stoopid" : 1.5, "The Strokes" : 2.5, "Vampire Weekend" : 2.0},
//"Bill" : {"Blues Traveler": 2.0, "Broken Bells" : 3.5, "Deadmau5" : 4.0, "Phoenix" : 2.0, "Slightly Stoopid" : 3.5, "Vampire Weekend" : 3.0},

	//std::cout << euclidean_distance(v1, v2) << "\n";
	//std::cout << pearson(v1, v2) << "\n";

	// TEST_n2v();

	TEST_normalizeVector();

	return 0;
}

void TEST_n2v()
{
	// TEST n2v
	std::map<int, std::vector<double>> dataFrame;
	loadEmbGraph(dataFrame, "./emb/karate.emb");
	std::map<std::string, double> Dis;
	computeDistance(Dis, dataFrame);
	// END TEST n2v
}


void TEST_normalizeVector()
{
	std::vector<double> list1 = { 54, 72, 78, 49, 65, 63, 75, 67, 54, 76, 68,
		61, 58, 70, 70, 70, 63, 65, 66, 61 };

	std::vector<double> list2 = { 66, 162, 204, 90, 99, 106, 175, 123, 68,
		200, 163, 95, 77, 108, 155, 155, 108, 106, 97, 76 };

	double m1 = getMedian(list1);
	double m2 = getMedian(list2);

	double asd1 = getAbsoluteStandardDeviation(list1, m1);
	double asd2 = getAbsoluteStandardDeviation(list2, m2);

	std::vector<double> score1;
	std::vector<double> score2;

	normalizeVector(score1, m1, asd1, list1);
	normalizeVector(score2, m2, asd2, list2);

	std::cout << "Median:"<< m1 << ",ASD:"<< asd1 <<"\n"; // 65.5, 5.95
	for (size_t i = 0; i<score1.size(); ++i)
	{
		//std::cout << "["<< score1[i] << ","<< score2[i] << "]"<<"\n";
		std::cout << score1[i] << "\n";
	}

	std::cout << "Median:" << m2 << ",ASD:" << asd2 << "\n"; // 107, 33.65
	for (size_t i = 0; i<score2.size(); ++i)
	{
		//std::cout << "[" << score1[i] << "," << score2[i] << "]" << "\n";
		std::cout << score2[i] << "\n";
	}

	std::cout << "\n";
}