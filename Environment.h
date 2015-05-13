#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <utility>
#include <vector>
#include <string>

class Agent;

class Environment{
public:
	Environment();
	Environment(char *);
	void setAgent(Agent*);
	void simulate();
	void printFitness();
	int getCitynum();
private:
	std::vector<std::string> split(const std::string &,char );
	std::vector<std::vector<double> > cost;
	Agent* agent;
	int cityNum;
	double minFitness;

	typedef struct{
		int c;
		double x;
		double y;
	}City;
};

#endif