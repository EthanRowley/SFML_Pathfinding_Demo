 #include "headers/Box.hpp"


 Box::Box(int x, int y){
    this->body.setSize(sf::Vector2f(10.f, 10.f));
    this->body.setPosition(sf::Vector2f(x, y));
    this->body.setOutlineColor(sf::Color::Black);
    this->body.setOutlineThickness(1.f);
        
    this->value = NULL; // holds its location in the vector
    this->type = 0; // 1 = barrier, 2 = start, 3 = end, 0 = empty
    this->xLocation = NULL;
    this->yLocation = NULL;
    this->visited = false;
    this->prev = NULL;
    
 }