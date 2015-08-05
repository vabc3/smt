TARGETS		= img logo text
CC			= armv6j-hardfloat-linux-gnueabi-gcc
CFLAGS		= -Ilibpcd -Wall
LDFLAGS		= -lpthread -lm
# precompiled static lib
LIBWP		= ../wiringPi/wiringPi/libwiringPi.a
# target machine location
TARGETHOST	= root@pi
TESTTARGET	= text

.PHONY : all clean deploy $(LIBWP)

all     : $(TARGETS)

clean   :
	rm -rf $(TARGETS) *.o *~

deploy  : all
	scp $(TESTTARGET) $(TARGETHOST):deploy/

test	: deploy
	ssh $(TARGETHOST) deploy/$(TESTTARGET)

img 	: img.o pipcd.o PCD8544.o $(LIBWP)

text	: text.o pipcd.o PCD8544.o $(LIBWP)

logo	: logo.o pipcd.o PCD8544.o $(LIBWP)

PCD8544.o : libpcd/PCD8544.c
	$(CC) $(CFLAGS) -c $< -o $@ 