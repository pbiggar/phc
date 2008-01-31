ALLOWED_TARGETS	= clpa clpa-worker cilcc dbfind dbfindc dbkeys

OUTPUT_REDIR =
ifndef VERBOSE
OUTPUT_REDIR += > /dev/null
endif

all: build-interceptor build-cil build-libevent $(ALLOWED_TARGETS)

debug: build-interceptor build-cil build-libevent $(ALLOWED_TARGETS:=-debug)
profile: build-interceptor build-cil build-libevent $(ALLOWED_TARGETS:=-profile)
nativeprofile: build-interceptor build-cil build-libevent $(ALLOWED_TARGETS:=-nativeprofile)
clean: $(ALLOWED_TARGETS:=-clean)

#
# Add patterns to excluded.txt to remove files from the distribution.
# Note the distribution is built in clpa's parent directory.
#
distribution: 
	cd ..; zip -r saturn clpa -x@clpa/excluded.txt

realclean: clean
	@cd build-intercept && $(MAKE) clean
	-@cd libevent && test -f Makefile && $(MAKE) clean
	-rm -f libevent/config.status
	-@cd cil && test -f Makefile && $(MAKE) clean
	-rm -f cil/config.stamp
	make -C solve/minisat clean

build-interceptor:
	@cd build-intercept && $(MAKE)

cil/config.stamp:
	@cd cil && ./configure
	@touch cil/config.stamp

libevent/config.status:
	@cd libevent && ./configure
	@touch libevent/config.status

build-cil: cil/config.stamp
	@cd cil && $(MAKE)

build-libevent: libevent/config.status
	@cd libevent && $(MAKE)

$(ALLOWED_TARGETS):
	@echo -n "Compiling $@..."
	@$(MAKE) -f makefile-clpa \
		OBJ_NAME=$@ native $(OUTPUT_REDIR)
	@echo "done!"

%-debug:
	@echo -n "Compiling $* debug..."
	@$(MAKE) -f makefile-clpa \
		OBJ_NAME=$* debug $(OUTPUT_REDIR)
	@echo "done!"

%-profile:
	@echo -n "Compiling $* profile..."
	@$(MAKE) -f makefile-clpa \
		OBJ_NAME=$* PROFILE=1 $(OUTPUT_REDIR)
	@echo "done!"

%-nativeprofile:
	@echo -n "Compiling $* profile..."
	@$(MAKE) -f makefile-clpa \
		OBJ_NAME=$* native PROFILE=1 $(OUTPUT_REDIR)
	@echo "done!"

%-clean:
	@echo -n "Cleaning up $*..."
	@$(MAKE) -f makefile-clpa \
		OBJ_NAME=$* clean $(OUTPUT_REDIR)
	@echo "done!"
