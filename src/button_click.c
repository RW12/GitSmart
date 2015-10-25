#include <pebble.h>
#include <header.h>

static Window *window;
static TextLayer *text_layer;

int topic_type = 0;
int index1 = 0;
int index2 = 0;
int totalMathCards = 11;
int totalVocabCards = 20;
int topic_selection = 1;
int cardSide = 1;
int totalNumberOfTopics;

static void TopicSelection(){
  if (topic_selection == 0){
    topic_selection = 1;
  } else {
    topic_selection = 0;
  }
}

static void CardSelectionDown(){
  if (topic_selection == 0) {
    if (index1 < totalVocabCards - 1){
      index1++;
    } else {
      index1 = 0;
    }
  } else {
    if (index2 < totalMathCards - 1){
      index2++;
    } else {
      index2 = 0;
    }
  }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //Pseudo Code
  if (cardSide == 0){
    cardSide = 1;
  } else {
    cardSide = 0;
  }
  if (topic_selection == 0){
    text_layer_set_text(text_layer, vocab[index1][cardSide]);
  } else {
    text_layer_set_text(text_layer, math[index2][cardSide]);
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
  TopicSelection();
  if (topic_selection == 0){
    text_layer_set_text(text_layer, vocab[index1][0]);
  } else {
    text_layer_set_text(text_layer, math[index2][0]);
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
  CardSelectionDown();
  if (topic_selection == 0){
    text_layer_set_text(text_layer, vocab[index1][0]);
  } else {
    text_layer_set_text(text_layer, math[index2][0]);
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_text(text_layer, "Select a topic");
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