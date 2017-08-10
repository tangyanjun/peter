CC =/opt/buildroot-2012.08/arm920t/usr/bin/arm-linux-gcc
objs   =  serial.o analyze.o test.o
srcs   =  serial.c analyze.c test.c

gps: $(objs)
	$(CC) -o gps $(objs)
	@make clean

test.o: $(srcs) gps.h
	$(CC) -c $(srcs)

serial.o: serial.c
	$(CC) -c serial.c

analyze.o: analyze.c gps.h
	$(CC) -c analyze.c

clear:
	@rm  gps

	.PHONY: clean
clean:
	@rm *.o
