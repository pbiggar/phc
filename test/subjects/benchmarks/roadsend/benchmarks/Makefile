TOPLEVEL      = ../
MY_TESTDIR    = benchmarks/tests/
MY_REGRESSIONDIR    = benchmarks/regression/
MY_TESTOUTDIR = benchmarks/testoutput/
DOTEST        = ./dotest

check : 
	-rm -rf $(TOPLEVEL)$(MY_TESTOUTDIR)
	-mkdir $(TOPLEVEL)$(MY_TESTOUTDIR)
	@(cd $(TOPLEVEL) && $(DOTEST) $(MY_TESTDIR) $(MY_TESTOUTDIR))

regression : 
	-rm -rf $(TOPLEVEL)$(MY_TESTOUTDIR)
	-mkdir $(TOPLEVEL)$(MY_TESTOUTDIR)
	@(cd $(TOPLEVEL) && $(DOTEST) $(MY_REGRESSIONDIR) $(MY_TESTOUTDIR))


clean :
	-rm -rf testoutput

.PHONY: regression