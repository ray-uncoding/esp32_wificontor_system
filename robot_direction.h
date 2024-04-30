#ifndef _robot_direction_
#define _robot_direction_

#include "global_defs.h"

// Forward declare the function before it's used
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);  //123

void onCarInputWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                              void *arg, uint8_t *data, size_t len);

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

void move(int inputValue);

void servo_contrl(int servo_num, int inputValue);

void servo_init();

#endif
