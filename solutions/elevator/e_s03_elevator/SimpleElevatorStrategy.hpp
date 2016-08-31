#ifndef SIMPLEELEVATORSTRATEGY_HPP_
#define SIMPLEELEVATORSTRATEGY_HPP_

#include "ElevatorStrategy.hpp"

/**
 * @name SimpleElevatorStrategy
 * @author cppp
 * @brief simple elevator strategy just adding moved floors
 */
class SimpleElevatorStrategy: public ElevatorStrategy {
public:
    /**
     * @name ~SimpleElevatorStrategy();
     * @author cppp
     * @brief destructor
     */
	virtual ~SimpleElevatorStrategy();
    /**
     * @name nextFloor()
     * @author cppp
     * @brief calculation of senseful next floor
     * @return int senseful next floor
     */
	virtual int nextFloor();
};

#endif /* SIMPLEELEVATORSTRATEGY_HPP_ */
