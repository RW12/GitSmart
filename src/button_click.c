#include <pebble.h>
#include <header.h>

static Window *window;
static TextLayer *text_layer;

int array_of_column_index[5] ={0, 0, 0, 0, 0};    // here 2 and 0,0 should be updated once totalNumberOfTopics is updated
int array_of_max_column_index[5] ={20, 11, 20, 20, 11}; //here 2 and 11, 20 should be updated once totalNumberOfTopics is udpated
int topic_index = 0;    //maximum of this int is (totalNumberOfTopics - 1)
int stage_index = 0;    // 0 represents subject selection, 1 represents word scrolling interface, 2 represents detailed definition of the word
int totalNumberOfTopics = 5;

//for background color 
GColor8 color;

//Rotate through 4 colors in order
void setColor(){
  switch(array_of_column_index[topic_index] % 4){
    case 0: color = GColorLavenderIndigo;
            break;
    case 1: color = GColorMintGreen;
            break;
    case 2: color = GColorChromeYellow;
            break;
    case 3: color = GColorPictonBlue;
            break;
    default: break;
  }
  
  //fill with background color
  text_layer_set_background_color(text_layer, color);
  window_set_background_color(window, color);
}

static void TopicSelectionUp(){
  if(topic_index == 0){
    topic_index = totalNumberOfTopics - 1;
  }
  else{
    topic_index = topic_index - 1;
  }
}

static void TopicSelectionDown(){
  if(topic_index < totalNumberOfTopics - 1){
    topic_index++;
  }
  else{
    topic_index = 0;
  }
}   
  
static void CardSelectionUp(){
  if(array_of_column_index[topic_index] == 0){
    array_of_column_index[topic_index] = array_of_max_column_index[topic_index] - 1;
  }
  else{
    array_of_column_index[topic_index] = array_of_column_index[topic_index] - 1;
  }
  
  setColor();
}

static void CardSelectionDown(){
  if((array_of_column_index[topic_index]) < array_of_max_column_index[topic_index] - 1){
    array_of_column_index[topic_index]++;
  } 
  else{   //already at the bottom of the array
    array_of_column_index[topic_index] = 0; 
  }
  
  setColor();
}
  
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(stage_index < 2 && stage_index>=0 ){
    stage_index++;
    if(topic_index == 0){
      text_layer_set_text(text_layer, vocab[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 1){
      text_layer_set_text(text_layer, math[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 2){
      text_layer_set_text(text_layer, countries[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 3){
      text_layer_set_text(text_layer, pertable[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 4){
      text_layer_set_text(text_layer, biosystems[array_of_column_index[topic_index]][stage_index]);
    }
  }
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (stage_index > 0 && stage_index <= 2){
    stage_index = stage_index - 1;
    if(topic_index == 0){
      text_layer_set_text(text_layer, vocab[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 1){
      text_layer_set_text(text_layer, math[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 2){
      text_layer_set_text(text_layer, countries[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 3){
      text_layer_set_text(text_layer, pertable[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 4){
      text_layer_set_text(text_layer, biosystems[array_of_column_index[topic_index]][stage_index]);
    }
    //add more subjects here
  }
}


static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(stage_index == 0){
    TopicSelectionUp();
    text_layer_set_text(text_layer, topics[topic_index]);
  }
  else if(stage_index == 1){
    CardSelectionUp();
    if(topic_index == 0){
      text_layer_set_text(text_layer, vocab[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 1){
      text_layer_set_text(text_layer, math[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 2){
      text_layer_set_text(text_layer, countries[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 3){
      text_layer_set_text(text_layer, pertable[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 4){
      text_layer_set_text(text_layer, biosystems[array_of_column_index[topic_index]][stage_index]);
    }
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(stage_index == 0){
    TopicSelectionDown();
    text_layer_set_text(text_layer, topics[topic_index]);
  }
  else if(stage_index == 1){
    CardSelectionDown();
    if(topic_index == 0){
      text_layer_set_text(text_layer, vocab[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 1){
      text_layer_set_text(text_layer, math[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 2){
      text_layer_set_text(text_layer, countries[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 3){
      text_layer_set_text(text_layer, pertable[array_of_column_index[topic_index]][stage_index]);
    }
    if(topic_index == 4){
      text_layer_set_text(text_layer, biosystems[array_of_column_index[topic_index]][stage_index]);
    }
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(text_layer, topics[0]);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}