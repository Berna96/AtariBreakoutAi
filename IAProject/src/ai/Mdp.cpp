/*
 * Mdp.cpp
 *
 *  Created on: 8 nov 2019
 *      Author: Berna
 */

#include "Mdp.h"
#include "../game.h"
#include <iostream>
#include <map>
#include <tuple>
#include <cmath>
#include <limits>
using namespace std;

namespace ai {

Mdp::Mdp() : V_old(0.0), Delta(std::numeric_limits<float>::max()), cicle_end(false), gamma(1), theta(0.1){
	a[0] = GameUtils::command::LEFT;
	a[1] = GameUtils::command::STOP;
	a[2] = GameUtils::command::RIGHT;


	V[State::C] = 0.0;
	V[State::UL] = 0.0;
	V[State::UR] = 0.0;
	V[State::DL] = 0.0;
	V[State::DR] = 0.0;
	V[State::GO] = 0.0;

	policy[State::C] = a[1];
	policy[State::UL] = a[1];
	policy[State::UR] = a[1];
	policy[State::DL] = a[1];
	policy[State::DR] = a[1];
	policy[State::GO] = a[1];

	/*0-center --> stop*/
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.027027, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.243243, State::DL, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.243243, State::DR, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.243243, State::UR, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.243243, State::UL, -0.5)));
	//0-center --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::LEFT), make_tuple(0.45, State::UR, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::LEFT), make_tuple(0.1, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::LEFT), make_tuple(0.45, State::DR, -0.5)));
	//0-center --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.225, State::UL, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.05, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.225, State::DL, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.45, State::GO, -10)));
	//1-up-left --> stop
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::STOP), make_tuple(1, State::UL, -1)));
	//1-up-left --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::LEFT), make_tuple(0.9, State::UL, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::LEFT), make_tuple(0.1, State::C, 0)));
	//1-up-left --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::RIGHT), make_tuple(1, State::UL, -1)));
	//2-up-right --> stop
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UR, GameUtils::command::STOP), make_tuple(1, State::UR, 0)));
	//2-up-right --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UR, GameUtils::command::LEFT), make_tuple(1, State::UR, -1)));
	//2-up-right --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UR, GameUtils::command::RIGHT), make_tuple(0.9, State::UR, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UR, GameUtils::command::RIGHT), make_tuple(0.1, State::C, 0)));
	//3-down-left --> stop
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::STOP), make_tuple(0.333, State::DL, -2)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::STOP), make_tuple(0.667, State::GO, -10)));
	//3-down-left --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::RIGHT), make_tuple(0.333, State::DL, -2)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::RIGHT), make_tuple(0.667, State::GO, -10)));
	//3-down-left --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::LEFT), make_tuple(0.310345, State::DL, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::LEFT), make_tuple(0.068965, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DL, GameUtils::command::LEFT), make_tuple(0.62069, State::GO, -10)));
	//4-down-right --> stop
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::STOP), make_tuple(0.333, State::DR, -2)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::STOP), make_tuple(0.667, State::GO, -10)));
	//4-down-right --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::RIGHT), make_tuple(0.310345, State::DR, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::RIGHT), make_tuple(0.068965, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::RIGHT), make_tuple(0.62069, State::GO, -10)));
	//down-right --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::LEFT), make_tuple(0.333, State::DR, -2)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::DR, GameUtils::command::LEFT), make_tuple(0.667, State::GO, -10)));
}

bool Mdp::valueIterationAlgorithm(){
	if (Delta < theta)	cicle_end = true;
	if (!cicle_end)	updateValueIteration();
	else createPolicy();
	return cicle_end;
}

void Mdp::updateValueIteration(){
	cout << "inizio iterazione" << endl;
	Delta = 0.0;
	map<int, float>::iterator i;
	for (i = V.begin(); i!=V.end(); i++){
		int s = i->first;
		V_old = V[s];
		float sum[3] = {0,0,0};	//sum[i] assciato a a[i]
		for (int j=0; j<3; j++){
			typedef std::multimap<tuple<int, int>, tuple< float, int, int>>::iterator MMAPIterator;
			pair<MMAPIterator, MMAPIterator> result = mdp.equal_range(make_tuple(s, a[j]));
			for (MMAPIterator it = result.first; it != result.second; it++){
				float p;
				int s_next, r;
				tie(p, s_next, r) = it->second;
				sum[j] += p * (r + gamma * V.at(s_next));
			}
		}
		i->second = max(max(sum[0], sum[1]) , sum[2]);	//update V[s]
		Delta = max(Delta, abs(V_old - V[s]));

		cout << "V(" << i->first << ") : " << i->second << endl;
	}
	cout << "fine iterazione" << endl;
}

void Mdp::createPolicy(){
	map<int, float>::iterator i;
	for (i = V.begin(); i!=V.end(); i++){
		int s = i->first;
		float sum[3] = {0,0,0};
		for (int j=0; j<3; j++){
			typedef std::multimap<tuple<int, int>, tuple< float, int, int>>::iterator MMAPIterator;
			pair<MMAPIterator, MMAPIterator> result = mdp.equal_range(make_tuple(s, a[j]));
			for (MMAPIterator it = result.first; it != result.second; it++){
				float p;
				int s_next, r;
				tie(p, s_next, r) = it->second;
				sum[j] += p * (r + gamma * V.at(s_next));
			}
		}

		int aMax;
		if (sum[0] > sum[1] && sum[0] > sum[2]){
			aMax = a[0];
		}else{
			if (sum[1] > sum[2]){
				aMax = a[1];
			}else{
				aMax = a[2];
			}
		}
		policy[s] = aMax;
		cout << "Policy[" << s << "] = " << policy[s] << endl;
	}

}

int Mdp::getCommandFromPolicy(int current_State){
	return policy.at(current_State);
}

Mdp::~Mdp(){}

} /* namespace data */
