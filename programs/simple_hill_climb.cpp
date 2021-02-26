/* This is a simple hill climber, we just look at the first better neighbour and use it as new best*/
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
	while (not_finished) {
		broken=0;
		for (int i=0; i<N; i++) {
			for (int j=1; j<=max_move; j++) {
				temp_cost=current_best.neighbour(i,LEFT,j).cost();
				if (temp_cost<best_cost) {
					current_best=current_best.neighbour(i,LEFT,j);
					best_cost=temp_cost;
					std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
					current_best.print();
					step++;
					broken=1;
					break;//If we find even one that is better we take it immediately and break the for loop
				}
				temp_cost=current_best.neighbour(i,RIGHT,j).cost();
       		                if (temp_cost<best_cost) {
	                                current_best=current_best.neighbour(i,RIGHT,j);
	       	                        best_cost=temp_cost;
					std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                	                current_best.print();
                        	        step++;
					broken=1;
					break;
                        	}
			}
		}
		if (best_cost==0) not_finished=0;
		if (!broken) not_finished=0;
	}
	std::cout << "I'm done, final cost is: " << best_cost << std::endl;
}
