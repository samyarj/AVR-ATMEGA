#include "ObjectAbs.h"

class Tile : public ObjectAbs
{
public:
    Tile(uint8_t x, uint8_t y) : ObjectAbs(x, y){};
    ~Tile() = default;
};
