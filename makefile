EXEC = Predator_Prey

CC = g++

CCFLAGS = -c
CCFLAGS += -g
CCFLAGS += -std=c++0x
CCFLAGS += -Wall
CCFLAGS += -Wextra
CCFLAGS += -pedantic-errors

LFLAGS = 

SRCS = ${wildcard *.cpp}
OBJS = ${SRCS:.cpp=.o}

all: ${EXEC}

# link
${EXEC}: ${OBJS}
	${CC} ${LFLAGS} ${OBJS} -o ${EXEC}

# pull in dependency info for *existing* .o files
-include ${OBJS:.o=.d}

# http://scottmcpeak.com/autodepend/autodepend.html
# compile and generate dependency info; all prereqs listed also become
# command-less, prereq-less targets
# 	sed:	strip the target (everything before the colon)
# 	sed:	remove any continuation backslashes
# 	fmt -1:	list words one per line
# 	sed:	strip leading spaces
# 	sed:	add trailing colons
%.o: %.cpp
	${CC} ${CCFLAGS} $<
	${CC} -MM ${CCFLAGS} $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	rm -f ${OBJS} ${OBJS:.o=.d} ${EXEC}
