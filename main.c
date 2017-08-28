#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "common.h"

static const char* proxyHost;
static const char* proxyPort;

void usage(const char* binName)
{
  printf("Usage: %s [show | on | off <proxy host> <proxy port> [-wait-and-cleanup]]\n", binName);
  exit(INVALID_FORMAT);
}

void handleSignals(int signal)
{
  toggleProxy(false, proxyHost, proxyPort);
}

void setupSignals()
{
  // Register signal handlers to make sure we turn proxy off no matter what
  signal(SIGABRT, handleSignals);
  signal(SIGFPE, handleSignals);
  signal(SIGILL, handleSignals);
  signal(SIGINT, handleSignals);
  signal(SIGSEGV, handleSignals);
  signal(SIGTERM, handleSignals);
  signal(SIGSEGV, handleSignals);
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
    int retval = INVALID_FORMAT;
    proxyHost = argv[2];
    proxyPort = argv[3];
    if (strcmp(argv[1], "on") == 0) {
      retval = toggleProxy(true, proxyHost, proxyPort);
      if (argc >= 5) {
        if (strcmp(argv[4], "-wait-and-cleanup") == 0) {
          setupSignals();
#ifdef _WIN32
          setupSystemShutdownHandler()
#endif
          // wait for input from stdin (or close), then toggle off
          getchar();
          retval = toggleProxy(false, proxyHost, proxyPort);
        } else {
          usage(argv[0]);
        }
      }
    } else if (strcmp(argv[1], "off") == 0) {
      retval = toggleProxy(false, proxyHost, proxyPort);
    } else {
      usage(argv[0]);
    }
    return retval;
  }
  // code never reaches here, just avoids compiler from complaining.
  return RET_NO_ERROR;
}
