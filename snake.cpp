#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <iostream>

using namespace std;

int randomGen(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

list<sf::Vector2f> initialSnake()
{
    sf::Vector2f part1(640, 360);
    sf::Vector2f part2(680, 360);
    sf::Vector2f part3(720, 360);

    list<sf::Vector2f> snake = {part1, part2, part3};

    return snake;
}

list<sf::Vector2f> fillFruits(list<sf::Vector2f> fruits, int width, int height, int fruitLimit)
{
    while (fruits.size() < fruitLimit)
    {
        int xPos = 1;
        while (xPos % 40 != 0)
        {
            xPos = randomGen(0, width - 40);
        }
        int yPos = 1;
        while (yPos % 40 != 0)
        {
            yPos = randomGen(0, height - 40);
        }
        sf::Vector2f position(xPos, yPos);
        fruits.push_front(position);
    }

    return fruits;
}

bool spriteOverlap(sf::Vector2f fruitPosition, sf::Vector2f snakePosition)
{
    if (fruitPosition.x == snakePosition.x)
    {
        if (fruitPosition.y == snakePosition.y)
        {
            return true;
        }
    }
    return false;
}

list<sf::Vector2f> fruitCollision(list<sf::Vector2f> snake, list<sf::Vector2f> fruits)
{
    list<sf::Vector2f>::iterator fruitItr;
    for (fruitItr = fruits.begin(); fruitItr != fruits.end(); fruitItr++)
    {

        sf::Vector2f fruitPosition = *fruitItr;
        
        
        if (spriteOverlap(fruitPosition, snake.front()))
        {
            cout << fruitPosition.x;
            fruits.erase(fruitItr);
            break;
        }
        

    }
    return fruits;
}

bool snakeCollision(list<sf::Vector2f> snake)
{
    list<sf::Vector2f>::iterator snakeItr;
    snakeItr = snake.begin();
    snakeItr++;
    for (snakeItr; snakeItr != snake.end() ; snakeItr++)
    {
        
        sf::Vector2f position(*snakeItr);
        if (spriteOverlap(*snakeItr, snake.front()))
        {
            return true;
        }
    }
    return false;
}

list<sf::Vector2f> updateSnake(list<sf::Vector2f> snake, sf::String direction)
{
    snake.pop_back();
    sf::Vector2f head(snake.front());

    if (direction == "left")
    {
        head.x -= 40;
    }
    else if (direction == "right")
    {
        head.x += 40;
    }
    else if (direction == "up")
    {
        head.y -= 40;
    }
    else if (direction == "down")
    {
        head.y += 40;
    }

    snake.push_front(head);

    return snake;
}

list<sf::Vector2f> addSegment(list<sf::Vector2f> snake)
{
    sf::Vector2f newSegment = snake.back();
    sf::Vector2f lastSegment = snake.back();
    list<sf::Vector2f>::iterator itr;
    itr = snake.end();
    itr--;
    sf::Vector2f penSegment = *itr;
    if(penSegment.x == lastSegment.x){
        if(penSegment.y - lastSegment.y < 0){
            newSegment.y += 40;
        }
        else{
            newSegment.y -= 40;
        }
    }
    else if (penSegment.y == lastSegment.y){
        if(penSegment.x - lastSegment.x < 0 ){
            newSegment.x +=40;
        }
        else{
            newSegment.x -= 40;
        }
    }
    snake.push_back(newSegment);
    return snake;
}

int main()
{
    int width = 1280;
    int height = 720;
    sf::String direction = "left";
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
    window.setFramerateLimit(15);

    int fruitLimit = 3;

    list<sf::Vector2f> snake = initialSnake();
    list<sf::Vector2f> fruits;

    fruits = fillFruits(fruits, width, height, fruitLimit);

    while (window.isOpen())
    {
        window.clear();

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & direction != "right")
        {
            direction = "left";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & direction != "left")
        {
            direction = "right";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) & direction != "down")
        {
            direction = "up";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & direction != "up")
        {
            direction = "down";
        }

        snake = updateSnake(snake, direction);

        if(snakeCollision(snake)){
            window.close();
        }

        fruits = fruitCollision(snake, fruits);
        

        if (fruits.size() < fruitLimit)
        {
            snake = addSegment(snake);
            fruits = fillFruits(fruits, width, height, fruitLimit);
        }

        for (sf::Vector2f position : snake)
        {
            sf::Vector2f sectionSize(40, 40);
            sf::RectangleShape snakeSection(sectionSize);
            snakeSection.setFillColor(sf::Color(100, 250, 50));

            snakeSection.setPosition(position);

            window.draw(snakeSection);
        }

        for (sf::Vector2f position : fruits)
        {
            sf::Vector2f fruitSize(40, 40);
            sf::RectangleShape fruitSection(fruitSize);
            fruitSection.setFillColor(sf::Color(250, 0, 0));

            fruitSection.setPosition(position);

            window.draw(fruitSection);
        }

        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}