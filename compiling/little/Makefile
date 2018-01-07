CC := gcc
RM := rm -f
APPNAME := little

run: $(APPNAME)
	./$<

$(APPNAME): $(APPNAME).lex.c $(APPNAME).yacc.c generateParseTree.c
	$(CC) $(APPNAME).lex.c $(APPNAME).yacc.c generateParseTree.c -o $@

$(APPNAME).yacc.c : $(APPNAME).y
	@yacc -d $< -o $(APPNAME).yacc.c
	@# $(RM) $(APPNAME).yacc.c.h
	@# why?
	@$(RM) $(APPNAME).yahh

$(APPNAME).yacc.h: $(APPNAME).y
	yacc -d $< -o $(APPNAME).yacc
	@$(RM) $(APPNAME).yacc

$(APPNAME).lex.c: $(APPNAME).l $(APPNAME).yacc.h
	lex -o $(APPNAME).lex.c $<

# for dubug purpose only
eog: graph.svg
	eog graph.svg

graph.svg: graph.dot
	dot -Tsvg -o graph.svg graph.dot

clean:
	$(RM) $(APPNAME).lex.c $(APPNAME).yacc.c $(APPNAME).yacc.h $(APPNAME) graph.dot graph.svg
