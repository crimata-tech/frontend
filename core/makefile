#################################################
#
#	Makefile - Test GUI
#
#	Crimata Technologies 2020 
#
#####################################################

CXX      := -gcc
CXXFLAGS := `pkg-config --cflags gtk+-3.0`


LDFLAGS  := \
	-L/usr/lib \
	-L/usr/local/lib \
	-lfvad \
	-lportaudio \

APP_NAME     := Crimata
BUILD_DIR    := ./build
OBJ_DIR      := $(BUILD_DIR)/objects
APP_DIR      := $(BUILD_DIR)/apps
EXE_DIR      := $(BUILD_DIR)/apps/$(APP_NAME).app/Contents/MacOS
INCLUDE      := \
	-I . \
	-I include/ \
	-I ../gui/include/ \
	-I ../networking/include/ \
	-I ../audio/include/ \
	-I /usr/include/gtk-3.0

SRC := \
	$(wildcard src/main.c) \
	$(wildcard ../gui/src/gtk-cairo_api.c) \
	$(wildcard ../gui/src/anims.c) \
	$(wildcard ../gui/src/eases.c) \
	$(wildcard ../networking/src/package_handler.c) \
	$(wildcard ../audio/src/audio_handler.c) \
	$(wildcard ../audio/src/frame_buffer.c) \


OBJECTS  := $(SRC:%.c=$(OBJ_DIR)/%.o)


#  Rules
all: kill clean build $(EXE_DIR)/$(APP_NAME) run


#	Compile all src files into object files into object directory 
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@


#	Link and make exe
$(EXE_DIR)/$(APP_NAME): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ `pkg-config --libs gtk+-3.0` $(LDFLAGS)


.PHONY: all build clean debug release


build:
	@mkdir -p $(APP_DIR)/$(APP_NAME).app/Contents/{MacOS,Resources}
	@mkdir -p $(OBJ_DIR)
	@cp Info.plist $(APP_DIR)/$(APP_NAME).app/Contents/
	@cp resources/* $(APP_DIR)/$(APP_NAME).app/Contents/Resources/

# debug: CXXFLAGS += -DDEBUG -g
# debug: all


# release: CXXFLAGS += -O2
# release: all


run: $(EXE_DIR)/$(APP_NAME)
	# remove object file directories
	rm -rvf $(BUILD_DIR)/audio $(BUILD_DIR)/gui $(BUILD_DIR)/networking
# 	$<


clean:
	-@rm -rvf $(BUILD_DIR)/*

kill:
	@pkill $(APP_NAME) || true
