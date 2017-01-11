/*
 * IRShooter.cpp
 *
 *  Created on: 18 feb. 2016
 *      Author: Dylan Vos
 */

#include <IRShooter.h>

IRShooter::IRShooter(uint32_t shootingWheel1Channel, uint32_t shootingWheel2Channel, uint32_t intakeChannel) :
	shootingWheel1(shootingWheel1Channel),
	shootingWheel2(shootingWheel2Channel),
	intake(intakeChannel)
{
	shootingWheel1.SetInverted(true);
}

void IRShooter::Shoot()
{
	shootingWheel1.Set(1);
	shootingWheel2.Set(1);
}

void IRShooter::StopShoot()
{
	shootingWheel1.Set(0);
	shootingWheel2.Set(0);
}

void IRShooter::ShootingSequence()
{
	intake.Set(-0.7);
	Wait(0.5);
	Shoot();
	StopInTake();
	Wait(0.75);
	TakeIn();
	Wait(0.25);
	StopInTake();
	StopShoot();
}

void IRShooter::CurvedShoot(float curve)
{
	if(curve<0 )
	{
		shootingWheel1.Set(1+curve);
		shootingWheel2.Set(1);
	}

	else if(curve>0)
	{
		shootingWheel1.Set(1);
		shootingWheel2.Set(1-curve);
	}
}

void IRShooter::TakeIn()
{
	intake.Set(1);
}

void IRShooter::TakeOut()
{
	intake.Set(-1);
}

void IRShooter::StopInTake()
{
	intake.Set(0);
}
