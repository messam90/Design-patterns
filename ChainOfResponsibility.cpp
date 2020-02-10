/*
 * ChainOfResponsibility.cpp
 *
 *  Created on: Feb 10, 2020
 *      Author: home
 */
#include "ChainOfResponsibility.hpp"

namespace CORExcercise{
  Creature::Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                          base_defense(base_defense) {}
  int Creature::get_attack(){
    return base_attack;
  }
  int Creature::get_defense(){
    return base_defense;
  }
  void Creature::set_attack(int attack){
    this->base_attack = attack;
  }
  void Creature::set_defense(int defense){
    this->base_defense  = defense;
  }

  CreatureModifier::CreatureModifier(Creature& Cr, int Bonus): Cr(Cr), Bonus(Bonus){}

  void CreatureModifier::Add(CreatureModifier* CM){
    if(Next) Next->Add(CM);
    else Next = CM;
  }
  void CreatureModifier:: Handle(){
    if(Next) Next->Handle();
  }

  AttackModifier::AttackModifier(Creature& Cr, int Bonus) : CreatureModifier(Cr, Bonus){}

  void AttackModifier::Handle(){
    Cr.set_attack(Cr.get_attack() + Bonus);
    CreatureModifier::Handle();
  }

  DefenseModifier::DefenseModifier(Creature& Cr, int Bonus): CreatureModifier(Cr, Bonus){}

  void DefenseModifier::Handle(){
    Cr.set_defense(Cr.get_defense() + Bonus);
    CreatureModifier::Handle();
  }

  Goblin::Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

  Goblin::Goblin(Game &game) : Creature(game, 1, 1) {
    for(auto GoblinPtr: game.creatures){
      GoblinPtr->CMPtr->Add(new DefenseModifier(*GoblinPtr, 1));
    }
    CMPtr = new CreatureModifier(*this, 0);
    CMPtr->Add(new DefenseModifier(*this, game.creatures.size()));
  }

  GoblinKing::GoblinKing(Game &game) : Goblin(game, 3, 3) {
    for(auto GoblinPtr : game.creatures){
      GoblinPtr->CMPtr->Add(new AttackModifier(*GoblinPtr, 1));
      GoblinPtr->CMPtr->Add(new DefenseModifier(*GoblinPtr, 1));
    }
    CMPtr = new CreatureModifier(*this, 0);
    CMPtr->Add(new DefenseModifier(*this, game.creatures.size()));
  }

  void Game::ApplyBonuses(){
	  for(auto CreaturePtr : creatures){
		  CreaturePtr->CMPtr->Handle();
	  }
  }
}



