SOURCE := upscale.c lerImagem.cpp
OBJ    := $(addsuffix .o,$(basename $(SOURCE)))
EXEC := main
PYTHON3VERSION  := 3.10
PYTHON3NAME     := python$(PYTHON3VERSION)
OPENCV          := opencv4
PYTHON3INCLPATH := /usr/include/$(PYTHON3NAME)
OPENCV4INCLPATH := /usr/include/$(OPENCV)

INCLUDECPPFLAGS := $(addprefix -I,$(PYTHON3INCLPATH) $(OPENCV4INCLPATH))
LINKLIBS := -l$(PYTHON3NAME) $(shell pkg-config --libs $(OPENCV))
$(RM) := rm -f

all: CPPFLAGS += -l$(PYTHON3NAME)
all: $(OBJ)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(EXEC) $(LINKLIBS)

%.o: CPPFLAGS += $(INCLUDECPPFLAGS) $(shell $(PYTHON3NAME)-config --ldflags)


.PHONY: clean
clean:
	$(RM) $(EXEC)
	$(RM) *.o
