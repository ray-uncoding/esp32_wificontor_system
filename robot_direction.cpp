#include "robot_direction.h"
#include "global_defs.h"
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 100
#define SERVOMAX 640
#define nintydeg 370

int servonum_left_forward[] = { 0, 1, 2 };
int servonum_left_backward[] = { 4, 5, 6 };
int servonum_right_forward[] = { 8, 9, 10 };
int servonum_right_backward[] = { 12, 13, 14 };

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0
#define shoot 5

#define left_front_foot 1
#define left_hind_foot 2
#define right_front_foot 3
#define right_hind_foot 4
#define head 5

void onCarInputWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                              void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;
  }
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info;
  info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    std::string myData = "";
    myData.assign((char *)data, len);
    std::istringstream ss(myData);
    std::string key, value;
    std::getline(ss, key, ',');
    std::getline(ss, value, ',');
    Serial.printf("Key [%s] Value[%s]\n", key.c_str(), value.c_str());
    int valueInt = atoi(value.c_str());

    if (key == "Move") {
      moveCar(valueInt);
    } else if (key == "head") {
      servo_contrl(head, valueInt);
    } else if (key == "left_front_foot") {
      servo_contrl(left_front_foot, valueInt);
    } else if (key == "left_hind_foot") {
      servo_contrl(left_hind_foot, valueInt);
    } else if (key == "right_front_foot") {
      servo_contrl(right_front_foot, valueInt);
    } else if (key == "right_hind_foot") {
      servo_contrl(right_hind_foot, valueInt);
    }
  }
  break;
}

void move(int inputValue) {
  Serial.printf("Got value as %d\n", inputValue);
  switch (inputValue) {
    case UP:
      break;
    case DOWN:
      break;
    case LEFT:
      break;
    case RIGHT:
      break;
    case STOP:
      break;
    default:
      break;
  }
}

void servo_contrl(int servo_num, int inputValue) {
  Serial.printf("Got value as %d\n", inputValue);
  switch (servo_num) {
    case left_front_foot:
      break;
    case left_hind_foot:
      break;
    case right_front_foot:
      break;
    case right_hind_foot:
      break;
    case head:
      break;
    default:
      break;
  }
}

void servo_init() {
  myServo.begin();
  myServo.setPWMFreq(60);
}