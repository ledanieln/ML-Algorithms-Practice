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

class Point
{
public:	
	double x;
	double y;
	int id;
	
	Point(double x1, double y1, int id)
	{
		this->x = x1;
		this->y = y1;
        this->id = id;
	}		
};

struct distIndex
{
	double distance;
	int index;
};

void printClusters(std::vector<std::vector<Point>> clusters)
{
	std::cout << "The clusters are: " << std::endl;

	for(int i = 0; i < clusters.size(); i++)
	{
		std::cout << "Cluster " << i+1 << ":" << " { ";
		for (int j = 0; j < clusters[i].size(); j++)
		{
			std::cout << "A" << clusters[i][j].id;
			
			if(clusters[i].size() > 1 && j != clusters[i].size()-1)
			{
				std::cout << " ";
			}
			
		}
		std::cout << " }" << std::endl;
	}
	
}

double calcEucDistance(Point one, Point two)
{
	return std::sqrt(  std::pow((two.x - one.x), 2) + std::pow((two.y - one.y), 2)   );
}

double calcSingleLink(std::vector<Point> clusterOne, std::vector<Point> clusterTwo)
{
	double minDistance;
	double tempMin;
	
	minDistance = std::numeric_limits<double>::max();
	for(int i = 0; i < clusterOne.size(); i++)
	{
		for(int j = 0; j < clusterTwo.size(); j++)
		{
			tempMin = calcEucDistance(clusterOne[i], clusterTwo[j]);
			
			if(tempMin < minDistance)
			{
				minDistance = tempMin;
			}
		}
	}
	
	return minDistance;
}

double calcCompleteLink(std::vector<Point> clusterOne, std::vector<Point> clusterTwo)
{
	double maxDistance;
	double tempMax;
	
	maxDistance = 0;
	for(int i = 0; i < clusterOne.size(); i++)
	{
		for(int j = 0; j < clusterTwo.size(); j++)
		{
			tempMax = calcEucDistance(clusterOne[i], clusterTwo[j]);
			
			if(tempMax > maxDistance)
			{
				maxDistance = tempMax;
			}
		}
	}
	
	return maxDistance;
}


std::vector<std::vector<double>> genDistMatrix(std::vector<std::vector<Point>> clusters, const int &size, int option)
{
	std::vector<std::vector<double>> distMatrix;
	std::vector<double> columns;
	
	for(int i = 0; i < size; i++)
	{
		distMatrix.push_back(columns);
	}
	
	switch(option)
	{
		//Calculate initial euclidean distance
		case 1:
			{
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						distMatrix[i].push_back(calcEucDistance(clusters[i][0], clusters[j][0]));
					}
				}
				break;
			}
		//Calculate single linkage distance
		case 2:
			{
				for (int i = 0; i < size; i++)
				{
					for(int j = 0; j < size; j++)
					{
						distMatrix[i].push_back(calcSingleLink(clusters[i], clusters[j]));
					}
				}
				break;
			}
		//Calculate complete linkage distance
		case 3:
			{
				for (int i = 0; i < size; i++)
				{
					for(int j = 0; j < size; j++)
					{
						distMatrix[i].push_back(calcCompleteLink(clusters[i], clusters[j]));
					}
				}
				break;
			}
			
		default:
			std::cout << "You did not choose a case. " << std::endl;
			break;
	}
	
	return distMatrix;
}	

std::vector<distIndex> idClosestCluster(std::vector<std::vector<Point>> clusters, std::vector<std::vector<double>> distMatrix)
{
	double min;
	int minIndex;
	double tempMin;
	std::vector<distIndex> closestCluster(distMatrix.size());

	for(int i = 0; i < distMatrix.size(); i++)
	{
		min = std::numeric_limits<double>::max();
		for(int j = 0; j < distMatrix.size(); j++)
		{
			tempMin = distMatrix[i][j];
			if (tempMin + 0.00001 < min && i != j)
			{
				min = distMatrix[i][j];
				minIndex = j;
			}
		}
		closestCluster[i].distance = min;
		closestCluster[i].index = minIndex;
	}

	return closestCluster;
}	
	
std::vector<std::vector<Point>> recluster(std::vector<std::vector<Point>> clusters, std::vector<distIndex> distances) {
	
	std::vector<Point> tempCluster;
	std::vector<std::vector<Point>> tempClusters;
	int minIndex;
	double min;
	double tempMin;
	
	tempClusters = clusters;
	
	min = std::numeric_limits<double>::max();
	for(int i = 0; i < distances.size(); i++)
	{
		tempMin = distances[i].distance;
		if (tempMin < min)
		{
			min = tempMin;
			minIndex = distances[i].index;
		}
	}
	
	tempCluster = clusters[minIndex];
	
	for(int i = 0; i < clusters[distances[minIndex].index].size(); i++)
	{
		tempCluster.push_back(clusters[distances[minIndex].index][i]);
	}

	tempClusters.erase(tempClusters.begin() + minIndex);
	
	if(minIndex < distances[minIndex].index)
	{
		tempClusters.erase(tempClusters.begin() + (distances[minIndex].index - 1));
	}
	else
	{
		tempClusters.erase(tempClusters.begin() + distances[minIndex].index);
	}
	
	
	tempClusters.push_back(tempCluster);
	
	return tempClusters;
}

int main() {
	std::vector<std::vector<double>> distMatrix;
	std::vector<std::vector<Point>> clusters;
	std::vector<Point> cluster;
	std::vector<distIndex> minDist;
	int sampleSize = 12;
	
	//Populate empty 2D vector
	for(int i = 0; i < sampleSize; i++)
	{
		clusters.push_back(cluster);
	}
	
	//Load data
	clusters[0].push_back(Point(2.0,2.0,1));
	clusters[1].push_back(Point(3.01,2.0,2));
	clusters[2].push_back(Point(4.02,2.0,3));
	clusters[3].push_back(Point(5.03,2.0,4));
	clusters[4].push_back(Point(6.04,2.0,5));
	clusters[5].push_back(Point(7.05,2.0,6));
	clusters[6].push_back(Point(2.0,3.5,7));
	clusters[7].push_back(Point(3.01,3.5,8));
	clusters[8].push_back(Point(4.02,3.5,9));
	clusters[9].push_back(Point(5.03,3.5,10));
	clusters[10].push_back(Point(6.04,3.5,11));
	clusters[11].push_back(Point(7.05,3.5,12));
	
	
	//Calculate initial euclidean distance matrix
	distMatrix = genDistMatrix(clusters, sampleSize, 1);	
	
	while(clusters.size() > 1)
	{
		//maintain minimum distances for each cluster
		minDist = idClosestCluster(clusters, distMatrix);
			
		//Add the closest two points into a cluster, remove the two that are added, and add the new cluster back into the cluster vector
		clusters = recluster(clusters, minDist);
		
		//Recalculate distance matrix using single/complete linkage
		distMatrix = genDistMatrix(clusters, clusters.size(), 3);
	
		for(int i = 0; i < minDist.size(); i++)
		{
			std::cout << "distance: " << minDist[i].distance << " index: " << minDist[i].index << std::endl;
		}
	
		printClusters(clusters);
	}
	
	
}
