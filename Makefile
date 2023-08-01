CPP := g++
CPPFLAGS := -I include/ -L lib/ -mwindows
LIBFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC_FILES := src/*.cpp

ICON_DATA := dev_resources/icon_data.res

EXEC := "Orbital Prospector.exe"

all: icon
	$(CPP) $(SRC_FILES) -o bin/$(EXEC) ${ICON_DATA} -O3 $(CPPFLAGS) $(LIBFLAGS)

debug:
	$(CPP) $(SRC_FILES) -o bin/$(EXEC) -O3 $(CPPFLAGS) $(LIBFLAGS) -g

run:
	cd bin && ./$(EXEC)

icon:
	windres dev_resources/icon_data.rc -O coff -o ${ICON_DATA}
