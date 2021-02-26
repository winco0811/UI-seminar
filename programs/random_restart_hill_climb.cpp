/*This is random-restart take on hill climbing:
 * we are doing simple hill climb multiple times, each time on a random starting point, hoping we will climb a better (higher) hill
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
        bool not_finished=1,broken;
        int temp_cost;
        int step=2;
	solution top_best=current_best;
	int top_cost=best_cost;

	while (top_cost!=0)  { //repeat until we found the solution: this algo finite for n>3 beacause there is always a solution for n>3
        	while (not_finished) { //simple hill climbing
                	broken=0;
                	for (int i=0; i<N; i++) {
                        	for (int j=1; j<=max_move; j++) {
                                	temp_cost=current_best.neighbour(i,LEFT,j).cost();
                                	if (temp_cost<best_cost) {
                                        	current_best=current_best.neighbour(i,LEFT,j);
                                        	best_cost=temp_cost;
                                        	broken=1;
                                        	break;
                                	}
                                	temp_cost=current_best.neighbour(i,RIGHT,j).cost();
                                	if (temp_cost<best_cost) {
                                        	current_best=current_best.neighbour(i,RIGHT,j);
                                        	best_cost=temp_cost;
                                        	broken=1;
                                        	break;
                                	}
                        	}
                	}
                if (best_cost==0) not_finished=0;
                if (!broken) not_finished=0;
        	}
		if (best_cost<top_cost) { //if the result is better than saved solution take the result
			top_cost=best_cost;
			top_best=current_best;
			std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
       			current_best.print();
        		step++;
		}
		current_best.randomize();
		best_cost=current_best.cost();
		not_finished=1;
	}
	std::cout << "I'm done, final cost is: " << top_cost << std::endl;
}

