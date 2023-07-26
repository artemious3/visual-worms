//
//  Agent.cpp
//  ai_try
//
//  Created by Артем Подгайский on 10.07.23.
//  Copyright © 2023 Артем Подгайский. All rights reserved.
//


#include "Agent.hpp"

//in radians
float r_angleComposition(float a1, float a2)
{
    float M2_PI = M_PI*2;
    if(a1 + a2 > M2_PI)
        return a1 + a2 - M2_PI;
    if (a1 + a2 < 0)
        return a1 + a2 + M2_PI;
    else
        return a1 + a2;
}


void Agent::initialize()
{
    speed = _SPEED;
    //angles
    direction = (rand() % 360) * (M_PI/180.0f);
    deltaAngle = _dANGLE * (M_PI/180.0f);
    constantAngle = _cANGLE * (M_PI/180.0f);
}

Agent::Agent()
{
}

void Agent::setDetectorAngle(float dAngle)
{
    detectorAngle = dAngle * (M_PI/180.0f);
}

void Agent::setDetectorLength(float dLength)
{
    detectorLength = dLength;
}

//choose the direction (straight by default)
Direction choose(float amounts[])
{

    //handle the situation when agent goes STRAIGHT into a border
    //then we choose random direction (right or left)
    if (amounts[1] == -1.0f)
        return (rand() % 2) ? static_cast<Direction>(1) : static_cast<Direction>(-1);
    
    //straight by default
    int defaultDirection = 1;
    
    if(amounts[0] > amounts[defaultDirection])
        defaultDirection = 0;
    if(amounts[2] > amounts[defaultDirection])
        defaultDirection = 2;
    return static_cast<Direction>(defaultDirection-1);
}

//if the agent tries to get substance amount out of the window, return -1.0
float Agent::protected_getAmount(const fmatrix& map, const float dx, const float dy)
{
    int mapPositionX = roundf(getPosition().x + dx);
    int mapPositionY = roundf(getPosition().y + dy);
    if(mapPositionX >= map.size() || mapPositionX < 0.0f ||
       mapPositionY >= map.size() || mapPositionY < 0.0f)
    {
        return  -1.0f;
    }
    else return map[mapPositionX][mapPositionY];
}

//get the direction of current agent
Direction Agent::getDirection(const fmatrix& map)
{
    float substanceAmounts[3];
    
    //check amount of subatance for each detector
    for(int i = -1; i <= 1; i++)
    {
        //absolute angle in window coordinate system
        float checkingAngle = r_angleComposition(direction, i*detectorAngle);
        float dx = cosf(checkingAngle)*detectorLength;
        float dy = sinf(checkingAngle)*detectorLength;
        substanceAmounts[i+1] = protected_getAmount(map, dx, dy);
    }
    return choose(substanceAmounts);
}

//agent leaves substance when moving
void Agent::makeTrail(fmatrix& map)
{
    float startX = getPosition().x - getOrigin().x;
    float startY = getPosition().y - getOrigin().y;
    float endX = startX + getSize().x;
    float endY = startY + getSize().y;
    
    for(int i = startX; i < endX; i++)
    {
        for(int j = startY; j < endY; j++)
        {
            if(i < _WINSIZE && i > 0.0f && j < _WINSIZE && j > 0.0f)
                map[i][j] = 1.0f;
        }
    }
}

void Agent::update(fmatrix& map)
{
    makeTrail(map);
    direction = r_angleComposition(direction,constantAngle);
    Direction direction_enum = getDirection(map);
    direction = r_angleComposition(direction, deltaAngle*direction_enum);
    float dx = cosf(direction)*speed;
    float dy = sinf(direction)*speed;
    move(dx, dy);
    
}
//IMAGE OPTIMIZATION
