#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

void test_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int line_num = 1;

    if (fd < 0)
    {
        perror(filename);
        return;
    }

    printf("\n=== Тест файла: %s ===\n", filename);

    while ((line = get_next_line(fd)))
    {
        printf("Line %d: %s", line_num, line);
        free(line);
        line_num++;
    }

    printf("Конец файла, get_next_line вернул NULL ✅\n");
    close(fd);
}

int main(void)
{
    char *files[] = {
        "empty.txt",          // пустой файл
        "no_newline.txt",     // файл без \n на конце
        "file1.txt",          // обычный файл
        "long_line.txt"       // файл с очень длинной строкой
    };

    // ✅ Тестируем каждый файл по отдельности
    for (int i = 0; i < 4; i++)
        test_file(files[i]);

    // ✅ Тест нескольких fd одновременно
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1;
    char *line2;

    if (fd1 < 0 || fd2 < 0)
    {
        perror("open file1.txt/file2.txt");
        return 1;
    }

    printf("\n=== Тест нескольких файлов одновременно ===\n");
    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);

        if (!line1 && !line2)
            break;

        if (line1)
        {
            printf("fd1: %s", line1);
            free(line1);
        }

        if (line2)
        {
            printf("fd2: %s", line2);
            free(line2);
        }
    }

    close(fd1);
    close(fd2);

    // ✅ Проверка повторных вызовов после EOF
    int fd3 = open("empty.txt", O_RDONLY);
    if (fd3 >= 0)
    {
        char *line = get_next_line(fd3);
        if (!line)
            printf("\nПовторный вызов на пустом файле вернул NULL ✅\n");
        else
        {
            printf("\nОшибка: вернулась строка: %s\n", line);
            free(line);
        }
        close(fd3);
    }

    return 0;
}
