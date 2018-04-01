_RUTILS = process.o network.o string.o file.o

RUTILS = $(patsubst %,$(RUTILS_DIR)%, $(_RUTILS))

rutils.a: $(RUTILS)
	$(AR) rcs $@ $^
	ranlib $@
