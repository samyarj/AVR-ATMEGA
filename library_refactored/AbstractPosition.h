#include <avr/io.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

class AbsPosition
{
public:
    AbsPosition(uint8_t x, uint8_t y) : x_(x), y_(y){}
    
    uint8_t getPosX() { return x_; }
    uint8_t getPosY() { return y_; }
    
    void setPosX(uint8_t x) { x_ = x; }
    void setPosY(uint8_t y) { y_ = y; }

private:
    uint8_t x_;
    uint8_t y_;
};
