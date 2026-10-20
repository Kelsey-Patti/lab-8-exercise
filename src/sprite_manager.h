#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

using SpriteID = size_t;

class SpriteManager {

public:
    sf::Texture& registerTexture(const std::string& filepath){
        if (mTextures.find(filepath) != mTextures.end()){
            return mTextures[filepath];
        }
        sf::Texture texture = sf::Texture(filepath);
        mTextures[filepath] = texture;
        return mTextures[filepath];
    };

    template <typename... Args> SpriteID createSprite(Args&&... args){
        mSprites.emplace_back(Sprite(std::forward<Args>(args)...));
        return mSprites.size()-1;
    }

    Sprite& getSprite(SpriteID id){
        return mSprites[id];
    }

    std::unordered_map<std::string, sf::Texture> mTextures;
    std::vector<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
