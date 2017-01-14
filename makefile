#��ӹ���

release = true

include Rules.mk

#����ͷ�ļ�·��
INC_DIRS += -I./cpps/
SRC_FILES += $(wildcard ./cpps/*.c*)

#�궨���޸�
MACROS += -DREDIS_EXPORT
libpath = ./$(BIN_DIR)

GEN_EXE = ./$(BIN_DIR)/libcpps


$(shell mkdir -p $(OBJ_DIR)/cpps)

.PHONY: all

all: $(OBJ_FILES)
	$(CPP) $(CPPFLAGS) $(PIC) $(INC_DIRS) $(GEN_OBJS) $(LIB_DIRS) $(LNK_LIBS) -o $(GEN_EXE)

#���������ļ�����	
clean: force
	$(RM) $(PCH)
	$(RM) $(OUT_DIR)

force:
