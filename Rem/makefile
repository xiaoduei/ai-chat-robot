LDFLAGS=-ljsoncpp -lcurl -lcrypto
INCLUDE=-Ispeech

Rem:rem.cc
	g++ -o $@ $^ $(INCLUDE) $(LDFLAGS) -std=c++11

.PHONY:clean
clean:
	rm -f Rem
