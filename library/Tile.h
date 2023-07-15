#include "ObjectAbs.h"

class Tile : public ObjectAbs
{
public:
    Tile(uint32_t x, uint32_t y) : ObjectAbs(x, y){};
    ~Tile() = default;

    void setNeighbour(uint8_t angle, int idNeighbour);

private:
    uint32_t neighbours_[8];
};
