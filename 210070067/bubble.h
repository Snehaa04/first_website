#include <simplecpp>
#include "shooter.h"

/* Bubble Vars */
const int BUBBLE_START_X = 250;
const int BUBBLE_START_Y = 50;
const int BUBBLE_DEFAULT_RADIUS = 10;
const int BUBBLE_RADIUS_THRESHOLD = 10;
const int BUBBLE_DEFAULT_VX = 60;
const int BUBBLE_DEFAULT_VY = 60;
const int PLAY_Y_HEIGHT = 450;
const int a = 200;// new variable for acceleration
int score=0;// no. of bullets hit by the shooter, increase in score


vector<Bullet> bullets;//need to declare the bullets here

class Bubble
{
private:
    Circle circle;  // the circle representing the bubble
    double vx, vy,new_vy;  // velocity in x and y direction
    Color color;    // color of the bubble

public:
    Bubble(double cx, double cy, double r, double vx_=BUBBLE_DEFAULT_VX, double vy_=BUBBLE_DEFAULT_VY, Color color_=COLOR(0, 0, 255))
    {
        // Bubble constructor
        color = color_;
        circle = Circle(cx, cy, r);
        circle.setColor(color);
        circle.setFill(true);

        vx = vx_;
        vy = vy_;
        new_vy = vy;


    }

    int timetillnow=50;//records the most recent time that bubble hit the shooter

    bool nextStep(double t)
    {   // move the bubble
        for(unsigned int i=0; i < bullets.size() ;i++){
        if((abs(bullets[i].get_center_y()- circle.getY())<= circle.getRadius()+ 0.5*(bullets[i].get_height()))&&( abs(bullets[i].get_center_x()- circle.getX())<=circle.getRadius()+bullets[i].get_width())){
        score+=1;// updating the score
        bullets.erase(bullets.begin()+i);//deleting the bullet after hitting the bubble

        return false;
        }
        }


       // move the bubble
        double new_x = circle.getX() + vx*t;//updating x direction
        new_vy = new_vy + a*t; //new y velocity due to acceleration
        double new_y = circle.getY() + new_vy*t + 0.5*a*t*t;// updating the new y coordinate

        if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
            ||
            (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
        {

            vx = -vx;
            new_x = circle.getX() + vx*t;

        }

        if(new_y>(PLAY_Y_HEIGHT- circle.getRadius())){//bouncing along y direction
        new_vy = -new_vy;
        new_y = circle.getY()+ new_vy*t + 0.5*a*t*t;
        }

        circle.moveTo(new_x, new_y);// final position of the bubble
        return true;
    }

    double get_radius()
    {
        // return the radius of the bubble
        return circle.getRadius();
    }

    double get_center_x()
    {
        // return the x coordinate of the center of the bubble
        return circle.getX();
    }

    double get_center_y()
    {
        // return the y coordinate of the center of the bubble
        return circle.getY();
    }

    double get_vx()
    {
        // return the x velocity of the bubble
        return vx;
    }
    double get_vy()
    {
        // return the y velocity of the bubble
        return vy;
    }

    Color get_color()
    {
        // return the color of the bubble
        return color;
    }

};
