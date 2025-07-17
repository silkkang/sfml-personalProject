#include "stdafx.h"
#include "TileMap.h"


bool TileMap::Load(const std::string& tmxFile, const std::string& tilesetFile, int firstGid)
{
    if (!tileset.loadFromFile(tilesetFile))
        return false;

    pugi::xml_document doc;
    if (!doc.load_file(tmxFile.c_str()))
        return false;

    auto mapNode = doc.child("map");
    mapWidth = mapNode.attribute("width").as_int();
    mapHeight = mapNode.attribute("height").as_int();
    tileWidth = mapNode.attribute("tilewidth").as_int();
    tileHeight = mapNode.attribute("tileheight").as_int();

    vertices.clear();
    vertices.setPrimitiveType(sf::Quads);

    auto layer = mapNode.child("layer");
    auto data = layer.child("data");
  
    std::string csv = data.text().as_string();
    std::stringstream ss(csv);

    tileData.clear();
    tileData.resize(mapHeight, std::vector<int>(mapWidth, 0));

    int i = 0;
    std::string value;
    while (std::getline(ss, value, ','))
    {
        int gid = std::stoi(value);

        int x = i % mapWidth;
        int y = i / mapWidth;
        ++i;

        if (gid == 0)
            continue;

        int localId = gid - firstGid;
        if (localId < 0)
            continue;

        int tu = localId % (tileset.getSize().x / tileWidth);
        int tv = localId / (tileset.getSize().x / tileWidth);

        sf::Vertex quad[4];

        quad[0].position = sf::Vector2f(x * tileWidth, y * tileHeight);
        quad[1].position = sf::Vector2f((x + 1) * tileWidth, y * tileHeight);
        quad[2].position = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
        quad[3].position = sf::Vector2f(x * tileWidth, (y + 1) * tileHeight);

        quad[0].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
        quad[3].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);

        vertices.append(quad[0]);
        vertices.append(quad[1]);
        vertices.append(quad[2]);
        vertices.append(quad[3]);

        tileData[y][x] = gid;
    }

    return true;
}

void TileMap::Draw(sf::RenderWindow& window)
{
  
    sf::RenderStates states;
    states.transform *= getTransform();
    states.texture = &tileset;
    window.draw(vertices, states);
}

bool TileMap::IsBlocked(sf::Vector2f& pos)
{
    int x = static_cast<int>(pos.x) / tileWidth;
    int y = static_cast<int>(pos.y) / tileHeight;

    if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
        return true; 

    return tileData[y][x] == 2;
}

int TileMap::IsSpawn(const sf::Vector2f& pos)
{
    int x = static_cast<int>(pos.x) / tileWidth;
    int y = static_cast<int>(pos.y) / tileHeight;

    if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
        return -1;

    return tileData[y][x];
}
