/**
    K Means Algorithm Implementation
    @author Daniel Le
    @date 09/26/18 
*/
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

//Point class has x and y values. To randomize, the constructor will take a seed which then generates the x and y values.
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

//Prints sample data in sample points
void printAData(std::vector<Point> &samples, int sampleSize)
{
    std::cout << "[ ";
    for(int i = 0; i < sampleSize; i++)
    {
        std::cout << "(A" << samples[i].getPos() << ")";
    }
    std::cout << " ]" << std::endl;
}

//Prints coordinate data
void printData(std::string title, std::vector<Point> &samples, int sampleSize)
{
    std::cout << title << std::endl;
    std::cout << "[ ";
    for(int i = 0; i < sampleSize; i++)
    {
        std::cout << "(" << samples[i].getX() << "," << samples[i].getY() << ")";
    }
    std::cout << " ]" << std::endl;
}

//Returns random centers from existing data points.
std::vector<Point> genRandomCenters(std::vector<Point> &samples, const int &sampleSize, int k)
{
    std::vector<Point> tempData = samples;
    std::vector<Point> centers;
    centers.reserve(k);

    for(int i = 0; i < k; i++)
    {
        int j = std::rand() % tempData.size();
        centers.push_back(tempData[j]);
        tempData.erase(tempData.begin()+j);
    }

    return centers;
}

//Generates centers from given points
std::vector<Point> genGivenCenters(std::vector<Point> samples, const int &c1, const int &c2, const int &c3, const int &k)
{
    std::vector<Point> centers;
    centers.reserve(k);

    centers.push_back(samples[c1-1]);
    centers.push_back(samples[c2-1]);
    centers.push_back(samples[c3-1]);

    return centers;
}

std::vector<Point> genRandom10Centers(const int &k)
{
    std::vector<Point> centers;
    centers.reserve(k);

    centers.push_back(Point(std::rand()%10, std::rand()%10, 0));
    centers.push_back(Point(std::rand()%10, std::rand()%10, 0));
    centers.push_back(Point(std::rand()%10, std::rand()%10, 0));

    return centers;
}

//Calculate euclidean distance
double calcDistance(Point one, Point two)
{   
    return ( std::abs(one.getX() - two.getX()) + std::abs(one.getY() - two.getY()) );
}

std::vector<std::vector<Point>> assignClusters(std::vector<Point> &samples, const std::vector<Point> &centers, const int &sampleSize, const int &k)
{
    std::vector<std::vector<Point>> clusters;
    std::vector<Point> points;
    clusters.reserve(k);
    points.reserve(sampleSize);
    double minDistance;
    int minIndex;
    
    //initiate clusters vector with empty vectors
    for(int i = 0; i < k; i++)
    {
        clusters.push_back(points);
    }

    for(int i = 0; i < sampleSize; i++)
    {
        minDistance = std::numeric_limits<double>::max();
        for(int j = 0; j < k; j++)
        {
            if (calcDistance(samples[i], centers[j]) < minDistance)
            {
                minDistance = calcDistance(samples[i], centers[j]);
                minIndex = j;
            }
        }
        clusters[minIndex].push_back(samples[i]);
    }
    return clusters;
}

std::vector<Point> recalcCenters(std::vector<std::vector<Point>> &clusters, std::vector<Point> &samples, 
    const std::vector<Point> &centers, const int &sampleSize, const int &k)
{
    std::vector<Point> new_centers = centers;
    double div;

    for(int i = 0; i < k; i++)
    {
        double Xmean = 0;
        double Ymean = 0;
        double count = 0;

        for (int j = 0; j < clusters[i].size(); j++)
        {
            Xmean += clusters[i][j].getX();
            Ymean += clusters[i][j].getY();
            count++;
        }
        
        new_centers[i].setX(Xmean/count);
        new_centers[i].setY(Ymean/count);
    }

    return new_centers;
}

