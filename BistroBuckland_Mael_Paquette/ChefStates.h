
#pragma once
#include "State.h"


class Chef;
struct Telegram;


class ChefGlobalState : public State<Chef>
{
private:

	ChefGlobalState() {}

	//copy ctor and assignment should be private
	ChefGlobalState(const ChefGlobalState&);
	ChefGlobalState& operator=(const ChefGlobalState&);

public:

	//this is a singleton
	static ChefGlobalState* Instance();

	virtual void Enter(Chef* pChef);

	virtual void Execute(Chef* pChef);

	virtual void Exit(Chef* pChef);

	virtual bool OnMessage(Chef* pChef, const Telegram& msg);
};


class CookDish : public State<Chef>
{
private:

	CookDish() {}

	//copy ctor and assignment should be private
	CookDish(const CookDish&);
	CookDish& operator=(const CookDish&);

public:

	//this is a singleton
	static CookDish* Instance();

	virtual void Enter(Chef* pChef);

	virtual void Execute(Chef* pChef);

	virtual void Exit(Chef* pChef);

	virtual bool OnMessage(Chef* pChef, const Telegram& msg);
};


class WaitForOrder : public State<Chef>
{
private:

	WaitForOrder() {}

	//copy ctor and assignment should be private
	WaitForOrder(const WaitForOrder&);
	WaitForOrder& operator=(const WaitForOrder&);

public:

	//this is a singleton
	static WaitForOrder* Instance();

	virtual void Enter(Chef* pChef);

	virtual void Execute(Chef* pChef);

	virtual void Exit(Chef* pChef);

	virtual bool OnMessage(Chef* pChef, const Telegram& msg);
};


class Restock : public State<Chef>
{
private:

	Restock() {}

	//copy ctor and assignment should be private
	Restock(const Restock&);
	Restock& operator=(const Restock&);

public:

	//this is a singleton
	static Restock* Instance();

	virtual void Enter(Chef* pChef);

	virtual void Execute(Chef* pChef);

	virtual void Exit(Chef* pChef);

	virtual bool OnMessage(Chef* pChef, const Telegram& msg);
};





