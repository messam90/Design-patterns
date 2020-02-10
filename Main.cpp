/*
 * Main.cpp
 *
 *  Created on: Feb 10, 2020
 *      Author: home
 */
#include "ChainOfResponsibility.hpp"

int main(){
	COR::Creature CR("Goblin", 10, 15);
	cout<<CR;
	COR::CreatureModifier CM(CR);
	COR::DoubleAttackModifier DAM(CR);
	COR::DoubleDefenseModifier DDM(CR);

	CM.Add(&DAM);
	CM.Add(&DDM);
	CM.Handle();
	cout<<CR;

	CORExcercise::Game game;
	CORExcercise::Goblin Goblin1(game);
	game.creatures.push_back(&Goblin1);
	CORExcercise::GoblinKing GoblinKing(game);
	game.creatures.push_back(&GoblinKing);
	game.ApplyBonuses();
	cout<<"Attack "<<Goblin1.get_attack()<<" Defense: "<<Goblin1.get_defense()<<endl;
	cout<<"Attack "<<GoblinKing.get_attack()<<" Defense: "<<GoblinKing.get_defense()<<endl;

	return 0;
}



