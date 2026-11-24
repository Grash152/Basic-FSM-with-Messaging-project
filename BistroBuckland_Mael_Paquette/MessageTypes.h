#include <string>

enum message_type
{
    Msg_Arrive,
    Msg_ReadyToOrder,
    Msg_NewOrder,
	Msg_DishCooked,
	Msg_OrderReady,
	Msg_FoodServed,
    Msg_BillPlease,
	Msg_HereIsTheBill,
};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
	case Msg_Arrive: return "Nouveau client arrive";
	case Msg_ReadyToOrder: return "Je suis pret pour passer commande";
	case Msg_NewOrder: return "On a une nouvelle commande";
	case Msg_DishCooked: return "Le plat est pret";
	case Msg_OrderReady: return "La commande est prête";
	case Msg_FoodServed: return "Le repas est servi";
	case Msg_BillPlease: return "Je voudrais l'amande";
	case Msg_HereIsTheBill: return "Voici l'amande";
    default:

        return "Not recognized!";
    }
}