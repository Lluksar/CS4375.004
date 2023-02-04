#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

double min(vector<double> v)
{
	sort(v.begin(), v.end());

	return v[0];
}

double max(vector<double> v)
{
	sort(v.begin(), v.end());

	return v[v.size() - 1];
}

double sumVector(vector<double> v)
{
	double sum = 0;
	for (int i = 0; i < v.size(); i++)
		sum += v[i];

	return sum;
}

double meanVector(vector<double> v)
{
	double mean = sumVector(v) / v.size();

	return mean;
}

double medianVector(vector<double> v)
{
	int size = v.size();
	double median = 0;
	sort(v.begin(), v.end());

	if (size % 2 == 1)
		median = v[size / 2 + 1];
	else
		median = v[size / 2];

	return median;
}

// Inefficient, sorts vector twice
vector<double> rangeVector(vector<double> v)
{
	vector<double> range = { min(v), max(v) };

	return range;
}

// Standard Deviation
double calcSD(vector<double> v)
{
	double mean = meanVector(v);
	double SD = 0;

	for (int i = 0; i < v.size(); i++)
		SD += pow(v[i] - mean, 2);

	return sqrt(SD / v.size());
}

double covar(vector<double> x, vector<double> y)
{
	if (x.size() != y.size())
	{
		cout << "ERROR: Covar vectors different sizes" << endl;
		return 0;
	}

	double meanX = meanVector(x);
	double meanY = meanVector(y);
	double summation = 0;

	for (int i = 0; i < x.size(); i++)
	{
		summation += (x[i] - meanX) * (y[i] - meanY);
	}

	return summation / (x.size() - 1);
}

double cor(vector<double> x, vector<double> y)
{
	return covar(x, y) / (calcSD(x) * calcSD(y));
}

void printStats(vector<double> v)
{
	vector<double> range = rangeVector(v);

	cout << "Min   : " << min(v) << endl;
	cout << "Sum   : " << sumVector(v) << endl;
	cout << "Mean  : " << meanVector(v) << endl;
	cout << "Median: " << medianVector(v) << endl;
	cout << "Range : " << range[0] << " " << range[1] << endl;
	cout << "Max   : " << max(v) << endl;
}


int main(int argc, char** argv)
{
	ifstream inFS;
	string line;
	string rm_in, medv_in;
	const int MAX_LEN = 1000;
	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);

	cout << "Opening file Boston.csv." << endl;

	inFS.open("Boston.csv");
	if (!inFS.is_open())
	{
		cout << "Could not open file Boston.csv." << endl;
		return 1;
	}

	cout << "Reading line 1" << endl;
	getline(inFS, line);

	cout << "heading: " << line << endl;

	int numObservations = 0;
	while (inFS.good())
	{
		getline(inFS, rm_in, ',');
		getline(inFS, medv_in, '\n');

		rm.at(numObservations) = stof(rm_in);
		medv.at(numObservations) = stof(medv_in);

		numObservations++;
	}

	rm.resize(numObservations);
	medv.resize(numObservations);

	cout << "new length " << rm.size() << endl;

	cout << "Closing file Boston.csv." << endl;
	inFS.close();

	cout << "Number of records: " << numObservations << endl;

	cout << "\nStats for rm" << endl;
	printStats(rm);

	cout << "\nStats for medv" << endl;
	printStats(medv);

	cout << "\n Covariance = " << covar(rm, medv) << endl;

	cout << "\n Correlation = " << cor(rm, medv) << endl;

	cout << "\nProgram terminated.";

	return 0;
}