
typedef enum {
  rising_edge,
  falling_edge,
  change
} MODE;

bool pinDetection(uint8_t pin, MODE mode) {
  int laststate = state;
  int state = digitalRead(pin);
  if (mode == rising_edge) {
    if (state == HIGH && laststate == low) {
      return true;
    } else {
      return false;
    }
  } else if (mode == falling_edge) {
    if (state == LOW && laststate == HIGH) {
      return true;
    } else {
      return false;
    }
  } else if (mode == change) {
    if (state != laststate) {
      return true;
    } else {
      return false;
    }
  }
}