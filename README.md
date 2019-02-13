# zero_brightness_fixer

This small utilite fixes laptop brightness drop to zero in Linux. It doesn't consume any CPU since it waits for inode notifications (inotify mechanism), it can be used on any laptop without any battery penalty.

Tested in Debian Jessie, but will also work with any other Linux (Ubuntu, Centos, Fedora, Arch) with working acpi brightness control via sysfs.

```
./zero_brigtness_fixer pathname [minimal_brightness] [default_brightness]
```
where ***minimal_brigthness*** - the level of brightness which should be increased to ***default_brightness***. These two parameters are optional, default values are 0 and 47 respectively; ***pathname*** - path to sysfs file to configure backlight brightness level, usually */sys/class/backlight/intel_backlight/brightness* on Intel machines.

The path to the acpi control file can be different than */sys/class/backlight/intel_backlight/brightness*, to find it simply run `
find /sys/class/ /sys/devices/ -name "*backlight*"`

Application sends all output to syslog wih LOG_USER flag, so you can find the logs in */var/log/user.log*. Critical errors are sent to stderr and application exits.

## Installation

Make sure to have gcc (g++) installed, e.g. in Debian/Ubuntu run `sudo apt-get install g++` to install it, then perform the following actions:

```
git clone https://github.com/nuccy/zero_brightness_fixer.git
cd zero_brightness_fixer
make
```

## Usage example (standalone)
```
./zero_brigtness_fixer /sys/class/backlight/intel_backlight/brightness 10 100
```
So if the brightness will drop below 10 it would be automatically set to 100.

Application should be run as **root**, or otherwise before it is executed by nonprivileged user just adjust the permissions:

```
chmod 777 /sys/class/backlight/intel_backlight/brightness
```
  
## Usage example (systemctl)

Edit the *zero_brightness_fixer.service* to include correct ***pathname*** to the brightness control sysfs file and desired ***minimal_brightness*** and ***default_brightness*** values. Then run:

```
sudo mv zero_brightness_fixer /usr/local/bin/
sudo mv zero_brightness_fixer.service /etc/systemd/system/
sudo systemctl enable zero_brightness_fixer
sudo service zero_brightness_fixer start
```
The utilite will then run in the background and will be restarted after Linux startup.
