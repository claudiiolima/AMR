CC = /mingw64/bin/cc
CXX = /mingw64/bin/c++
INCLUDE_PATH = -I . -I ../Middleware/ -I ../Middleware/Adapter/ -I ../Middleware/Debouncer/ -I ../Middleware/Proxy/ -I ./mock/
INCLUDE_GTEST_PATH = -I ../Tools/gtest/googletest/include/
CCFLAGS = -Wall $(INCLUDE_PATH) $(INCLUDE_GTEST_PATH) -c
CXXFLAGS = -Wall $(INCLUDE_PATH) $(INCLUDE_GTEST_PATH) -c
LXXFLAGS =
OBJECTS = ./obj/digital_input.o ./obj/gtest_main.o ./obj/mock_core.o ./obj/test_digital_input.o
GTEST = ../Tools/gtest/build/lib/libgtest.a
TARGET = gtest_main

$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/digital_input.o: ../Middleware/Proxy/digital_input.cpp
	$(CXX) $(CXXFLAGS) ../Middleware/Proxy/digital_input.cpp -o ./obj/digital_input.o
./obj/test_digital_input.o: ./test_digital_input.cpp
	$(CXX) $(CXXFLAGS) ./test_digital_input.cpp -o ./obj/test_digital_input.o
./obj/mock_core.o: ./mock/mock_core.c
	$(CC) $(CCFLAGS) ./mock/mock_core.c -o ./obj/mock_core.o
./obj/gtest_main.o: ./gtest_main.cpp
	$(CXX) $(CXXFLAGS) ./gtest_main.cpp -o ./obj/gtest_main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)