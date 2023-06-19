#include "SFML/Graphics.hpp"
#include "headers/Box.hpp"
#include <vector>
#include <stack>
#include <iostream>


void BFS(std::vector<std::vector<Box*> >, sf::RenderWindow&, int, int);
void DFS(std::vector<std::vector<Box*> >, sf::RenderWindow&, int, int);
void dijkstra(std::vector<std::vector<Box*> > b, sf::RenderWindow& window, int startX, int startY);


int main(int argc, char* argv[]){

    sf::RenderWindow window(sf::VideoMode(1280,720), "Path Finding");

    
    int count = 0;
    int startX;
    int startY;

    int endX;
    int endY;

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


    while (window.isOpen()){
        sf::Event event;
        sf::Vector2i mousePosition;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
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
                    // UNCOMMENT ONE TO RUN IT
                    BFS(boxes, window, startX, startY);
                    //DFS(boxes, window, startX, startY);
                    dijkstra(boxes,window,startX, startY);
                    count++;
                } 
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                mousePosition = sf::Mouse::getPosition(window);
                int x = NULL, y = NULL; 
                startX = mousePosition.x / 10;
                startY = mousePosition.y / 10;
                boxes[startY][startX]->body.setFillColor(sf::Color::Green);
                boxes[startY][startX]->type = 2;
                
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                mousePosition = sf::Mouse::getPosition(window);
                int x = NULL, y = NULL; 
                endX = mousePosition.x / 10;
                endY = mousePosition.y / 10;
                boxes[endY][endX]->body.setFillColor(sf::Color::Red);
                boxes[endY][endX]->type = 3;
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

void dijkstra(std::vector<std::vector<Box*> > b, sf::RenderWindow& window, int startX, int startY){
    int step = 0;

    


}
void DFS(std::vector<std::vector<Box*> > b, sf::RenderWindow& window, int startX, int startY){
    std::cout << "DFS" << std::endl;
    int xPos = startX;
    int yPos = startY;

    std::vector<Box*> visited;
    std::stack<Box*> stack; 

    visited.push_back(b.at(yPos).at(xPos));



    while(visited.at(visited.size()-1)->type != 3){
        if (stack.size() > 0){
            xPos = stack.top()->xLocation;
            yPos = stack.top()->yLocation;
            visited.push_back(b.at(yPos).at(xPos));
            visited.at(visited.size()-1)->body.setFillColor(sf::Color::Blue);
            stack.pop();

        }


        if (yPos - 1 >= 1 && b.at(yPos-1).at(xPos)->visited == false ){
            stack.push(b.at(yPos-1).at(xPos));
            b.at(yPos-1).at(xPos)->body.setFillColor(sf::Color::Magenta);
            b.at(yPos-1).at(xPos)->visited = true;
            b.at(yPos-1).at(xPos)->xLocation = xPos;
            b.at(yPos-1).at(xPos)->yLocation = yPos-1;
            continue;
        }

        if (yPos + 1 <= 71 && b.at(yPos+1).at(xPos)->visited == false){
            stack.push(b.at(yPos+1).at(xPos));
            b.at(yPos+1).at(xPos)->body.setFillColor(sf::Color::Magenta);
            b.at(yPos+1).at(xPos)->visited = true;
            b.at(yPos+1).at(xPos)->xLocation = xPos;
            b.at(yPos+1).at(xPos)->yLocation = yPos+1;
            continue;
        }

        if (xPos - 1 >= 0 && b.at(yPos).at(xPos-1)->visited == false){
            stack.push(b.at(yPos).at(xPos-1));
            b.at(yPos).at(xPos-1)->body.setFillColor(sf::Color::Magenta);
            b.at(yPos).at(xPos-1)->visited = true;
            b.at(yPos).at(xPos-1)->xLocation = xPos-1;
            b.at(yPos).at(xPos-1)->yLocation = yPos;
            continue;
        }

        if (xPos + 1 <= 127 && b.at(yPos).at(xPos+1)->visited == false){
            stack.push(b.at(yPos).at(xPos+1));
            b.at(yPos).at(xPos+1)->body.setFillColor(sf::Color::Magenta);
            b.at(yPos).at(xPos+1)->visited = true;
            b.at(yPos).at(xPos+1)->xLocation = xPos+1;
            b.at(yPos).at(xPos+1)->yLocation = yPos;
            continue;
        }

        

        window.clear(sf::Color::White);
        for (int i = 0; i < 72; i++){
            for (int j = 0; j < 128; j++){
                window.draw(b.at(i).at(j)->body);
            }
        }
        window.display();

    }

}
void BFS(std::vector<std::vector<Box*> > b, sf::RenderWindow& window, int startX, int startY){

    std::vector<Box*> visited;
    std::vector<Box*> queue;

    int yPos = startY;
    int xPos = startX;
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
            b.at(yPos-1).at(xPos)->prev = b.at(yPos).at(xPos);
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }
        // south
        if (yPos + 1 <= 71 && b.at(yPos+1).at(xPos)->visited == false && (b.at(yPos+1).at(xPos)->type == 0 || b.at(yPos+1).at(xPos)->type == 3)){
            queue.push_back(b.at(yPos+1).at(xPos));
            b.at(yPos+1).at(xPos)->xLocation = xPos;
            b.at(yPos+1).at(xPos)->yLocation = yPos+1;
            b.at(yPos+1).at(xPos)->prev = b.at(yPos).at(xPos);
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }
        // east
        if (xPos - 1 >= 0 && b.at(yPos).at(xPos-1)->visited == false && (b.at(yPos).at(xPos-1)->type == 0 || b.at(yPos).at(xPos-1)->type == 3)){
            queue.push_back(b.at(yPos).at(xPos-1));
            b.at(yPos).at(xPos-1)->xLocation = xPos-1;
            b.at(yPos).at(xPos-1)->yLocation = yPos;
            b.at(yPos).at(xPos-1)->prev = b.at(yPos).at(xPos);
            queue.at(queue.size()-1)->body.setFillColor(sf::Color::Magenta);
            queue.at(queue.size()-1)->visited = true;
        }
        // west
        if (xPos + 1 <= 127 && b.at(yPos).at(xPos+1)->visited == false && (b.at(yPos).at(xPos+1)->type == 0 || b.at(yPos).at(xPos+1)->type == 3)){
            queue.push_back(b.at(yPos).at(xPos+1));
            b.at(yPos).at(xPos+1)->xLocation = xPos+1;
            b.at(yPos).at(xPos+1)->yLocation = yPos;
            b.at(yPos).at(xPos+1)->prev = b.at(yPos).at(xPos);
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

    Box* temp = visited.at(visited.size()-1);
    while (temp->prev != NULL){
        temp->body.setFillColor(sf::Color::Yellow);
        temp = temp->prev;
    }

}