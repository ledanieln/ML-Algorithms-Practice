#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

//Random Point class has random x and y values. The constructor will take a seed which then generates the x and y values.
class Point
{

private:
	int x;
	int y;

public:
	Point(int x, int y)
	{
		x = this.x;
		y = this.y;
	}

	//constructor generates random x and y
	Point(int seed)
	{
		std::srand(seed);
    	x = std::rand() % 100;
    	y = std::rand() % 100;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

};

int main() 
{
    //use the current time as a seed for the random number
    std::srand(std::time(nullptr));
    
    std::vector<Point> randomSamples;
    std::vector<Point> givenSamples;
    int sampleSize = 8; 

    //reserve capacity of array to be sampleSize
    randomSamples.reserve(sampleSize);
    givenSamples.reserve(sampleSize);

    //populate array of random data samples
    for(int i = 0; i < sampleSize; i++)
    {
    	randomSamples.push_back(Point(std::rand()));
    }

    //populate array of given samples
    givenSamples.push_back(Point(2,10));
    givenSamples.push_back(Point(2,5));
    givenSamples.push_back(Point(8,4));
    givenSamples.push_back(Point(5,8));
    givenSamples.push_back(Point(7,5));
    givenSamples.push_back(Point(6,4));
    givenSamples.push_back(Point(1,2));
    givenSamples.push_back(Point(4,9));

    std::String title = "Random sample data:";
    printData(title, randomSamples);

    title = "Given sample data:"
    printData(title, givenSamples);
}

void printData(std::String title, std::vector<Point> samples)
{
    std::cout << title << std::endl;
    for(int i = 0; i < sampleSize; i++)
    {
        std::cout << "The sample number is: " << i << "." << std::endl;
        std::cout << "X is: " << samples[i].getX() << std::endl;
        std::cout << "Y is: " << samples[i].getY() << std::endl;
    }
}





