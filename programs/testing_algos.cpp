#include <cmath>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "nqcommon.h"
#define TIME_CONSTRAINT 100.0
#define INITIAL_TEMP 100 
#define TEMP_DECAY 0.001 
#define COOLED 0 
#define BC 1.380649e-23
int simple_hill_climb (solution start, int N, int max_move) {
        solution current_best=start;
        int best_cost=current_best.cost();
        bool not_finished=1,broken;
        int temp_cost;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        while (not_finished && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT) {
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
		t2 = std::chrono::high_resolution_clock::now();
        }
        return best_cost;
}
int steepest_hill_climb(solution start, int N, int max_move) {
        solution current_best=start;
        int best_cost=current_best.cost();
        bool not_finished=1,changed;
        int temp_cost,temp_best_cost=best_cost;
        solution temp_best;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        while (not_finished && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT) {
                changed=0;
                for (int i=0; i<N; i++) { 
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
                if (changed) {
                        current_best=temp_best;
                        best_cost=temp_best_cost;
                }
                else {
                        not_finished=0;
                }
                if (best_cost==0) not_finished=0;
		t2 = std::chrono::high_resolution_clock::now();
        }
        return best_cost;
}
int random_neighbour_hill_climb(solution start, int N, int max_move) {
        solution current_best=start;
        int best_cost=current_best.cost();
        bool not_finished=1,changed;
        int temp_cost,temp_best_cost=best_cost;
        solution temp_best;
	int top_cost=best_cost;
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	while (not_finished && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT) {
                changed=0;
                for (int i=0; i<N; i++) {
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
                if (changed) {
                        current_best=temp_best;
                        best_cost=temp_best_cost;
			if (best_cost<top_cost) top_cost=best_cost;
                }
                else {
                        if (best_cost!=0) {
                                current_best=current_best.random_neighbour(max_move);
                                best_cost=current_best.cost();
                        }
                        else {
                                not_finished=0;
                        }
                }
                if (best_cost==0) not_finished=0;
		t2 = std::chrono::high_resolution_clock::now();
        }
        return top_cost;
}
int random_restart_hill_climb(solution start, int N, int max_move) {
        solution current_best=start;
        int best_cost=current_best.cost();
        bool not_finished=1,broken;
        int temp_cost;
        solution top_best=current_best;
        int top_cost=best_cost;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        while (top_cost!=0 && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT)  {
                while (not_finished && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT) {
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
			t2 = std::chrono::high_resolution_clock::now();
                }
                if (best_cost<top_cost) {
                        top_cost=best_cost;
                        top_best=current_best;
                }
                current_best.randomize();
                best_cost=current_best.cost();
                not_finished=1;
		t2 = std::chrono::high_resolution_clock::now();
        }
        return top_cost;
}
int stochastic_hill_climb(solution start, int N, int max_move) {
        solution current_best=start;
        solution temp_best;
        int best_cost=current_best.cost();
        bool not_finished=1;
        int temp_cost;
	int top_cost=best_cost;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        while (not_finished && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT) {
                do {
                        temp_best=current_best.random_neighbour(max_move);
                        temp_cost=temp_best.cost();
                }
                while(random_real<double>(0,1)>1.0/(1+exp(temp_cost-best_cost)));
                current_best=temp_best;
                best_cost=temp_cost;
		if (best_cost<top_cost) top_cost=best_cost;
                if (best_cost==0) not_finished=0;
		t2 = std::chrono::high_resolution_clock::now();
        }
        return top_cost;
}
int simulated_anneling(solution start, int N, int max_move) {
        solution current_best=start;
        int best_cost=current_best.cost();
	int top_cost=best_cost;
        double temp=INITIAL_TEMP;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        while (temp>COOLED && std::chrono::duration<double, std::milli>(t2-t1).count()<TIME_CONSTRAINT) {
                solution ran_sol=current_best.random_neighbour(max_move);
                int ran_cost=ran_sol.cost();
                if (ran_cost<best_cost) {
                        current_best=ran_sol;
                        best_cost=ran_cost;
			if (best_cost<top_cost) top_cost=best_cost;
                }
                else {
                        int cost_inc=ran_cost-best_cost;
                        double probability=exp(-cost_inc/(temp*BC));
                        double roll=random_real<double>(0,1);
                        if (roll<=probability) {
                                current_best=ran_sol;
                                best_cost=ran_cost;
				if (best_cost<top_cost) top_cost=best_cost;
                        }
                }
                temp-=TEMP_DECAY;
                if (best_cost==0) temp=0;
		t2 = std::chrono::high_resolution_clock::now();
        }
        return best_cost;
}
int main (int argc, char* argv[]) {
	if (argc<4) exit(EXIT_FAILURE);
        int max_move=std::atoi(argv[2]);
        int N=std::atoi(argv[1]);
	int tries=std::atoi(argv[3]);
	int costs[6]={0};
	double times[6]={0};
	int successes[6]={0};
	int tmp;
	for (int i=0; i<tries; i++) {
		solution start(N);
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		tmp=simple_hill_climb(start,N,max_move);
		costs[0]+=tmp;
		if (!tmp) successes[0]++;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		times[0]+=std::chrono::duration<double, std::milli>(t2-t1).count();
                t1 = std::chrono::high_resolution_clock::now();
                tmp=steepest_hill_climb(start,N,max_move);
                costs[1]+=tmp;
                if (!tmp) successes[1]++;
		t2 = std::chrono::high_resolution_clock::now();
                times[1]+=std::chrono::duration<double, std::milli>(t2-t1).count();
                t1 = std::chrono::high_resolution_clock::now();
                tmp=random_neighbour_hill_climb(start,N,max_move);
                costs[2]+=tmp;
                if (!tmp) successes[2]++;
		t2 = std::chrono::high_resolution_clock::now();
                times[2]+=std::chrono::duration<double, std::milli>(t2-t1).count();
                t1 = std::chrono::high_resolution_clock::now();
                tmp=random_restart_hill_climb(start,N,max_move);
                costs[3]+=tmp;
                if (!tmp) successes[3]++;
		t2 = std::chrono::high_resolution_clock::now();
                times[3]+=std::chrono::duration<double, std::milli>(t2-t1).count();
                t1 = std::chrono::high_resolution_clock::now();
                tmp=stochastic_hill_climb(start,N,max_move);
                costs[4]+=tmp;
                if (!tmp) successes[4]++;
		t2 = std::chrono::high_resolution_clock::now();
                times[4]+=std::chrono::duration<double, std::milli>(t2-t1).count();
                t1 = std::chrono::high_resolution_clock::now();
                tmp=simulated_anneling(start,N,max_move);
                costs[5]+=tmp;
                if (!tmp) successes[5]++;
		t2 = std::chrono::high_resolution_clock::now();
                times[5]+=std::chrono::duration<double, std::milli>(t2-t1).count();	
	}
	for (int i=0; i<6; i++) {
		switch (i) {
			case 0:
				std::cout << "Simple hill climb";
				break;
                        case 1:
                                std::cout << "Steepest hill climb";
                                break;
                        case 2:
                                std::cout << "Random neighbour hill climb";
                                break;
                        case 3:
                                std::cout << "Random restart hill climb";
                                break;
                        case 4:
                                std::cout << "Stochastic hill climb";
                                break;
                        case 5:
                                std::cout << "Simulated anneling";
                                break;
		}
		std::cout << ":" << std::endl 
			<< "Total time: " << times[i] << "ms (AVG " << times[i]/(double) tries << "ms)" << std::endl
			<< "Total cost: " << costs[i] << " (AVG " << costs[i]/(double) tries << ")" << std::endl 
			<< "Number of times an optimal solution was found: " << successes[i] << " (" << (double)successes[i]/(double)tries*100.0 << "%)"<< std::endl << std::endl;
	}
}

