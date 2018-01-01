CC := gcc
RM := rm -f
APPNAME := calculator

run: $(APPNAME)
	./$<

$(APPNAME): $(APPNAME).lex.c $(APPNAME).yacc.c
	$(CC) $(APPNAME).lex.c $(APPNAME).yacc.c -o $@

$(APPNAME).yacc.c : $(APPNAME).y
	yacc -d $< -o $(APPNAME).yacc.c
	# $(RM) $(APPNAME).yacc.c.h
	# why?
	$(RM) $(APPNAME).yahh

$(APPNAME).yacc.h: $(APPNAME).y
	yacc -d $< -o $(APPNAME).yacc
	$(RM) $(APPNAME).yacc

$(APPNAME).lex.c: $(APPNAME).l $(APPNAME).yacc.h
	lex -o $(APPNAME).lex.c $<


clean:
	$(RM) $(APPNAME).lex.c $(APPNAME).yacc.c $(APPNAME).yacc.h $(APPNAME)
