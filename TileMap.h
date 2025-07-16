
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

    std::vector<std::vector<int>> tileData;
public:
    TileMap() = default;
    virtual ~TileMap() = default;

    int GetMapWidth() const { return mapWidth; }
    int GetMapHeight() const { return mapHeight; }
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }

    bool IsBlocked(sf::Vector2f& pos);
    int IsSpawn(const sf::Vector2f& pos);

    bool Load(const std::string& tmxFile, const std::string& tilesetFile, int firstGid);
    virtual void Draw(sf::RenderWindow& window);
};