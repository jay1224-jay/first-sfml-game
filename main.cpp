#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <utility>
#include <string>

#include "main.hpp"

#define WIDTH  800
#define HEIGHT 700
#define GROUND HEIGHT - 50
#define HEALTH 10  // min: 0;

#define bullets_size  10


int main() {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game");

    window.setFramerateLimit(60);


    sf::RectangleShape player(sf::Vector2f(55.f, 100.f));
    sf::Texture villager_texture;

    if ( !villager_texture.loadFromFile("./resource/villager.jpeg") )
        std::cout << " error while loading villager.jpeg\n";
    player.setTexture(&villager_texture);
    player.setPosition(100.f, GROUND - player.getSize().y);  
    player.setFillColor( sf::Color::White );
    player.setOutlineThickness(10);

    
    typedef std::pair<sf::RectangleShape, double> bullet_pair;
    bullet_pair bullets[bullets_size];

    srand(time(NULL));

    for ( bullet_pair * p = bullets ; p != bullets + bullets_size ; ++p ) {

        p->first.setSize( sf::Vector2f( 20.f, 10.f ) ); 
        p->first.setFillColor(sf::Color::Red);
        p->first.setPosition( 760, generate_randint( 0, GROUND ));
        
        // set velocity
        p->second = -1 * generate_randint( 1, 6 );

    }



    // sf::RectangleShape bullet(sf::Vector2f(20.f, 10.f));
    // bullet.setPosition(560.f, 600.f);
    // bullet.setFillColor(sf::Color::Red);

    sf::SoundBuffer hit_sound_buf;


    if ( !hit_sound_buf.loadFromFile("./resource/hit_sound.oga") ) // from minecraft;
        std::cout << "there is something wrong while loading hit_sound.mp3\n";

    sf::Sound hit_sound;
    hit_sound.setBuffer(hit_sound_buf);


    sf::Font text_font;

    text_font.loadFromFile("./resource/lemon_day.ttf");

    sf::Text health_text;
    
    // select the font
    health_text.setFont(text_font); // font is a sf::Font
    
    // set the string to display

    int health = HEALTH;
    std::string health_string = "Health: " + std::to_string(health);
    health_text.setString(health_string);
    
    // set the character size
    health_text.setCharacterSize(24); // in pixels, not points!
    
    // set the color
    health_text.setFillColor(sf::Color::Black);

    health_text.setPosition(350, 20);
    
    // set the text style
    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    
    sf::RectangleShape restart_button(sf::Vector2f(100.f, 50.f));
    restart_button.setPosition( WIDTH / 2 - 70 / 2, HEIGHT / 2 - 30 / 2 );
    restart_button.setFillColor(sf::Color::Blue);

    sf::Text restart_text("Restart", text_font);
    restart_text.setPosition(WIDTH / 2 - 70 / 2 + 5, HEIGHT / 2 - 30 / 2 + 5);
    restart_text.setCharacterSize(24);
    restart_text.setFillColor(sf::Color::White);



    bool jump_flag = false;
    bool hit_sound_play_flag = false;
    bool game_over = false;

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


        // collision detection ========

        // same 2;
        // if ( collision_detect(bullet, player) ) {
        // if ( player.getGlobalBounds().intersects(bullet.getGlobalBounds()) ) {
        //

        for ( bullet_pair * bullet = bullets ; bullet != bullets + 10 ; ++bullet ) {

            if ( bullet->first.getGlobalBounds().intersects(player.getGlobalBounds()) ) {

                if ( !hit_sound_play_flag )
                    hit_sound_play_flag = true;
                player.setOutlineColor(sf::Color::Blue);

                if ( --health <= 0 ) { 
                    game_over = true;
                }
                
            } 
        }

        if ( hit_sound_play_flag ) {
            if ( hit_sound.getStatus() != 2 ) // 2 means Playing
                hit_sound.play();
            else
                hit_sound_play_flag = false;
        }

        // collision detection ========



        window.clear( sf::Color::White );


        if ( ! game_over ) {
            // draw bullets

            for ( bullet_pair * p = bullets ; p != bullets + bullets_size ; ++p ) {

                window.draw( p->first );
                if ( p->first.getPosition().x <= 0 ||
                    p->first.getGlobalBounds().intersects(player.getGlobalBounds()) ) {

                    p->first.setPosition( 760, generate_randint( 0, GROUND ));
                    p->second = -1 * generate_randint( 1, 6 );

                }
                p->first.move(p->second, 0.f);

            }

            // draw bullets


            window.draw(player);

            health_text.setString( "Health: " + std::to_string(health)  );

            window.draw(health_text);
       } else {

            window.draw(restart_button);
            window.draw(restart_text);

            if ( event.type == sf::Event::MouseButtonPressed ) {
                if ( event.mouseButton.button == sf::Mouse::Left ) {

                    if ( restart_button.getGlobalBounds().contains
                            (event.mouseButton.x, event.mouseButton.y) ) {

                        game_over = false;
                        health = HEALTH;
                        player.setPosition(100.f, GROUND - player.getSize().y);  
                    }
                
                }
            }
                            

       }
        
        window.display();
    }

}
