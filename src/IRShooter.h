/*
 * IRShooter.h
 *
 *  Created on: 18 feb. 2016
 *      Author: Dylan Vos
 */

#ifndef SRC_IRSHOOTER_H_
#define SRC_IRSHOOTER_H_

#include "WPILIB.h"

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
	Spark shootingWheel1, shootingWheel2;
	Victor intake;

};

#endif /* SRC_IRSHOOTER_H_ */
