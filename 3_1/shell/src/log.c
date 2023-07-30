/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l) {
    // 检查参数是否合法
    if (l == NULL) {
        return;
    }
    // 把 head 指针设为 NULL
    l->head = NULL;
}

/**
销毁一个log，释放所有内存空间，log的“析构函数”
 */

void log_destroy(log_t* l) {
    // 检查参数是否合法
    if (l == NULL || l->head == NULL) {
        return;
    }
    // 定义一个临时指针，用来遍历链表
    node *temp = l->head;
    
    // 循环释放每个结点的内存空间
    while (temp != NULL) {
        // 保存下一个结点的地址
        node *next = temp->next;
        // 释放当前结点的 cmd 字符串的内存空间
        if(temp->cmd!=NULL)
        free(temp->cmd);
        // 释放当前结点的内存空间
        if(temp!=NULL)
        free(temp);
        // 移动到下一个结点
        temp = next;
    }
   
    // 把 head 指针设为 NULL
   // l->head = NULL;
}

/**
向log中推入一个字符串，你可以将log视为一个由链表组成的栈
 */

void log_push(log_t* l, const char *item) {
    // 检查参数是否合法
    if (l == NULL || item == NULL) {
        return;
    }
    // 为新的结点分配内存空间
    node *new_node = (node *)malloc(sizeof(node));
    // 检查内存分配是否成功
    if (new_node == NULL) {
        return;
    }
    // 为新结点的 cmd 字符串分配内存空间，并复制 item 的内容
    new_node->cmd = item;
    // 检查内存分配是否成功
    if (new_node->cmd == NULL) 
    {
        // 如果失败，释放新结点的内存空间，并返回
        free(new_node);
        return;
    }
    // 把新结点插入到链表的头部
    new_node->next = l->head;
    l->head = new_node;
}

/**
搜索log中是否含有对应前缀的字符串
 */

char *log_search(log_t* l, const char *prefix) {
    // 检查参数是否合法
    if (l == NULL || l->head == NULL || prefix == NULL) {
        return NULL;
    }
    // 定义一个临时指针，用来遍历链表
    node *temp = l->head;
    // 循环比较每个结点的 cmd 字符串是否包含 prefix
    while (temp != NULL) {
        // 如果包含 prefix，就返回这个字符串
        if (strncmp(temp->cmd, prefix, strlen(prefix)) == 0) {
            return temp->cmd;
        }
        // 移动到下一个结点
        temp = temp->next;
    }
    // 如果没有找到，就返回 NULL
    return NULL;
}
