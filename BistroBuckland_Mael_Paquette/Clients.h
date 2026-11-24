#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <vector>

#include "BaseGameEntity.h"

#include "ConsoleUtils.h"
#include "StateMachine.h"
#include "State.h"
#include "ClientsStates.h"

class Clients : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Clients>* m_pStateMachine;
    int m_Patience;
    int m_ReadingMenu;
    int m_Eating;
    int m_BusyTime;
	bool once = true;


public:

	Clients(int id, int patience) : BaseGameEntity(id), m_Patience(patience), m_ReadingMenu(3), m_Eating(4), m_BusyTime(1)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<Clients>(this);

        m_pStateMachine->SetCurrentState(Outside::Instance());

        m_pStateMachine->SetGlobalState(ClientsGlobalState::Instance());
    }

    ~Clients() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<Clients>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
	virtual int Patience() const { return m_Patience; }
	virtual void LowerPatience() { m_Patience--; }
	virtual void AddPatience() { m_Patience ++; }
	virtual int ReadMenu() { m_ReadingMenu--; return m_ReadingMenu; }
	virtual int Eat() { m_Eating--; return m_Eating; }
    virtual int BusyTime() { return m_BusyTime; }
    virtual void CountBusyTime() { m_BusyTime--; }
    virtual void SetBusyTime(int time) { m_BusyTime = time; }
	virtual bool Once() { return once; }
	virtual void SetOnce(bool value) { once = value; }
};
