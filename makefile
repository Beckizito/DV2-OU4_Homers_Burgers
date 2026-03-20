# Makefile (C)

CC := gcc 
CFLAGS := -O2 -Wall -Wextra -g

SRCDIR := src
OBJDIR := build
BINDIR := bin

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

TARGET := $(BINDIR)/myprog

# Colors
GREEN := \033[1;32m
BLUE := \033[1;34m
YELLOW := \033[1;33m
RESET := \033[0m

.PHONY: all clean run clear_screen

all: clear_screen $(TARGET)

clear_screen:
	clear

$(BINDIR):
	@echo "$(BLUE)==> Creating bin directory...$(RESET)"
	@mkdir -p $(BINDIR)

$(OBJDIR):
	@echo "$(BLUE)==> Creating build directory...$(RESET)"
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJS) | $(BINDIR) $(OBJDIR)
	@echo "$(YELLOW)==> Linking program...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "$(GREEN)==> Build complete!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "$(BLUE)==> Compiling $< ...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $<

ARGS =
run: all
	@echo "$(GREEN)==> Running program...$(RESET)"
	@./$(TARGET) $(ARGS)

valgrind: all
	@echo "$(GREEN)==> Running program with Valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(TARGET) $(ARGS)

clean:
	@echo "$(YELLOW)==> Cleaning files...$(RESET)"
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "$(GREEN)==> Clean complete!$(RESET)"