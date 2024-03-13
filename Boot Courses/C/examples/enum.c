#include <stdio.h>

typedef enum Colors {
  RED,
  BLUE,
  GREEN,
} colors_t;

int main() {
  colors_t color = BLUE;

  // Should we let them do this once without any breaks?
  //    So that they can see what this does?
  //    It is usually pretty instructive since you completely
  //    don't expect that terrible behavior LUL
  //
  // Could do with quiz and ask what they think after we have
  // introduced both concepts?
  switch (color) {
  case RED:
    printf("RED\n");
  case BLUE:
    printf("BLUE\n");
  case GREEN:
    printf("GREEN\n");
  default:
    printf("Unknown color\n");
  }

  printf("==== with breaks ====\n");
  switch (color) {
  case RED:
    printf("RED\n");
    break;
  case BLUE:
    printf("BLUE\n");
    break;
  case GREEN:
    printf("GREEN\n");
    break;
  default:
    printf("Unknown color\n");
    break;
  }
}
