# Thorsten Schubert, OFFIS

# Kind of generic makefile. Hopefully no dependency is missing ;-)
# Tested with GNU Make 3.80

# TODO: Use a more suitable build system

SYSTEMC_HOME_DIR = $(SYSTEMC_HOME)
SYSTEMC_LIB_SUBDIR ?= lib-linux_gcc-3.4.4
  
COMPILER_OPTIONS ?= -DDEBUG -ggdb3 -O0

SYSTEMC_LIB_BASENAME = systemc
SYSTEMC_LIB_PATH     = $(SYSTEMC_HOME_DIR)/$(SYSTEMC_LIB_SUBDIR)
SYSTEMC_LIB_FILENAME = $(SYSTEMC_LIB_PATH)/lib$(SYSTEMC_LIB_BASENAME).a
SYSTEMC_INCLUDE_DIR  = $(SYSTEMC_HOME_DIR)/include

PERFORM_ENV_CHECK = 1

ifeq ($(MAKECMDGOALS),)
PERFORM_ENV_CHECK = 0
endif
ifeq ($(MAKECMDGOALS),help)
PERFORM_ENV_CHECK = 0
endif
ifeq ($(MAKECMDGOALS),clean)
PERFORM_ENV_CHECK = 0
endif
ifeq ($(MAKECMDGOALS),ultra-clean)
PERFORM_ENV_CHECK = 0
endif

REBUILD_DEPS ?= 1

ifeq ($(PERFORM_ENV_CHECK),1)

  ifndef SYSTEMC_HOME
  $(warning WARNING: $$SYSTEMC_HOME not defined)
  endif

  ifeq ($(wildcard $(SYSTEMC_LIB_FILENAME)),)
  $(warning WARNING: Unable to locate the systemc library: $(SYSTEMC_LIB_FILENAME))
  endif
  
endif

SOURCES = $(shell find src -name '*.cpp')

QUINY_SYSTEMC_INCLUDE = include
QUINY_INCLUDE = include 


LIB_NAME = quiny
QUINY_LIB_DIR = lib
QUINY_LIB_FILE = $(QUINY_LIB_DIR)/lib$(LIB_NAME).a

BACKEND_LIB_DIR=$(QUINY_LIB_DIR)/Backends

TEST_DIRS= $(shell find test -type d | grep -v '.svn' | egrep '[0-9][0-9][1-9]')

BACKEND_DIRS = $(shell find backends/ -mindepth 1 -maxdepth 1 -type d | grep -v '.svn')

# Derive the target names for a tests in the form <testsubdir>_XYZ.x, where XYZ is the
# test number
DERIVE_TARGET_NAME = $(shell echo $(1) | sed 's/test\/\(.*\)\/\(...\).*/\1_\2/g')

BUILD_DIR = build
SIM_DIR = sim
OBJ_DIR =$(BUILD_DIR)/objs


#TEST_TARGET_NAME = $(foreach x,$(TEST_DIRS), $(call DERIVE_TARGET_NAME,$x))

.PHONY: help
help:
	@echo 
	@echo 'Available testing targets (which will build all necessary libraries) are:'
	@echo 
	@$(foreach target,$(TEST_TARGET_LIST),echo "  $(target)" ;) true	@echo 
	@echo 
	@echo "Note: Appending a '.x' to the targets listed above will build the corresponding "
	@echo "      executable. Without '.x' the target will be built and run."
	@echo "      '_<Backend>_q' is the Quiny mode for the given Backend, "
	@echo "      '_s' the SystemC mode"
	@echo   
	@echo Backend library targets
	@echo   
	@$(foreach target,$(BACKEND_LIB_TARGET_LIST),echo "  $(target)" ;) true	@echo 
	@echo   
	@echo Further targets:
	@echo 
	@echo "lib-quiny     build the library"
	@echo "clean         clean intermediate files"
	@echo "ultra-clean   remove all genereated files"
	@echo "deps          update all generated Makefiles (implies building the lib)"
	@echo "deps-lib      update lib's generated Makefile"
	@echo "all           build and run all tests (and implicitly build all libs)"
	@echo
	@echo "IMPORTANT: Dependencies are always updated. To prevent this set REBUILD_DEPS=0,"
	@echo "           e.g. make lib-quiny REBUILD_DEPS=0"
	@echo

.PHONY: lib-quiny
lib-quiny: $(QUINY_LIB_FILE)

QUINY_MAKEFILE = $(BUILD_DIR)/Makefile.gen

MAKE_GEN_CMD = make GCC=g++

# must be phony, otherwise an existing Makefile will prevent a rebuild
# Note: This is generally true for all files which are created by a sub make,
#       because effectively, we delegate the dependency checking to the sub make.

