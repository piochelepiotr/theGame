CC=g++
MOC=moc
SOURCES=main.cpp
MOC_HEADERS=


CPPFLAGS=-Wall -Wextra -std=gnu++11 -fPIC 
INCDIRS=-I/home/piotr/Qt/5.8/gcc_64/include/
INCLIB=/home/piotr/Qt/5.8/gcc_64/lib
LDFLAGS=-L$(INCLIB)
LIBS=-lQt5Widgets -lQt5Core -lGL -lQt5Gui -lpthread
EXEC=game
MOC_SOURCES=$(MOC_HEADERS:.h=.moc.cpp)
OBJECTS=$(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)

all:$(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -Wl,-rpath,$(INCLIB) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o:%.cpp
	$(CC) $(CPPFLAGS) $(INCDIRS) -c $< -o $@

%.moc.cpp:%.h
	$(MOC) $(INCDIRS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.moc.cpp


