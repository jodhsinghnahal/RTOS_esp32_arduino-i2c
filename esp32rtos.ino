#include <Wire.h>

#define p1_pin 35
#define p2_pin 34
#define joystick_x_pin A0 
#define joystick_y_pin A3

int pot_arr[2] = {0, 0};
float joy_arr[2] = {0, 0};
int butt_arr[5] = {0, 0, 0, 0, 0};

void pot_read(void *arg){
  pinMode(p1_pin, INPUT);
  while(1){
    int pot = analogRead(p1_pin);
    pot_arr[0] = pot;
    vTaskDelay(200/portTICK_PERIOD_MS);
  }
}

void pot_read2(void *arg){
  pinMode(p2_pin, INPUT);
  while(1){
    int pot2 = analogRead(p2_pin);
    pot_arr[1] = pot2;
    vTaskDelay(200/portTICK_PERIOD_MS);
  }
}

void joystick(void *arg){
  while(1){
  int x_adc_val, y_adc_val; 
  x_adc_val = analogRead(joystick_x_pin); 
  y_adc_val = analogRead(joystick_y_pin);
  joy_arr[0] = ( ( x_adc_val * 3.3 ) / 4095 ); 
  joy_arr[1] = ( ( y_adc_val * 3.3 ) / 4095 ); 

  vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void receiveEvent(int bytesReceived){
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived);
    // log_print_buf(temp, bytesReceived);
    butt_arr[0] = temp[0]-48;
    butt_arr[1] = temp[1]-48;
    butt_arr[2] = temp[2]-48;
    butt_arr[3] = temp[3]-48;
    butt_arr[4] = temp[4]-48;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  xTaskCreate(pot_read, "pot read", 2048, NULL, 1, NULL);
  xTaskCreate(pot_read2, "pot read", 2048, NULL, 1, NULL);
  xTaskCreate(joystick, "js read", 2048, NULL, 1, NULL);
}

void loop(){
  Serial.print("Pot1: ");
  Serial.print(pot_arr[0]);
  Serial.print(", Pot2: ");
  Serial.print(pot_arr[1]);
  Serial.print(" X_Voltage: ");
  Serial.print(joy_arr[0]);
  Serial.print(" Y_Voltage: ");
  Serial.print(joy_arr[1]);
  Serial.print(" Button 1: ");
  Serial.print(butt_arr[0]);
  Serial.print(" Button 2: ");
  Serial.print(butt_arr[1]);

  Serial.print(" Button 3: ");
  Serial.print(butt_arr[2]);

  Serial.print(" Button 4: ");
  Serial.print(butt_arr[3]);

  Serial.print(" Button 5: ");
  Serial.println(butt_arr[4]);

  delay(100);  
}
