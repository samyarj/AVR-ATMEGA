# include "RobotController.h"
# include "Strategy.h"

// implémenter patron stratégie afin de changer order algo
class RobotManager
{
public:
    RobotManager(RobotController* controller) : controller_(controller);
    ~RobotManager();

private:
    RobotController* controller_;
    Strategy* strategy; 
};