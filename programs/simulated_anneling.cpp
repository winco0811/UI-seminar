/* Simulated annealing algorithm 
 * uses slow reduction of temperature (entropy), Bolzmann constant and something similar to hill climbing to optimize the solution
 */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "nqcommon.h"
#define INITIAL_TEMP 100 //Starting temperature for annealing
#define TEMP_DECAY 0.001 //How much will our temperature decay after one iteration
#define COOLED 0 //When do we consider out solution to be "cooled", to be done
#define BC 1.380649e-23 /Bolzmann constant
int main (int argc, char* argv[]) {
	if (argc<3) exit(EXIT_FAILURE);
        int max_move=std::atoi(argv[2]);
        int N=std::atoi(argv[1]);
        solution current_best(N); //Start with random configuration
        int best_cost=current_best.cost();
        std::cout << "1. (cost=" << best_cost << ")" << std::endl;
        current_best.print();
        int step=2;
	double temp=INITIAL_TEMP;
        while (temp>COOLED) {
		solution ran_sol=current_best.random_neighbour(max_move); //We look at random neighbour
		int ran_cost=ran_sol.cost();
		if (ran_cost<best_cost) { //If it's better use it as new best
        		current_best=ran_sol;
                	best_cost=ran_cost;
                	std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                	current_best.print();
                	step++;
		}
		else { //If it isn't use it anyway with a certain chance
			int cost_inc=ran_cost-best_cost;
			double probability=exp(-cost_inc/(temp*BC));
			double roll=random_real<double>(0,1);
			if (roll<=probability) {
				current_best=ran_sol;
                       		best_cost=ran_cost;
                        	std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                        	current_best.print();
                        	step++;
			}
		}
		temp-=TEMP_DECAY;
		if (best_cost==0) temp=0;
        }
        std::cout << "I'm done, final cost is: " << best_cost << std::endl;
}
