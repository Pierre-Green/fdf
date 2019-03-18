# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 15:01:06 by pguthaus          #+#    #+#              #
#    Updated: 2019/03/14 17:40:17 by pierre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRODFILE	=	make/Makefile.prod
DEVFILE		=	make/Makefile.dev

all: bin

pre:
	@$(MAKE) -C libft lib

devpre:
	@$(MAKE) -C libft dev

bin: pre
	@echo "Making the executable..."
	@$(MAKE) -f $(PRODFILE)
	@echo "Executable has been made"

dev: devpre
	@echo "Making the debugable executable..."
	@$(MAKE) -f $(DEVFILE)
	@echo "Debugable executable has been made"

devre: fclean dev

re: fclean bin

clean:
	@echo "Cleaning object files"
	@rm -rf objs/

fclean: clean
	@echo "Cleaning everything"
	@$(MAKE) -f $(PRODFILE) fclean
	@$(MAKE) -f $(DEVFILE) fclean
	@$(MAKE) -C libft fclean

getsources:
	@rm -f make/sources.mk
	@touch make/sources.mk
	@find src/ -name "*.c" | sed  "s/src\//SRCS+=/g" >> make/sources.mk
