# include "RobotController.h"
# include "Strategy.h"

// implémenter patron stratégie afin de changer order algo
class RobotManager
{
public:
    RobotManager(RobotController* controller) : controller_(controller);
    ~RobotManager();

    void setStrategy(Strategy *strategy) {
        delete this->strategy;
        this->strategy = strategy;
    }

    void executeStrategy(Deplacement &deplacement) {
        if (this->strategy != nullptr)
            this->strategy->execute(deplacement);
    }

private:
    RobotController* controller_;
    Strategy* strategy_; 
};