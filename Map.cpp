#include "Map.h"

#define BLOCK_SIZE 18.f
#define size_map_y 22
#define size_map_x 26

Cell::Cell() {
	shape.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
}

sf::RectangleShape Cell::getShape()
{
	return shape;
}

void Cell::setCell(CellCategory _category, int x, int y) {
	category = _category;
	if (category == WALL) {
		shape.setFillColor(sf::Color(52, 93, 199));
	}
	if (category == COIN) {
		shape.setFillColor(sf::Color(255, 255, 255));
	}
	if (category == EMPTY) {
		shape.setFillColor(sf::Color(40, 40, 40));
	}
	shape.setPosition(x * BLOCK_SIZE, y *BLOCK_SIZE);
	
}

Map::Map() {
	cells = new Cell * [size_map_y];
	for (size_t i = 0; i < size_map_y; i++) {
		cells[i] = new Cell[size_map_x];
	}
}

Map::~Map() {
	for (size_t i = 0; i < size_map_y; i++) {
		delete[] cells[i];
	}
	delete[] cells;
}

void Map::setMap()
{
	char map[size_map_y][size_map_x]{
	"|-----------------------|",//0
	"|'''''''''''|'''''''''''|",//1
	"|'|||'|||||'|'|||||'|||'|",//2
	"|'|||'|||||'|'|||||'|||'|",//3
	"|'''''''''''''''''''''''|",//4
	"|'|||'|'---------'|'|||'|",//5
	"|'''''|'''''|'''''|'''''|",//6
	"|----'|---  |  ---|'-----",//7
	"    |'|           |'|   ",//8
	"-----'|  |-----|  |'-----",//9
	"     '   |     |   '     ",//10
	"-----'|  -------  |'-----",//11
	"    |'|           |'|    ",//12
	"-----'|  -------  |'-----",//13
	"|'''''''''''|'''''''''''|",//14
	"|'--|'-----'|'-----'---'|",//15
	"|'''|'''''''''''''''|'''|",//16
	"|--'|'|''-------''|'|'--|",//17
	"|'''''|'''''|'''''|'''''|",//18
	"|'--------''|''--------'|",//19
	"|'''''''''''''''''''''' |",//20
	"|-----------------------|",//21
	};
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			CellCategory _category;
			if (map[i][j] == '|' or map[i][j] == '-') {
				_category = WALL;
			}
			if (map[i][j] == '\'') {
				_category = COIN;
			}
			if (map[i][j] == ' ') {
				_category = EMPTY;
			}
			cells[i][j].setCell(_category, j, i);
		}
	}
}

void Map::draw(sf::RenderWindow& window) {
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			window.draw(cells[i][j].getShape());
		}
	}
}