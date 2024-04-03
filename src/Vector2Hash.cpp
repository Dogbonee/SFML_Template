//
// Created by 24crickenbach on 4/2/2024.
//

#include "Vector2Hash.h"

#include <cstddef>
#include <functional>

size_t Vector2Hash::operator()(const sf::Vector2i &vector) const
{
    std::size_t hash = std::hash<int>()(vector.x);
    hash ^= std::hash<int>()(vector.y) << 1;
    return hash;
}
