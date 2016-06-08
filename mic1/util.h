//  DEFINE GUARD
#ifndef MIC1_CLOCK_H
#define MIC1_CLOCK_H

//  INCLUDES
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "globals.h"
#include "variables.h"

//  DECLARATIONS
void Set_blocking_io(void);
void Set_nonblocking_io(void);
void Set_blocking_io(void);
void Set_nonblocking_io(void);
char btoc(char *mem_loc);
int btoi(char *mem_loc);
int True_ascii_to_mem_ascii(char *mem_location, char *character);

//  END DEFINE GUARD
#endif