.PHONY: $(QUINY_LIB_FILE)

$(QUINY_LIB_FILE): $(QUINY_MAKEFILE)
	$(MAKE_GEN_CMD) -f $(QUINY_MAKEFILE)

.PHONY:clean
clean:
	-rm -rf $(BUILD_DIR)

.PHONY: ultra-clean
ultra-clean: clean
	-rm -rf lib sim

ALL_GEN_MAKEFILES = $(QUINY_MAKEFILE)

.PHONY: deps
deps:
	gmake -B $(ALL_GEN_MAKEFILES)

.PHONY: deps-lib
deps-lib:
	gmake -B $(QUINY_MAKEFILE)

.PHONY: all
all: $(TEST_TARGET_LIST)


#
# Makefile for building the quiny lib
#
ifeq ($(REBUILD_DEPS),1)
.PHONY : $(QUINY_MAKEFILE)
endif
$(QUINY_MAKEFILE):
	test -e $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	test -e lib || mkdir lib
	scripts/CreateMakefile.sh \
   INCLUDES $(QUINY_INCLUDE) \
   SOURCES $(SOURCES) \
   COMPILER_OPTS $(COMPILER_OPTIONS) \
   OBJECT_DIR $(OBJ_DIR) \
   OUTPUT_FILE $(QUINY_LIB_FILE) \
   LINKER_OPTS \
   MAKEFILE $@


#
# Template for the test cases
#

TEST_TARGET_LIST = 

define MAKEFILE_GEN_TEMPLATE

# 1 : test name
# 2 : path to test
# 3 : extension
# 4 : lib: libraries to link with (file names)
# 5 : include
# 6 : lib options for $(strip $(4)) (-Llib -l$(LIB_NAME))
# 7 : the Makefiles the generated Makefile depends on (i.e., the Makefiles
#     which are needed to build the input libs)
# 6 is currently not used

