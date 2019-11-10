/*
 * Mdp.h
 *
 *  Created on: 8 nov 2019
 *      Author: Berna
 */

#ifndef AI_MDP_H_
#define AI_MDP_H_
#include<iostream>
#include<tuple>
#include<list>
#include <map>
using namespace std;
namespace ai {

class Mdp {
private:
	multimap<tuple<int, int>, tuple< float, int, int>> mdp;	//(s, a, p, s', r)
	map<int, float> V;	//s-->V(s)
	map<int, float> V_old;	//s-->V_old(s)
	map<int, float> Delta;	//s-->Delta(s)
	map<int, int> policy;	//s-->a
	int a[3];
	bool cicle_end;
	float gamma, theta;
	void updateValueIteration();
	void createPolicy();
	bool checking_delta();

public:
	enum State {C, UL, UR, DL, DR, GO};
	Mdp();
	bool valueIterationAlgorithm();
	int getCommandFromPolicy(int);
	virtual ~Mdp();
};

} /* namespace data */

#endif /* AI_MDP_H_ */
