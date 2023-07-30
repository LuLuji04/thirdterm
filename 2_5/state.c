#include "state.h"
#include <stdlib.h>

void init_State(struct State *s) {
    s->data = NULL;
    s->width = 0;
    s->height = 0;
}

void delete_State(struct State *s) {
    if (s->data) {
        for (int i = 0; i < s->height; i++) {
            free(s->data[i]);
        }
        free(s->data);
    }
    s->width = 0;
    s->height = 0;
}

void assign(struct State *a, struct State *b) {
    a->width = b->width;
    a->height = b->height;

    if (a->data) {
        delete_State(a);
    }

    if (b->data) {
        a->data = (int **)malloc(a->height * sizeof(int *));
        for (int i = 0; i < a->height; i++) {
            a->data[i] = (int *)malloc(a->width * sizeof(int));
            for (int j = 0; j < a->width; j++) {
                a->data[i][j] = b->data[i][j];
            }
        }
    } else {
        a->data = NULL;
    }
}

void parse(struct State *s, struct PNG *p) {
    int width = png_get_width(p);
    int height = png_get_height(p);
    s->width = width;
    s->height = height;

    s->data = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        s->data[i] = (int *)malloc(width * sizeof(int));
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r = get_red(p, x, y);
            int g = get_green(p, x, y);
            int b = get_blue(p, x, y);
            int industry = 255 * 255 * 3 - r * r - g * g - b * b;
            s->data[y][x] = industry;
        }
    }
}

int solve1(struct State *s) {
    int **dp = (int **)malloc(s->height * sizeof(int *));
    for (int i = 0; i < s->height; i++) {
        dp[i] = (int *)malloc(s->width * sizeof(int));
    }

    dp[0][0] = s->data[0][0];
    for (int i = 1; i < s->height; i++) {
        dp[i][0] = dp[i - 1][0] + s->data[i][0];
    }
    for (int j = 1; j < s->width; j++) {
        dp[0][j] = dp[0][j - 1] + s->data[0][j];
    }
    for (int i = 1; i < s->height; i++) {
        for (int j = 1; j < s->width; j++) {
            dp[i][j] = s->data[i][j] + ((dp[i - 1][j] < dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1]);
        }
    }

    int result = dp[s->height - 1][s->width - 1];
    // Clean up memory
    for (int i = 0; i < s->height; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int solve2(struct State *s) {
    int min1 = solve1(s); // Calculate the minimum sum of industries

    int **dp = (int **)malloc(s->height * sizeof(int *));
    for (int i = 0; i < s->height; i++) {
        dp[i] = (int *)malloc(s->width * sizeof(int));
    }

    dp[0][0] = s->data[0][0];
    for (int i = 1; i < s->height; i++) {
        dp[i][0] = dp[i - 1][0] + s->data[i][0];
    }
    for (int j = 1; j < s->width; j++) {
        dp[0][j] = dp[0][j - 1] + s->data[0][j];
    }
    for (int i = 1; i < s->height; i++) {
        for (int j = 1; j < s->width; j++) {
            dp[i][j] = s->data[i][j] + ((dp[i - 1][j] < dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1]);
        }
    }

    int result = dp[s->height - 1][s->width - 1];
    if (result == min1) {
        result = dp[s->height - 2][s->width - 2];
    }

    // Clean up memory
    for (int i = 0; i < s->height; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

   
