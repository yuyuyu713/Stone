#include "n2v_define.hpp"

#include <assert.h>

using namespace std;

//ostringstream对象用来进行格式化的输出，常用于将各种类型转换为string类型
//ostringstream只支持<<操作符
template<typename T> string toStdString(const T& t) {
	ostringstream oss;  //创建一个格式化输出流
	oss << t;             //把值传递如流中
	return oss.str();
}


//构建属性结构,读取txt文件中的字符串  
struct TupleTitle {
	string attr1;
	string attr2;
	string attr3;
	string attr4;
	string attr5;

	string toString()
	{
		string str = attr1 + "\t";
		str.append(attr2 + "\t")
			.append(attr3 + "\t")
			.append(attr4 + "\t")
			.append(attr5);

		return str;
	}
};

//构建属性结构，将数据转换为所需要的数据以及字符串  
struct TupleData {
	float attr1;
	float attr2;
	float attr3;
	float attr4;
	string attr5;

	bool isExsist(string strColumnName) const
	{
		if (0 == strColumnName.compare("attr1"))
		{
			return true;
		}
		else if (0 == strColumnName.compare("attr2"))
		{
			return true;
		}
		else if (0 == strColumnName.compare("attr3"))
		{
			return true;
		}
		else if (0 == strColumnName.compare("attr4"))
		{
			return true;
		}

		return (false);
	}

	float getColumnValue(string strColumnName) const
	{
		if (0 == strColumnName.compare("attr1"))
		{
			return attr1;
		}
		else if (0 == strColumnName.compare("attr2"))
		{
			return attr2;
		}
		else if (0 == strColumnName.compare("attr3"))
		{
			return attr3;
		}
		else if (0 == strColumnName.compare("attr4"))
		{
			return attr4;
		}

		assert(false);

		return -1.0f;
	}

	void setColumnValue(string strColumnName, float value)
	{
		if (0 == strColumnName.compare("attr1"))
		{
			attr1 = value;
		}
		else if (0 == strColumnName.compare("attr2"))
		{
			attr2 = value;
		}
		else if (0 == strColumnName.compare("attr3"))
		{
			attr3 = value;
		}
		else if (0 == strColumnName.compare("attr4"))
		{
			attr4 = value;
		}
	}

	string getLabel() const
	{
		return attr5;
	}

	void setLabel(string strLabel)
	{
		attr5 = strLabel;
	}

	string toString() const
	{
		string str = toStdString(attr1) + "\t";
		str.append(toStdString(attr2) + "\t")
			.append(toStdString(attr3) + "\t")
			.append(toStdString(attr4) + "\t")
			.append(attr5);

		return str;
	}
};


int readDataFile(TupleTitle &outTitle, vector<TupleData> &outVecTupleData, const char *fileName, bool bIsContainsTitle)
{
	if (nullptr == fileName)
	{
		return -1;
	}

	ifstream infile;
	infile.open(fileName, ios::in);

	if (!infile)
	{
		cout << "文件打开错误" << endl;
		return -1;
	}

	//输入样本的特征  
	int lineCount = 0;

	TupleTitle &title = outTitle;
	vector<TupleData> &vecTupleData = outVecTupleData;
	vecTupleData.clear();

	char line[1024] = { 0 };

	// 读取标题
	if (bIsContainsTitle)
	{
		infile.getline(line, sizeof(line));
		std::stringstream strTitle(line);
		strTitle >> title.attr1;
		strTitle >> title.attr2;
		strTitle >> title.attr3;
		strTitle >> title.attr4;
		strTitle >> title.attr5;

		++lineCount;

		//std::cout << title.toString() << std::endl;
	}
	
	TupleData tupleData;
	

	//从文件中读取数据  
	while (infile.getline(line, sizeof(line)))
	{
		std::stringstream rawData(line);

		rawData >> tupleData.attr1;
		rawData >> tupleData.attr2;
		rawData >> tupleData.attr3;
		rawData >> tupleData.attr4;
		rawData >> tupleData.attr5;

		vecTupleData.push_back(tupleData);
		++lineCount;

		//std::cout << tupleData.toString() << std::endl;
	}

	infile.close();

	assert(lineCount == (vecTupleData.size() + (bIsContainsTitle ? 1 : 0)));

	return lineCount;
}


class Classifier
{
public:
	Classifier(string strFile);
	~Classifier();

	void training();

	// 返回正确率
	float testClassify(vector<TupleData> &vecTupleData);

	string classify(TupleData data);

private:
	// 计算列属性的中位数和绝对标准差
	void computeMedianDeviation(string strColumn);

	// 计算单个值的标准分数(使用测试数据生成的中位数和绝对标准差)
	// 测试或预测时使用
	void normalizeTupleData(TupleData &tupleData);

	TupleData nearestNeighbor(TupleData data);

	float manhattanDistance(TupleData &data1, TupleData &data2);
	float euclideanDistance(TupleData &data1, TupleData &data2);

public:
	TupleTitle m_title;
	vector<TupleData> m_vecTupleData;

	// map<column, pair<median,deviation>  
	// column mean's property.
	map<string, pair<float, float> > m_mapMedianDeviation;
};

static string S_ColumnNames[] = { "attr1", "attr2", "attr3", "attr4"};

Classifier::Classifier(string strFile)
{
	// load the Training-Set
	cout << "Training-Set Count: " << readDataFile(m_title, m_vecTupleData, strFile.c_str(), true) << endl;
}

Classifier::~Classifier()
{

}

void Classifier::computeMedianDeviation(string strColumn)
{
	// strColumn: attr1,attr3,attr3,attr4,attr5
	size_t size = m_vecTupleData.size();
	vector<float> columnValue;

	for (size_t i = 0; i < size; ++i)
	{
		TupleData &data = m_vecTupleData[i];

		if (data.isExsist(strColumn))
		{
			columnValue.push_back(data.getColumnValue(strColumn));
		}
	}

	float median = getMedian(columnValue);
	float asd = getAbsoluteStandardDeviation(columnValue, median);
	
	m_mapMedianDeviation[strColumn] = make_pair(median, asd);

	//cout << strColumn <<"\tMedian: " << median << "\tASD: " << (asd) << endl;
}

void Classifier::training()
{
	// S_ColumnNames: attr1,attr3,attr3,attr4,attr5

	//1. 计算中位数和绝对标准差
	// TODO:
	int size = sizeof(S_ColumnNames) - sizeof(string);
	for (size_t i = 0; i < 4; ++i)
	{
		string strColumnName = S_ColumnNames[i];
		computeMedianDeviation(strColumnName);
	}

	//2. 为每个training-data计算标准分数
	size = m_vecTupleData.size();
	for (size_t i = 0; i < size; ++i)
	{
		TupleData &data = m_vecTupleData[i];
		normalizeTupleData(data);
	}
}

// 计算单个值的标准分数(使用测试数据生成的中位数和绝对标准差)
void Classifier::normalizeTupleData(TupleData &tupleData)
{
	TupleData &data = tupleData;
	for(size_t i=0; i< S_ColumnNames->size(); ++i)
	{
		if (data.isExsist(S_ColumnNames[i]))
		{
			// 改进后的标准分数 = （（每个值） - （中位数）） / （绝对标准差）
			float normalizeValue = (data.getColumnValue(S_ColumnNames[i]) - m_mapMedianDeviation[S_ColumnNames[i]].first) / m_mapMedianDeviation[S_ColumnNames[i]].second;
			data.setColumnValue(S_ColumnNames[i], normalizeValue);
		}
	}

	//cout << "normalizeTupleData: " << data.toString() << endl;
}

float Classifier::manhattanDistance(TupleData &data1, TupleData &data2)
{
	TupleData &t1 = data1;
	TupleData &t2 = data2;

	float dis = 0.f;
	dis += abs(t1.attr1 - t2.attr1);
	dis += abs(t1.attr2 - t2.attr2);
	dis += abs(t1.attr3 - t2.attr3);
	dis += abs(t1.attr4 - t2.attr4);

	return dis;
}

float Classifier::euclideanDistance(TupleData &data1, TupleData &data2)
{
	TupleData &t1 = data1;
	TupleData &t2 = data2;

	float dis = 0.f;
	dis = sqrt((t1.attr1 - t2.attr1)*(t1.attr1 - t2.attr1) + (t1.attr2 - t2.attr2)*(t1.attr2 - t2.attr2)
		+ (t1.attr3 - t2.attr3)*(t1.attr3 - t2.attr3) + (t1.attr4 - t2.attr4)*(t1.attr4 - t2.attr4));

	return dis;
}

TupleData Classifier::nearestNeighbor(TupleData data)
{
	int nearestIndex = 0;
	float minDis = float(LONG_MAX);
	size_t size = m_vecTupleData.size();
	//vector<float> dis;
	//columnValue.resize(size);

	//string str = data.toString();
	normalizeTupleData(data);
	//cout << "target vector:\n" << data.toString() << endl;
	//cout << "+\t" << str << endl;

	for (size_t i = 0; i < size; ++i)
	{
		TupleData &data2 = m_vecTupleData[i];
		//float dataDis = manhattanDistance(data, data2);
		float dataDis = euclideanDistance(data, data2);

		if (dataDis < minDis)
		{
			minDis = dataDis;
			nearestIndex = i;
		}
	}

	//cout << "minDis: " << (minDis) << endl;
	//cout << "nearestNeighbor: " << nearestIndex << "("<< (minDis) << "), [ " << m_vecTupleData[nearestIndex].toString() << "]" << endl;

	return m_vecTupleData[nearestIndex];
}

string Classifier::classify(TupleData data)
{
	TupleData t = nearestNeighbor(data);

	return t.getLabel();
}

// 返回正确率
float Classifier::testClassify(vector<TupleData> &vecTupleData)
{
	size_t size = vecTupleData.size();
	int numCorrect = 0;
	string strClass;

	for (size_t i = 0; i < size; ++i)
	{
		TupleData data = vecTupleData[i];
		strClass = data.attr5;

		if ( 0 == strClass.compare(classify(data)) )
		{
			++numCorrect;
		}
	}

	return ( numCorrect*100.f / float(size) );
}