CXX=clang++
FLEX=flex
BISON=bison

# Directories
SRC=src
BIN=bin
GEN=gen

# Input files
CXXFILES=$(SRC)/driver.cpp $(SRC)/ast.cpp  $(SRC)/util.cpp $(SRC)/codegen.cpp
FLEXFILES=$(SRC)/scanner.ll
BISONFILES=$(SRC)/parser.ypp

# Output files
BISON_TARGET=$(GEN)/parser.cpp
BISON_XML=$(BISONFILES:$(SRC)/%.ypp=$(GEN)/%.xml)
BISON_HTML=$(BISON_XML:%.xml=%.html)
BISON_SHARE_DIR=/usr/share/bison
FLEX_TARGET=$(GEN)/scanner.cpp
OFILES=$(CXXFILES:$(SRC)/%.cpp=$(BIN)/%.o) \
	$(FLEX_TARGET:$(GEN)/%.cpp=$(BIN)/%.o) \
	$(BISON_TARGET:$(GEN)/%.cpp=$(BIN)/%.o)
DEPFILES=$(OFILES:%.o=%.d)

CXXFLAGS=-c -g -O0 -std=c++14 -I$(GEN) -I$(GEN)/include -Iinclude -MP -MMD -Wall \
	$(shell pkg-config --cflags uuid)
LDFLAGS=-g -lboost_system -lboost_filesystem \
	$(shell pkg-config --libs uuid)
LFLAGS=-+ --header
BISONFLAGS=--defines=$(GEN)/include/parser.hpp

TARGET=lisplike

print-%: ; @echo $*=$($*)

all: $(TARGET)

-include $(DEPFILES)
$(TARGET): gencode $(OFILES)
	$(CXX) $(LDFLAGS) $(OFILES) -o $(TARGET)

$(BIN)/%.o: $(SRC)/%.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: gencode
gencode: $(FLEX_TARGET) $(BISON_TARGET)

$(FLEX_TARGET:$(GEN)/%.cpp=$(BIN)/%.o): $(FLEX_TARGET) | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BISON_TARGET:$(GEN)/%.cpp=$(BIN)/%.o): $(BISON_TARGET) | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

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
	$(RM) -rf $(TARGET) $(BIN) $(GEN) $(BISON_XML)

.PHONY: html
html: | $(GEN)
	$(BISON) --xml=$(BISON_XML) $(BISONFILES)
	rm {location,position,stack}.hh parser.tab.{cpp,hpp}
	xsltproc $(BISON_SHARE_DIR)/xslt/xml2xhtml.xsl $(BISON_XML) > $(BISON_HTML)
