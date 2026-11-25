#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
    int show_all;       // -a: Показване на скрити файлове
    int long_format;    // -l: Дълъг формат с детайли
    int recursive;      // -R: Рекурсивно обхождане на поддиректории
    int sort_by_size;   // -S: Сортиране по размер на файла
    int sort_by_time;   // -t: Сортиране по време на последна промяна
    int reverse_sort;   // -r: Обръщане на реда на сортиране
    int human_readable; // -h: Форматиране на размера
} Options;

void parse_options(int argc, char *argv[], Options *opt);

#endif
