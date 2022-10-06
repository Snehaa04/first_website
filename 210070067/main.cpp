#include <simplecpp>
#include "bubble.h"

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);
int loop=0;// represents no. of loops
int time=50;

void move_bullets(vector<Bullet> &bullets){// function to move bullets
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
       if(!bubbles[i].nextStep(STEP_TIME)){
       if(bubbles[i].get_radius()==BUBBLE_DEFAULT_RADIUS)// creating two bubbles on being hit by the bullet
       {
       bubbles.push_back(Bubble(bubbles[i].get_center_x(),bubbles[i].get_center_y(),0.5*BUBBLE_DEFAULT_RADIUS,-BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
       bubbles.push_back(Bubble(bubbles[i].get_center_x(),bubbles[i].get_center_y(),0.5*BUBBLE_DEFAULT_RADIUS,BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
       }
       bubbles.erase(bubbles.begin()+i);// deleting original bubble
       }
       }
}

vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    return bubbles;
}


int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);// cmd textbox

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();// command to initialise bubble vector defined in main.cpp

    Text life(WINDOW_X*0.1,TOP_MARGIN,"LIFE:");//textbox displayinf LIFE
    Text life_count(WINDOW_X*0.15,TOP_MARGIN,shooter_life);// textbox for life_count
    Text life_total(WINDOW_X*0.18,TOP_MARGIN,"/ 3");

    Text SCORE(WINDOW_X*0.44,BOTTOM_MARGIN,"SCORE:_");
    Text Score(WINDOW_X*0.5, BOTTOM_MARGIN,score);// score textbox

    Text TIME(WINDOW_X*0.75,BOTTOM_MARGIN,"TIME:_");
    Text Time(WINDOW_X*0.8,BOTTOM_MARGIN,time);  //time textbox
    Text time_total(WINDOW_X*0.84,BOTTOM_MARGIN,"/50");

    XEvent event;

    // Main game loop
    while (true)
    {
    for(unsigned int i=0; i< bubbles.size();i++){
       if((abs(bubbles[i].get_center_x()-shooter.get_body_center_x())<= 0.5*shooter.get_body_width()+bubbles[i].get_radius())&&(bubbles[i].get_center_y()>=PLAY_Y_HEIGHT - (shooter.get_body_height()+2*shooter.get_head_radius()+ bubbles[i].get_radius())))
       {
        if(time<bubbles[i].timetillnow-1.5){//bubble hiting the shooter
        shooter_life-=1;
        bubbles[i].timetillnow=time;}
        }
        }

         ostringstream strg,timestrg,lifestrg;// converting int to stream to display it on the textboxes
          strg<< score;
          string s1 = strg.str();//s1 represents score
          timestrg<< time;
          string s2 = timestrg.str();// s2 represents time
          lifestrg<<shooter_life;
          string s3 = lifestrg.str();// s3 represents life_count

          Score.setMessage(s1);// updating the parametres of each textbox
          Time.setMessage(s2);
         life_count.setMessage(s3);

         bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);
        // update the color of the shooter
        shooter.shooter_color();

        wait(STEP_TIME);

        loop+=1;// no. of loops
        time=50-(loop)/50;//updating time

        if((shooter_life < 1)||(time==0)||(bubbles.size()==0))
        {
          Time.setMessage("0");
          break;
          } // breaking the loop if the shooter is dead or time ends or all the bubbles are busted.


    }
      string statement;
      Text final(0.5*WINDOW_X,0.5*WINDOW_Y,statement);
      if(bubbles.size()==0)
      final.setMessage("CONGRATULATIONS!!");//when all the bubbles are shot
      else
      final.setMessage("GAME OVER");// in case time gets over or the life_count becomes 0.
      wait(120);



 }
