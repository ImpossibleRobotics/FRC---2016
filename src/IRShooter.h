/*
 * IRShooter.h
 *
 *  Created on: 18 feb. 2016
 *      Author: Dylan Vos
 */

#pragma once

#include <Spark.h>
#include <Victor.h>

class IRShooter {
public:
	IRShooter(uint32_t shootingWheel1Channel, uint32_t shootingWheel2Channel, uint32_t intakeChannel);

	void Shoot();
	void StopShoot();
	void ShootingSequence();
	void CurvedShoot(float curve);
	void TakeIn();
	void TakeOut();
	void StopInTake();

protected:
	frc::Spark shootingWheel1, shootingWheel2;
	frc::Victor intake;

};
