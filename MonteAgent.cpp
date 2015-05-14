#include "MonteAgent.h"
#include "Util.h"
#include <stdio.h>
#include <limits.h>
#include <algorithm>

#define RANGE 0	// 0~31
#define SEED 50

MonteAgent::MonteAgent(){
	Util::setSeed(SEED);
}

MonteAgent::MonteAgent(int t){
	Util::setSeed(t+SEED);
}

void MonteAgent::setCityNum(int n){
	Agent::setCityNum(n);
	rank;
}

void MonteAgent::setCityWeight(std::vector<std::vector<double> > weight){
	Agent::setCityWeight(weight);

	for(int c=0;c<cityNum;c++){
		std::vector<int> temp;
		for(int i=0;i<cityNum;i++){
			temp.push_back(i);
		}
		rank.push_back(std::vector<std::pair<int,double> >());
		for(int i=0;i<cityNum;i++){
			double cost=INT_MAX;
			int num=-1;
			for(int j=0;j<temp.size();){
				if(cost>weight[c][temp[j]]){
					cost=weight[c][temp[j]];
					num=j;
				}
				j++;
			}
			rank[c].push_back(std::pair<int,double>(temp[num],cost));
			getVector(temp,num);
		}
	}
}

std::vector<int> MonteAgent::getCityTurn(){
	std::vector<std::vector<std::pair<int,double> > > city=rank;
	std::vector<int> turn;
	turn.push_back(0);
	erase(city,0);
	for(int i=0;i<cityNum-2;i++){
		int prev=turn[turn.size()-1];
		//int r=Util::getRand(std::min((int)RANGE,(int)city[prev].size()-1),0);
		double sum=0;
		for(int j=0;j<city[prev].size();j++){
			sum+=city[prev][j].second;
		}
		int r=Util::getRand((int)(sum),0);
		double saving=0;
		for(int j=0;j<city[prev].size();j++){
			saving+=sum-city[prev][j].second;
			if(saving>=r){
				turn.push_back(city[prev][j].first);
				erase(city,city[prev][j].first);
				break;
			}
		}
	}
	turn.push_back(city[turn.size()-1][0].first);
	return turn;
}

void MonteAgent::setFitness(int value){
	Agent::setFitness(value);
}

int MonteAgent::getVector(std::vector<int> &vector,int n){
	int r;
	std::vector<int>::iterator it=vector.begin();
	for(int i=0;it!=vector.end();it++,i++){
		if(i==n){
			r=(*it);
			vector.erase(it);
			break;
		}
	}
	return r;
}

void MonteAgent::erase(std::vector<std::vector<std::pair<int,double> > > &city,int idx){
	for(int i=0;i<city.size();i++){
		std::vector<std::pair<int,double> >::iterator it=city[i].begin();
		while(it!=city[i].end()){
			if((*it).first==idx){
				city[i].erase(it);
				break;
			}
			it++;
		}
	}
}