bool checkChange(std::vector<Point> &centers, std::vector<Point> &newCenters, const std::vector<Point> &samples, 
    const int k, const int sampleSize)
{
    double minDistance;
    double newMinDistance;
    int minIndex;
    int newMinIndex;
    std::vector<int> minIndexVec;
    std::vector<int> newMinIndexVec;
    minIndexVec.reserve(sampleSize);
    newMinIndexVec.reserve(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        minDistance = std::numeric_limits<double>::max();
        for(int j = 0; j < k; j++)
        {
            if (calcDistance(samples[i], centers[j]) < minDistance)
            {
                minDistance = calcDistance(samples[i], centers[j]);
                minIndex = j;
            }
        }
        minIndexVec.push_back(minIndex);
    }

    for(int i = 0; i < sampleSize; i++)
    {
        newMinDistance = std::numeric_limits<double>::max();
        for(int j = 0; j < k; j++)
        {
            if (calcDistance(samples[i], newCenters[j]) < newMinDistance)
            {
                newMinDistance = calcDistance(samples[i], newCenters[j]);
                newMinIndex = j;
            }
        }
        newMinIndexVec.push_back(newMinIndex);
    }

    for(int i = 0; i < sampleSize; i++)
    {
        if (minIndexVec[i] != newMinIndexVec[i])
        {
            return true;
        }
    }

    return false;
}

void kMeans(std::vector<Point> &givenSamples, std::vector<std::vector<Point>> &clusters, std::vector<Point> &centers, 
    std::vector<Point> &new_centers, const int &sampleSize, const int &k, bool change)
{
    while(change)
    {
        new_centers = recalcCenters(clusters, givenSamples, centers, sampleSize, k);
        change = checkChange(centers, new_centers, givenSamples, k, sampleSize);      
        centers = new_centers;    
        clusters = assignClusters(givenSamples, centers, sampleSize, k); 
    }

    printData("End Centers: ", centers, k);

    for (int i = 0; i < k; i++)
    {
        std::cout << "Cluster " << i+1 << ": " << std::endl;
        printAData(clusters[i], clusters[i].size());
    }
    std::cout << std::endl;
}

int main() 
{
    /*********************** INIT ***********************/
    std::vector<Point> givenSamples;
    std::vector<Point> centers;
    std::vector<Point> new_centers;
    std::vector<std::vector<Point>> clusters;
    int sampleSize = 8;
    int k = 3;
    bool change = true; 

    //reserve capacity of array to be sampleSize
    givenSamples.reserve(sampleSize);

    //populate array of given samples
    givenSamples.push_back(Point(2,10,1));
    givenSamples.push_back(Point(2,5,2));
    givenSamples.push_back(Point(8,4,3));
    givenSamples.push_back(Point(5,8,4));
    givenSamples.push_back(Point(7,5,5));
    givenSamples.push_back(Point(6,4,6));
    givenSamples.push_back(Point(1,2,7));
    givenSamples.push_back(Point(4,9,8));

    /*********************** RUN ***********************/
    /*----ROUND 1----*/
    std::cout << "----Round 1----" << std::endl;
    centers = genGivenCenters(givenSamples, 1, 7, 8, k);
    printData("Centers:", centers, k);

    //assign the initial clusters
    clusters = assignClusters(givenSamples, centers, sampleSize, k);
    kMeans(givenSamples, clusters, centers, new_centers, sampleSize, k, change);

    /*----ROUND 2----*/
    std::cout << "----Round 2----" << std::endl;
    centers = genGivenCenters(givenSamples, 2, 6, 8, k);
    printData("Centers:", centers, k);

    //assign the initial clusters
    clusters = assignClusters(givenSamples, centers, sampleSize, k);
    kMeans(givenSamples, clusters, centers, new_centers, sampleSize, k, change);

    /*----ROUND 3----*/
    std::cout << "----Round 3----" << std::endl;
    centers = genGivenCenters(givenSamples, 3, 5, 6, k);
    printData("Centers:", centers, k);

    //assign the initial clusters
    clusters = assignClusters(givenSamples, centers, sampleSize, k);
    kMeans(givenSamples, clusters, centers, new_centers, sampleSize, k, change);

    /*----ROUND 4----*/
    std::cout << "----Round 4----" << std::endl;
    centers = genGivenCenters(givenSamples, 2, 3, 7, k);
    printData("Centers:", centers, k);

    //assign the initial clusters
    clusters = assignClusters(givenSamples, centers, sampleSize, k);
    kMeans(givenSamples, clusters, centers, new_centers, sampleSize, k, change);

    /*----ROUND 5----*/
    std::cout << "----Round 5----" << std::endl;
    
    centers = genRandom10Centers(k);
    printData("Centers:", centers, k);

    //assign the initial clusters
    clusters = assignClusters(givenSamples, centers, sampleSize, k);
    kMeans(givenSamples, clusters, centers, new_centers, sampleSize, k, change);

    
}






