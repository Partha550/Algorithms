EXTENSION := $(shell python-config --extension-suffix)
INCDIRS := $(shell python -m pybind11 --includes)
CFLAGS := -O3 -Wall -shared -fPIC $(INCDIRS) -std=c++11
BASENAMES := substringmatch subsequencematch
OBJECTS := $(foreach BASENAME, $(BASENAMES), $(BASENAME)$(EXTENSION))
.PHONY: all
all: $(OBJECTS)
define MAKE_SO
$(1)$(EXTENSION): $(1).cpp
	c++ $(CFLAGS) $(1).cpp -o $(1)$(EXTENSION)
endef
$(foreach i, $(BASENAMES), $(eval $(call MAKE_SO, $(i))))
