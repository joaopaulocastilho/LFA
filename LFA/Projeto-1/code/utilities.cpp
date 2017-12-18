#include"utilities.h"

void new_state_inc(char *state) {
  if (state[0] == '\0') {
    state[0] = 'A';
    state[1] = '\0';
  }
  else if (state[0] == 'Z') {
    state[0] = 'A';
    new_state_inc(state + sizeof(char));
  }
  else state[0]++;
}
