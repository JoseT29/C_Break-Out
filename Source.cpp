#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<iostream>
using namespace std;


class brik {
private:
	int xpos;
	int ypos;
	int width;
	int height;
public:
	void init(int x, int y, int h, int w);
	bool collision(int bx, int by, int bw, int bh, int px, int py, int pw, int ph);
};

//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;

//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_RIGHT, KEY_LEFT,
};

//function decleration
bool collide(int bx, int by, int bw, int bh, int px, int py, int pw, int ph);

int main() {
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL; //bucket that holds all the events
	ALLEGRO_TIMER* timer = NULL; //conductor for your game


	//ball starting position
	float ball_x = 20;
	float ball_y = 200;


	//ball speed
	float ball_dx = -5.0, ball_dy = 4.0;

	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	ALLEGRO_BITMAP* pic = al_load_bitmap("lul.png");
	al_convert_mask_to_alpha(pic, al_map_rgb(255, 255, 255));

	// position of player
	double xPos = 230;
	double yPos = 430;

	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop

	timer = al_create_timer(1.0 / 60);
	display = al_create_display(500, 500);
	event_queue = al_create_event_queue();

	//tells the event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);

	while (!doexit) //game loop
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_RIGHT]) {
				xPos += 6.0;
			}

			if (key[KEY_LEFT]) {
				xPos -= 6.0;

			}

			if (ball_x < -10 || ball_x > 450) { //bounces against side walls
				ball_dx = -ball_dx;
			}

			if (ball_y < -10 || ball_y > 450) { //bounce against top and bottom walls
				ball_dy = -ball_dy;
			}
			//collision with paddles
			if (collide(ball_x, ball_y, 74, 48, xPos, yPos, 20, 60) == true) {
				ball_dy = -ball_dy;
				cout << "ping";
			}
			//MOVE
			ball_x += ball_dx;
			ball_y += ball_dy;

			redraw = true;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

		
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;


			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}


		//RENDER SECTION
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0)); //clears the screen
			al_draw_bitmap(pic, ball_x, ball_y, NULL);
			al_draw_rectangle(xPos, yPos, xPos + 60, yPos + 20, al_map_rgb(50, 120, 10), 4); //draw the player
			
			//al_draw_filled_circle(ball_x, ball_y, 20, al_map_rgb(200, 200, 100));
			al_flip_display();
		}//end render
	}//end game loop

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}// end main

//function definition 
bool collide(int bx, int by, int bw, int bh, int px, int py, int pw, int ph) {

	if ((bx + bw > px) &&
		(bx < px + pw) &&
		(by + bh > py) &&
		(by < py + ph)
		)
		return true;
	else
		return false;
}

void brik::init(int x, int y, int h, int w) {
	xpos = x;
	ypos = y;



}


bool brik::collision(int bx, int by, int bw, int bh, int px, int py, int pw, int ph) {

	if ((bx + bw > px) &&
		(bx < px + pw) &&
		(by + bh > py) &&
		(by < py + ph)
		)
		return true;
	else
		return false;
}