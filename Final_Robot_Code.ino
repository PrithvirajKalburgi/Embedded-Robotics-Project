#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

#define pulse_port_right 3
#define pulse_port_left 2

int right_wheel_pulse_count = 1;
int left_wheel_pulse_count = 0;


int number;

void setup() {
  Serial.begin(9600);
  pinMode(pulse_port_right , INPUT);
  attachInterrupt(digitalPinToInterrupt(pulse_port_right), right_wheel_pulse, RISING);
  pinMode(pulse_port_left , INPUT);
  attachInterrupt(digitalPinToInterrupt(pulse_port_left), left_wheel_pulse, RISING);
  Serial.println("Write a number to the serial monitor.");
}

void loop() {
  
}

void serialEvent() {
  while (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    Serial.println(message); 
    int pos_s = message.indexOf("Move");
   

    if (pos_s > -1){
      pos_s = message.indexOf(":");
      if (pos_s > -1){
        String stat = message.substring(pos_s + 1);

        if (stat.charAt(0) == '-') {
          number = stat.substring(1).toInt();
          move_backward(number);
        }
        else {
          number = stat.toInt();
          move_forward(number);
        }     

      }
    }
    else{
      Serial.println("dist:<number>");
     
    }

  }  

}

void move_forward(int cms) {
  digitalWrite(Motor_R_dir_pin, 0);
  digitalWrite(Motor_L_dir_pin, 1);  
  while (right_wheel_pulse_count < 11*cms) {
    digitalWrite(Motor_L_pwm_pin, 1);
    digitalWrite(Motor_R_pwm_pin, 1);
  }
  right_wheel_pulse_count = 0;
  digitalWrite(Motor_L_pwm_pin, 0);
  digitalWrite(Motor_R_pwm_pin, 0);
  
}

void move_backward(int cms) {
  digitalWrite(Motor_R_dir_pin, 1);
  digitalWrite(Motor_L_dir_pin, 0);
  while (right_wheel_pulse_count < 11*cms) {
    digitalWrite(Motor_L_pwm_pin, 1);
    digitalWrite(Motor_R_pwm_pin, 1);
  }
  right_wheel_pulse_count = 0;
  digitalWrite(Motor_L_pwm_pin, 0);
  digitalWrite(Motor_R_pwm_pin, 0);
}

void right_wheel_pulse() {
  right_wheel_pulse_count++;
}

void left_wheel_pulse() {
  left_wheel_pulse_count++;
}
