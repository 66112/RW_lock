my_rw:rw.cc
	g++ -o $@ $^ -lpthread -g -fpermissive
.PHONY:clean
clean:
	rm -f my_rw
