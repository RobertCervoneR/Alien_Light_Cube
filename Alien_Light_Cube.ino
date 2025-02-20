int colorEffect = 12;
int changeColor = 10;
int power = 8;
int redLED = 6;
int greenLED = 5;
int blueLED = 3;

int colorCycleDelayTime = 5;

void setup() {

pinMode(colorEffect, INPUT_PULLUP);
pinMode(changeColor, INPUT_PULLUP);
pinMode(power, INPUT_PULLUP);
pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);

Serial.begin(9600);
}

int set_color = "Red";

void loop() 
{
  set_color = colorBlink(set_color);
  
}

int colorBlink(int set_color)
{
  for(int i = 0; i < 255; i = i + 2)
  {
    color_output(set_color, i);

    int color_change_button_is_pressed = check_if_color_change_pressed();

    if(color_change_button_is_pressed == true)
    {
      set_color = colorChange(set_color);
    }

    delay(10);
  }

  for(int i = 0; i < 255; i = i + 2)
  {
    color_output(set_color, 255 - i);

    int color_change_button_is_pressed = check_if_color_change_pressed();

    if(color_change_button_is_pressed == true)
    {
      set_color = colorChange(set_color);
    }
    
    delay(10);
  }

  return set_color;
}

void color_output(int set_color, int i)
{
  if(set_color == "Red")
  {
    analogWrite(redLED, i);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  if(set_color == "Green")
  {
    digitalWrite(redLED, LOW);
    analogWrite(greenLED, i);
    digitalWrite(blueLED, LOW);
  }
  if(set_color == "Blue")
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    analogWrite(blueLED, i);
  }
  if(set_color == "White")
  {
    analogWrite(redLED, i);
    analogWrite(greenLED, i);
    analogWrite(blueLED, i);
  }
  if(set_color == "Purple")
  {
    analogWrite(redLED, i);
    digitalWrite(greenLED, LOW);
    analogWrite(blueLED, i);
  }
  if(set_color == "Light Blue")
  {
    digitalWrite(redLED, LOW);
    analogWrite(greenLED, i);
    analogWrite(blueLED, i);
  }
  if(set_color == "Yellow")
  {
    analogWrite(redLED, i);
    analogWrite(greenLED, i/3);
    digitalWrite(blueLED, LOW);
  }

  return 0;
}

int check_if_color_change_pressed()
{
  int color_change_pressed = digitalRead(changeColor);
  int color_change_is_pressed;

  if(color_change_pressed == 0)
  {
    while(color_change_pressed == 0)
    {
      color_change_pressed = digitalRead(changeColor);
      continue;
    }
    return color_change_is_pressed = true;
  }
  else
  {
    return color_change_is_pressed = false;
  }

}

int colorChange(int set_color)
{
  if(set_color == "Red")
  {
    return set_color = "Green";
  }
  else if(set_color == "Green")
  {
    return set_color = "Yellow";
  }
  else if(set_color == "Yellow")
  {
    return set_color = "Blue";
  }
  else if(set_color == "Blue")
  {
    return set_color = "Light Blue";
  }
  else if(set_color == "Light Blue")
  {
    return set_color = "Purple";
  }
  else if(set_color == "Purple")
  {
    return set_color = "White";
  }
  else if(set_color == "White")
  {
    return set_color = "Red";
  }
}