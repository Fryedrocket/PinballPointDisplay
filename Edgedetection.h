
typedef enum {
    rising_edge,
    falling_edge,
    change
} MODE;

uint8_t state, laststate;
bool pinDetection(uint8_t pin, MODE mode) {
    laststate = state;
    state = digitalRead(pin);
    if (mode == rising_edge) {
        if (state == HIGH && laststate == LOW) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (mode == falling_edge) {
        if (state == LOW && laststate == HIGH) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (mode == change) {
        if (state != laststate) {
            return true;
        }
        else {
            return false;
        }
    }
}