#include "Robot.h"

class RobotController
{
public:
    RobotController(Robot* robot) : robot_(robot) {}
    
private:
    Robot* robot_;
};
