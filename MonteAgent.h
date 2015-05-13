#ifndef _MONTEAGENT_H_
#define _MONTEAGENT_H_

#include "Agent.h"

class MonteAgent:public Agent{
public:
	MonteAgent();
	MonteAgent(int );
	std::vector<int> getCityTurn();
	void setFitness(int );
	void setCityNum(int);
	void setCityWeight(std::vector<std::vector<double> >);
private:
	int getVector(std::vector<int> &,int);
	void erase(std::vector<std::vector<std::pair<int,double> > >&,int);
	std::vector<std::vector<std::pair<int,double> > > rank;
};

#endif