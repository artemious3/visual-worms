//
//  Common.h
//  ai_try
//
//  Created by Артем Подгайский on 12.07.23.
//  Copyright © 2023 Артем Подгайский. All rights reserved.
//

#ifndef Common_h
#define Common_h

#pragma once
#include <set>
#include <vector>
#include <ctime>
#include <array>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
typedef std::vector<std::vector<float>> fmatrix;
typedef std::set<std::pair<float, float>> positionsSet;

//_______________________PARAMETERS__________________________

#define _ANGLE 60.0f //angle between side detectors and y-axis
#define _LENGTH 14.0f //length of detector
#define _dANGLE 20.0f //angle change when detector explores substance

#define _DIFUSSION 0.003f; //how fast the substance disappear
#define _cANGLE 0.2f //every update() call
                    //the agent rotates to _cANGLE

#define _SIZE 3.0f //size of agent (px)
#define _WINSIZE 1500 //size of window
#define _AMOUNT 1400 //amount of agents
#define _SPEED 5.0f //every update() call agent moves <_SPEED> px
#define _BORDER 100 //distance between window bound and bound of agents area

#define _COLOR_DIFUSSION 0.0006f //how fast the color of substance changes

//____________________________________________________________
#endif
