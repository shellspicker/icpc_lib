# 以下是生成.d文件的4种方法.
# 形如%.d %.o: %.c something.h...
# 生成.d的原因是.h里面增加或减少包含其他.h文件, .d也能同步更新.
# 可能都要加上$(INCLUDE), 实例见mkdep.
#@$(CC) -MM -MF $@ -MT '$(patsubst %.d,%.o,$@) $@' $<
#@$(CC) -MM $< | awk '{print "$@", $$0}' > $@
#@$(CC) -MM $< | awk '{printf "%s %s\n", "$@", $$0}' > $@
#@$(CC) -MM $< | sed 's:^\(.*\):$@ \1:g' > $@
#@$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
#	sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' < $@.$$$$ > $@; \
#	rm -f $@.$$$$

# 约定俗成的根据源文件自动生成头文件依赖.
# func: get dependence rule file.
# args: (src, dep_file, compiler).
# src file like .c .cpp ...
# dependence rule file like .d .o: .c(pp) .h(pp) ...
define mkdep
	@set -e
	@rm -f $(2)
	@$(3) $(INCLUDE) -MM -MF $(2) -MT '$(patsubst %.d,%.o,$(2)) $(2)' $(1)
endef
%.d: %.c
	@$(call mkdep,$<,$@,$(CC))

%.d: %.cpp
	@$(call mkdep,$<,$@,$(CXX) -std=c++11)

space = $(none) # space ' '
# func: get suffix, match them in SRCEXT.
# args: (srcs).
get_suffix = $(filter $(suffix $(1)),$(SRCEXT))
# func: get suffix is .c or .cpp...
# args: (srcs, suffix).
define init_suffix
	ifeq ($(words $(call get_suffix,$(1))),1)
		$(2) = $(call get_suffix,$(1))
	endif
endef
# func: get compiler is gcc or g++.
# args: (suffix, compiler).
define init_compiler
	ifeq ($(1),.c)
		$(2) = $(CC)
	endif
	ifeq ($(1),.cpp)
		$(2) = $(CXX)
	endif
endef

# 按照源文件类型获得后缀和编译器类型.
# func: get file suffix and compiler type.
# args: (id).
define preprocess
	$(eval $(call init_suffix,$(SRCS_$(1)),SUFFIX_$(1)))
	$(eval $(call init_compiler,$(SUFFIX_$(1)),CC_$(1)))
	OBJS_$(1) = $(SRCS_$(1):$(SUFFIX_$(1))=.o)
	export OBJS_$(id) CC_$(id) SUFFIX_$(1)
endef

# compile relevant.
# func: compile as exe.
# args: (cc).
define compile_exe
	$(1) -o $@ $^ $(LDFLAGS)
endef
# func: compile as static library.
# args: ().
define compile_static
	$(AR) crs $@ $^
	$(RANLIB) $@
endef
# func: compile as dynamic library.
# args: (cc).
define compile_dynamic
	$(1) $(SHARE) $@ $^ $(LDFLAGS)
endef

# func: dim file info.
# args: (id, mode, dest, src).
define dim_file_relevant
	aimid_all += $(1)
	MODE_$(1) = $(2)
	$(eval ALL_$(1) = $(3))
	SRCS_$(1) = $(4)
	TARGET += $(ALL_$(1))
	export MODE_$(1) ALL_$(1) SRCS_$(1)
endef

# debug key info.
# args: (id).
# call as below.
#	@echo $(foreach id,$(aimid_all),$(call debug,$(id)))
define debug
"\n"\
"\bdebug begin!!!\n"\
"suffix: $(SUFFIX_$(1))\n"\
"cc: $(CC_$(1))\n"\
"objs: $(OBJS_$(1))\n"\
"all: $(ALL_$(1))\n"\
"srcs: $(SRCS_$(1))\n"\
"req: $(REQ_$(1))\n"\
"mode: $(MODE_$(1))\n"\
"\bdebug end!!!\n"
endef
