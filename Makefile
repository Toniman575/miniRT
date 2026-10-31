# ---- project ------------------------------------------------------------- #
NAME       = miniRT

# ---- compiler / linker --------------------------------------------------- #
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -MMD -MP
ARENA_SIZE ?= 64
CPPFLAGS   = -I inc -I $(LIBFT_DIR) -I $(LIBFT_DIR)/arena -I $(LIBFT_DIR)/gnl -D ARENA_SIZE=$(ARENA_SIZE)
LDFLAGS    =
LDLIBS     = -lmlx -lX11 -lXext -lm

# ---- build directories --------------------------------------------------- #
RELEASE_DIR = build/release
DEBUG_DIR   = build/debug

# ---- libraries ----------------------------------------------------------- #
LIBFT_DIR     = libft
LIBFT_RELEASE = $(LIBFT_DIR)/libft.a
LIBFT_DEBUG   = $(DEBUG_DIR)/libft.a

# ---- sources ------------------------------------------------------------- #
SRCS        = \
			main.c \
			main_loop.c \
			init.c \
			hooks.c \
			exit_handling.c \
			render.c \
			intersection.c \
			vector.c

DEBUG_SRCS  =


RELEASE_OBJS = $(addprefix $(RELEASE_DIR)/, $(SRCS:.c=.o))
DEBUG_OBJS   = $(addprefix $(DEBUG_DIR)/, $(SRCS:.c=.o)) \
               $(addprefix $(DEBUG_DIR)/, $(DEBUG_SRCS:.c=.o))

# ---- source lookup ------------------------------------------------------- #
vpath %.c srcs

# ---- build flags --------------------------------------------------------- #
RELEASE_FLAGS = -O2
DEBUG_FLAGS   = -O0 -g3 -DDEBUG

# ---- targets ------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(RELEASE_OBJS) $(LIBFT_RELEASE)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

debug: $(NAME)-debug

$(NAME)-debug: $(DEBUG_DIR)/$(NAME)
	ln -sf $(DEBUG_DIR)/$(NAME) $@

$(DEBUG_DIR)/$(NAME): $(DEBUG_OBJS) $(LIBFT_DEBUG)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# ---- object compilation -------------------------------------------------- #
$(RELEASE_DIR)/%.o: BUILD_FLAGS = $(RELEASE_FLAGS)
$(DEBUG_DIR)/%.o:   BUILD_FLAGS = $(DEBUG_FLAGS)

$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(BUILD_FLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(BUILD_FLAGS) -c $< -o $@

# ---- libft --------------------------------------------------------------- #
$(LIBFT_RELEASE): FORCE
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_DEBUG): FORCE
	$(MAKE) -C $(LIBFT_DIR) debug
	cp -u $(LIBFT_RELEASE) $@

FORCE:

# ---- utility targets ----------------------------------------------------- #
run: $(NAME)
	./$(NAME)

run-debug: $(NAME)-debug
	./$(NAME)-debug

doc:
	printf '%s\n' \
	  'OUTPUT_DIRECTORY = docs' \
	  'GENERATE_MAN = YES' \
	  'MAN_OUTPUT = man' \
	  'INPUT = inc srcs debug_srcs' \
	  'EXTRACT_ALL = YES' \
	  'OPTIMIZE_OUTPUT_FOR_C = YES' \
	  > docs/Doxyfile
	doxygen docs/Doxyfile

compile_flags.txt:
	@echo setup $@
	@echo -n > $@
	@for flag in $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS); do \
		echo $$flag >> $@ ; \
	done

test: $(NAME) $(NAME)-debug
	./test/runner.sh

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf build docs/Doxyfile

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME)-debug
	rm -rf docs
	rm -f compile_flags
	rm -rf log

re: 
	$(MAKE) fclean
	$(MAKE) all

# ---- phony targets ------------------------------------------------------- #
.PHONY: all debug run run-debug doc test clean fclean re FORCE

# ---- dependencies -------------------------------------------------------- #
-include $(RELEASE_OBJS:.o=.d)
-include $(DEBUG_OBJS:.o=.d)
