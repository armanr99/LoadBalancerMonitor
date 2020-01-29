SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OUTPUT_DIR = output
EXECUTABLE_FILE = a.out

CC = g++
CFLAGS = -std=c++11 -I $(INCLUDE_DIR)

OBJECTS = $(BUILD_DIR)/main.o \
		  $(BUILD_DIR)/TrafficHandler.o \
		  $(BUILD_DIR)/Monitor.o \
		  $(BUILD_DIR)/Tools.o \
		  $(BUILD_DIR)/PathEdge.o \
		  $(BUILD_DIR)/Car.o


.PHONY: all build_objects make_output_dir make_build_dir clean

all: make_build_dir make_output_dir build_objects

build_objects: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE) -lpthread -lrt

make_build_dir:
	mkdir -p $(BUILD_DIR)

make_output_dir:
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR) *.o *.out


mainSensitivityList = $(SRC_DIR)/main.cpp \
					  $(INCLUDE_DIR)/TrafficHandler.hpp

TrafficHandlerSensitivityList = $(SRC_DIR)/TrafficHandler.cpp \
								$(INCLUDE_DIR)/TrafficHandler.hpp \
								$(INCLUDE_DIR)/Tools.hpp \
								$(INCLUDE_DIR)/PathEdge.hpp \
								$(INCLUDE_DIR)/constants.hpp \
								$(INCLUDE_DIR)/Car.hpp

MonitorSensitivityList = $(SRC_DIR)/Monitor.cpp \
						 $(INCLUDE_DIR)/Monitor.hpp

ToolsSensitivityList = $(SRC_DIR)/Tools.cpp \
					   $(INCLUDE_DIR)/Tools.hpp	

PathEdgeSensitivityList = $(SRC_DIR)/PathEdge.cpp \
					 	  $(INCLUDE_DIR)/PathEdge.hpp \
					 	  $(INCLUDE_DIR)/Monitor.hpp	

CarSensitivityList = $(SRC_DIR)/Car.cpp \
					 $(INCLUDE_DIR)/Car.hpp \
					 $(INCLUDE_DIR)/constants.hpp \
					 $(INCLUDE_DIR)/Tools.hpp
						 

$(BUILD_DIR)/main.o: $(mainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/TrafficHandler.o: $(TrafficHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/TrafficHandler.cpp -o $(BUILD_DIR)/TrafficHandler.o

$(BUILD_DIR)/Monitor.o: $(MonitorSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Monitor.cpp -o $(BUILD_DIR)/Monitor.o

$(BUILD_DIR)/Tools.o: $(ToolsSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Tools.cpp -o $(BUILD_DIR)/Tools.o

$(BUILD_DIR)/PathEdge.o: $(PathEdgeSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/PathEdge.cpp -o $(BUILD_DIR)/PathEdge.o

$(BUILD_DIR)/Car.o: $(CarSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Car.cpp -o $(BUILD_DIR)/Car.o