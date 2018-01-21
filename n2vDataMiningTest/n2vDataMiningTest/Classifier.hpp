#include "n2v_define.hpp"

#include <assert.h>

using namespace std;

//ostringstream�����������и�ʽ��������������ڽ���������ת��Ϊstring����
//ostringstreamֻ֧��<<������
template<typename T> string toStdString(const T& t) {
	ostringstream oss;  //����һ����ʽ�������
	oss << t;             //��ֵ����������
	return oss.str();
}


//�������Խṹ,��ȡtxt�ļ��е��ַ���  
struct _TupleTitle
{
	std::vector<int>  attrType; // 0:string, 1:float
	std::vector<string>  attrName;

	string toString()
	{
		string str;
		for (auto item : attrName)
		{
			str.append(item + "\t");
		}
		return str;
	}
};

////�������Խṹ��������ת��Ϊ����Ҫ�������Լ��ַ���  
struct _TupleData
{
	long id_l;
	float dis;
	vector<float> value_f;
	vector<string> value_str;

	_TupleData()
		: id_l(-1)
		, dis(0)
	{}

	bool isExsist(string strColumnName) const
	{
		return (true);
	}

	long getId() const
	{
		return id_l;
	}

	void setId(long id)
	{
		id_l = id;
	}

	float getColumnValue(string strColumnName, const _TupleTitle &title) const
	{
		size_t sz = title.attrName.size();

		for (size_t i=0; i<sz; ++i)
		{
			if (0 == strColumnName.compare(title.attrName[i]))
			{
				if (i < value_f.size())
				{
					return value_f[i];
				}
				//return value_str[i - value_f.size()];
			}
		}

		assert(false);

		return -1.0f;
	}

	void setColumnValue(string strColumnName, float value, const _TupleTitle &title)
	{
		size_t sz = title.attrName.size();

		for (size_t i = 0; i<sz; ++i)
		{
			if (0 == strColumnName.compare(title.attrName[i]))
			{
				if (i < value_f.size())
				{
					value_f[i] = value;
				}
			}
		}
	}

	string getLabel(const string &strColumnName, const _TupleTitle &title) const
	{
		size_t sz = title.attrName.size();

		for (size_t i = 0; i<sz; ++i)
		{
			if (0 == strColumnName.compare(title.attrName[i]))
			{
				if (i < value_f.size())
				{
					assert(false);
				}

				return value_str[i- value_f.size()];
			}
		}

		return string("");
	}

	void setLabel(string strLabel, const string &strColumnName, const _TupleTitle &title)
	{
		size_t sz = title.attrName.size();

		for (size_t i = 0; i<sz; ++i)
		{
			if (0 == strColumnName.compare(title.attrName[i]))
			{
				if (i < value_f.size())
				{
					assert(false);
				}

				value_str[i - value_f.size()] = strLabel;
			}
		}
	}

	string toString() const
	{
		string str;

		for (auto itemf : value_f)
		{
			str.append(toStdString(itemf) + "\t");
		}

		for (auto itemstr : value_str)
		{
			str.append(itemstr + "\t");
		}

		return str;
	}
};

