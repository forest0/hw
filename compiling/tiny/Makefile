CC := gcc
CFLAGS := -g

RM := rm -f

OBJS := main.o scan.o utils.o parse.o

EXECUTABLE := tiny
INPUT := ./source.tny

PIC_FILE_BASENAME := syntaxTree
PIC_FILE_FORMAT   := svg
DOT_FILE := syntaxTree.dot
PIC_FILE := $(PIC_FILE_BASENAME).$(PIC_FILE_FORMAT)

PIC_VIEWER := eog # picture viewer

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c scan.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

scan.o: scan.c scan.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

parse.o: parse.c parse.h utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c utils.h globals.h
	$(CC) $(CFLAGS) -c $< -o $@

$(DOT_FILE):
ifneq ($(DOT_FILE), $(wildcard $(DOT_FILE)))
	@echo ">>>>>>>> no dot file detected, please generate it first <<<<<<<<"
endif

dot2pic: $(DOT_FILE)
	@dot -T $(PIC_FILE_FORMAT) -o $(PIC_FILE) $(DOT_FILE)

$(PIC_FILE): dot2pic

show_grapical_syntax_tree: $(PIC_FILE)
	$(PIC_VIEWER) $(PIC_FILE)

.PHONY: clean

clean:
	$(RM) $(OBJS) $(EXECUTABLE) $(DOT_FILE) $(PIC_FILE)
