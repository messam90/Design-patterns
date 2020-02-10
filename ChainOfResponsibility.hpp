/*
 * ChainOfResponsibility.hpp
 *
 *  Created on: Feb 10, 2020
 *      Author: home
 */

#ifndef CHAINOFRESPONSIBILITY_HPP_
#define CHAINOFRESPONSIBILITY_HPP_

#include "Headers.hpp"

namespace COR{
  class Creature{
    private:
    string Name;
    int Attack, Defense;
    public:
    Creature(string Name, int Attack, int Defense): Name(Name), Attack(Attack), Defense(Defense){}

    friend ostream& operator<< (ostream& OS, Creature& Obj){
      OS<<"Creature: "<<Obj.Name<<" has Attack: "<<Obj.Attack<<" and Defense: "<<Obj.Defense<<endl;
      return OS;
    }

    friend class DoubleAttackModifier;
    friend class DoubleDefenseModifier;
  };

  class CreatureModifier{
    private:
    CreatureModifier* Next{nullptr};

    protected:
    Creature& CreatureRef;

    public:
    CreatureModifier(Creature& Creature) : CreatureRef(Creature){}

    void Add(CreatureModifier* CMPtr){
      if(Next) Next->Add(CMPtr);
      else Next = CMPtr;
    }

    virtual void Handle(){
      //if(Next) Next->Handle();
      CreatureModifier* TempNext = Next;
      while(TempNext){
        TempNext->Handle();
        TempNext = TempNext->Next;
      }
    }
  };

  class DoubleAttackModifier : public CreatureModifier{
    public:
    DoubleAttackModifier(Creature& Creature) : CreatureModifier(Creature){}
    void Handle() override{
      CreatureRef.Attack *= 2;
      //CreatureModifier::Handle();
    }
  };

  class DoubleDefenseModifier : public CreatureModifier{
    public:
    DoubleDefenseModifier(Creature& Creature) : CreatureModifier(Creature){}
    void Handle() override{
      CreatureRef.Defense *= 2;
      //CreatureModifier::Handle();
    }
  };

  class NoBonusModifier : public CreatureModifier{
    public:
    NoBonusModifier(Creature& Creature) : CreatureModifier(Creature){}
    void Handle() override{

    }
  };
}

namespace CORExcercise{
  struct Creature;
  struct Game
  {
    vector<Creature*> creatures;
    void ApplyBonuses();
  };

  struct StatQuery
  {
    enum Statistic { attack, defense } statistic;
    int result;
  };

  class CreatureModifier{
    private:
    CreatureModifier* Next{nullptr};
    protected:
    Creature& Cr;
    int Bonus{0};
    public:
    CreatureModifier() = default;
    CreatureModifier(Creature& Cr, int Bonus);
    void Add(CreatureModifier* CM);
    virtual void Handle();
  };

  class AttackModifier : public CreatureModifier{
    public:
    AttackModifier(Creature& Cr, int Bonus);
    void Handle() override;
  };

  class DefenseModifier : public CreatureModifier{
    public:
    DefenseModifier(Creature& Cr, int Bonus);
    void Handle() override;
  };

  struct Creature
  {
    protected:
    Game& game;
    int base_attack, base_defense;


    public:
    Creature(Game &game, int base_attack, int base_defense);
    int get_attack();
    int get_defense();
    void set_attack(int attack);
    void set_defense(int defense);

    CreatureModifier* CMPtr;
  };

  class Goblin : public Creature
  {
    public:
    Goblin(Game &game, int base_attack, int base_defense);
    Goblin(Game &game);
    Goblin(Goblin& Gob);
  };

  class GoblinKing : public Goblin
  {
    public:
    GoblinKing(Game &game);
  };
}



#endif /* CHAINOFRESPONSIBILITY_HPP_ */
