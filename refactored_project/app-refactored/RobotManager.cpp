#include "RobotManager.h"


void RobotManager::setStrategy(Strategy *strategy) 
{
    delete this->strategy_;
    this->strategy_ = strategy;
}

void RobotManager::executeStrategy(Deplacement &deplacement) 
{
    if (this->strategy_ != nullptr)
        this->strategy_->execute(deplacement);
}