#include <pebble.h>

Window * window;
TextLayer * text_layer;

void init(){
  window = window_create();
  text_layer = text_layer_create(GRect(0,0,144,40));
  text_layer_set_text(text_layer, "Hello, Pebble!");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
  
  window_stack_push(window, true);
}

void deinit(){
  window_destroy(window);
  text_layer_destroy(text_layer);
}

int main(){
  //initialize app
  init();
  
  //wait for app events
  app_event_loop();
  
  //deinitialize the app
  deinit();
  
  return 0;
}