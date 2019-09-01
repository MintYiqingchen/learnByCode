CCFLAG =  -std=c++11
CC = g++

.PHONY: all clean

objective = timestampTcpClient timestampTcpServer

all: $(objective)

$(objective): % : %.cc net_utils.cc net_utils.h
	$(CC) $(CCFLAG) $< net_utils.cc -o $@

clean:
	-rm *.o
	-rm $(objective) 