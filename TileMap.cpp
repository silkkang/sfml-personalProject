//#include "stdafx.h"
//#include "TileMap.h"
//
//TileMap::TileMap(const std::string& name)
//	: GameObject(name)
//{
//}
//
//void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
//{
//	cellCount = count;
//	cellSize = size;
//
//	va.clear();
//	va.setPrimitiveType(sf::Quads);
//	va.resize(count.x * count.y * 4);
//
//	sf::Vector2f posOffset[4] =
//	{
//		{ 0.f, 0.f },
//		{ size.x, 0.f },
//		{ size.x, size.y },
//		{ 0.f, size.y },
//	};
//
//	sf::Vector2f texCoords[4] =
//	{
//		{ 0.f, 0.f },
//		{ 50.f, 0.f },
//		{ 50.f, 50.f },
//		{ 0.f, 50.f },
//	};
//
//	for (int i = 0; i < count.y; ++i)
//	{
//		for (int j = 0; j < count.x; ++j)
//		{
//			int texIndex = 0;
//			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
//			{
//				texIndex = 3;
//			}
//			else if (i == 25 && j == 25|| i == 25 && j == 50|| i == 25 && j == 75
//				|| i == 50 && j == 25 || i == 50 && j == 50 || i == 50 && j == 75
//				|| i == 75 && j == 25 || i == 75 && j == 50 || i == 75 && j == 75)
//			{
//				texIndex = 1;
//			}
//			else 
//			{
//				texIndex = Utils::RandomRange(0, 2);
//				if (texIndex == 1)
//					texIndex = 0;
//			}
//
//			int quadIndex = i * count.x + j;
//			sf::Vector2f quadPos(j * size.x, i * size.y);
//
//			for (int k = 0; k < 4; ++k)
//			{
//				int vertexIndex = quadIndex * 4 + k;
//				va[vertexIndex].position = quadPos + posOffset[k];
//				va[vertexIndex].texCoords = texCoords[k];
//				va[vertexIndex].texCoords.y += texIndex * 50.f;
//			}
//		}
//	}
//}
//
//void TileMap::UpdateTransform()
//{
//	transform = sf::Transform::Identity;
//	transform.translate(position);
//	transform.rotate(rotation);
//	transform.scale(scale);
//	transform.translate(-origin);
//}
//
//void TileMap::SetPosition(const sf::Vector2f& pos)
//{
//	GameObject::SetPosition(pos);
//	UpdateTransform();
//}
//
//void TileMap::SetRotation(float rot)
//{
//	GameObject::SetRotation(rot);
//	UpdateTransform();
//}
//
//void TileMap::SetScale(const sf::Vector2f& s)
//{
//	GameObject::SetScale(s);
//	UpdateTransform();
//}
//
//void TileMap::SetOrigin(const sf::Vector2f& o)
//{
//	GameObject::SetOrigin(o);
//	UpdateTransform();
//}
//
//void TileMap::SetOrigin(Origins preset)
//{
//	GameObject::SetOrigin(preset);
//	if (preset != Origins::Custom)
//	{
//		sf::FloatRect rect;
//		rect.width = cellCount.x * cellSize.x;
//		rect.height = cellCount.y * cellSize.y;
//
//		origin.x = rect.width * ((int)preset % 3) * 0.5f;
//		origin.y = rect.height * ((int)preset / 3) * 0.5f;
//	}
//	UpdateTransform();
//}
//
//void TileMap::Init()
//{
//	sortingLayer = SortingLayers::Background;
//	sortingOrder = 0;
//
//	Set({ 100, 100 }, {50.f, 50.f});
//}
//
//void TileMap::Release()
//{
//}
//
//void TileMap::Reset()
//{
//	texture = &TEXTURE_MGR.Get(spriteSheetId);
//
//	SetOrigin(Origins::MC);
//	SetScale({ 1.f, 1.f });
//	SetPosition({ 0.f, 0.f });
//}
//
//void TileMap::Update(float dt)
//{
//}
//
//void TileMap::Draw(sf::RenderWindow& window)
//{
//	sf::RenderStates state;
//	state.texture = texture;
//	state.transform = transform;
//	window.draw(va, state);
//}
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

    int i = 0;
    for (auto tile = data.child("tile"); tile; tile = tile.next_sibling("tile"))
    {
        int gid = tile.attribute("gid").as_int();

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
    }

    std::cout << "TileMap Loaded, Vertex Count = " << vertices.getVertexCount() << std::endl;
 
    return true;
}

void TileMap::Draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.transform *= getTransform();
    states.texture = &tileset;
    window.draw(vertices, states);
}

