#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <vector>

#include "BaseGameEntity.h"

#include "ConsoleUtils.h"
#include "ChefStates.h"
#include "StateMachine.h"
#include "State.h"



class Chef : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Chef>* m_pStateMachine;

	std::vector<int> m_DishesToCook;
    int m_Stock;
    bool m_Cooking;

    



public:

	Chef(int id) : m_Stock(1), m_Cooking(false), BaseGameEntity(id)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<Chef>(this);

        m_pStateMachine->SetCurrentState(WaitForOrder::Instance());

        m_pStateMachine->SetGlobalState(ChefGlobalState::Instance());
    }

    ~Chef() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<Chef>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
	virtual bool Cooking() const { return m_Cooking; }
	virtual void SetCooking(bool cooking) { m_Cooking = cooking; }
	virtual void AddDishToCook(int client) { m_DishesToCook.push_back({client}); }
	virtual void CookDish() { m_Stock --; }
	virtual void DishDone() { m_DishesToCook.erase(m_DishesToCook.begin()); } 
	virtual int GetStock() const { return m_Stock; }
	virtual int DishesToCook() const { return m_DishesToCook.size(); }
	virtual void GettingStock() { m_Stock++; }
	virtual int NextOrder() { if (!m_DishesToCook.empty()) { return m_DishesToCook.front(); } else { return -1; } }


};
