//
// Created by 24crickenbach on 4/2/2024.
//

#ifndef PODCOLLECTION_H
#define PODCOLLECTION_H
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Vector2Hash.h"


using PodMap = std::unordered_map<sf::Vector2i, int, Vector2Hash>;
using PodGroup = std::vector<sf::Vector2i>;

class PodCollection : public sf::Drawable{

    PodGroup m_alivePods;
    std::vector<sf::RectangleShape> m_podVisuals;
    PodMap m_nextTurn;




public:
    PodCollection();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void CalculateNextTurn();
    void PopulateVisualArray();
    void TogglePod(sf::Vector2i podPos);
    size_t CollectionSize() const;


    const static int PodSize = 30;
};



#endif //PODCOLLECTION_H
