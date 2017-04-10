/*
 * EnergyMinimizingStrategy.h
 *
 *  Created on: 15.07.2013
 *      Author: anjorin
 */

#ifndef ENERGYMINIMIZINGSTRATEGY_H_
#define ENERGYMINIMIZINGSTRATEGY_H_

#include "ElevatorStrategy.h"

class EnergyMinimizingStrategy : public ElevatorStrategy {
public:
	EnergyMinimizingStrategy();
	virtual ~EnergyMinimizingStrategy();

	virtual const Floor* next(const Elevator* elevator) const;
};

#endif /* ENERGYMINIMIZINGSTRATEGY_H_ */
