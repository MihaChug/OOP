#pragma once

static const enum GEARBOX_STATE {back = -1, neutral = 0, first = 1, second = 2, third = 3, fourth = 4, fifth = 5};

static const enum MOVEMENT_DRIECTION { backward = -1, stay = 0, forward = 1};

static const std::map<GEARBOX_STATE, std::pair<unsigned, unsigned>> SPEED_RANGE =
{
	{ GEARBOX_STATE::back, {0, 20 }},
	{ GEARBOX_STATE::neutral, { 0, 150 }},
	{ GEARBOX_STATE::first, { 0, 30 }},
	{ GEARBOX_STATE::second, { 20, 50 }},
	{ GEARBOX_STATE::third, { 30, 60 }},
	{ GEARBOX_STATE::fourth, { 40, 90 }},
	{ GEARBOX_STATE::fifth, { 50, 150 }}
};

class CCar
{
public:
	CCar();
	~CCar() = default;
	bool IsEngineWorking() const
	{
		return m_isEngineTurnedOn;
	}
	bool TurnOnEngine();
	bool TurnOffEngine();
	GEARBOX_STATE GetGear() const;
	MOVEMENT_DRIECTION GetMovementDirection() const;
	unsigned GetCurrentSpeed() const;
	bool SetSpeed(unsigned const& speed);
	bool SetGear(GEARBOX_STATE const& gearState);

private:
	void SetMovementDirection();
	unsigned m_currentSpeed;
	bool m_isEngineTurnedOn;
	GEARBOX_STATE m_gearboxState;
	MOVEMENT_DRIECTION m_movementDirection;
};