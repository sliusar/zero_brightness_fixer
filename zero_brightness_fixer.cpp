/*************************************************************************\
*                                                                        *
* Author: Nuccy                                                          *
* Github repo: https://github.com/nuccy/zero_brightness_fixer/           *
* Create: August, 2016                                                   *
*                                                                        *                                                                       *
\*************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/inotify.h>
#include <limits.h>
#include <iostream>
#include <syslog.h>

int DEFAULT_BRIGHTNESS = 47;
int MINIMAL_BRIGHTNESS = 0;

using namespace std;

static void checkFile(char* filename) {
  FILE* file = fopen (filename, "r+");
  int detected = 0;
  int val = 0;

  while (!feof (file))
  {
      fscanf (file, "%d", &val);
      if (val <= MINIMAL_BRIGHTNESS) { detected = 1; }
  }

  if (detected) {
    syslog(LOG_INFO, "Too low brightness (%d) detected, writing %d to %s", val, DEFAULT_BRIGHTNESS, filename);
    fprintf(file, "%d", DEFAULT_BRIGHTNESS);
  }
  fclose (file);
}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void doExit(int code) {
    closelog();
    exit(code);
}

int
main(int argc, char *argv[])
{
    openlog("zero_brightness_fixer", LOG_PID|LOG_CONS, LOG_USER);
    int inotifyFd, wd;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;
    if (argc < 2 || argc > 4 || strcmp(argv[1], "--help") == 0) { cerr << "Usage:\n\t" << argv[0] << " pathname [minimal_brightness] [default_brightness]\n" << endl; doExit(-1); }
    if (argc >= 3) {
        sscanf(argv[2], "%d", &MINIMAL_BRIGHTNESS);
        if (argc == 4) sscanf(argv[3], "%d", &DEFAULT_BRIGHTNESS);
        if (DEFAULT_BRIGHTNESS <= MINIMAL_BRIGHTNESS) {
          cerr << "Warning: default_brightness=" << DEFAULT_BRIGHTNESS << " shout be greater than minimal_brightness=" << MINIMAL_BRIGHTNESS << "! Setting default_brightness=" << MINIMAL_BRIGHTNESS + 1 << endl;
          DEFAULT_BRIGHTNESS = MINIMAL_BRIGHTNESS + 1; 
        }
    }

    inotifyFd = inotify_init();                 /* Create inotify instance */
    if (inotifyFd == -1) { cerr << "Error: inotify_init failed" << endl; doExit(-2); }

    wd = inotify_add_watch(inotifyFd, argv[1], IN_ALL_EVENTS);
    if (wd == -1) { cerr << "Error: inotify_add_watch failed" << endl; doExit(-2); }

    syslog(LOG_INFO, "Watching for brightness changes on %s, minimal_brightness=%d, default_brightness=%d", argv[1], MINIMAL_BRIGHTNESS, DEFAULT_BRIGHTNESS);
    checkFile(argv[1]);

    while (1) {                                  /* Read events forever */
        numRead = read(inotifyFd, buf, BUF_LEN);
        if (numRead == 0) { cerr << "Fatal: read() from inotify fd returned 0!" << endl; doExit(-3); }
        if (numRead == -1) { cerr << "Error: read returned -1" << endl; doExit(-4); }

        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            if (event->mask & IN_MODIFY) checkFile(argv[1]);
            p += sizeof(struct inotify_event) + event->len;
        }
    }
    doExit(EXIT_SUCCESS);
}
