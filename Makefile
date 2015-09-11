TARGET        := node
TARGET_TEST   := node_test
SOURCE_DIR    := source
OBJ_DIR       := obj
INCLUDE_DIR   := include
TEST_DIR		  := test
OBJ_TEST_DIR  := obj
BIN_DIR       := bin
MAIN_SOURCE		:= main

SOURCE_EXT    := cpp
SOURCES       := $(shell find $(SOURCE_DIR) -type f -name *.$(SOURCE_EXT))
OBJECTS       := $(patsubst $(SOURCE_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.$(SOURCE_EXT)=.o))
SOURCES_TESTS := $(shell find $(TEST_DIR) -type f -name *.$(SOURCE_EXT))
OBJECTS_TESTS := $(patsubst $(TEST_DIR)/%,$(OBJ_TEST_DIR)/%,$(SOURCES_TESTS:.$(SOURCE_EXT)=.o))

LIB           :=
INC           := -I $(INCLUDE_DIR)

CXX           := g++-4.9
CXXFLAGS      := -g -W -O3 -pedantic

RM            := rm -f

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET) $(LIB)"; $(CXX) $^ -o $(BIN_DIR)/$(TARGET) $(LIB)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.$(SOURCE_EXT)
	@mkdir -p $(OBJ_DIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

run: $(TARGET)
	./$(BIN_DIR)/$(TARGET)

clean:
	@echo " Cleaning...";
	$(RM) -r $(OBJ_DIR) $(BIN_DIR)

run_tests: $(TARGET) $(OBJECTS_TESTS)
	@echo " Linking Tests..."
	@echo " $(RM) $(OBJ_DIR)/$(MAIN_SOURCE).o"; $(RM) $(OBJ_DIR)/$(MAIN_SOURCE).o
	@echo " $(CXX) $(filter-out obj/$(MAIN_SOURCE).o,$(OBJECTS)) $(OBJECTS_TESTS) -o $(TARGET_TEST) $(LIB) -lcppunit"; $(CXX) $(filter-out obj/$(MAIN_SOURCE).o,$(OBJECTS)) $(OBJECTS_TESTS) -o $(BIN_DIR)/$(TARGET_TEST) $(LIB) -lcppunit
	@echo ""
	./$(BIN_DIR)/$(TARGET_TEST)

$(OBJ_TEST_DIR)/%.o: $(TEST_DIR)/%.$(SOURCE_EXT)
	@mkdir -p $(OBJ_TEST_DIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

.PHONY: clean

