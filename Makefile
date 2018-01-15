

all: zero_brightness_fixer.cpp
	g++ -g -Wall -o zero_brightness_fixer zero_brightness_fixer.cpp

clean: 
	$(RM) zero_brightness_fixer
