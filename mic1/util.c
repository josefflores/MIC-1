#include "util.h"

/* passed an array of bytes of 16 ascii 1s and 0s */
/* and a final 17th NULL byte, and converts the   */
/* information into a true binary integer         */

int btoi(char *mem_loc) {
  int i, result;

  result = 0;

  for (i = 0; i < 16; i++) {
    if (mem_loc[i] == '1')
      result += power2[15 - i];
  }
  return result;
}

/* passed an array of bytes of 16 ascii 1s and 0s */
/* and a final 17th NULL byte, and converts the   */
/* information into a true char (8 bit ascii)     */
/* by skipping the first 8 bytes and converting   */
/* the last 8                                     */

char btoc(char *mem_loc) {
  int i, result;

  result = 0;

  for (i = 8; i < 16; i++) {
    if (mem_loc[i] == '1')
      result += power2[15 - i];
  }
  return ((char)result);
}

/* passed a memory location and a true binary char */
/* will fill low order 8 bit memory location with  */
/* 1s and 0s corresponding to the ascii character  */

int True_ascii_to_mem_ascii(char *mem_location, char *character) {
  int i;

  for (i = 0; i < 16; i++) {
    mem_location[i] = '0';
  }
  mem_location[16] = '\0';
  for (i = 8; i < 16; i++) {
    if (power2[15 - i] & (*character)) {
      mem_location[i] = '1';
    }
  }
  return 1;
}

void Set_blocking_io(void) {
  if (fcntl(0, F_SETFL, original_stdin_channel_flags) == -1) {
    perror("reset fcntl error: ");
    exit(2);
  }
}

void Set_nonblocking_io(void) {
  if (fcntl(0, F_SETFL, nonblock_stdin_channel_flags) == -1) {
    perror("set blocking fcntl error: ");
    exit(2);
  }
}