ifeq ($(REBUILD_DEPS),1)
.PHONY : $(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen
endif

DBG_VAR = "NEW" $(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen: $(7) $(DBG_VAR)

$(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen:
	test -e $(OBJ_DIR)/$(strip $(1))_$(strip $(3)) || mkdir -p $(OBJ_DIR)/$(strip $(1))_$(strip $(3))
	test -e $(SIM_DIR)/$(strip $(1)) || mkdir -p $(SIM_DIR)/$(strip $(1))
	scripts/CreateMakefile.sh \
   INCLUDES $(strip $(5)) $(strip $(2)) \
   SOURCES $(shell find $(strip $(2)) -name '*.cpp') \
   COMPILER_OPTS $(COMPILER_OPTIONS) \
   OBJECT_DIR $(OBJ_DIR)/$(strip $(1))_$(strip $(3)) \
   OUTPUT_FILE $(SIM_DIR)/$(strip $(1))/$(strip $(1))_$(strip $(3)).x \
   LINKER_OPTS $(4)\
   MAKEFILE $(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen

ALL_GEN_MAKEFILES = $(ALL_GEN_MAKEFILES) $(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen


# must be phony, otherwise an existing Makefile will prevent a rebuild
.PHONY: $(strip $(1))_$(strip $(3)).x
$(strip $(1))_$(strip $(3)).x : $(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen $(4)
#	@$(foreach makefile,$(7),echo "Invoking sub-make: $(MAKE_GEN_CMD) $(makefile)" ; $(MAKE_GEN_CMD) $(makefile) ; ) true
	$(MAKE_GEN_CMD) -f $(BUILD_DIR)/Makefile_$(strip $(1))_$(strip $(3)).gen

.PHONY: $(strip $(1))_$(strip $(3))
$(strip $(1))_$(strip $(3)) : $(strip $(1))_$(strip $(3)).x
	cd $(SIM_DIR)/$(strip $(1)) ; ./$(strip $(1))_$(strip $(3)).x

TEST_TARGET_LIST = $(TEST_TARGET_LIST) $(strip $(1))_$(strip $(3))

endef



#
# Template for building the backend libs
#

BACKEND_LIB_TARGET_LIST = 

define MAKEFILE_GEN__LIB_TEMPLATE

# 1 : library base name
# 2 : path to the backend

ifeq ($(REBUILD_DEPS),1)
.PHONY : $(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(1)).gen
endif

# The backend Makefile does not depend on other Makefiles, because there are no input
# libs
$(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(1)).gen:
	test -e $(OBJ_DIR)/Backend/$(strip $(1)) || mkdir -p $(OBJ_DIR)/Backend/$(strip $(1))
	test -e $(BACKEND_LIB_DIR) || mkdir -p $(BACKEND_LIB_DIR)
	scripts/CreateMakefile.sh \
   INCLUDES $(QUINY_INCLUDE) $(strip $(2)) \
   SOURCES $(shell find $(strip $(2)) -name '*.cpp') \
   COMPILER_OPTS $(COMPILER_OPTIONS) \
   OBJECT_DIR $(OBJ_DIR)/Backend/$(strip $(1)) \
   OUTPUT_FILE $(BACKEND_LIB_DIR)/lib$(strip $(1)).a \
   LINKER_OPTS \
   MAKEFILE $(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(1)).gen

ALL_GEN_MAKEFILES = $(ALL_GEN_MAKEFILES) $(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(1)).gen

# must be phony, otherwise an existing Makefile will prevent a rebuild
.PHONY: lib-$(strip $(1))   
lib-$(strip $(1)) : $(BACKEND_LIB_DIR)/lib$(strip $(1)).a 

# must be phony, otherwise an existing Makefile will prevent a rebuild
.PHONY: $(BACKEND_LIB_DIR)/lib$(strip $(1)).a
$(BACKEND_LIB_DIR)/lib$(strip $(1)).a : $(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(1)).gen
	$(MAKE_GEN_CMD) -f $(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(1)).gen

BACKEND_LIB_TARGET_LIST = $(BACKEND_LIB_TARGET_LIST) lib-$(strip $(1))

endef


#
# Create rules for each backend
#

DERIVE_BACKEND_NAME = $(notdir $(1))
GET_BACKEND_LIB = $(BACKEND_LIB_DIR)/lib$(call DERIVE_BACKEND_NAME,$(1)).a
GET_BACKEND_LIB_OPTS = -L$(BACKEND_LIB_DIR) -l$(call DERIVE_BACKEND_NAME,$(1))

$(foreach ex,$(BACKEND_DIRS),$(eval $(call MAKEFILE_GEN__LIB_TEMPLATE,$(call DERIVE_BACKEND_NAME,$(ex)),$(ex))))



# Some helper functions for determining the correct options depending on whether SystemC (s)
# or Quiny (q) is given

IS_SYSTEMC_VERSION = $(findstring s,$(1))

GET_LIB      = $(if $(call IS_SYSTEMC_VERSION,$(1)),$(SYSTEMC_LIB_FILENAME),$(QUINY_LIB_FILE))
GET_INCLUDE  = $(if $(call IS_SYSTEMC_VERSION,$(1)),$(SYSTEMC_INCLUDE_DIR),$(QUINY_INCLUDE))
GET_LIB_OPTS = $(if $(call IS_SYSTEMC_VERSION,$(1)),\
                   -L$(SYSTEMC_LIB_PATH) -l$(SYSTEMC_LIB_BASENAME),\
                   -L$(QUINY_LIB_DIR) -l$(LIB_NAME) $(call GET_BACKEND_LIB_OPTS,$(2)))
GET_MAKEFILE = $(if $(call IS_SYSTEMC_VERSION,$(1)),,$(QUINY_MAKEFILE) $(BUILD_DIR)/Makefile_Backend_LIB_$(strip $(call DERIVE_BACKEND_NAME,$(2))).gen)

# Create rules for each test case in combination with each backend-lib in combination with SystemC or Quiny

test_func = $(warning 1="$(strip $(strip $(1)))" 2="$(strip $(2))" 3="$(strip $(3))" 4="$(strip $(4))" 5="$(strip $(5))" 6="$(strip $(6))")

TEST_EXTENSIONS = s q

# Quiny targets
$(foreach backend,$(BACKEND_DIRS),\
      $(foreach test,$(TEST_DIRS),$(eval $(call MAKEFILE_GEN_TEMPLATE,\
        $(call DERIVE_TARGET_NAME,$(test)),\
        $(test),\
        $(call DERIVE_BACKEND_NAME,$(backend))_q,\
        $(call GET_LIB,q) $(call GET_BACKEND_LIB,$(backend)) $(call GET_LIB,q),\
        $(call GET_INCLUDE,q), \
        $(call GET_LIB_OPTS,q,$(backend)), \
        $(call GET_MAKEFILE,q,$(backend)) \
    ))) \
 )

# SystemC targets
$(foreach test,$(TEST_DIRS),$(eval $(call MAKEFILE_GEN_TEMPLATE,\
  $(call DERIVE_TARGET_NAME,$(test)),\
  $(test),\
  s,\
  $(call GET_LIB,s),\
  $(call GET_INCLUDE,s), \
  $(call GET_LIB_OPTS,s), \
  $(call GET_MAKEFILE,s) \
   )) \
 )


test_me:
	@echo $(DBG_VAR)
