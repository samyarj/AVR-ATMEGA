#include "Position.h"
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <memory>

class ObjectAbs
{
public:
    ObjectAbs(uint8_t posX, uint8_t posY) { position_ = new Position(posX, posY); };
    virtual ~ObjectAbs() { delete position_; };

private:
    Position *position_;
};
