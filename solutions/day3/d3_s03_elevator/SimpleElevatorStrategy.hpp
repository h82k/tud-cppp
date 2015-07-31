#ifndef SIMPLEELEVATORSTRATEGY_HPP_
#define SIMPLEELEVATORSTRATEGY_HPP_

#include "ElevatorStrategy.hpp"

class SimpleElevatorStrategy: public ElevatorStrategy {
public:
	virtual ~SimpleElevatorStrategy();
	virtual int nextFloor();
};

#endif /* SIMPLEELEVATORSTRATEGY_HPP_ */
