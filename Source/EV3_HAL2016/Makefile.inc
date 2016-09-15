mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
GyroAdmin_ohs.o \
RayReflectAdmin_ohs.o \
RunningAdmin_ohs.o \
TailAdmin_ohs.o \
RunLineCalculator_ohs.o \
Balancer_ohs.o\
TrackCompass_ohs.o\
LineTracer_ohs.o \
PatternSequencer_ohs.o\
EvStateAdmin_ohs.o\
ScenarioConductor_ohs.o


SRCLANG := c++


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif


srcpath = $(mkfile_path)calculation $(mkfile_path)device_ope $(mkfile_path)main_app

ifdef app
  APPL_DIR += $(srcpath)
endif

ifdef mod
  SRCDIRS += $(srcpath)
endif

# これ入れるとincludeのパス指定省略できるよ
# INCLUDES += \
#	-I$(mkfile_path)calculation \
#	-I$(mkfile_path)device_ope \
#	-I$(mkfile_path)main_app