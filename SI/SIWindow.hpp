//
//  SIWindow.hpp
//  ai_try
//
//  Created by Артем Подгайский on 10.07.23.
//  Copyright © 2023 Артем Подгайский. All rights reserved.
//

#ifndef SIWindow_hpp
#define SIWindow_hpp

#include "Agent.hpp"
#include "Common.h"

//external funcs
inline std::pair<float, float> randomCoordinate(int rangeX, int rangeY);

//in-class funcs
class SIWindow : public sf::RenderWindow
{
private:
    int agentAmount;
    float difussion;
    //only used during initialization
    std::vector<Agent>* agents;
    fmatrix substanceMap;
    sf::Image substanceImage;
    sf::Texture substanceTexture;
    float colorWeights[3] = {1.0f, 0.0f, 0.0f};

private:
    void chooseRandomPositions(std::unique_ptr<positionsSet>& firstPositions);
    void initializeMap();
    void updateMap();
    void makeAgents();
    void drawSubstance();
    void updateColorWeights();
    
public:
    SIWindow(sf::VideoMode mode, const sf::String title, int aAmount);
    void update();
};


#endif /* SIWindow_hpp */
