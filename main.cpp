#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include<windows.h>

using namespace sf;
using namespace std;

#define PI 3.14159265

const char* nameProject = "Project_2";

Font font;
Text text;
RenderWindow window(VideoMode(1920, 1080), nameProject, Style::Fullscreen);
Event event;
Mouse mouse;
Clock gameClock;

bool fullscreen = true;
bool pause;

struct point{
    float x;
    float y;
    float vx;
    float vy;
    float r;
};

vector<point> player;
point newPlayer;

float dist(float a, float b, float c, float d){
    return sqrt(pow((c-a), 2) + pow((d-b), 2));
}

int main(){
    window.setFramerateLimit(144);

    int res = 40;

    srand(time(NULL));

    Texture texture;
    if (!texture.loadFromFile("images/circle.png"))
        return 0;

    VertexArray circles(PrimitiveType::Triangles);

    VertexArray dot(PrimitiveType::Triangles);

    VertexArray lines(PrimitiveType::Lines);

    
    for(int i=0; i<((1920/res)*(1080/res)); i++){
        dot.append(Vector2f(0, 0));
        dot.append(Vector2f(0, 0));
        dot.append(Vector2f(0, 0));
        dot.append(Vector2f(0, 0));
        dot.append(Vector2f(0, 0));
        dot.append(Vector2f(0, 0));

        dot[i*6+0].texCoords = Vector2f(0, 0);
        dot[i*6+1].texCoords = Vector2f(1000, 0);
        dot[i*6+2].texCoords = Vector2f(1000, 1000);

        dot[i*6+3].texCoords = Vector2f(0, 0);
        dot[i*6+4].texCoords = Vector2f(0, 1000);
        dot[i*6+5].texCoords = Vector2f(1000, 1000);

        int n = rand()%2;
        
        dot[i*6+0].color = Color(n*255, n*255, n*255);
        dot[i*6+1].color = Color(n*255, n*255, n*255);
        dot[i*6+2].color = Color(n*255, n*255, n*255);
        dot[i*6+3].color = Color(n*255, n*255, n*255);
        dot[i*6+4].color = Color(n*255, n*255, n*255);
        dot[i*6+5].color = Color(n*255, n*255, n*255);
    }

    for(int i=0; i<5; i++){
        player.push_back(newPlayer);
        player[i].r = 100;
        //player[i].vx=rand()%200-100;
        //player[i].vy=rand()%200-100;
        player[i].x=rand()%(window.getSize().x-int(2*player[i].r))+player[i].r;
        player[i].y=rand()%(window.getSize().y-int(2*player[i].r))+player[i].r;
        
        circles.append(Vector2f(player[i].x-player[i].r, player[i].y-player[i].r));
        circles.append(Vector2f(player[i].x+player[i].r, player[i].y-player[i].r));
        circles.append(Vector2f(player[i].x+player[i].r, player[i].y+player[i].r));
        circles.append(Vector2f(player[i].x-player[i].r, player[i].y-player[i].r));
        circles.append(Vector2f(player[i].x-player[i].r, player[i].y+player[i].r));
        circles.append(Vector2f(player[i].x+player[i].r, player[i].y+player[i].r));
        
        circles[i*6+0].texCoords = Vector2f(0, 0);
        circles[i*6+1].texCoords = Vector2f(1000, 0);
        circles[i*6+2].texCoords = Vector2f(1000, 1000);

        circles[i*6+3].texCoords = Vector2f(0, 0);
        circles[i*6+4].texCoords = Vector2f(0, 1000);
        circles[i*6+5].texCoords = Vector2f(1000, 1000);
        
        circles[i*6+0].color = Color::Red;
        circles[i*6+1].color = Color::Red;
        //circles[i*6+2].color = Color::Red;
        circles[i*6+3].color = Color::Red;
        circles[i*6+4].color = Color::Red;
        //circles[i*6+5].color = Color::Red;
    }

    while(window.isOpen()){
        window.clear(Color(32, 32, 32, 255));

        float dt = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();

        while(window.pollEvent(event)){
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Enter) && (!fullscreen)) {
				fullscreen = true;
				window.create(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));
			}
            else if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape) && (fullscreen)) {
				fullscreen = false;
				window.create(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));
			}
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space) && (fullscreen)) {
                pause = !pause;
			}
            if(event.type == Event::Closed){
                window.close();
            }
        }

        for(int i=0; i<player.size(); i++){
            if(fullscreen && !pause){
                player[i].x+=player[i].vx*dt;
                player[i].y+=player[i].vy*dt;

                if(player[i].x < player[i].r){
                    player[i].x += 2*(player[i].r-player[i].x);
                    player[i].vx *= -1;
                }
                else if(player[i].x > window.getSize().x-player[i].r){
                    player[i].x += 2*(window.getSize().x-player[i].r-player[i].x);
                    player[i].vx *= -1;
                }
                if(player[i].y < player[i].r){
                    player[i].y += 2*(player[i].r-player[i].y);
                    player[i].vy *= -1;
                }
                else if(player[i].y > window.getSize().y-player[i].r){
                    player[i].y += 2*(window.getSize().y-player[i].r-player[i].y);
                    player[i].vy *= -1;
                }
            }

            if(fullscreen){
                circles[i*6+0].position = Vector2f(player[i].x-player[i].r, player[i].y-player[i].r);
                circles[i*6+1].position = Vector2f(player[i].x+player[i].r, player[i].y-player[i].r);
                circles[i*6+2].position = Vector2f(player[i].x+player[i].r, player[i].y+player[i].r);

                circles[i*6+3].position = Vector2f(player[i].x-player[i].r, player[i].y-player[i].r);
                circles[i*6+4].position = Vector2f(player[i].x-player[i].r, player[i].y+player[i].r);
                circles[i*6+5].position = Vector2f(player[i].x+player[i].r, player[i].y+player[i].r);
            }
        }

        for(int i=0; i<1920; i+=res){
            for(int j=0; j<1080; j+=res){
                dot[((j/res)*1920/res+(i/res))*6+0].position = Vector2f(i-5+res/2, j-5+res/2);
                dot[((j/res)*1920/res+(i/res))*6+1].position = Vector2f(i+5+res/2, j-5+res/2);
                dot[((j/res)*1920/res+(i/res))*6+2].position = Vector2f(i+5+res/2, j+5+res/2);

                dot[((j/res)*1920/res+(i/res))*6+3].position = Vector2f(i-5+res/2, j-5+res/2);
                dot[((j/res)*1920/res+(i/res))*6+4].position = Vector2f(i-5+res/2, j+5+res/2);
                dot[((j/res)*1920/res+(i/res))*6+5].position = Vector2f(i+5+res/2, j+5+res/2);
            }
        }
        
        //window.draw(circles, &texture);

        window.draw(lines);

        window.draw(dot, &texture);

        window.display();
    }

    return 0;
}