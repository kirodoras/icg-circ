// Circunferência por ponto medio => bresenham
// compile: gcc circ.c -o circ -lm
// execute: ./circ
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void setPixel(unsigned char (**im)[3], int i, int j, unsigned char r, unsigned char g, unsigned char b)
{
    im[i][j][0] = r;
    im[i][j][1] = g;
    im[i][j][2] = b;
}

void setOctantesPixel(unsigned char (**im)[3], int l, int h, int xc, int yc, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    if (xc + x >= 0 && xc + x < l && yc + y >= 0 && yc + y < h)
        setPixel(im, xc + x, yc + y, r, g, b);

    if (xc + y >= 0 && xc + y < l && yc + x >= 0 && yc + x < h)
        setPixel(im, xc + y, yc + x, r, g, b);
    if (xc - x >= 0 && xc - x < l && yc + y >= 0 && yc + y < h)
        setPixel(im, xc - x, yc + y, r, g, b);

    if (xc - y >= 0 && xc - y < l && yc + x >= 0 && yc + x < h)
        setPixel(im, xc - y, yc + x, r, g, b);

    if (xc + x >= 0 && xc + x < l && yc - y >= 0 && yc - y < h)
        setPixel(im, xc + x, yc - y, r, g, b);

    if (xc + y >= 0 && xc + y < l && yc - x >= 0 && yc - x < h)
        setPixel(im, xc + y, yc - x, r, g, b);

    if (xc - x >= 0 && xc - x < l && yc - y >= 0 && yc - y < h)
        setPixel(im, xc - x, yc - y, r, g, b);

    if (xc - y >= 0 && xc - y < l && yc - x >= 0 && yc - x < h)
        setPixel(im, xc - y, yc - x, r, g, b);
}

void circ(unsigned char (**im)[3], int l, int h, int xc, int yc, int radius, unsigned char r, unsigned char g, unsigned char b)
{
    int x = 0, y = radius, p = 3 - 2 * radius;
    while (y >= x)
    {
        setOctantesPixel(im, l, h, xc, yc, x, y, r, g, b);
        if (p < 0)
            p += 4 * x + 6;
        else
        {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void main(int argc, char **argv)
{
    int i, j, l, h;
    unsigned char cmax = 255;
    l = h = 500;
    FILE *fp;

    unsigned char(**imagem)[3];

    j = l * sizeof(char *);
    imagem = malloc(j);

    j = h * 3;
    for (i = 0; i < l; i++)
        imagem[i] = malloc(j);

    for (j = 0; j < h; j++)
        for (i = 0; i < l; i++)
        {
            setPixel(imagem, i, j, 0, 0, 0);
        }

    srand(time(NULL));
    for (i = 0; i < 20; i++)
        circ(imagem, l, h, rand() % l, rand() % h, rand() % 200 + 20, rand(), rand(), rand());

    fp = fopen("output.ppm", "w");
    fprintf(fp, "P6\n");
    fprintf(fp, "%u %u\n255\n", l, h);
    for (j = 0; j < h; j++)
        for (i = 0; i < l; i++)
            fprintf(fp, "%c%c%c", imagem[i][j][0], imagem[i][j][1], imagem[i][j][2]);
    fclose(fp);

    for (i = 0; i < l; i++)
        free(imagem[i]);
    free(imagem);
}