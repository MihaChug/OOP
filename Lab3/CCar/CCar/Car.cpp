#include "stdafx.h"
#include "ClassCar.h"

static const std::map <std::string, GEARBOX_STATE> GEARBOX_STATES_MAP = 
{
	{ "back", GEARBOX_STATE::back },
	{ "neutral", GEARBOX_STATE::neutral },
	{ "first", GEARBOX_STATE::first },
	{ "second", GEARBOX_STATE::second },
	{ "third",GEARBOX_STATE::third },
	{ "fourth", GEARBOX_STATE::fourth },
	{ "fifth",GEARBOX_STATE::fifth }
};

static const std::map <GEARBOX_STATE, std::string> GEARBOX_INFO_MAP = 
{
	{ GEARBOX_STATE::back, "back" },
	{ GEARBOX_STATE::neutral, "neutral" },
	{ GEARBOX_STATE::first, "first" },
	{ GEARBOX_STATE::second, "second" },
	{ GEARBOX_STATE::third, "third" },
	{ GEARBOX_STATE::fourth, "fourth" },
	{ GEARBOX_STATE::fifth, "fifth" }
};

static const std::map <MOVEMENT_DRIECTION, std::string> MOVEMENT_INFO_MAP = {
	{ MOVEMENT_DRIECTION::forward, "Forward" },
	{ MOVEMENT_DRIECTION::backward, "Backward" },
	{ MOVEMENT_DRIECTION::stay, "Stay" }
};

void ShowCarInfo(CCar const& car)
{
	std::string infoStr;
	infoStr = (car.IsEngineWorking() == true ? "Engine working!" : "Engine standing by");
	std::cout << infoStr << std::endl;

	std::cout << "Movement Direction: " << MOVEMENT_INFO_MAP.find(car.GetMovementDirection())->second << std::endl;
	std::cout << "Current Speed " << car.GetCurrentSpeed() << std::endl;
	std::cout << "Gearbox state " << GEARBOX_INFO_MAP.find(car.GetGear())->second << std::endl;

}

void ShowHelp()
{
	std::cout << "Using commands: " << std::endl;
	std::cout << "TurnOn/ TurnOff - to start/stop engine working" << std::endl;
	std::cout << "SetSpeed - to set speed" << std::endl;
	std::cout << "SetGear  - to set gear from list :" << std::endl;
	std::cout << "back/ neutral/ first/ second/ third/ fouth/ fifth." << std::endl;
	std::cout << "Info - show current car information" << std::endl;
	std::cout << "Help - Show THIS info" << std::endl;
}

int main()
{
	CCar m_Car;
	std::string str;
	unsigned value;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << ">";
		std::cin >> str;

		if (str == "TurnOff")
		{
			m_Car.TurnOffEngine();
		}
		else if (str == "TurnOn")
		{
			m_Car.TurnOnEngine();
		}
		else if (str == "SetSpeed")
		{
			std::cin >> value;
			m_Car.SetSpeed(value);
		}
		else if (str == "SetGear")
		{
			std::cin >> str;
			if (GEARBOX_STATES_MAP.find(str) != GEARBOX_STATES_MAP.end())
			{
				m_Car.SetGear(GEARBOX_STATES_MAP.find(str)->second);
			}

		}
		else if (str == "Info")
		{
			ShowCarInfo(m_Car);
		}
		else if (str == "Help")
		{
			ShowHelp();
		}
		else
		{
			std::cout << "Invalid Command! Use Help!" << std::endl;
		}
	}
    return 0;
}

