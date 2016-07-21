APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
RunningAdmin_ohs.o \
Balancer_ohs.o \
GyroAdmin_ohs.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
