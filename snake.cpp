// Include librarys used in the code
// These were all written by there respective owners and not me
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <iostream>

using namespace std;

/*
    A function making use of the random library. Upon recieving a
    minimum and maximum value it will generate a random number between
    them.
*/
int randomGen(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

/*
    A function to set the initial snake. Defines 3 segments of the snake
    then return the list that makes up the snake.
*/
list<sf::Vector2f> initialSnake()
{
    sf::Vector2f part1(640, 360);
    sf::Vector2f part2(680, 360);
    sf::Vector2f part3(720, 360);

    list<sf::Vector2f> snake = {part1, part2, part3};

    return snake;
}

/*
    A function to ensure that there is enough fruit to reach the fruit limit
    this makes sure that the list of vector2 passed in has enough fruits.
    It makes use of my randomGen() function in order to randomly create them.
*/
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

/*
    Checks is any 2 vector2 passed into the function are overlapping. In this game
    I can just compare if they have the same postion of the bottom left vertex
    as the game is grid based.
*/
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

/*
    Adds a new segment to the snake it compares the position of the previous 2
    segments to decide which way to add the snake segment.
*/
list<sf::Vector2f> addSegment(list<sf::Vector2f> snake)
{
    sf::Vector2f newSegment = snake.back();
    sf::Vector2f lastSegment = snake.back();
    list<sf::Vector2f>::iterator itr;
    itr = snake.end();
    itr--;
    sf::Vector2f penSegment = *itr;
    if (penSegment.x == lastSegment.x)
    {
        if (penSegment.y - lastSegment.y < 0)
        {
            newSegment.y += 40;
        }
        else
        {
            newSegment.y -= 40;
        }
    }
    else if (penSegment.y == lastSegment.y)
    {
        if (penSegment.x - lastSegment.x < 0)
        {
            newSegment.x += 40;
        }
        else
        {
            newSegment.x -= 40;
        }
    }
    snake.push_back(newSegment);
    return snake;
}

/*
    Loops through all the created fruit then checks if they overlap with the head
    of the snake using the spriteOverlap() function. Then if it is removes a fruit
    and increases the length of the snake.
*/
void fruitCollision(list<sf::Vector2f> &snake, list<sf::Vector2f> &fruits)
{
    list<sf::Vector2f>::iterator fruitItr;
    for (fruitItr = fruits.begin(); fruitItr != fruits.end(); fruitItr++)
    {

        sf::Vector2f fruitPosition = *fruitItr;

        if (spriteOverlap(fruitPosition, snake.front()))
        {
            fruits.erase(fruitItr);
            snake = addSegment(snake);
            break;
        }
    }
}

bool snakeCollision(list<sf::Vector2f> snake, int width, int height)
{
    list<sf::Vector2f>::iterator snakeItr;
    snakeItr = snake.begin();
    snakeItr++;
    for (snakeItr; snakeItr != snake.end(); snakeItr++)
    {

        sf::Vector2f position(*snakeItr);
        if (spriteOverlap(*snakeItr, snake.front()))
        {
            return true;
        }
    }
    

    if (snake.front().x < 0 | snake.front().x >= width)
    {
        cout<<"test";
        return true;
    }
    else if(snake.front().y > 0 | snake.front().y <= height){
        
        return true;
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

string getInput(sf::String direction)
{
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
    return direction;
}

void drawSnake(list<sf::Vector2f> snake, sf::RenderWindow &window)
{
    for (sf::Vector2f position : snake)
    {
        sf::Vector2f sectionSize(40, 40);
        sf::RectangleShape snakeSection(sectionSize);
        snakeSection.setFillColor(sf::Color(100, 250, 50));

        snakeSection.setPosition(position);

        window.draw(snakeSection);
    }
}

void drawFruit(list<sf::Vector2f> fruits, sf::RenderWindow &window)
{
    for (sf::Vector2f position : fruits)
    {
        sf::Vector2f fruitSize(40, 40);
        sf::RectangleShape fruitSection(fruitSize);
        fruitSection.setFillColor(sf::Color(250, 0, 0));

        fruitSection.setPosition(position);

        window.draw(fruitSection);
    }
}

void closeWindow(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void mainGame(sf::RenderWindow &window, sf::String &direction, list<sf::Vector2f> &snake, list<sf::Vector2f> &fruits, int fruitLimit)
{
    int width = window.getSize().x;
    int height = window.getSize().y;
    direction = getInput(direction);

    snake = updateSnake(snake, direction);

    if (snakeCollision(snake, width, height))
    {
        window.close();
    }

    fruitCollision(snake, fruits);
    fruits = fillFruits(fruits, width, height, fruitLimit);

    drawSnake(snake, window);
    drawFruit(fruits, window);

    closeWindow(window);
}

bool menuRender(sf::RenderWindow &window)
{
    bool endLoop = false;

    window.clear(sf::Color::Blue);

    sf::Font font;
    font.loadFromFile("../ArialFont/arial.ttf");

    sf::Vector2f titlePosition(440, 60);
    sf::Text title;
    title.setFont(font);
    title.setString("Snake");
    title.setCharacterSize(72);
    title.setFillColor(sf::Color::Red);
    title.setPosition(titlePosition);

    sf::Vector2f buttonTextPosition(515, 217);
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Play");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Red);
    buttonText.setPosition(buttonTextPosition);

    sf::Vector2f groundSize(window.getSize().x, 200);
    sf::Vector2f groundPosition(0, window.getSize().y - 200);
    sf::RectangleShape ground(groundSize);
    ground.setFillColor(sf::Color(0, 250, 0));
    ground.setPosition(groundPosition);

    sf::Vector2f buttonSize(200, 50);
    sf::Vector2f buttonPosition(440, 210);
    sf::RectangleShape button(buttonSize);
    button.setFillColor(sf::Color(0, 0, 0));
    button.setPosition(buttonPosition);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if((mousePos.x > buttonPosition.x) & (mousePos.x < (buttonPosition.x + buttonSize .x))){
            if((mousePos.y > buttonPosition.y) & (mousePos.y < (buttonPosition.y + buttonSize.y))){
                endLoop = true;
                return endLoop;
            }
        }
    }

    window.draw(button);
    window.draw(buttonText);
    window.draw(ground);
    window.draw(title);

    closeWindow(window);

    return endLoop;
}

int main()
{
    int width = 1080;
    int height = 720;
    sf::String direction = "left";
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
    window.setFramerateLimit(15);

    int fruitLimit = 10;

    list<sf::Vector2f> snake = initialSnake();
    list<sf::Vector2f> fruits;

    fruits = fillFruits(fruits, width, height, fruitLimit);

    bool menu = true;

    while (window.isOpen())
    {
        window.clear();
        if (menu)
        {
            if(menuRender(window)){
                menu = false;
            }
        }
        else
        {
            mainGame(window, direction, snake, fruits, fruitLimit);
        }

        window.display();
    }
}
