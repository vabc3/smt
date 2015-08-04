TARGETS		= img logo
CC			= armv6j-hardfloat-linux-gnueabi-gcc
CFLAGS		= -Ilibpcd -Wall
LDFLAGS		= -lpthread
# precompiled static lib
LIBWP		= ../wiringPi/wiringPi/libwiringPi.a
# target machine location
TARGETHOST	= root@pi
TESTTARGET	= img

.PHONY : all clean deploy $(LIBWP)

all     : $(TARGETS)

clean   :
	rm -rf $(TARGETS) *.o *~

deploy  : all
	scp $(TESTTARGET) $(TARGETHOST):deploy/

test	: deploy
	ssh $(TARGETHOST) deploy/$(TESTTARGET)

img 	: img.o pipcd.o PCD8544.o img.o $(LIBWP)

PCD8544.o : libpcd/PCD8544.c
	$(CC) $(CFLAGS) -c $< -o $@ 