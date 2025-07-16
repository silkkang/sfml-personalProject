
#pragma once
#include <SFML/Graphics.hpp>
#include "pugixml.hpp"

class TileMap : public sf::Transformable
{
protected:
    sf::VertexArray vertices;
    sf::Texture tileset;

    int mapWidth = 0;
    int mapHeight = 0;
    int tileWidth = 0;
    int tileHeight = 0;

public:
    TileMap() = default;
    virtual ~TileMap() = default;

    int GetMapWidth() const { return mapWidth; }
    int GetMapHeight() const { return mapHeight; }
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }

    bool Load(const std::string& tmxFile, const std::string& tilesetFile, int firstGid);
    virtual void Draw(sf::RenderWindow& window);
};