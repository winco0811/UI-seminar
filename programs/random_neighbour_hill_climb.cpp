/*this program uses random neighbours approach to hill climbing: 
 * we take the solution and look at all of its neighbours
 * if at least one of them is larger then the solution we
 * make the new solution that neighbour
 * if there is no higher neighbour but there are equal ones we pick any random neighbour
 * we repeat this until all of the neighbours are smaller then the current solution
 * if the solution isn't optimal we do a random neighbour: pick any neighbour as the next solution
 */
#include <cstdlib>
#include <iostream>
#include "nqcommon.h"
int main (int argc, char* argv[]) {
	if (argc<3) exit(EXIT_FAILURE);
        int max_move=std::atoi(argv[2]);
        int N=std::atoi(argv[1]);
        solution current_best(N);
        int best_cost=current_best.cost();
        std::cout << "1. (cost=" << best_cost << ")" << std::endl;
        current_best.print();
        bool not_finished=1,changed;
        int temp_cost,temp_best_cost=best_cost;
        solution temp_best(N);
        int step=2;
        while (not_finished) {
                changed=0;
                for (int i=0; i<N; i++) {
			for (int j=1; j<=max_move; j++) { //for every possible neighbour we check if its better
                        	temp_cost=current_best.neighbour(i,LEFT,j).cost();
	                        if (temp_cost<temp_best_cost) {
        	                        temp_best=current_best.neighbour(i,LEFT,j);
                	                temp_best_cost=temp_cost;
                        	        changed=1;
	                        }
                	        temp_cost=current_best.neighbour(i,RIGHT,j).cost();
                        	if (temp_cost<temp_best_cost) {
	                                temp_best=current_best.neighbour(i,RIGHT,j);
        	                        temp_best_cost=temp_cost;
                	                changed=1;
                        	}
        	        }
		}
                if (changed) { //if there is a better option climb it
                        current_best=temp_best;
                        best_cost=temp_best_cost;
                        std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                        current_best.print();
                        step++;
                }
                else {
			if (best_cost!=0) { //if there are multiple same cost neigbours and our current solution take a random step (attempt to step out of shoulder or local optima). If we dont hve equal options, but cost isnt 0 we are in local optima, not the global one!
				current_best=current_best.random_neighbour(max_move);
				best_cost=current_best.cost();
				std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                        	current_best.print();
                        	step++;
			}
			else {
                		not_finished=0; //if there are no better options and no equal options we are in global optima
			}
                }
                if (best_cost==0) not_finished=0;
        }
        std::cout << "I'm done, final cost is: " << best_cost << std::endl;
}

