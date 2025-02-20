// Button variable names
int colorEffect = 12;
int changeColor = 10;
int tiltSwitch = 8;

// LED variable names
int redLED = 6;
int greenLED = 5;
int blueLED = 3;

void setup() {

digitalWrite(tiltSwitch, HIGH);
digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);

// Button pin types
pinMode(colorEffect, INPUT_PULLUP);
pinMode(changeColor, INPUT_PULLUP);
pinMode(tiltSwitch, INPUT);

// LED pin types
pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);

Serial.begin(9600);
}

int set_color = "Red";
int color_strobe_button_is_pressed = false;

void loop() 
{
  set_color = colorBlink(set_color);

  
}

// Idly pulses current color until button press occurs
int colorBlink(int set_color)
{
  // Increasing light
  for(int i = 0; i < 255; i = i + 2)
  {
    color_output(set_color, i);
    // Check for button presses
    int color_change_button_is_pressed = check_if_color_change_pressed();
    int color_strobe_button_is_pressed = check_if_color_strobe_pressed();
    int check_if_panik_mode_activated = check_panik();

    // If color change button is pressed, changes variable to next color and continues
    if(color_change_button_is_pressed == true)
    {
      set_color = colorChange(set_color);
    }

    // If strobe effect button is pressed, does effect, returns current color, and restarts color pulsing
    if(color_strobe_button_is_pressed == true)
    {
      colorStrobe();
      return set_color;
      break;
    }

    // If device is turned on its side, starts pulsing rapidly in red, returns set_color when upright again, and restarts
    if(check_if_panik_mode_activated == true)
    {
      panikMode();
      return set_color;
      break;
    }

    delay(10);
  }

  // Decreasing light
  for(int i = 0; i < 255; i = i + 2)
  {
    color_output(set_color, 255 - i);
    // Check for button presses
    int color_change_button_is_pressed = check_if_color_change_pressed();
    int color_strobe_button_is_pressed = check_if_color_strobe_pressed();
    int check_if_panik_mode_activated = check_panik();

    // If color change button is pressed, changes variable to next color and continues
    if(color_change_button_is_pressed == true)
    {
      set_color = colorChange(set_color);
    }

    // If strobe effect button is pressed, does effect, returns current color, and restarts color pulsing
    if(color_strobe_button_is_pressed == true)
    {
      colorStrobe();
      return set_color;
      break;
    }

    // If device is turned on its side, starts pulsing rapidly in red, returns set_color when upright again, and restarts
    if(check_if_panik_mode_activated == true)
    {
      panikMode();
      return set_color;
      break;
    }
    
    delay(10);
  }

  return set_color;
}

// Different pin output combinations for different colors during idle pulsing loops
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
    // Allows for you to keep pressing button without issue
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

int check_if_color_strobe_pressed()
{
  int color_strobe_pressed = digitalRead(colorEffect);
  int color_strobe_is_pressed;

  if(color_strobe_pressed == 0)
  {
    // Allows for you to keep pressing button without issue
    while(color_strobe_pressed == 0)
    {
      color_strobe_pressed = digitalRead(colorEffect);
      continue;
    }
    return color_strobe_is_pressed = true;
  }
  else
  {
    return color_strobe_is_pressed = false;
  }
}

// Change the current color setting while idling
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

// Quickly strobes through red, green, and blue, respectively
void colorStrobe()
{
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  int increment = 5;

  for(int i = 0; i < 255; i = i + increment)
  {
    analogWrite(redLED, i);
    delay(10);
  }

  for(int i = 0; i < 255; i = i + increment)
  {
    analogWrite(redLED, 255 - i);
    delay(10);
  }

  for(int i = 0; i < 255; i = i + increment)
  {
    analogWrite(greenLED, i);
    delay(10);
  }

  for(int i = 0; i < 255; i = i + increment)
  {
    analogWrite(greenLED, 255 - i);
    delay(10);
  }

  for(int i = 0; i < 255; i = i + increment)
  {
    analogWrite(blueLED, i);
    delay(10);
  }

  for(int i = 0; i < 255; i = i + increment)
  {
    analogWrite(blueLED, 255 - i);
    delay(10);
  }

  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
}

int check_panik()
{
  int current_reading = 0;
  int running_total = 0;
  int time_to_panik;

  for(int i = 0; i < 20; i++)
  {
    current_reading = digitalRead(tiltSwitch);
    running_total = current_reading + running_total;
  }

  if(running_total > 14)
  {
    time_to_panik = true;
    return time_to_panik;
  }
  else
  {
    time_to_panik = false;
    return time_to_panik;
  }
}

int panikMode()
{
  int time_to_panik = check_panik();
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  while(time_to_panik == true)
  {
    time_to_panik = check_panik();

    digitalWrite(redLED, HIGH);
   
    delay(250);

    time_to_panik = check_panik();

    digitalWrite(redLED, LOW);

    delay(250); 
  }

}