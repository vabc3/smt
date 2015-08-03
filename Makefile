TARGETS	= run
CC		= armv6j-hardfloat-linux-gnueabi-gcc
CFLAGS	= -Ilibpcd
LDFLAGS	= -lpthread
# precompiled static lib
LIBWP	= ../wiringPi/wiringPi/libwiringPi.a
# target machine location
TM		= root@pi

.PHONY : all clean deploy $(LIBWP)

all     : $(TARGETS)

clean   :
	rm -rf $(TARGETS) *.o *~

deploy  : all
	scp $(TARGETS) $(TM):deploy/

test	: deploy
	ssh $(TM) deploy/run

run     : run.o PCD8544.o $(LIBWP)

PCD8544.o : libpcd/PCD8544.c
	$(CC) $(CFLAGS) -c $< -o $@ 