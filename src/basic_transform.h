#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // TODO: Determine if possible in general, else provide counterexample:
    // compose(f, g) is equivalent to first applying g, then applying f.
   
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        BasicTransform newTransform;
        newTransform.scale.x = f.scale.x * g.scale.x;
        newTransform.translation.x = f.scale.x*g.translation.x + f.translation.x;

        newTransform.scale.y = f.scale.y * g.scale.y;
        newTransform.translation.y = f.scale.y*g.translation.y + f.translation.y;
        return newTransform;
       
    };

    // TODO: Determine if possible in general, else provide counterexample:
    static BasicTransform inverse(const BasicTransform& f) {
        BasicTransform newTransform;
        newTransform.scale.x = 1/f.scale.x;
        newTransform.scale.y = 1/f.scale.y;
        newTransform.translation.x = -1*f.translation.x;
        newTransform.translation.y = -1*f.translation.y;
        return newTransform;
    };

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif