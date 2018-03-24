// KMeans-GMM-HMM.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
//
//
//int main()
//{
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <assert.h>
#include "KMeans.h"
#include "CHMM.h"
#include "GMM.h"


using namespace std;

int kMeans_main();
int GMM_main();

int main()
{
	//cout << "Hello world!" << endl;
	kMeans_main();

	//GMM_main();

	return 0;
}

int kMeans_main()
{
	double data[] = {
		0.0, 0.2, 0.4,
		0.3, 0.2, 0.4,
		0.4, 0.2, 0.4,
		0.5, 0.2, 0.4,
		5.0, 5.2, 8.4,
		6.0, 5.2, 7.4,
		4.0, 5.2, 4.4,
		10.3, 10.4, 10.5,
		10.1, 10.6, 10.7,
		11.3, 10.2, 10.9
	};

	const int size = 10; //Number of samples
	const int dim = 3;   //Dimension of feature
	const int cluster_num = 4; //Cluster number

	KMeans* kmeans = new KMeans(dim, cluster_num);
	int* labels = new int[size];
	kmeans->SetInitMode(KMeans::InitUniform);
	kmeans->Cluster(data, size, labels);

	for (int i = 0; i < size; ++i)
	{
		printf("%f, %f, %f belongs to %d cluster\n", data[i*dim + 0], data[i*dim + 1], data[i*dim + 2], labels[i]);
	}

	delete[]labels;
	delete kmeans;

	return 0;
}

int GMM_main()
{
	double data[] = {
		0.0, 0.2, 0.4,
		0.3, 0.2, 0.4,
		0.4, 0.2, 0.4,
		0.5, 0.2, 0.4,
		5.0, 5.2, 8.4,
		6.0, 5.2, 7.4,
		4.0, 5.2, 4.4,
		10.3, 10.4, 10.5,
		10.1, 10.6, 10.7,
		11.3, 10.2, 10.9
	};

	const int size = 10; //Number of samples
	const int dim = 3;   //Dimension of feature
	const int cluster_num = 4; //Cluster number

	double test_data[4][3] = {
		0.1, 0.2, 0.3,
		0.4, 0.5, 0.6,
		5.0, 6.2, 8.4,
		10.3, 10.4, 10.5
	};

	//Test GMM
	GMM *gmm = new GMM(dim, 3); //GMM has 3 SGM
	gmm->Train(data, size); //Training GMM

	printf("\nTest GMM:\n");
	for (int i = 0; i < 4; ++i)
	{
		printf("The Probability of %f, %f, %f  is %f \n", test_data[i][0], test_data[i][1], test_data[i][2], gmm->GetProbability(test_data[i]));
	}

	//save GMM to file
	ofstream gmm_file("gmm.txt");
	assert(gmm_file);
	gmm_file << *gmm;
	gmm_file.close();

	delete gmm;

	return 0;
}