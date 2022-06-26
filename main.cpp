#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/System/Vector2.hpp>
#include "vector_utils.h"

sf::Vector2f movecalc(float velocity, float angle) {
    auto y = velocity * sin(angle);
    auto x = velocity * sin((M_PI / 2) - angle);
    return sf::Vector2f(x, y);
}

sf::Vector2f predict_collision(sf::Vector2f source, sf::Vector2f target, float vs, float vt, float at) {
    sf::Vector2f off = target-source;

    auto r = movecalc(vt, at);
    auto j = 2*off.x*r.x*off.y*r.y+pow(vs, 2)*pow(off.x, 2)+pow(vs, 2)*pow(off.y, 2)-pow(r.x, 2)*pow(off.y, 2)-pow(r.y,2)*pow(off.x, 2);
    if (j < 0)
        j = 0;
    auto n = sqrt(j);
    auto res = (off.x*r.x+off.y*r.y+n)/pow(vs, 2)-pow(r.x, 2)-pow(r.y, 2);
    return sf::Vector2f(r.x*res+target.x, r.y*res+target.y);
}

class Obj {
public:
    sf::RenderWindow* window;
    std::string tag;
    virtual void update() {
    }
    virtual std::string get_tag() {
        return this->tag;
    }
};

sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "movement prediction");
auto objects = std::vector<Obj*>();

Obj* get_object(std::string name) {
    for (auto o: objects) {
        std::cout << o->get_tag() << std::endl;
        if(o->get_tag() == name) {
            return o;
        }
    }
    return nullptr;
}

std::vector<Obj*> get_objects(std::string name) {
    std::vector<Obj*> objs;

    for (auto o: objects) {
        if (o->get_tag() == name)
            objs.push_back(o);
    }
    return objs;
}

class Player: public Obj {
public:
    sf::CircleShape shape = sf::CircleShape(50);
    std::string tag = "player";
    sf::Vector2f pos;
    float angle;
    float velocity;
    sf::RenderWindow* window;
    void calculate() {
        pos.x += velocity * sin((PI / 2) - angle);
        pos.y += velocity * sin(angle);
    }
    Player(sf::RenderWindow* window) {
        this->window = window;
        this->shape.setFillColor(sf::Color::Blue);
    }

    std::string get_tag() {
        return tag;
    }

        void update() {
            auto m = mouse2screen(window);
            auto v = m-pos;
            if (v.x < 0) {
                angle = -asin(v.y/mag(v))+PI;
        }
        else {
            angle = asin(v.y/mag(v));
        }
        velocity = mag(v)/500;
        calculate();
        shape.setPosition(sf::Vector2f(pos.x-shape.getRadius(), pos.y-shape.getRadius()));
        window->draw(shape);
    }
};

class Projectile: public Obj {
public:
    sf::CircleShape shape = sf::CircleShape(10);
    sf::Vector2f pos;
    float angle;
    float velocity;
    std::string tag = "projectile";
    sf::RenderWindow* window;
    void calculate() {
        pos.x += velocity * sin((PI / 2) - angle);
        pos.y += velocity * sin(angle);
    }
    Projectile(sf::RenderWindow* window, sf::Vector2f pos, float angle, float vel) {
        this->window = window;
        this->pos = pos;
        this->angle = angle;
        this->velocity = vel;
        shape.setFillColor(sf::Color::Red);
    }

    std::string get_tag() {
        return tag;
    }

    void update() {
        calculate();
        shape.setPosition(sf::Vector2f(pos.x-shape.getRadius(), pos.y-shape.getRadius()));
        window->draw(shape);
    }
};

class Turret: public Obj {
public:
    sf::CircleShape shape = sf::CircleShape(50);
    sf::Vector2f pos;
    float angle;
    float velocity;
    bool x = true;
    std::string tag = "turret";
    sf::RenderWindow* window;

    Turret(sf::RenderWindow* window) {
        this->window = window;
        this->shape.setFillColor(sf::Color::Yellow);
    }

    std::string get_tag() {
        return tag;
    }

    void shoot() {
        auto player = (Player*) get_object("player");
        if (player == nullptr) {
            std::cout << "nullptr exception" << std::endl;
            exit(0);
            return;
        }
        // sf::Vector2f predict_interseption(sf::Vector2f source, sf::Vector2f target, float vs, float vt, float at
        auto p = predict_collision(pos, player->pos, 4.0f, player->velocity, player->angle);
        //auto p = player->pos;
        auto v = p-pos;
        if (v.x < 0) {
            angle = -asin(v.y/mag(v))+PI;
        }
        else {
            angle = asin(v.y/mag(v));
        }
        velocity = 4.0f;
        // Projectile(sf::RenderWindow* window, sf::Vector2f pos, float angle, float vel)
        auto o = new Projectile(window, pos, angle, 4);
        objects.push_back(o);
    }

    void update() {
        auto s = window->getSize();

        pos.x = s.x/2;
        pos.y = s.y/2;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (x) {
                shoot();
            }
             x = false;
        }
        else {
            x = true;
        }
        shape.setPosition(sf::Vector2f(pos.x-shape.getRadius(), pos.y-shape.getRadius()));
        window->draw(shape);
    }
};

void input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::Resized) {
            auto r = sf::FloatRect();
            r.height = event.size.height;
            r.width = event.size.width;
            window.setView(sf::View(r));
        }

}
window.clear();
}
void start() {
    window.clear();
}
void finish() {
    window.display();
    int i = 0;
    for (auto o: objects) {
        if (o->get_tag() == "projectile")
            if (abs(((Projectile*)o)->pos.x) > window.getSize().x*1.5 && abs(((Projectile*)o)->pos.y) > window.getSize().y*1.5) {
                free(o);
                objects.erase(objects.begin()+i);
                std::cout << "gc" << std::endl;
            }
        i++;
    }
}
void draw() {
    for (auto o: objects) {
        o->update();
    }
}
void run() {
    while (window.isOpen()) {
        input();
        start();
        draw();
        finish();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main() {
    auto p = new Player(&window);
    objects.push_back(p);
    auto t = new Turret(&window);
    objects.push_back(t);
    run();
}
