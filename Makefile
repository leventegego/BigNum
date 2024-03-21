COMP = c:/mingw64/bin/g++
COMPILEROPTIONS = -g -Wall -m64
LINKEROPTIONS = -static
NAME = program

INCLUDE = 
LIB = 
LIBS = 

rwildcard=$(foreach d,$(wildcard $(patsubst %, %/*, $1)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

HDRS := $(call rwildcard, src, *.h)
SRCS := $(call rwildcard, src, *.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))
OUT = bin/$(NAME).exe



$(OUT): $(OBJS)
	$(COMP) $(OBJS) $(LIB) $(LIBS) $(LINKEROPTIONS) -o $(OUT)


obj/%.o: src/%.cpp $(HDRS)
	$(COMP) -c $< $(INCLUDE) $(COMPILEROPTIONS) -o $@

reset:
	-rm obj/*
	-rm $(OUT)

rebuild: reset $(OUT)

print:
	@echo srcs: $(SRCS)
	@echo objs: $(OBJS)
	@echo out: $(OUT)
	@echo $$PATH


run: $(OUT)
	$<
