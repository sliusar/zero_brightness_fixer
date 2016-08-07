# zero_brigthness_fixer
The inotify enabled app to fix brightness drop in Linux.

Works in Debian Jessie, but will also work with any other Linux (Ubuntu, Centos, Fedora, Arch) with working acpi brightness control via sysfs.

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
./zero_brigtness_fixer /sys/class/backlight/intel_backlight/brightness 10 100
```
So if the brightness will drop below 10 it would be automatically set to 100.

Application should be run as ***root***, or otherwise before it is executed by nonprivileged user just run this as root:
```
chmod 777 /sys/class/backlight/intel_backlight/brightness
```

Application sends all output to syslog, to be more exact it sends it wih LOG_USER flag so you can find the logs in /var/log/user.log. Critical errors are sent to stderr and application exits.
  

