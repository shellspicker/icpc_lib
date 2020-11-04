# 以下一般不需要改
PHONY: build rebuild all clean cleanall fake_all fake_clean fake_view
build: all
rebuild: cleanall build
all: init_all
	@$(MAKE) -f $(MAKEFILE) fake_all
clean: init_all
	@$(MAKE) -f $(MAKEFILE) fake_clean
cleanall: clean
	rm -f $(TARGET)
view: init_all
	@$(MAKE) -f $(MAKEFILE) fake_view
fake_all: $(TARGET)
fake_clean:
	rm -f *.orig *~ $(obj_all) $(obj_all:.o=.d)
fake_view:
	@echo $(foreach id,$(aimid_all),$(call debug,$(id)))
