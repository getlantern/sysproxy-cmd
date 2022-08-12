#include <errno.h>
#ifndef _WIN32
#include <stdbool.h>
#endif

#ifdef DARWIN
int setUid();
int elevate(char *path, char *prompt, char *iconPath);
#endif

#ifdef _WIN32
void setupSystemShutdownHandler();
#endif

int show(void);
int toggleProxy(bool turnOn, const char *host, const char *port);

enum RET_ERRORS {
  RET_NO_ERROR = 0,
  INVALID_FORMAT = 1,
  NO_PERMISSION = 2,
  SYSCALL_FAILED = 3,
  NO_MEMORY = 4
};
