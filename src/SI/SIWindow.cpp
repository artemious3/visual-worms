//
//  SIWindow.cpp
//  ai_try
//
//  Created by Артем Подгайский on 10.07.23.
//  Copyright © 2023 Артем Подгайский. All rights reserved.
//

#include "SIWindow.hpp"

//choose random coordinate pair in the window
inline std::pair<float, float> randomCoordinate(int rangeX,int rangeY)
{
    return std::make_pair(rand() % rangeX + _BORDER, rand() % rangeY + _BORDER);
}

//initilize internal window
SIWindow::SIWindow(sf::VideoMode mode, const sf::String title, const int aAmount):
    sf::RenderWindow(mode, title), agentAmount(aAmount)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    setFramerateLimit(60);
    initializeMap();
    makeAgents();
    substanceImage.create(getSize().x, getSize().y);
    clear();
}

void SIWindow::chooseRandomPositions(std::unique_ptr<positionsSet> & firstPositions)
{
    int sizeX = getSize().x;
    int sizeY = getSize().y;
    while (firstPositions->size() < agentAmount)
    {
        firstPositions->insert(randomCoordinate(sizeX-(2*_BORDER), sizeY-(2*_BORDER)));
    }
}



void SIWindow::makeAgents()
{
    //создаем set и создаем агентов
    std::unique_ptr<positionsSet> firstPositions = std::make_unique<positionsSet>();
    chooseRandomPositions(firstPositions);
    agents = new std::vector<Agent>(agentAmount);
    
    //перебираем агентов одновременно с координатами множества, инициализируя агентов
    auto coordinate = firstPositions->begin();
    for (auto a_iter = agents->begin(); a_iter < agents->end(); a_iter++)
    {
        a_iter->setSize(sf::Vector2f(_SIZE,  _SIZE));
        a_iter->setPosition(coordinate->first, coordinate->second);
        a_iter->setFillColor(sf::Color::Green);
        a_iter->setDetectorAngle(_ANGLE);
        a_iter->setDetectorLength(_LENGTH);
        a_iter->setOrigin(_SIZE/2.0f, _SIZE/2.0f);
        a_iter->initialize();
        coordinate++;
    }
}

void SIWindow::update()
{
    updateMap();
    for(Agent& agent : *agents)
    {
        agent.update(substanceMap);
        //draw(agent);
    }
    if(_COLOR_DIFUSSION)
        updateColorWeights();
    drawSubstance();
}

void SIWindow::updateMap()
{
    for(auto& i : substanceMap)
    {
        for(auto& j : i)
        {
            if(j > difussion)
                j-=difussion;
            else
                j = 0.0f;
        }
    }
}

inline int nextWeight(int i)
{
    //assert(i < 3);
    return (i==2) ? 0 : i+1;
}

//OPTIMIZATION
void SIWindow::updateColorWeights()
{
    static int decreasingIndex = 0;
    if(colorWeights[decreasingIndex] - _COLOR_DIFUSSION > 0.0f)
    {
        colorWeights[decreasingIndex] -= _COLOR_DIFUSSION;
    }
    else
    {
        colorWeights[decreasingIndex] = 0.0f;
        decreasingIndex = nextWeight(decreasingIndex);
    }
    int  nxtIndex = nextWeight(decreasingIndex);
    if(colorWeights[nxtIndex] + _COLOR_DIFUSSION < 1.0f)
    {
        colorWeights[nxtIndex] += _COLOR_DIFUSSION;
    }
    else
    {
        colorWeights[nxtIndex] = 1.0f;
    }
}

void SIWindow::initializeMap()
{
    substanceMap = fmatrix(getSize().x);
    for(auto &i : substanceMap)
    {
        i = std::vector<float>(getSize().y);
        for (auto &j : i)
        {
            j = 0.00000f;
        }
    }
    difussion = _DIFUSSION;
}

void SIWindow::drawSubstance()
{
    for(int i = 0; i < substanceMap.size();i++)
    {
        for(int j = 0; j < substanceMap[i].size(); j++)
        {
            substanceImage.setPixel(i, j, sf::Color(150*substanceMap[i][j]*colorWeights[0],    150*substanceMap[i][j]*colorWeights[1], 200*substanceMap[i][j]*colorWeights[2]));
        }
    }
    substanceTexture.loadFromImage(substanceImage);
    sf::Sprite bckgr;
    bckgr.setTexture(substanceTexture);
    draw(bckgr);
}


