# zero_brigthness_fixer
The inotify enabled app to fix zero brightness drop in Linux.

Works in Debian Jessie, but will also work with any other Linux (Ubuntu, Centos, Fedora, Arch) with working brightness control via sysfs, for example in my case the file is /sys/class/backlight/intel_backlight/brightness

The minimal or desired brightness level can be set by changing DEFAULT_BRIGHTNESS parameter in source code or by setting this value when executed.

Compile:
  make
  
Run:
  ./zero_brigtness_fixer /sys/class/backlight/intel_backlight/brightness

