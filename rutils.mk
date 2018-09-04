_RUTILS =  network.o string.o file.o math.o

RUTILS = $(patsubst %,$(RUTILS_DIR)%, $(_RUTILS))

rutils.a: $(RUTILS)
	$(AR) rcs $@ $^
	ranlib $@
