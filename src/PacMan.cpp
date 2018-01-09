#include "../include/PacMan.hpp"
#include "../include/MenuScene.hpp"

PacMan::PacMan(sf::Color color, Transform transform) : MovableObject(transform), color(color)
{
    physical = true;
    boosted = 0;
    layer = 1;
    tag = "PacMan";
    idString = "PacMan";
    shape = sf::RectangleShape(sf::Vector2f(transform.rect.width, transform.rect.height));
    shape.setFillColor(color);
    ignoredMoveCollisions.insert(tag);
    ignoredMoveCollisions.insert("Dot");
    ignoredMoveCollisions.insert("Fruit");
    ignoredMoveCollisions.insert("Boost");
    ignoredMoveCollisions.insert("Ghost");
}

PacMan::PacMan(Transform transform) : PacMan(sf::Color::Green, transform)
{
}

void PacMan::init()
{
    MovableObject::init();
}

void PacMan::start()
{
    MovableObject::start();
}

void PacMan::update()
{
    for (auto event : scene->events)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            changeDir(event.key.code);
        }
    }

    move();
}

void PacMan::render()
{
    shape.setPosition(transform.rect.left, transform.rect.top);
    scene->draw(shape);
}

void PacMan::onCollision(GameObject *other)
{
    if (!boosted && other->tag == "Ghost")
    {
        scene->passMessage("LifesText", "LoseLife");
        scene->removeGameObject(this);
        scene->passMessage(idString + "Spawn", "Respawn");
        scene->passMessages("Ghost", "PacManCaught");
        return;
    }

    if (other->tag == "Dot")
    {
        scene->passMessage("ScoreText", "AddPoint");
        return;
    }

    if (other->tag == "Boost")
    {
        scene->passMessages("Ghost", "PacManBoosted");
        ++boosted;
        return;
    }
}

void PacMan::parseMessage(std::string message)
{
    if (message == "BoostVanished")
    {
        --boosted;
        std::cout << "Boosts: " << boosted << '\n';
    }
}