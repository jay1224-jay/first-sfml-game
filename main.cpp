#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "main.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 700), "Game");

    window.setFramerateLimit(60);


    sf::RectangleShape player(sf::Vector2f(55.f, 100.f));
    sf::Texture villager_texture;

    if ( !villager_texture.loadFromFile("./resource/villager.jpeg") )
        std::cout << " error while loading villager.jpeg\n";
    player.setTexture(&villager_texture);
    player.setPosition(100.f, 550.f);
    player.setFillColor( sf::Color::White );
    player.setOutlineThickness(10);

    
    sf::RectangleShape bullet(sf::Vector2f(20.f, 10.f));
    bullet.setPosition(560.f, 600.f);
    bullet.setFillColor(sf::Color::Red);

    sf::SoundBuffer hit_sound_buf;


    if ( !hit_sound_buf.loadFromFile("./resource/hit_sound.oga") ) // from minecraft;
        std::cout << "there is something wrong while loading hit_sound.mp3\n";

    sf::Sound hit_sound;
    hit_sound.setBuffer(hit_sound_buf);

    bool jump_flag = false;



    while (window.isOpen()) {

        sf::Event event;
        while ( window.pollEvent(event) ) {

            if (event.type == sf::Event::Closed)
                window.close();

        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A )) {
            if ( player.getPosition().x > 0 )
                player.move(-5.f, 0.f);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D )) {
            if ( player.getPosition().x + player.getSize().x < window.getSize().x )
                player.move(5.f, 0.f);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space )) {
            jump_flag = true;
        }

        if ( jump_flag ) {
            bool status = jump(player);
            if ( !status )
                jump_flag = false;
        }
        

        /*
        else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W ))  {
            player.move(0.f, -5.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S )) {
            player.move(0.f, 5.f);
        }
        */

        
        bullet.move(-2.f, 0.f);

        if ( collision_detect(bullet, player) ) {
            hit_sound.play();
            player.setOutlineColor(sf::Color::Blue);
        } 


        window.clear( sf::Color::White );


        window.draw(bullet);


        window.draw(player);


        
        window.display();
    }

}
