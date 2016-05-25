#include "stdafx.h"
#include "ClassCar.h"

CCar::CCar()
	: m_isEngineTurnedOn(false)
	, m_gearboxState(GEARBOX_STATE::neutral)
	, m_movementDirection(MOVEMENT_DRIECTION::stay)
	, m_currentSpeed(0)
{
}

bool CCar::TurnOnEngine()
{
	if (m_isEngineTurnedOn)
	{
		return false;
	}
	m_isEngineTurnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_isEngineTurnedOn || m_currentSpeed != 0 || m_gearboxState != GEARBOX_STATE::neutral)
	{
		return false;
	}
	m_isEngineTurnedOn = false;
	return true;
}

GEARBOX_STATE CCar::GetGear() const
{
	return m_gearboxState;
}

MOVEMENT_DRIECTION CCar::GetMovementDirection() const
{
	return m_movementDirection;
}

unsigned CCar::GetCurrentSpeed() const
{
	return m_currentSpeed;
}

bool CCar::SetSpeed(unsigned const& speed)
{
	if (!m_isEngineTurnedOn || (speed > m_currentSpeed && m_gearboxState == GEARBOX_STATE::neutral))
	{
		return false;
	}
	auto speed_limits = SPEED_RANGE.find(m_gearboxState) -> second;
	if (speed_limits.first <= speed && speed_limits.second >= speed)
	{
		m_currentSpeed = speed;
		SetMovementDirection();
		return true;
	}
	return false;
}

bool CCar::SetGear(GEARBOX_STATE const& gearState)
{
	if (!m_isEngineTurnedOn)
	{
		return false;
	}

	if (gearState == GEARBOX_STATE::back && m_currentSpeed != 0)
	{
		return false;
	}

	if (gearState == GEARBOX_STATE::first && m_currentSpeed != 0)
	{
		return false;
	}

	if (m_gearboxState == GEARBOX_STATE::back && (gearState != GEARBOX_STATE::back && gearState != GEARBOX_STATE::neutral) && m_currentSpeed != 0)
	{
		return false;
	}	

	auto speed_limits = SPEED_RANGE.find(gearState)->second;
	if (speed_limits.first <= m_currentSpeed && speed_limits.second >= m_currentSpeed)
	{
		m_gearboxState = gearState;
		return true;
	}

	return false;
}

void CCar::SetMovementDirection()
{
	if (m_currentSpeed != 0)
	{
		if (m_gearboxState == GEARBOX_STATE::back)
		{
			m_movementDirection = MOVEMENT_DRIECTION::backward;
		}
		else if (m_gearboxState != GEARBOX_STATE::neutral)
		{
			m_movementDirection = MOVEMENT_DRIECTION::forward;
		}
	}
	else
	{
		m_movementDirection = MOVEMENT_DRIECTION::stay;
	}
}