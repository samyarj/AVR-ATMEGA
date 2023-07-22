#include "ObjectAbs.h"

class Tile : public ObjectAbs
{
public:
    Tile(uint32_t x, uint32_t y) : ObjectAbs(x, y) {};
    ~Tile() = default;

    void setNeighbour(uint8_t angle, int idNeighbour);

private:
    std::vector<int> neighbours_ = std::vector<int>(8, 0);
    
    // this is the format of the `neigbours_`:
    std::map<uint8_t, int> angleToIndex_ = {
        {0, 0}, {45, 1}, {90, 2}, {135, 3},
        {180, 4}, {225, 5}, {270, 6}, {315, 7}
    };
};
