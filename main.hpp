

#define jump_quadratic_equation(x) (6 * x * x)
#define jump_equ_x_default         1.5

typedef sf::RectangleShape rect;

bool collision_detect( rect, rect);
bool jump( rect& );
int generate_randint(int , int );


bool collision_detect( rect small_one , rect large_one ) {

    sf::Vector2f small_size = small_one.getSize();
    sf::Vector2f large_size = large_one.getSize();

    sf::Vector2f small_pos = small_one.getPosition();
    sf::Vector2f large_pos = large_one.getPosition();

    sf::Vector2f small_one_corner[4];
    sf::Vector2f temp = small_one.getPosition();

    small_one_corner[0] = small_one.getPosition(); // left_up

    temp.x += small_one.getSize().x;
    small_one_corner[1] = temp ;// right up

    temp.y += small_one.getSize().y;
    small_one_corner[2] = temp ;// right bottom

    temp = small_one.getPosition();
    temp.y += small_one.getSize().y;
    small_one_corner[3] = temp ;// left bottom

    for ( sf::Vector2f *p = small_one_corner ; p != small_one_corner + 4 ; ++p ) {

        if ( p->x > large_pos.x && p->x < large_pos.x + large_size.x ) {
            if ( p->y > large_pos.y && p->y < large_pos.y + large_size.y )
                return true;
        }
    }

    return false;
}


double jump_equ_x = jump_equ_x_default;  // range: to -jump_equ_x_default;
double origin_velocity = -20;
double velocity = origin_velocity;
double acceleration = 1;

bool jump ( rect &obj ) {

    obj.move(0.f, velocity);

    velocity += acceleration;

    if ( obj.getPosition().y >= 550 ) {

        velocity = origin_velocity;
        return false;
    }

    return true;
}


/*
bool jump( rect& obj ) {

    if ( jump_equ_x < 0 )
        obj.move( 0.f, jump_quadratic_equation( jump_equ_x ) );
    else
        obj.move( 0.f, -1 * jump_quadratic_equation( jump_equ_x ) );


    if ( jump_equ_x <= -1 * jump_equ_x_default ) {
        jump_equ_x = jump_equ_x_default;
        return false;
    }
    
    jump_equ_x -= 0.1;

    return true;

}
*/

int generate_randint(int _begin, int _end) {


    int r;  // range: 0 ~ (_end -1)

    while ( (r = rand() % _end) < _begin  )
        ;

    return r;

}   


