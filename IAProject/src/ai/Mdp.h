/*
 * Mdp.h
 *
 *  Created on: 8 nov 2019
 *      Author: Berna
 */

#ifndef AI_MDP_H_
#define AI_MDP_H_
#include<iostream>
#include <fstream>
#include<tuple>
#include<list>
#include <map>
using namespace std;
namespace ai {

class Mdp {
private:
	multimap<tuple<int, int>, tuple< float, int, int>> mdp;	//(s, a, p, s', r)
	map<int, float> V;	//s-->V(s)
	float V_old, Delta;
	map<int, int> policy;	//s-->a
	int a[3];
	bool cicle_end;
	float gamma, theta;
	int iter;
	ofstream report;
	void updateValueIteration();
	void createPolicy();

public:
	enum State {C, UL, UR, DL, DR, GO};
	enum Actions {LEFT, STOP, RIGHT};
	Mdp();
	bool valueIterationAlgorithm();
	int getCommandFromPolicy(int);
	virtual ~Mdp();
};

} /* namespace data */

#endif /* AI_MDP_H_ */
