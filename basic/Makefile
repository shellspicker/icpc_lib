# 编译参数
CC = gcc
CXX = g++
AR = ar
RANLIB = ranlib
SHARE = -fpic -shared -o
INCLUDE = -I./\
	-I/usr/include/\
	-I/usr/local/include/
LIBS = -L./\
	-L/usr/lib/\
	-L/usr/lib32/\
	-L/usr/lib64/\
	-L/usr/local/lib/
LDFLAGS = $(LIBS) -Wl,-rpath=$(subst $(space),:,$(subst -L,,$(LIBS)))
DEFINES =
CFLAGS = -g -Wall -O2 $(INCLUDE) $(DEFINES)
CXXFLAGS = -std=c++11 $(CFLAGS) -DHAVE_CONFIG_H

# make工具, Makefile指定.
MAKE = make
MAKEFILE = Makefile

# 文件扩展名相关.
SRCEXT = .c .cc .cpp .cxx .c++

# recipe and compile rule.
# args: (id).
define recipe
$(ALL_$(1)): $(REQ_$(1))
	$$(call compile_$(MODE_$(1)),$(CC_$(1)))
endef

# default target
default: all
fake_all: $(TARGET)

# 万事具备, 展开所有必要的静态规则.
ifneq ($(aimid_all),)
    # 固定格式的编译规则调用.
    $(foreach id,$(aimid_all),$(eval $(call recipe,$(id))))
    # 自动生成的所有文件对应的头文件依赖.
    obj_all = $(foreach id,$(aimid_all),$(OBJS_$(id)))
    ifneq ($(obj_all),)
        sinclude $(obj_all:.o=.d)
    endif
endif

# 这块自行修改.
.PHONY: init_all
init_all:
# 添加需要的目标文件.
# 自定义文件, 支持多个目标, 写好每个目标的信息, 具体看函数的参数.
#	$(eval $(call dim_file_relevant,,,,))
	$(eval $(call dim_file_relevant,1,exe,exp,calc_exp.cpp))
	$(eval $(call dim_file_relevant,2,exe,rad,radix_sort.cpp))
	@$(foreach id,$(aimid_all),\
		$(eval $(call preprocess,$(id)))\
		$(eval REQ_$(id) = $(OBJS_$(id)))\
		)
# 额外的目标之间的依赖.
#	$(eval REQ_XXX += $(ALL_XXX))
	@$(foreach id,$(aimid_all),\
		$(eval export REQ_$(id))\
		)
	$(eval export aimid_all TARGET)

# 以下一般不需要改
.PHONY: build rebuild all clean cleanall
build: all
rebuild: cleanall build
all: init_all
	@$(MAKE) -f $(MAKEFILE) fake_all
clean: init_all
	rm -f *.orig *~ *.o *.d
cleanall: clean
	rm -f $(TARGET)

# 约定俗成的根据源文件自动生成头文件依赖.
# func: get dependence rule file.
# args: (src, dep_file, compiler).
# src file like .c .cpp ...
# dependence rule file like .d .o: .c(pp) .h(pp) ...
define mkdep
	@set -e
	@rm -f $(2)
	@$(3) -MM -MF $(2) -MT '$(patsubst %.d,%.o,$(2)) $(2)' $(1)
endef
%.d: %.c
	@$(call mkdep,$<,$@,$(CC))

%.d: %.cpp
	@$(call mkdep,$<,$@,$(CXX))

# 以下是生成.d文件的4种方法.
# 形如%.d %.o: %.c something.h...
# 生成.d的原因是.h里面增加或减少包含其他.h文件, .d也能同步更新.
#@$(CC) -MM -MF $@ -MT '$(patsubst %.d,%.o,$@) $@' $<
#@$(CC) -MM $< | awk '{print "$@", $$0}' > $@
#@$(CC) -MM $< | awk '{printf "%s %s\n", "$@", $$0}' > $@
#@$(CC) -MM $< | sed 's:^\(.*\):$@ \1:g' > $@
#@$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
#	sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' < $@.$$$$ > $@; \
#	rm -f $@.$$$$

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
	export OBJS_$(id) CC_$(id)
endef

# compile relevant.
# args: (cc).
define compile_exe
	$(1) -o $@ $^ $(LDFLAGS)
endef
# args: ().
define compile_static
	$(AR) crs $@ $^
	$(RANLIB) $@
endef
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
#	@$(foreach id,$(aimid_all),$(call debug,$(id)))
define debug
	@echo -en "debug begin!!!\n"
	@echo -en "suffix: $(SUFFIX_$(1))$$\n"
	@echo -en "cc: $(CC_$(1))$$\n"
	@echo -en "objs: $(OBJS_$(1))$$\n"
	@echo -en "all: $(ALL_$(1))$$\n"
	@echo -en "srcs: $(SRCS_$(1))$$\n"
	@echo -en "req: $(REQ_$(1))$$\n"
	@echo -en "mode: $(MODE_$(1))$$\n"
	@echo -en "debug end!!!\n"
endef
