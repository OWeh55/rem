#
COPT= -O3 -Wall -g --std=c++11
#
%.cpp:%.ag
	AppGen $*.ag $*.cpp

%.o: %.cpp
	g++ $(COPT) -c $*.cpp

%.o: %.c
	gcc $(COPT) -c $*.c

%:	%.o 
	g++ $(COPT) -o $* $*.o

OBJECTS=rem.o regexp.o regexp_after.o regexp_before.o regexp_match.o trim.o regexp_exclude.o translate.o filter.o

rem: $(OBJECTS)
	g++ $(COPT) -o rem $(OBJECTS)
# -lefence

test: rem rtest
	rtest

regexp_test: regexp_test.cpp regexp.o regexp_before.o regexp_after.o
	g++ $(COPT) -o regexp_test regexp_test.cpp regexp.o regexp_before.o regexp_after.o

clean_files:
	rm -f *.o rem *.orig *~

clean: clean_files dep

ASTYLE := astyle
# format options for beautifier
ASTYLE_OPT = --style=gnu --unpad-paren --pad-header --pad-oper --indent-namespaces --indent=spaces=2 --convert-tabs --align-pointer=type --align-reference=type

format:
	$(ASTYLE) $(ASTYLE_OPT) *.cpp      
	$(ASTYLE) $(ASTYLE_OPT) *.h
	$(ASTYLE) $(ASTYLE_OPT) *.ag

dep:
	-rm depend 
	touch depend
	$(CXX) -M $(COPT) $(INCLUDE) *.cpp >> depend    

-include depend
