#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CHARACTER_SIDE 32
#define FACING_RIGHT 1
#define FACING_LEFT 0


int main(int argc, char **argv) {

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* playerImage = NULL;
	ALLEGRO_BITMAP* enemyImage = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_KEYBOARD_STATE keyState;
	const float FPS = 60.0;
	bool exit = false;
	int playerDirection = FACING_RIGHT;
	float posP1_x = 0;
	float posP1_y = 0;
	float posP2_x = SCREEN_WIDTH / 2.f;
	float posP2_y = SCREEN_HEIGHT / 2.f;
	float moveSpeed = 5;


	if (!al_init()) {
		al_show_native_message_box(display,
			"Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display,
			"Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	playerImage = al_load_bitmap("megaman.png");

	if (!playerImage) {
		al_show_native_message_box(display,
			"Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	enemyImage = al_load_bitmap("protoman.png");

	if (!enemyImage) {
		al_show_native_message_box(display,
			"Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display,
			"Error", "Error", "failed to create event_queue!\n",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return -1;
	}

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	while (!exit) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_UP) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				exit = true;
			}
		}
		if (events.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_D) &&
				(posP1_x < SCREEN_WIDTH - CHARACTER_SIDE)) {

				posP1_x += moveSpeed;
				playerDirection = FACING_RIGHT;
			} else if (al_key_down(&keyState, ALLEGRO_KEY_A) &&
				(posP1_x > 0)) {

				posP1_x -= moveSpeed;
				playerDirection = FACING_LEFT;
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_S) &&
				(posP1_y < SCREEN_HEIGHT - CHARACTER_SIDE)) {

				posP1_y += moveSpeed;
			} else if (al_key_down(&keyState, ALLEGRO_KEY_W) &&
				(posP1_y > 0)) {

				posP1_y -= moveSpeed;
			}
		}


		al_draw_bitmap(playerImage, posP1_x, posP1_y, playerDirection);
		al_draw_bitmap(enemyImage, posP2_x, posP2_y, 0);


		if (((posP1_x + CHARACTER_SIDE > posP2_x) && (posP1_x < posP2_x + CHARACTER_SIDE)) &&
			((posP1_y + CHARACTER_SIDE > posP2_y) && (posP1_y < posP2_y + CHARACTER_SIDE))) {

			exit = true;
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);
	al_destroy_bitmap(playerImage);

	return 0;
}