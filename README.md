# zero_brigthness_fixer
The inotify enabled app to fix zero brightness drop in Linux.

Works in Debian Jessie, but will also work with any other Linux (Ubuntu, Centos, Fedora, Arch) with working brightness control via sysfs, for example in my case the file is /sys/class/backlight/intel_backlight/brightness

The minimal or desired brightness level can be set by changing DEFAULT_BRIGHTNESS parameter in source code or by setting this value when executed.

## Compile
```bash
make
```
  
## Run

```bash
./zero_brigtness_fixer /sys/class/backlight/intel_backlight/brightness
```
  
Please note that you can have a different file path instead of /sys/class/backlight/intel_backlight/brightness to find your file to control brightness simply run:

```bash
find /sys/class -name "*backlight*"
```

or
```bash
find /sys/class -name "*brightness*"
```

