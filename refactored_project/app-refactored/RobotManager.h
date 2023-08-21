# include "RobotController.h"
# include "RobotTracker.h"
# include "Strategy.h"


// This is the Contexte of the detection strategies in Strategy design pattern
class RobotManager
{
public:
    RobotManager(RobotController* controller) : controller_(controller);
    ~RobotManager();

    Strategy* setStrategy(Strategy *strategy);
    void executeStrategy();  // this method also updates `tracker_`

private:
    Strategy* strategy_;

    RobotController* controller_;
    RobotTracker* tracker_;
};
