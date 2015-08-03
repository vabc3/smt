TARGETS	= run
CC		= armv6j-hardfloat-linux-gnueabi-gcc

.PHONY : all clean deploy

all     : $(TARGETS)

clean   :
	rm -rf $(TARGETS) *.o *~

deploy  : all
	scp $(TARGETS) $(TM):deploy/

test	: deploy
	ssh $(TM) deploy/run

run     : run.o
