#include <stdlib.h>
#include <string.h>
#include "common.h"

void usage(const char* binName)
{
  printf("Usage: %s [show | on | off <proxy host> <proxy port>]\n", binName);
  exit(INVALID_FORMAT);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage(argv[0]);
  }

#ifdef DARWIN
  if (strcmp(argv[1], "setuid") == 0) {
    return setUid();
  }
#endif

  if (strcmp(argv[1], "show") == 0) {
    return show();
  } else {
    if (argc < 4) {
      usage(argv[0]);
    }
    if (strcmp(argv[1], "on") == 0) {
      return toggleProxy(true, argv[2], argv[3]);
    } else if (strcmp(argv[1], "off") == 0) {
      return toggleProxy(false, argv[2], argv[3]);
    } else {
      usage(argv[0]);
    }
  }
  // code never reaches here, just avoids compiler from complaining.
  return RET_NO_ERROR;
}
