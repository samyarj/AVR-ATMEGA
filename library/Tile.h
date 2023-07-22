#include "ObjectAbs.h"

#include <vector>
#include <map>

class Tile : public ObjectAbs
{
public:
    Tile(uint32_t x, uint32_t y) : ObjectAbs(x, y) {};
    ~Tile() = default;

    void setNeighbour(uint8_t angle, int idNeighbour)
    {
        if (angleToIndex.count(angle) > 0) {
            neighbour_[angleToIndex.at(angle)] = idNeighbour;
        }
    }
private:
    std::vector<int> neighbour_ = std::vector<int>(8, 0);
    std::map<uint8_t, int> angleToIndex = {
        {0, 0}, {45, 1}, {90, 2}, {135, 3},
        {180, 4}, {225, 5}, {270, 6}, {315, 7}
    };
};

