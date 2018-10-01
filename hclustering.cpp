/**
    Hierarchical Clustering Algorithm
    @author Daniel Le
    @date 09/26/18 
*/
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

//Point class has x and y values. To randomize, the constructor will take a seed which then generates the x and y values.
struct clusters
{
	int index1;
	int index2;
};

struct distIndex
{
	double distance;
	int index;
};

class Point
{

private:
	double x;
	double y;
    int pos;

public:
	Point(double x1, double y1, int pos)
	{
		this->x = x1;
		this->y = y1;
        this->pos = pos;
	}

	double getX()
	{
		return x;
	}

	double getY()
	{
		return y;
	}

    int getPos()
    {
        return pos;
    }

    void setX(double x1)
    {
        this->x = x1;
    }

    void setY(double y1)
    {
        this->y = y1;
    }

};

double calcDistance(Point one, Point two)
{
	return std::sqrt(  std::pow((two.getX() - one.getX()), 2) + std::pow((two.getY() - one.getY()), 2)   );
}

void printMatrix(std::vector<std::vector<double>> matrix, const int &sampleSize)
{
	for(int i = 0; i < sampleSize; i++)
	{
		for(int j = 0; j < sampleSize; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void printIntVector(std::vector<int> vector)
{
	std::cout << "The vector elements are: " << std::endl;

	for(int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	
}

std::vector<std::vector<double>> genDistMatrix(std::vector<Point> samples, const int &sampleSize)
{
	std::vector<std::vector<double>> distMatrix;
	std::vector<double> columns;
	distMatrix.reserve(sampleSize);
	columns.reserve(sampleSize);

	for(int i = 0; i < sampleSize; i++)
	{
		distMatrix.push_back(columns);
	}

	for(int i = 0; i < sampleSize; i++)
	{
		for(int j = 0; j < sampleSize; j++)
		{
			distMatrix[i].push_back(calcDistance(samples[i], samples[j]));
		}
	}

	return distMatrix;
}

std::vector<int> genActiveClusters(const int &sampleSize)
{
	std::vector<int> activeClusters;

	for(int i = 0; i < sampleSize; i++)
	{
		activeClusters.push_back(1);
	}

	return activeClusters;
}

std::vector<distIndex> idClosestCluster(std::vector<Point> samples, std::vector<std::vector<double>> sim, const int &sampleSize)
{
	double min;
	int minIndex;
	std::vector<distIndex> closestCluster(sampleSize);

	for(int i = 0; i < sampleSize; i++)
	{
		min = std::numeric_limits<double>::max();
		for(int j = 0; j < sampleSize; j++)
		{
			if (sim[i][j] < min && i != j)
			{
				min = sim[i][j];
				minIndex = j;
			}
		}
		closestCluster[i].distance = min;
		closestCluster[i].index = minIndex;
	}

	return closestCluster;
}

struct clusters genCluster(std::vector<distIndex> minDist, const int &sampleSize)
{	
	struct clusters tempCluster;
	double min = std::numeric_limits<double>::max();

	for(int i = 0; i < sampleSize; i++)
	{	
		if(minDist[i].distance < min)
		{
			min = minDist[i].distance;
			tempCluster.index1 = i;
			tempCluster.index2 = minDist[i].index;
		}
	}

	return tempCluster;
}

std::vector<std::vector<double>> updateMatrix(std::vector<std::vector<double>> sim, std::vector<distIndex> minDist, 
	std::vector<clusters> mergeHistory )
{
	for (int i = 0; i < sampleSize; i++)
	{
		sim[i][index1]
	}
}


/*std::vector<Point> hierarchicalClustering(std::vector<Point> samples, const int &sampleSize)
{
	std::vector<std::vector<double>> sim;
	std::vector<int> activeClusters;
	std::vector<int> closestCluster;

	sim = genDistMatrix(samples, sampleSize);
	activeClusters = genActiveClusters(sampleSize);
	closestCluster = idClosestCluster(samples, sim, sampleSize);
	printIntVector(closestCluster);
}*/

int main()
{
	std::vector<std::vector<double>> sim;
	std::vector<Point> samples;
	int sampleSize = 12;
	samples.reserve(sampleSize);
	std::vector<int> activeClusters;
	std::vector<distIndex> minDist;
	std::vector<clusters> mergeHistory;

	//load data
	samples.push_back(Point(2,2,1));
	samples.push_back(Point(3.01,2,2));
	samples.push_back(Point(4.02,2,3));
	samples.push_back(Point(5.03,2,4));
	samples.push_back(Point(6.04,2,5));
	samples.push_back(Point(7.05,2,6));
	samples.push_back(Point(2,3.5,7));
	samples.push_back(Point(3.01,3.5,8));
	samples.push_back(Point(4.02,3.5,9));
	samples.push_back(Point(5.03,3.5,10));
	samples.push_back(Point(6.04,3.5,11));
	samples.push_back(Point(7.05,3.5,12));

	//generate distance matrix
	sim = genDistMatrix(samples, sampleSize);
	activeClusters = genActiveClusters(sampleSize);
	minDist = idClosestCluster(samples, sim, sampleSize);

	for(int i = 0; i < sampleSize; i++)
	{
		std::cout << "index: " << minDist[i].index << " distance: " << minDist[i].distance << " size: " << minDist.size() << std::endl;
	}


	mergeHistory.push_back(genCluster(minDist, sampleSize));

	for(int i = 0; i < mergeHistory.size(); i++)
	{
		std::cout << "index1: " << mergeHistory[i].index1 << " index2: " << mergeHistory[i].index2 << std::endl;
	}

}












