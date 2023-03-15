SOURCE := upscale_main.c
EXEC := main
PYTHON3VERSION  := 3.10
PYTHON3NAME     := python$(PYTHON3VERSION)
PYTHON3INCLPATH := /usr/include/$(PYTHON3NAME)
$(RM) := rm -f

all: CPPFLAGS += -I$(PYTHON3INCLPATH) -l$(PYTHON3NAME)
all:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(EXEC) $(SOURCE)


.PHONY: clean
clean:
	$(RM) $(EXEC)
