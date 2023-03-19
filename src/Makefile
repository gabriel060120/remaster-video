SOURCE := upscale_main.c
OBJ    := $(subst .c,.o,$(SOURCE))
EXEC := main
PYTHON3VERSION  := 3.10
PYTHON3NAME     := python$(PYTHON3VERSION)
PYTHON3INCLPATH := /usr/include/$(PYTHON3NAME)
$(RM) := rm -f

all: CPPFLAGS += -l$(PYTHON3NAME)
all: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(EXEC) -l$(PYTHON3NAME)

%.o: CPPFLAGS += -I$(PYTHON3INCLPATH) $(shell $(PYTHON3NAME)-config --ldflags)


.PHONY: clean
clean:
	$(RM) $(EXEC)
	$(RM) *.o
