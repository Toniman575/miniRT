# ---- project ------------------------------------------------------------- #
NAME		= miniRT

# ---- compiler / linker --------------------------------------------------- #
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP
ARENA_SIZE	?= 64
CPPFLAGS	= -I inc -I $(LIBFT_DIR) -I $(LIBFT_DIR)/arena -I $(LIBFT_DIR)/gnl -D ARENA_SIZE=$(ARENA_SIZE)
LDFLAGS 	=
LDLIBS		= -lmlx -lX11 -lXext -lm
RM			= rm
RMFLAGS		= -rf

# ---- make ---------------------------------------------------------------- #
ifeq ($(filter -j% --jobs%,$(MAKEFLAGS)),)
MAKEFLAGS += -j$(shell nproc 2>/dev/null || echo 1)
endif

# ---- sanitizer ----------------------------------------------------------- #
ifdef SAN
CFLAGS  += -fsanitize=address
LDFLAGS += -fsanitize=address
endif

# ---- build directories --------------------------------------------------- #
BUILD_DIR		= build
RELEASE_DIR		= $(BUILD_DIR)/release
DEBUG_DIR		= $(BUILD_DIR)/debug
RELEASE_NAME	= $(RELEASE_DIR)/$(NAME)
DEBUG_NAME		= $(DEBUG_DIR)/$(NAME)

# ---- libraries ----------------------------------------------------------- #
LIBFT_DIR		= libft
LIBFT_RELEASE	= $(LIBFT_DIR)/build/release/libft.a
LIBFT_DEBUG		= $(LIBFT_DIR)/build/debug/libft.a

# ---- sources ------------------------------------------------------------- #
SRCS	= \
		constructors.c \
		exit_handling.c \
		from.c \
		hooks.c \
		init.c \
		intersection.c \
		main.c \
		main_loop.c \
		parsing.c \
		render.c \
		vector_basics.c \
		vector_geometry.c \
		vector_utils.c

DEBUG_SRCS 	=

# ---- objects / dependencies ---------------------------------------------- #
RELEASE_OBJS	= $(addprefix $(RELEASE_DIR)/, $(SRCS:.c=.o))
DEBUG_OBJS  	= $(addprefix $(DEBUG_DIR)/, $(SRCS:.c=.o)) \
				  $(addprefix $(DEBUG_DIR)/, $(DEBUG_SRCS:.c=.o))
DEPS			= $(RELEASE_OBJS:.o=.d) $(DEBUG_OBJS:.o=.d)

# ---- source lookup ------------------------------------------------------- #
vpath %.c src

# ---- build flags --------------------------------------------------------- #
RELEASE_FLAGS	= -O2
DEBUG_FLAGS		= -O0 -g3 -DDEBUG

# ---- targets ------------------------------------------------------------- #
all: $(RELEASE_NAME)
	ln -sf $(RELEASE_NAME) $(NAME)

asan:
	$(MAKE) debug SAN=1

debug: $(DEBUG_NAME)
	ln -sf $(DEBUG_NAME) $(NAME)-debug

$(RELEASE_NAME): $(RELEASE_OBJS) $(LIBFT_RELEASE)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(DEBUG_NAME): $(DEBUG_OBJS) $(LIBFT_DEBUG)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# ---- object compilation -------------------------------------------------- #
$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(RELEASE_FLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# ---- libft --------------------------------------------------------------- #
$(LIBFT_RELEASE): FORCE
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_DEBUG): FORCE
	$(MAKE) -C $(LIBFT_DIR) debug

FORCE:

# ---- utility targets ----------------------------------------------------- #
run: all
	touch dummy.rt
	./$(NAME) dummy.rt

run-debug: debug
	touch dummy.rt
	./$(NAME)-debug dummy.rt

doc:
	@mkdir -p docs
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

test: all debug
	./test/runner.sh

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(RMFLAGS) $(RELEASE_OBJS) $(DEBUG_OBJS) $(DEPS)
	$(RM) $(RMFLAGS) docs/Doxyfile dummy.rt

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(RMFLAGS) $(NAME) $(NAME)-debug
	$(RM) $(RMFLAGS) $(BUILD_DIR) docs log compile_flags.txt

re:
	$(MAKE) fclean
	$(MAKE) all

# ---- phony targets ------------------------------------------------------- #
.PHONY: all debug asan run run-debug doc test clean fclean re FORCE

# ---- dependencies -------------------------------------------------------- #
-include $(DEPS)
