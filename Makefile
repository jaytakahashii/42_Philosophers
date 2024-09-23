# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/18 12:15:22 by jtakahas          #+#    #+#              #
#    Updated: 2024/09/23 16:09:27 by jtakahas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFILE
MAKEFILE = Makefile

# プロジェクト名
NAME = philosophers

# ソースファイルとオブジェクトファイルのディレクトリ
SRC_DIR = src/
OBJ_DIR = .obj/

# インクルードディレクトリ
INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
HEADERS = $(wildcard $(INCLUDE_DIR)*.h)

# 依存ファイル
DEPS = $(MAKEFILE) $(HEADERS)

# コンパイル設定
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -fsanitize=address,undefined -g

# クリーンアップコマンド
RM = rm -rf

# norminette
NORM = norminette

# ソースコードのサブディレクトリ
UTILS_DIR = 	utils/

# 各ディレクトリ内のソースファイル
UTILS_SRC = 	utils.c ft_uint_atoi.c ft_malloc.c

# ソースファイル
SRC_FILES = main.c validate_check.c philosophers.c initialize.c

# ソースファイルをまとめる
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS_SRC))

# オブジェクトファイルをまとめる
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

# color **********************************************
Y 			= "\033[33m"
R 			= "\033[31m"
G 			= "\033[32m"
B 			= "\033[34m"
X 			= "\033[0m"
UP 			= "\033[A"
CUT 		= "\033[K"
# *****************************************************

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(Y) "$(NAME) src files successfully compiled\n" $(X)
	@echo $(B) "$(NAME) creating" $(X)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

debug: $(OBJ_DIR) $(OBJS)
	@echo $(Y) "$(NAME) src files successfully compiled\n" $(X)
	@echo $(B) "$(NAME) creating" $(X)
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

# オブジェクトファイルのディレクトリを作成
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(addprefix $(OBJ_DIR), $(UTILS_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@echo $(Y) "Compiling $<" $(X)
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@
	@printf $(UP)$(CUT)

clean:
	@$(RM) $(OBJ_DIR)
	@echo $(R) "$(NAME) cleaned" $(X)

fclean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo $(R) "$(NAME) fcleaned" $(X)

re: fclean all

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | grep -v Error! | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true

.PHONY: all clean fclean re norm
