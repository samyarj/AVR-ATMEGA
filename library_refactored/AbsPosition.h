#include <avr/io.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;


// Abstract class for 2d position of objects
class AbsPosition
{
public:
    AbsPosition(uint32_t x, uint32_t y) : x_(x), y_(y){}
    
    uint32_t getPosX() { return x_; }
    uint32_t getPosY() { return y_; }
    
    void setPosX(uint32_t x) { x_ = x; }
    void setPosY(uint32_t y) { y_ = y; }

private:
    uint32_t x_;
    uint32_t y_;
};
