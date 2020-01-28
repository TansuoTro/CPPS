#��ӹ���

release = true

include Rules.mk

#����ͷ�ļ�·��
INC_DIRS += -I./cpps/
SRC_FILES += $(wildcard ./cpps/*.c*)

#�궨���޸�
MACROS += -DREDIS_EXPORT
libpath = ./$(BIN_DIR)

GEN_EXE = ./$(BIN_DIR)/cpps
GEN_LIB = ./$(BIN_DIR)/libcpps.so


$(shell mkdir -p $(OBJ_DIR)/cpps)

.PHONY: all

all: $(OBJ_FILES)
	$(CPP) $(CPPFLAGS) $(PIC) $(INC_DIRS) $(GEN_OBJS) $(LIB_DIRS) $(LNK_LIBS) -o $(GEN_EXE)
	
install: 
	install -d /usr/bin
	install -p -D -m 0755 $(GEN_EXE) /usr/bin
	install -p -D -m 0755 $(GEN_LIB) /usr/lib
	install -p -D -m 0755 $(GEN_LIB) /usr/lib64
	
#libcpps
lib: $(OBJ_FILES)
	$(CPP) $(CPPFLAGS) $(PIC) $(INC_DIRS) $(GEN_OBJS) $(LIB_DIRS) $(LNK_LIBS) $(SO) $(GEN_LIB)
	
	
#���������ļ�����	
clean: force
	$(RM) $(PCH)
	$(RM) $(OUT_DIR)

force:
