# include "RobotController.h"
# include "Strategy.h"


// This is the Contexte of the detection strategies in Strategy design pattern
class RobotManager
{
public:
    RobotManager(RobotController* controller) : controller_(controller);
    ~RobotManager();

    void setStrategy(Strategy *strategy);
    void executeStrategy(Deplacement &deplacement);

private:
    RobotController* controller_;
    Strategy* strategy_; 
};
