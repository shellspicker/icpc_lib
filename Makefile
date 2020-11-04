include mk/env.mk
include mk/recipe.mk

# 这块自行修改.
.PHONY: init_all
init_all:
# 添加需要的目标文件.
# 支持多个目标, 写好每个目标的信息.
# 定义每个目标调用一次dim_file_relevant.
# example:
#	$(eval $(call dim_file_relevant,id,mode,target,src))
# id:
#     自定义的字符串.
#     表示目标的编号.
# mode:
#     (exe, static, dynamic)其中之一.
#     表示编译出来的类型是(可执行文件, 静态库, 动态库).
# target:
#     自定义的字符串.
#     表示目标的名字.
# src:
#     编译目标所需要的源文件. 如果文件比较多, 可以考虑定义一个变量.
	@$(foreach id,$(aimid_all),\
		$(eval $(call preprocess,$(id)))\
		$(eval REQ_$(id) = $(OBJS_$(id)))\
		)
# 根据上面的id, 添加不同模块间的依赖(如果有的话).
# example:
#	$(eval REQ_XXX += $(ALL_YYY))
# 后缀XXX,YYY换成id.
	@$(foreach id,$(aimid_all),\
		$(eval export REQ_$(id))\
		)
	$(eval export aimid_all TARGET)

include mk/target.mk
include mk/util.mk
