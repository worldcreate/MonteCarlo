#include "Environment.h"
#include "Agent.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

Environment::Environment(){
	cityNum=4;
	int c[4][4]={
		{0,3,2,1},
		{3,0,6,3},
		{2,6,0,4},
		{1,3,4,0},
	};
	cost=std::vector<std::vector<double> >(cityNum,std::vector<double>(cityNum,0));
	for(int i=0;i<cityNum;i++){
		for(int j=0;j<cityNum;j++){
			cost[i][j]=c[i][j];
		}
	}
	minFitness=INT_MAX;
}

Environment::Environment(char *name){
	FILE *fp=fopen(name,"r");
	
	std::vector<City> cities;

	char str[256];

	fgets(str,256,fp);
	while(fgets(str,256,fp)!=NULL){
		City c;
		std::string s(str);
		std::vector<std::string> rets=split(s,',');
		c.c=atoi(rets[0].c_str());
		c.x=atof(rets[1].c_str());
		c.y=atof(rets[2].c_str());
		cities.push_back(c);
	}
	cost=std::vector<std::vector<double> >(cities.size(),std::vector<double>(cities.size(),0));
	for(int i=0;i<cities.size();i++){
		for(int j=0;j<cities.size();j++){
			cost[i][j]=sqrt(
				pow(cities[i].x-cities[j].x,2)+pow(cities[i].y-cities[j].y,2)
				);
		}
	}
	cityNum=cities.size();
	fclose(fp);
	minFitness=INT_MAX;
}

int Environment::getCitynum(){
	return cityNum;
}

void Environment::setAgent(Agent* agent){
	this->agent=agent;
	agent->setCityNum(cityNum);
	agent->setCityWeight(cost);
}

void Environment::simulate(){
	std::vector<int> array=agent->getCityTurn();

	double sum=0;
	for(int i=0;i<array.size()-1;i++){
		#ifdef DEBUG
			//printf("%d->%d:%lf\n",array[i],array[i+1],cost[array[i]][array[i+1]]);
		#endif
		sum+=cost[array[i]][array[i+1]];
	}
	#ifdef DEBUG
		//printf("%d->%d:%lf\n",array[array.size()-1],array[0],cost[array[array.size()-1]][array[0]]);
	#endif
	sum+=cost[array[array.size()-1]][array[0]];
	agent->setFitness(sum);
	if(sum<minFitness){
		minFitness=sum;
	}

	#ifdef DEBUG
		printf(":%lf\n",sum);
	#endif
}

std::vector<std::string> Environment::split(const std::string &str,char delim){
	std::istringstream iss(str);
	std::string tmp;
	std::vector<std::string> res;
	while(getline(iss,tmp,delim))
		res.push_back(tmp);
	return res;
}

void Environment::printFitness(){
	printf("min=%lf\n",minFitness);
}