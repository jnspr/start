NAME=start

.PHONY: all clean

all: $(NAME)
clean:
	rm -f $(NAME)

$(NAME): start.c
	$(CC) $(CFLAGS) -o $(NAME) start.c

