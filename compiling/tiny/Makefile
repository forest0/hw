CC := gcc
CFLAGS := -g

RM := rm -f

objs := main.o scan.o utils.o parse.o viz.o
EXECUTABLE := tiny
INPUT := ./source.tny

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT)

$(EXECUTABLE): $(objs)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c scan.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

scan.o: scan.c scan.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

parse.o: parse.c parse.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

viz.o: viz.c viz.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) $(objs) $(EXECUTABLE)
