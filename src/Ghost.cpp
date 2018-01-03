#include "../include/Ghost.hpp"

Ghost::Ghost(sf::Color color, Transform transform) : MovableObject(), color(color)
{
    layer = 2;
    physical = true;
    this->transform = transform;
    tag = "Ghost";
    shape = sf::RectangleShape(sf::Vector2f(transform.rect.width, transform.rect.height));
    shape.setFillColor(color);
    ignoredMoveCollisions.insert(tag);
    ignoredMoveCollisions.insert("Door");
    ignoredMoveCollisions.insert("Dot");
}

void Ghost::init()
{
    MovableObject::init();
}

void Ghost::update()
{
}

void Ghost::render()
{
    shape.setPosition(transform.rect.left, transform.rect.top);
    scene->draw(shape);
}

void Ghost::onCollision(GameObject *other)
{
}

void Ghost::parseMessage(std::string message)
{
}