#include "Position.h"

class ObjectAbs
{
public:
    ObjectAbs(uint8_t posX, uint8_t posY) { position_ = new Position(posX, posY); };
    virtual ~ObjectAbs() { delete position_; };

private:
    Position *position_;
};
