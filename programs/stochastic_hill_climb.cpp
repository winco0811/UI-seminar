/*We hill climb stocastically: we look at a neighbour, we have a set chance * bias (which is higher the better this neighbour is) chance to use it
 * otherwise we reject it and look at another neighbour untill we find one that rolls the probability
 */
#include <cstdlib>
#include <iostream>
#include "nqcommon.h"
int main (int argc, char* argv[]) {
        if (argc<3) exit(EXIT_FAILURE);
        int max_move=std::atoi(argv[2]);
        int N=std::atoi(argv[1]);
        solution current_best(N);
	solution temp_best;
        int best_cost=current_best.cost();
        std::cout << "1. (cost=" << best_cost << ")" << std::endl;
        current_best.print();
        bool not_finished=1;
        int temp_cost;
        int step=2;
        while (not_finished) {
		do { //Stochastic climbing, we use chance to climb or not climb
			temp_best=current_best.random_neighbour(max_move);
			temp_cost=temp_best.cost();
		}
		while(random_real<double>(0,1)>1.0/(1+exp(temp_cost-best_cost)));
                current_best=temp_best;
                best_cost=temp_cost;
                std::cout << step << ". (cost=" << best_cost << ")" << std::endl;
                current_best.print();
                step++;
                if (best_cost==0) not_finished=0;
        }
        std::cout << "I'm done, final cost is: " << best_cost << std::endl;
}

