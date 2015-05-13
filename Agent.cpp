#include "Agent.h"

Agent::Agent(){
	fitness=0;
}

void Agent::setCityNum(int num){
	cityNum=num;
}

void Agent::setFitness(int value){
	fitness=value;
}

void Agent::setCityWeight(std::vector<std::vector<double> > cost){
	weight=cost;
}