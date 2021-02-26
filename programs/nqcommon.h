#include <cstdlib>
#include <cmath>
#include <random>
#include <iostream>
#define LEFT -1
#define RIGHT 1
std::random_device rand_dev;
std::mt19937 generator(rand_dev());
template<typename T>
T random(T range_from, T range_to) {
    std::uniform_int_distribution<T> distr(range_from, range_to);
    return distr(generator);
}
template<typename R>
R random_real(R range_from, R range_to) {
    std::uniform_real_distribution<R> distr(range_from, range_to);
    return distr(generator);
}
/* Template for random number distribution downloaded from https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
 * uses 32-bit Mersenne Twister by Matsumoto and Nishimura, 1998 algorithm for generating pseudo-random numbers and a random device
 */
class solution {
	std::vector<int> queen_col;
	int N;
	public:
		solution(){};
		solution(const solution& original) {
			N=original.N;
			queen_col=original.queen_col;
		}
		solution(int number) {
			N=number;
			randomize();
		}
		solution& operator=(std::vector<int> &input);
		int cost();
		void randomize();
		solution random_neighbour(int max_step);
		solution neighbour(int row, int move, int step);
		void print();
};
/* Queens will be represented by numbers, such that there can be only one queen in a row and the number represents a column she's in
 * for instance, solution[i]=j means that a queen in row i is in column j
 * if an object is constructed with a n integer it will randomize queen positions (conforming to rules above)
 */

solution& solution::operator= (std::vector<int> &input) {
	N=input.size();
	queen_col=input;
	return *this;
}
/* Rewritten assosiation operator, so we can associate vectors with solution class
 */

int solution::cost() {
	int cost=0;
	for (int i=0; i<N; i++)  {
		for (int j=0; j<N; j++) {
			if (i!=j) {
				if (queen_col[i]==queen_col[j]) cost++; //queens attacking in column
				if (abs(queen_col[i]-queen_col[j])==abs(i-j)) cost++; //queens attacking on diagonals, |x_1-x_2|=|y_1-y_2|
			}
		}	
	}
	return cost/2;
}
/* This function returns the cost of the current solution: for each queen attacking another queen cost increases by 1
 * queens will never attack each other in the same row because of the way we set up our solutions
 * we want, of course, to minimise it (hopefully make it 0)
 * the cost will be in an increment of 2, because if A attacks B - B also attacks A, hence we divide by 2
 */
void solution::randomize() {
	queen_col.clear();
	for (int i=0; i<N; i++) queen_col.push_back(random<int>(0,N-1));
}
/* Randomizes queen positions, used in constructor and can be used during programs */
solution solution::random_neighbour(int max_step) {
	solution new_solution=*this;
	int picked_row=random<int>(0,N-1);
	int new_column=queen_col[picked_row]+((random<int>(0,1))?1:-1)*random<int>(1,max_step);
	new_column=(new_column<0)?(new_column%N)+N:new_column%N;
	new_solution.queen_col[picked_row]=new_column;
	return new_solution;
}
/*Function returns random neighbour of an object
 * basically picks a random row and adds or subtracts a random number between 1 and max_step from it
 * returns another object
 */
solution solution::neighbour(int row, int move, int step) { //move is -1 for left and 1 for right, cpp can use UP and DOWN constants
	solution new_solution=*this;
	int new_column=queen_col[row]+move*step;
	new_column=(new_column<0)?(new_column%N)+N:new_column%N;
	new_solution.queen_col[row]=new_column;
	return new_solution;
}
/*Returns a specific neighbour of an object:
 * neighbour is basically the same solution, just one queen moved step spaces left or right
 * row decides which row to move the queen in, move decides direction, step decides amount of fields
 */
void solution::print() {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			std::string out=(j==queen_col[i])?"Q ":"- ";
			std::cout << out;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
/* Prints out the solution in chessboardesque fashion */
