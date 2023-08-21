#include "RobotManager.h"


void RobotManager::setStrategy(Strategy *strategy) 
{
    delete this->strategy_;
    this->strategy_ = strategy;
}

void RobotManager::executeStrategy() 
{
    if (this->strategy_ != nullptr)
        this->strategy_->execute();
}
