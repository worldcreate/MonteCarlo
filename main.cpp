#include "Environment.h"
#include "MonteAgent.h"
#include "progress.h"

#define GEN 10000

int main(void){
	Environment env("city_position.csv");
	MonteAgent agent(0);
	env.setAgent(&agent);
	for(int j=0;j<GEN;j++){
		env.simulate();
		#ifndef DEBUG
			progress(j,GEN-1);
		#endif
	}
		
	env.printFitness();
	
	return 0;
}