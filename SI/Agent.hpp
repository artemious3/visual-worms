//
//  Agent.hpp
//  ai_try
//
//  Created by Артем Подгайский on 10.07.23.
//  Copyright © 2023 Артем Подгайский. All rights reserved.
//
#ifndef Agent_hpp
#define Agent_hpp
#include "Common.h"

enum Direction
{
    D_LEFT = -1,
    D_STRAIGHT = 0,
    D_RIGHT = 1
};

class Agent : public sf::RectangleShape
{
private:
    float direction, speed;
    float deltaAngle;
    float detectorLength, detectorAngle;
    float constantAngle;
    //between a vertical line and a detector;
    //const int detectorAmount = 3;

private:
    Direction getDirection(const fmatrix& map);
    void makeTrail(fmatrix& map);
    float protected_getAmount(const fmatrix& map, const float dx, const float dy);
    
    
public:
    Agent();
    Agent(float dAngle,  float dLength, const sf::Vector2f& size = sf::Vector2f(1.0, 1.0));
    
public:
    void update(fmatrix& map);
    void initialize(); //NECESSARY TO CALL AFTER SETTING eVARIABLES
    void setDetectorAngle(float dAngle);
    void setDetectorLength(float dLength);
    
};

#endif /* Agent_hpp */
