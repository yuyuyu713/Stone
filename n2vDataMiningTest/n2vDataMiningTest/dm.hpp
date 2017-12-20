#pragma once

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <numeric>
//#include <sstream>


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


// TODO: 当vector有些没有记录被0.0填充时，结果与python计算的不一样 
template <typename T>
double pearson(const std::vector<T>& a, const std::vector<T>& b)
{
	double n = a.size();
	
	std::vector<double>	xy;
	std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(xy),//
		[](T element1, T element2) {return (element1 * element2); });

	double sum_xy = std::accumulate(xy.begin(), xy.end(), 0.0);

	double sum_x = std::accumulate(a.begin(), a.end(), 0.0);
	double sum_y = std::accumulate(b.begin(), b.end(), 0.0);

	std::vector<double>	x2;
	std::transform(a.begin(), a.end(), std::back_inserter(x2),//
		[](T element1) -> T { return pow(element1, 2); });

	std::vector<double>	y2;
	std::transform(b.begin(), b.end(), std::back_inserter(y2),//
		[](T element1) -> T { return pow(element1, 2); });

	double sum_x2 = std::accumulate(x2.begin(), x2.end(), 0.0);
	double sum_y2 = std::accumulate(y2.begin(), y2.end(), 0.0);

	double denominator = sqrt(sum_x2 - pow(sum_x, 2) / n) * sqrt(sum_y2 - pow(sum_y, 2) / n);

	return (sum_xy - (sum_x*sum_y) / n) / denominator;
}

// 计算中位数
template <typename T>
double	getMedian(const std::vector<T>& a)
{
	size_t n = a.size();
	std::sort(a.begin(), a.end());

	if (1 == n % 2)
	{
		return a[int(((n + 1) / 2) - 1)];
	}

	T v1 = a[int(n / 2)];
	T v2 = a[(int(n / 2) - 1)];

	return  ((v1 + v2) / 2.0);
} // end template

//def getAbsoluteStandardDeviation(self, alist, median) :
//	"""given alist and median return absolute standard deviation"""
//	sum = 0
//	for item in alist :
//sum += abs(item - median)
//return sum / len(alist)

// 计算“标准差”
template <typename T>
double	getAbsoluteStandardDeviation(const std::vector<T>& a, T median)
{
	size_t n = a.size();

	if (0 == n)
	{
		return n;
	}

	T sum = 0;

	for (auto val : a)
	{
		sum += abs(val - median);
	}

	return  (sum / n);
} // end template