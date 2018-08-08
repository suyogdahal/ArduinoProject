#define m1a 2
#define m1b 3
#define m2a 4
#define m2b 5
boolean condition;
const int trigPin1 = 12;  //right
const int echoPin1 = 11;  //right
const int trigPin2 = 8;   //left
const int echoPin2 = 7;   //left
const int trigPin3 = 9;   //front
const int echoPin3 = 10;   //front
double duration1, dist_r, duration2, dist_l, dist_f, duration3;
void setup() {
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2 , OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3 , OUTPUT);
  pinMode(echoPin3, INPUT);

  Serial.begin(9600);
}
void ultrasonic()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  dist_r = (duration1 * .03430) / 2;
  Serial.print("dist_r: ");
  Serial.print (dist_r);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  dist_l = (duration2 * .03430) / 2;
  Serial.print("dist_l: ");
  Serial.println(dist_l);

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin2, HIGH);
  dist_f = (duration3 * .03430) / 2;
  Serial.print("dist_f: ");
  Serial.println(dist_f);
}
void forward() {
  Serial.println("Forward");
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}
void backward() {
  Serial.println("Backward");
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);;
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}
void right() {
  Serial.println("RIGHT");
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}
void left() {
  Serial.println("LEFT");
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}
void wait() {
  Serial.println("Wait");
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}
void automatic() {

  ultrasonic();
  if (dist_f > 5) {
    forward();
  }
  else if (((dist_r + dist_l) > 20) and dist_f < 5 )
  {
    if (dist_r > dist_l)
    {
      right();
    }
    else
    {
      left();
    }
  }
  else
  {
    backward();
  }
}
void loop() {
  if (Serial.available() >= 0)
  {
    char bluetooth = Serial.read();
    switch (bluetooth)
    {
      case 'F': forward(); condition = false; break;
      case'B': backward(); condition = false;  break;
      case'L': left(); condition = false;  break;
      case'R': right(); condition = false;  break;
      case'x': condition = true; break;
      default:
        if (condition == true)
        {
          automatic();
        }
        break;
    }
  }
}

