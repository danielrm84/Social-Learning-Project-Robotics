

VPATH = SOURCES:../include/sources

CC=g++
CFLAGS=-c 

SOURCES=agent.cpp agentFunctions.cpp sensor.cpp sensorFunctions.cpp \
neural_network.cpp Genetic_Algorithm.cpp geneticFunctions.cpp perceptron.cpp

MAIN=main.cpp

OBJECTS0=$(SOURCES:.cpp=.o) $(MAIN:.cpp=.o)

EXECUTABLE0=main

$(EXECUTABLE0): $(OBJECTS0)
	$(CC) $(OBJECTS0) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o main