int readDataFile(_TupleTitle &outTitle, vector<_TupleData> &outVecTupleData, const char *fileName, bool bIsContainsTitle)
{
	if (nullptr == fileName)
	{
		return -1;
	}

	ifstream infile;
	infile.open(fileName, ios::in);

	if (!infile)
	{
		cout << "�ļ��򿪴���" << endl;
		return -1;
	}

	//��������������  
	int lineCount = 0;

	_TupleTitle &title = outTitle;
	vector<_TupleData> &vecTupleData = outVecTupleData;
	vecTupleData.clear();

	char line[1024] = { 0 };

	// ��ȡ����
	if (bIsContainsTitle)
	{
		infile.getline(line, sizeof(line));
		std::stringstream strTitle(line);
		string str;

		for (size_t i = 0; i < title.attrType.size(); ++i)
		{
			strTitle >> str;
			title.attrName.push_back(str);
		}

		++lineCount;

		//std::cout << title.toString() << std::endl;
	}
	
	float value = 0.0f;
	string str;
	long index = 0;
	//���ļ��ж�ȡ����  
	while (infile.getline(line, sizeof(line)))
	{
		_TupleData tupleData;
		std::stringstream rawData(line);
		for (size_t i = 0; i < title.attrType.size(); ++i)
		{
			// float
			if (1 == title.attrType[i])
			{
				rawData >> value;
				tupleData.value_f.push_back(value);
			}
			else if(0 == title.attrType[i])// string
			{
				rawData >> str;
				tupleData.value_str.push_back(str);
			}
			else
			{
				assert(false);
			}
		}

		tupleData.setId(index++);

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
	Classifier();
	Classifier(_TupleTitle &title_, string strFile);
	~Classifier();

	void training();

	// ������ȷ��
	float testClassify(vector<_TupleData> &vecTupleData);

	string classify(_TupleData &data);

	// ....

	void _training();
	// ...

private:
	// ���������Ե���λ���;��Ա�׼��
	void _computeMedianDeviation(string strColumn);

	// ���㵥��ֵ�ı�׼����(ʹ�ò����������ɵ���λ���;��Ա�׼��)
	// ���Ի�Ԥ��ʱʹ��
	void _normalizeTupleData(_TupleData &tupleData);

	_TupleData nearestNeighbor(_TupleData &data);

	float manhattanDistance(_TupleData &data1, _TupleData &data2);
	float euclideanDistance(_TupleData &data1, _TupleData &data2);
	

public:
	_TupleTitle m_title_;
	vector<_TupleData> m_vecTupleData_;

	// map<column, pair<median,deviation>  
	// column mean's property.
	map<string, pair<float, float> > m_mapMedianDeviation;
};

Classifier::Classifier()
{
}

Classifier::Classifier(_TupleTitle &title_, string strFile)
	: m_title_(title_)
{
	// load the Training-Set
	cout << "Training-Set Count: " << readDataFile(m_title_, m_vecTupleData_, strFile.c_str(), true) << endl;
}

Classifier::~Classifier()
{

}


void Classifier::_computeMedianDeviation(string strColumn)
{
	size_t size = m_vecTupleData_.size();
	vector<float> columnValue;

	for (size_t i = 0; i < size; ++i)
	{
		_TupleData &data = m_vecTupleData_[i];

		if (data.isExsist(strColumn))
		{
			columnValue.push_back(data.getColumnValue(strColumn, m_title_));
		}
	}

	float median = getMedian(columnValue);
	float asd = getAbsoluteStandardDeviation(columnValue, median);

	m_mapMedianDeviation[strColumn] = make_pair(median, asd);

	//cout << strColumn <<"\tMedian: " << median << "\tASD: " << (asd) << endl;
}

void Classifier::_training()
{
	//1. ������λ���;��Ա�׼��
	for (size_t i = 0; i < m_title_.attrName.size(); ++i)
	{
		// ����������float��
		if(1 == m_title_.attrType[i])
		{
			string strColumnName = m_title_.attrName[i];
			_computeMedianDeviation(strColumnName);
		}
	}

	//2. Ϊÿ��training-data�����׼����
	size_t size = m_vecTupleData_.size();
	for (size_t i = 0; i < size; ++i)
	{
		_TupleData &data = m_vecTupleData_[i];
		_normalizeTupleData(data);
	}  
}

// ���㵥��ֵ�ı�׼����(ʹ�ò����������ɵ���λ���;��Ա�׼��)
void Classifier::_normalizeTupleData(_TupleData &tupleData)
{
	_TupleData &data = tupleData;
	for (size_t i = 0; i< m_title_.attrName.size(); ++i)
	{
		string strAttrName = m_title_.attrName[i];
		if (1 == m_title_.attrType[i] && data.isExsist(strAttrName))
		{
			// �Ľ���ı�׼���� = ����ÿ��ֵ�� - ����λ������ / �����Ա�׼�
			float normalizeValue = (data.getColumnValue(strAttrName, m_title_) - m_mapMedianDeviation[strAttrName].first) / m_mapMedianDeviation[strAttrName].second;
			data.setColumnValue(strAttrName, normalizeValue, m_title_);
		}
	}

	//cout << "normalizeTupleData: " << data.toString() << endl;
}

float Classifier::manhattanDistance(_TupleData &data1, _TupleData &data2)
{
	_TupleData &t1 = data1;
	_TupleData &t2 = data2;

	float dis = 0.f;
	for (size_t i = 0; i < data1.value_f.size(); ++i)
	{
		dis += abs(t1.value_f[i] - t2.value_f[i]);
	}

	return dis;
}

float Classifier::euclideanDistance(_TupleData &data1, _TupleData &data2)
{
	_TupleData &t1 = data1;
	_TupleData &t2 = data2;

	float dis = 0.f;
	for (size_t i = 0; i < data1.value_f.size(); ++i)
	{
		dis += pow((t1.value_f[i] - t2.value_f[i]), 2);
	}

	return (sqrt(dis));
}

_TupleData Classifier::nearestNeighbor(_TupleData &data)
{
	int nearestIndex = 0;
	float minDis = float(LONG_MAX);
	size_t size = m_vecTupleData_.size();
	//vector<float> dis;
	//columnValue.resize(size);

	//string str = data.toString();
	_normalizeTupleData(data);
	//cout << "target vector:\n" << data.toString() << endl;
	//cout << "+\t" << str << endl;

	for (size_t i = 0; i < size; ++i)
	{
		_TupleData &data2 = m_vecTupleData_[i];
		//float dataDis = manhattanDistance(data, data2);
		float dataDis = euclideanDistance(data, data2);
		data2.dis = dataDis;

		if (dataDis < minDis)
		{
			minDis = dataDis;
			nearestIndex = i;
		}
	}

	//cout << "minDis: " << (minDis) << endl;
	//cout << "nearestNeighbor: " << nearestIndex << "("<< (minDis) << "), [ " << m_vecTupleData[nearestIndex].toString() << "]" << endl;

	return m_vecTupleData_[nearestIndex];
}

string Classifier::classify(_TupleData &data)
{
	_TupleData t = nearestNeighbor(data);

	return t.getLabel(m_title_.attrName[m_title_.attrType.size()-1], m_title_);
}

// ������ȷ��
float Classifier::testClassify(vector<_TupleData> &vecTupleData)
{
	size_t size = vecTupleData.size();
	int numCorrect = 0;
	string strClass;

	for (size_t i = 0; i < size; ++i)
	{
		_TupleData data = vecTupleData[i];
		strClass = data.getLabel(m_title_.attrName[m_title_.attrType.size() - 1], m_title_);

		if ( 0 == strClass.compare(classify(data)) )
		{
			++numCorrect;
		}
	}

	return ( numCorrect*100.f / float(size) );
}