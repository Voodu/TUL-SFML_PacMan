#include "../include/Ghost.hpp"

Ghost::Ghost(sf::Color color, Transform transform) : MovableObject(transform), color(color)
{
    layer = 2;
    physical = true;
    tag = "Ghost";
    shape = sf::RectangleShape(sf::Vector2f(transform.rect.width, transform.rect.height));
    shape.setFillColor(color);
    ignoredMoveCollisions.insert(tag);
    ignoredMoveCollisions.insert("Door");
    ignoredMoveCollisions.insert("Dot");
    ignoredMoveCollisions.insert("Boost");
    ignoredMoveCollisions.insert("Fruit");
    ignoredMoveCollisions.insert("PacMan");
}

void Ghost::init()
{
    MovableObject::init();
}

void Ghost::start()
{
    // std::cout << "Starting Ghost\n";
    MovableObject::start();
    // std::cout << "Started Ghost\n";
}

void Ghost::update()
{
    if (!moves || nextDir == sf::Vector2f(0, 0))
    {
        changeDir(getNextTurn());
    }

    move();
}

void Ghost::render()
{
    shape.setPosition(transform.rect.left, transform.rect.top);
    scene->draw(shape);
}

void Ghost::onCollision(GameObject *other)
{
    if (other->tag == "PacMan" && static_cast<PacMan *>(other)->boosted)
    {
        scene->removeGameObject(this);
        scene->passMessage(idString + "Spawn", "Respawn");
    }
}

void Ghost::parseMessage(std::string message)
{
    if (message == "PacManCaught")
    {
        scene->removeGameObject(this);
        scene->passMessage(idString + "Spawn", "Respawn");
    }
}