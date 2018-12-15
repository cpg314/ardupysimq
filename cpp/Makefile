libs=LCD Relay ArduinoSim SoftwareSerialSim Time GSM Queue SDSim RFID Button WDT Buzzer RFID
cpp=$(foreach d,$(libs),$(wildcard lib/$(d)/*.cpp)) $(wildcard src/*.cpp)
obj=$(addprefix obj/,$(cpp:.cpp=.o))
CPPFLAGS=-x c++ -g -DSIMULATOR $(addprefix -Ilib/,$(libs))  -Isrc -Wno-write-strings -std=c++11
arduino:
	ino build
	python checkSize.py
obj/sketch.o: src/sketch.ino src/config.h
	mkdir -p obj/$(dir $<)
	g++ $(CPPFLAGS) -c $< -o $@
simulator: obj/sketch.o $(obj)
	g++ $^ -lzmq -g -o simulator
obj/%.o: %.cpp src/config.h
	mkdir -p obj/$(dir $<)
	g++ $(CPPFLAGS) -c $<  -o $@
upload:
	ino upload -p /dev/ttyUSB0
serial:
	picocom -b 9600 /dev/ttyUSB0
	#ino serial -p /dev/ttyUSB0
clean:
	ino clean
	rm -R obj
	rm simulator
all: arduino simulator
