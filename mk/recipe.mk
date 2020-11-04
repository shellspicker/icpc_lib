# recipe and compile rule.
# func: write a recipe.
# args: (id).
define recipe
$(ALL_$(1)): $(REQ_$(1))
	$$(call compile_$(MODE_$(1)),$(CC_$(1)))
endef

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
