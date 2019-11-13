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

std::ostream& operator<<(std::ostream& out, const Mdp::State value){
    static std::map<Mdp::State, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(Mdp::State::C);
        INSERT_ELEMENT(Mdp::State::DL);
        INSERT_ELEMENT(Mdp::State::DR);
        INSERT_ELEMENT(Mdp::State::UL);
        INSERT_ELEMENT(Mdp::State::UR);
        INSERT_ELEMENT(Mdp::State::GO);
#undef INSERT_ELEMENT
    }

    return out << strings[value];
}

std::ostream& operator<<(std::ostream& out, const Mdp::Actions value){
    static std::map<Mdp::Actions, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(Mdp::Actions::LEFT);
        INSERT_ELEMENT(Mdp::Actions::STOP);
        INSERT_ELEMENT(Mdp::Actions::RIGHT);
#undef INSERT_ELEMENT
    }

    return out << strings[value];
}

Mdp::Mdp() : V_old(0.0), Delta(std::numeric_limits<float>::max()), cicle_end(false), gamma(1), theta(0.1), iter(0){

	report.open("report.txt");

	a[Actions::LEFT] = GameUtils::command::LEFT;
	a[Actions::STOP] = GameUtils::command::STOP;
	a[Actions::RIGHT] = GameUtils::command::RIGHT;

	V[State::C] = 0.0;
	V[State::UL] = 0.0;
	V[State::UR] = 0.0;
	V[State::DL] = 0.0;
	V[State::DR] = 0.0;
	V[State::GO] = 0.0;

	policy[State::C] = a[Actions::STOP];
	policy[State::UL] = a[Actions::STOP];
	policy[State::UR] = a[Actions::STOP];
	policy[State::DL] = a[Actions::STOP];
	policy[State::DR] = a[Actions::STOP];
	policy[State::GO] = a[Actions::STOP];

	/*0-center --> stop*/
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.0526315, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.236842, State::DL, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.236842, State::DR, -1)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.236842, State::UR, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::STOP), make_tuple(0.236842, State::UL, -0.5)));
	//0-center --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::LEFT), make_tuple(0.45, State::UR, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::LEFT), make_tuple(0.1, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::LEFT), make_tuple(0.45, State::DR, -1)));
	//0-center --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.45, State::UL, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.1, State::C, 0)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::C, GameUtils::command::RIGHT), make_tuple(0.45, State::DL, -1)));
	//1-up-left --> stop
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::STOP), make_tuple(1, State::UL, -1)));
	//1-up-left --> left
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::LEFT), make_tuple(0.9, State::UL, -0.5)));
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::LEFT), make_tuple(0.1, State::C, 0)));
	//1-up-left --> right
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UL, GameUtils::command::RIGHT), make_tuple(1, State::UL, -1)));
	//2-up-right --> stop
	mdp.insert(pair<tuple<int, int>, tuple< float, int, int>>(make_tuple(State::UR, GameUtils::command::STOP), make_tuple(1, State::UR, -1)));
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
	cout << "inizio iterazione " << iter << endl;
	report << "inizio iterazione " << iter << endl;

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

		cout << "V(" << (State) i->first << ") : " << i->second << endl;
		report << "V(" << (State) i->first << ") : " << i->second << endl;
	}
	cout << "fine iterazione" << endl;
	report << "fine iterazione" << endl;
	iter++;
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
		cout << "Policy[" << (State) s << "] = " << (Actions) policy[s] << endl;
		report << "Policy[" << (State) s << "] = " << (Actions) policy[s] << endl;
	}
	report.close();
}

int Mdp::getCommandFromPolicy(int current_State){
	return policy.at(current_State);
}

Mdp::~Mdp(){}

} /* namespace data */
