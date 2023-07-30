#ifndef STATE_H_
#define STATE_H_
#include "suan_png.h"
#include "pxl.h"


struct State {
    int **data;
    int height;
    int width;
};

// function
void init_State(struct State *s);
void delete_State(struct State *s);
void assign(struct State *a, struct State *b);
void parse(struct State *s, struct PNG *p);
int solve1(struct State *s);
int solve2(struct State *s);
void insert(int u, int v, double w);
void insert2(int u, int v, double w);
void Path(int x);
int in(struct State *s,int x,int y);
int idx(struct State *s,int x,int y);

#endif
