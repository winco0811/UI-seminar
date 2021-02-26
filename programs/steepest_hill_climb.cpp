/* In this take on hill climbing we actually look at every neighbour and take the steepest one, the one with the best change in cost */
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
                for (int i=0; i<N; i++) { //If you find that neighbour is better than the current one beign considered best (temp best) use it as new temp best
			for (int j=1; j<=max_move; j++) {
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
		if (changed) { //Make the steepest climb
			current_best=temp_best;
			best_cost=temp_best_cost;
			std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                	current_best.print();
                	step++;
		}
		else {//If we cant climb we are done
			not_finished=0;
		}
                if (best_cost==0) not_finished=0;
        }
        std::cout << "I'm done, final cost is: " << best_cost << std::endl;
}
