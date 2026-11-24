
#ifndef MY_NAMES_H
#define MY_NAMES_H

#include <string>

enum
{
    ent_Chef,

    ent_Waiter,

    ent_Client1,

	ent_Client2,
};

inline std::string GetNameOfEntity(int n)
{
    switch (n)
    {
	case ent_Chef: return "Chef";
	case ent_Waiter: return "Waiter";
	case ent_Client1: return "Steve";
	case ent_Client2: return "Sophie";
    }
}

#endif