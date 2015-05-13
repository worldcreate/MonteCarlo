#include "Environment.h"
#include "MonteAgent.h"
#include "progress.h"

int main(void){
	Environment env("city_position.csv");
	MonteAgent agent(0);
	env.setAgent(&agent);
	for(int j=0;j<10000;j++){
		env.simulate();
		#ifndef DEBUG
			progress(j,10000-1);
		#endif
	}
		
	env.printFitness();
	
	return 0;
}