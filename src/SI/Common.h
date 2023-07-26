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
typedef std::vector< std::vector<float> > fmatrix;
typedef std::set< std::pair<float, float> > positionsSet;

//_______________________PARAMETERS__________________________

#define _ANGLE 40.0f //angle between side detectors and vertical detector
#define _LENGTH 20.0f //length of detector
#define _dANGLE 20.0f //chagne of agent's direction after side detectors explore more substance

#define _DIFUSSION 0.003f; //how fast the substance disappear
#define _cANGLE 0.2f //every update() call
                    //the agent changes its direction by _cANGLE

#define _SIZE 2.0f //size of agent (px)
#define _WINSIZE 1500 //size of window
#define _AMOUNT 1400 //amount of agents
#define _SPEED 2.0f //every update() call the agent moves by <_SPEED> px
#define _BORDER 100 //distance between window bound and bound of agents' area

#define _COLOR_DIFUSSION 0.0006f //how fast the color of substance changes

//____________________________________________________________
#endif
