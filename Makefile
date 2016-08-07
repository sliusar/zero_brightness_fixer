

all: zero_brigtness_fixer.cpp
	g++ -g -Wall -o zero_brigtness_fixer zero_brigtness_fixer.cpp

clean: 
	$(RM) zero_brigtness_fixer
