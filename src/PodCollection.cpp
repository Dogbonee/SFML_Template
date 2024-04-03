//
// Created by 24crickenbach on 4/2/2024.
//

#include "PodCollection.h"

PodCollection::PodCollection() = default;

void PodCollection::CalculateNextTurn()
{
    //For every alive pod, increment the neighbors in map by one.
    //When all is said and done, every map(x,y) will show the amount of neighbors that (x,y) has
    for(const auto& pod : m_alivePods)
    {
        for(int y = pod.y - 1; y <= pod.y + 1; y++)
        {
            for(int x = pod.x - 1; x <= pod.x + 1; x++)
            {
                if(x == pod.x && y == pod.y)continue;
                m_nextTurn[{x, y}]++;
            }
        }
    }
    //Create a new array of alive pods that based on the amount of neighbors in every map(x,y)
    //Since the values of every member of the array are vastly different from turn to turn,
    //it makes sense to create a new vector for every turn rather than keeping the array in place.
    PodGroup nextTurnPods;
    for(auto& pod : m_nextTurn)
    {
        if(pod.second == 3 && std::find(m_alivePods.begin(), m_alivePods.end(), pod.first) == m_alivePods.end() ||
            ((pod.second == 2 || pod.second == 3) && std::find(m_alivePods.begin(), m_alivePods.end(), pod.first) != m_alivePods.end()))
        {
            nextTurnPods.push_back(pod.first);
        }
    }
    m_alivePods = nextTurnPods;
    m_nextTurn.clear();
    PopulateVisualArray();
}

void PodCollection::PopulateVisualArray()
{
    //Clear the current pod visual and populate visual rects based on tile coords
    m_podVisuals.clear();
    for(auto& pod : m_alivePods)
    {
        sf::RectangleShape rect(sf::Vector2f(PodSize, PodSize));
        rect.setPosition(PodSize * pod.x, PodSize * pod.y);
        m_podVisuals.emplace_back(rect);
    }
}

void PodCollection::TogglePod(sf::Vector2i podPos)
{
    //If podPos exists in alivePods, delete it, otherwise add it to alivePods
    std::vector<sf::Vector2i>::iterator it;
    if((it = std::find(m_alivePods.begin(), m_alivePods.end(), podPos)) == m_alivePods.end())
    {
        m_alivePods.emplace_back(podPos);

    }else
    {
        m_alivePods.erase(it);
    }
    PopulateVisualArray();
}

size_t PodCollection::CollectionSize() const
{
    return m_alivePods.size();
}


void PodCollection::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto& rect : m_podVisuals)
    {
        target.draw(rect);
    }
}
