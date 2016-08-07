# zero_brigthness_fixer
The inotify enabled app to fix zero brightness drop in Linux.

Works in Debian Jessie, but will also work with any other Linux (Ubuntu, Centos, Fedora, Arch) with working brightness control via sysfs, for example in my case the file is /sys/class/backlight/intel_backlight/brightness

The minimal or desired brightness level can be set by changing DEFAULT_BRIGHTNESS parameter in source code or by setting this value when executed.

## Compile
```
make
```

## Usage
```
./zero_brigtness_fixer pathname [minimal_brightness] [default_brightness]
```
where ***minimal_brigthness*** - the level of brightness which should be increased to ***default_brightness***. These two parameters are optional, default values are 0 and 47 respectively; ***pathname*** - path to sysfs file to configure backlight brightness level, usually /sys/class/backlight/intel_backlight/brightness on Intel machines.

Please note that you can have a different file path instead of /sys/class/backlight/intel_backlight/brightness to find it on your machine simply run:

```
find /sys/class -name "*backlight*"
```
or
```
find /sys/class -name "*brightness*"
```

## Run example
```
./zero_brigtness_fixer /sys/class/backlight/intel_backlight/brightness
```
  

