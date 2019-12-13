#include "Map.h"
using namespace PB::Windows;

Map::Map(sprite* sprite, const Json::Value& json) : _sprite(sprite), _row(0), _col(0), _tileWidth(0), _tileHeight(0), _mapTiles(NULL)
{
    this->parse(json);
}

Map::~Map()
{
    this->clear();
}

void Map::parse(const Json::Value & json)
{
    this->clear();

    this->_bgm              = json["bgm"].asString();
    this->_row              = json["row"].asInt();
    this->_col              = json["col"].asInt();
    this->_tileWidth        = json["tile width"].asInt();
    this->_tileHeight       = json["tile height"].asInt();

    this->_mapTiles         = new std::string**[this->_col];
    for(int row = 0; row < this->_row; row++)
        this->_mapTiles[row]    = new std::string*[this->_col];

    Json::Value             data    = json["data"];
    for(Json::ValueIterator i1 = data.begin(); i1 != data.end(); i1++)
    {
        Json::Value         rowmap  = (*i1);
        for(Json::ValueIterator i2 = rowmap.begin(); i2 != rowmap.end(); i2++)
        {
            Json::Value     tile    = (*i2);
            if(tile.isNull())
            {
                this->_mapTiles[i1.index()][i2.index()]     = NULL;
            }
            else
            {
                auto name = new std::string(std::to_string(tile.asInt()));
                this->_mapTiles[i1.index()][i2.index()]     = name;
            }
        }
    }
}

void Map::clear()
{
    if(this->_mapTiles == NULL)
        return;

    for (int row = 0; row < this->_row; row++)
    {
        for (int col = 0; col < this->_col; col++)
        {
            if(this->_mapTiles[row][col] != NULL)
                delete this->_mapTiles[row][col];
        }
        delete[] this->_mapTiles[row];
    }

    delete[] this->_mapTiles;
    
    this->_mapTiles         = NULL;
}

const std::string& Map::bgm() const
{
    return this->_bgm;
}

void Map::onFrameMove(float elapsedTime)
{
}

void Map::onFrameRender(dcontextable & dc, float elapsedTime)
{
    if(this->_mapTiles == NULL)
        return;

    for(int row = this->_row - 1; row >= 0; row--)
    {
        for(int col = 0; col < this->_col; col++)
        {
            std::string*            name = this->_mapTiles[row][col];
            if(name == NULL)
                continue;

            image*                  img = this->_sprite->get(*name);
            if(img == NULL)
                return;

            rect                    area(col * this->_tileWidth, row * this->_tileHeight, img->width(), img->height());
            area.move(0, this->_tileHeight - img->height());

            dc.draw(img, area);
        }
    }
}
