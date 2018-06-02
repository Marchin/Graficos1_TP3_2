#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

int main(int argc, char **argv){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP  *image   = NULL;
   bool playing = true;

   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }

   if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }

   display = al_create_display(800,600);

   image = al_load_bitmap("megaman.png");

   if(!image) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }


   while (playing) {
	   al_draw_scaled_bitmap(image, 0, 0, 894, 894, 0, 0, 32, 32, 1);
	   al_flip_display();

   }
	  
   al_destroy_display(display);
   al_destroy_bitmap(image);

   return 0;
}