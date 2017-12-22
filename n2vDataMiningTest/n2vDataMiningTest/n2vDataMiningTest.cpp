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


int main()
{
	//std::vector<double> v1 = { 4.75,4.5,5.0,4.25,4.0 };
	//std::vector<double> v2 = { 4.0,3.0,5.0,2.0,1.0 };

	std::vector<double> v1 = { 3.5, 2.0, 0.0, 4.5, 5.0, 1.5, 2.5, 2.0};
	std::vector<double> v2 = { 2.0, 3.5, 4.0, 0.0, 2.0, 3.5, 0.0, 3.0};

//"Angelica": {"Blues Traveler": 3.5, "Broken Bells" : 2.0, "Norah Jones" : 4.5, "Phoenix" : 5.0, "Slightly Stoopid" : 1.5, "The Strokes" : 2.5, "Vampire Weekend" : 2.0},
//"Bill" : {"Blues Traveler": 2.0, "Broken Bells" : 3.5, "Deadmau5" : 4.0, "Phoenix" : 2.0, "Slightly Stoopid" : 3.5, "Vampire Weekend" : 3.0},

	//std::cout << euclidean_distance(v1, v2) << "\n";

	std::cout << pearson(v1, v2) << "\n";
	
	// TEST n2v
	//std::map<int, std::vector<double>> dataFrame;

	//loadEmbGraph(dataFrame, "./emb/karate.emb");

	//std::map<std::string, double> Dis;

	//computeDistance(Dis, dataFrame);
	// END TEST n2v

	return 0;
}