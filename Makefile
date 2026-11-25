CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -MMD -MP
TARGET = my_ls
SRC = main.c options.c scanner.c sort.c display.c file_info.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Програмата е успешно компилирана!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

.PHONY: clean run

clean:
	rm -f $(OBJ) $(TARGET) $(OBJ:.o=.d)
	@echo "Всички генерирани файлове са изтрити."

run: $(TARGET)
	./$(TARGET)
