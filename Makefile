CC			:= gcc
CFLAGS		:= -Wall -Wextra
LFLAGS		:= `sdl2-config --libs`
SRC_DIR		:= src
SRCS		:= $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR		:= out
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET_DIR	:= out/bin
TARGET		:= $(TARGET_DIR)/zqe

.PHONY: all clean

all: $(OBJ_DIR) $(TARGET_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(OBJ_DIR)
