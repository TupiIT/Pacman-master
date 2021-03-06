#include "stdafx.h"

Pacman::Pacman() {
	direction = STAY;
	shape.setFillColor(sf::Color(255, 216, 0));
	shape.setRadius(15.f);
    speed = 0.15;
}

void Pacman::keyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = DOWN;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = LEFT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = RIGHT;
    }
}

void Pacman::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

void Pacman::move(Map& _map) {
    coinIntersects(_map);
    switch (direction) {
        case UP: {
            shape.move(0, -speed);
            coinIntersects(_map);
            if (checkWallIntersects(_map)) {
                direction = STAY;
                shape.move(0, speed);
            }
            break;
        }
        case DOWN: {
            shape.move(0, speed);
            coinIntersects(_map);
            if (checkWallIntersects(_map)){
                direction = STAY;
                shape.move(0, -speed);
            }
            break;
        }
        case LEFT: {
            shape.move(-speed, 0);
            coinIntersects(_map);
            if (checkWallIntersects(_map)) {
                direction = STAY;
                shape.move(speed, 0);
            }
            break;
        }
        case RIGHT: {
            shape.move(speed, 0);
            coinIntersects(_map);
            if (checkWallIntersects(_map)) {
                direction = STAY;
                shape.move(-speed, 0);
            }
            break;
        }
    }
}

bool Pacman::checkWallIntersects(Map& _map) const {
    for (size_t i = 0; i < size_map_y; i++) {
        for (size_t j = 0;  j < size_map_x;  j++) {
            if (shape.getGlobalBounds().intersects(_map.getPointer()[i][j].getShape().getGlobalBounds())) {
                if(_map.getPointer()[i][j].getCategory() == WALL) return true;
            }
        }
    }
    return false;
}

void Pacman::coinIntersects(Map& _map) {
    for (size_t i = 0; i < size_map_y; i++) {
        for (size_t j = 0; j < size_map_x; j++) {
            if (shape.getGlobalBounds().intersects(_map.getPointer()[i][j].getShape().getGlobalBounds())) {
                if (_map.getPointer()[i][j].getCategory() == COIN) {
                    _map.getPointer()[i][j].setCategory(CellCategory::EMPTY);
                    _map.getPointer()[i][j].setCell(j, i);
                    return;
                }
            }
        }
    }
}

void Pacman::setStartPosition(sf::Vector2f position) {
    shape.setPosition(position);
}

sf::FloatRect Pacman::getGlobalBounds() const {
    return shape.getGlobalBounds();
}
