#include "SFML/Graphics.hpp"
#include "headers/Box.hpp"
#include <vector>
#include <iostream>


void BFS(std::vector<std::vector<Box*> >, sf::RenderWindow&);

int main(int argc, char* argv[]){

    sf::RenderWindow window(sf::VideoMode(1280,720), "Path Finding");

    
    int count = 0;

    std::vector<std::vector<Box*> > boxes;
    for (int i = 0; i < 72; i++){
        std::vector<Box*> temp;
        boxes.push_back(temp);
    }

    for (int i = 0; i < 72; i++){
        for (int j = 0; j < 128; j++){
            Box* b = new Box(j*10,i*10);
            boxes.at(i).push_back(b);
        }
    }


    // hard code start and end point
    boxes[3][22]->body.setFillColor(sf::Color::Green);
    boxes[3][22]->type = 2;

    boxes[15][10]->body.setFillColor(sf::Color::Red);
    boxes[15][10]->type = 3;

    while (window.isOpen()){
        sf::Event event;
        sf::Vector2i mousePosition;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        
            if (event.type == sf::Event::MouseButtonReleased){
                mousePosition = sf::Mouse::getPosition(window);
                
                int x = NULL, y = NULL; // x and y cordinate on 2d array
                x = mousePosition.x / 10;
                y = mousePosition.y / 10;
                boxes[y][x]->body.setFillColor(sf::Color::Black);
                boxes[y][x]->type = 1;

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if (count == 0){
                    std::cout << "pathfind" << std::endl;
                    BFS(boxes, window);
                    count++;
                } 
            }

        }

        

        // draws state to screen
        window.clear(sf::Color::White);
        for (int i = 0; i < 72; i++){
            for (int j = 0; j < 128; j++){
                window.draw(boxes.at(i).at(j)->body);
            }
        }
        window.display();

    }
}

void BFS(std::vector<std::vector<Box*> > b, sf::RenderWindow& window){

    std::vector<Box*> visited;
    std::vector<Box*> queue;

    int yPos = 3;
    int xPos = 22;
    visited.push_back(b.at(yPos).at(xPos));
    visited.at(0)->xLocation = xPos;
    visited.at(0)->yLocation = yPos;
    visited.at(0)->visited = true;



    while (visited.at(visited.size()-1)->type != 3){

        xPos = visited.at(visited.size()-1)->xLocation;
        yPos = visited.at(visited.size()-1)->yLocation;

        // add adjacent vertices to queue
        // north
        if (yPos - 1 >= 0 && b.at(yPos-1).at(xPos)->visited == false && (b.at(yPos-1).at(xPos)->type == 0 || b.at(yPos-1).at(xPos)->type == 3)){
            queue.push_back(b.at(yPos-1).at(xPos));
            b.at(yPos-1).at(xPos)->xLocation = xPos;
            b.at(yPos-1).at(xPos)->yLocation = yPos-1;
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }
        // south
        if (yPos + 1 <= 71 && b.at(yPos+1).at(xPos)->visited == false && (b.at(yPos+1).at(xPos)->type == 0 || b.at(yPos+1).at(xPos)->type == 3)){
            queue.push_back(b.at(yPos+1).at(xPos));
            b.at(yPos+1).at(xPos)->xLocation = xPos;
            b.at(yPos+1).at(xPos)->yLocation = yPos+1;
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }
        // east
        if (xPos - 1 >= 0 && b.at(yPos).at(xPos-1)->visited == false && (b.at(yPos).at(xPos-1)->type == 0 || b.at(yPos).at(xPos-1)->type == 3)){
            queue.push_back(b.at(yPos).at(xPos-1));
            b.at(yPos).at(xPos-1)->xLocation = xPos-1;
            b.at(yPos).at(xPos-1)->yLocation = yPos;
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }
        // west
        if (xPos + 1 <= 127 && b.at(yPos).at(xPos+1)->visited == false && (b.at(yPos).at(xPos+1)->type == 0 || b.at(yPos).at(xPos+1)->type == 3)){
            queue.push_back(b.at(yPos).at(xPos+1));
            b.at(yPos).at(xPos+1)->xLocation = xPos+1;
            b.at(yPos).at(xPos+1)->yLocation = yPos;
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }


        // check queue is not empty
        // add first item in queue to visited
        if (queue.size() >= 0){
            visited.push_back(queue.at(0));
            // remove first item in queue
            queue.erase(queue.begin());
        }

        visited.at(visited.size()-1)->body.setFillColor(sf::Color::Blue);

        // redraw display
        window.clear(sf::Color::White);
        for (int i = 0; i < 72; i++){
            for (int j = 0; j < 128; j++){
                window.draw(b.at(i).at(j)->body);
            }
        }
        window.display();

    }

}