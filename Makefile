CXX=clang++
FLEX=flex
BISON=bison

# Directories
SRC=src
BIN=bin
GEN=gen

# Input files
CXXFILES=$(SRC)/driver.cpp
FLEXFILES=$(SRC)/scanner.ll
BISONFILES=$(SRC)/parser.ypp

# Output files
BISON_TARGET=$(GEN)/parser.cpp
FLEX_TARGET=$(GEN)/scanner.cpp
OFILES=$(CXXFILES:$(SRC)/%.cpp=$(BIN)/%.o) \
	$(FLEX_TARGET:$(GEN)/%.cpp=$(BIN)/%.o) \
	$(BISON_TARGET:$(GEN)/%.cpp=$(BIN)/%.o)
DEPFILES=$(OFILES:%.o=%.d)

CXXFLAGS=-g -O2 -std=c++14 -I$(GEN) -I$(GEN)/include -Iinclude -MP -MMD
#LDFLAGS=-g
LFLAGS=-+ --header
BISONFLAGS=--defines=$(GEN)/include/parser.hpp

TARGET=lisplike

print-%: ; @echo $*=$($*)

all: $(TARGET)

-include $(DEPFILES)
$(TARGET): $(CXXFILES) $(FLEX_TARGET) $(BISON_TARGET) | $(BIN)
	$(CXX) $(CXXFLAGS) $(CXXFILES) $(FLEX_TARGET) $(BISON_TARGET) -o $(TARGET)

$(FLEX_TARGET): $(BISON_TARGET) $(FLEXFILES)
	$(FLEX) -o $(FLEX_TARGET) $(LFLAGS) $(FLEXFILES)

$(BISON_TARGET): $(BISONFILES) | $(GEN)
	$(BISON) -o $(BISON_TARGET) $(BISONFLAGS) $(BISONFILES)

$(GEN):
	@mkdir -vp $(GEN)/include

$(BIN):
	@mkdir -vp $(BIN)

.PHONY: clean
clean:
	$(RM) -rf $(TARGET) $(BIN) $(GEN)
