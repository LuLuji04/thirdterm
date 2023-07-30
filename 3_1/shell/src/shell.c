#include "shell.h"
/**
 * shell的入口
 */

//void freearg


void prefix() 
{
    // 定义一个字符数组，用来存储当前目录的路径
    char cwd[MAX_SIZE];
    char *ptr;
    memset(cwd,0x0,sizeof(cwd));
    ptr = getcwd(cwd,sizeof(cwd));
    // 调用 getcwd 函数，获取当前目录的路径，并存入 cwd 数组
    if (ptr == NULL) 
    {
        // 如果获取失败，打印错误信息，并退出程序
        perror("getcwd");
        exit(-1);
    }
    // 打印当前目录的路径和一个美元符号
    printf("%s$ ", cwd);
}

int execute(char* buffer) 
{
    // 检查参数是否合法
    if (buffer == NULL) 
    {
        return 1;
    }
    // 定义一个字符指针数组，用来存储命令和参数
    char *args[MAX_SIZE];
    // 调用 split 函数，把 buffer 按照空格分割成多个字符串，并存入 args 数组
    char argbuf[MAX_SIZE] ;
    strcpy(argbuf,buffer);
    int n = split(args, argbuf, " ");
    
    // 检查分割是否成功
    if (n == 0) 
    {
        return 1;
    }

    // 把输入的命令放入 log_t 中，除非是以 ! 开头的命令
    if (args[0][0] != '!') 
    {
        char* temp = (char*)malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(temp, buffer);
        log_push(&Log, temp);
    }

    // 判断第一个字符串是什么命令
    if (strcmp(args[0], "cd") == 0) 
    {
        // 如果是 cd 命令，就调用 chdir 函数，切换到指定的目录
        int ret = chdir(args[1]);
        if (ret == -1) 
        {
            // 如果切换失败，打印错误信息
            printf("%s: No such file or directory\n", args[1]);
            exit(-1);
        }
    } 

    else if (strcmp(args[0], "exit") == 0) 
    {
        // 如果是 exit 命令，就返回 0，表示退出程序
        return 0;
    } 

    else if (strcmp(args[0], "!#") == 0) 
    {
        // 如果是 !# 命令，就调用 list_log 函数，显示所有输入过的命令
        list_log(&Log);
    } 

    else if (args[0][0] == '!') 
    {
        // 如果是 ! 开头的命令，就调用 log_search 函数，搜索是否有包含指定前缀的命令
        char *cmd = log_search(&Log, args[0] + 1);
        if (cmd == NULL) 
        {
            // 如果没有找到，就打印 No Match 并换行
            printf("No Match\n");
        } 
        else 
        {
            // 如果找到了，就递归调用 execute 函数，执行这个命令，并把这个命令放入 log_t 中
            char *cmd1=(char *)malloc(sizeof(char)*(strlen(cmd)+1));
            strcpy(cmd1,cmd);
            //log_push(&Log, cmd1);
            execute(cmd1);
        }
    } 

    else if (strcmp(args[0], "ls") == 0) 
    {
        // 如果是 ls 命令，就直接用 system 函数执行这个命令
        system("ls");
    } 

    else 
    {
        // 否则，就认为是一个外部命令，需要用 fork 和 exec 等函数来执行
        // 定义一个进程 id 变量，用来存储子进程的 id
        int pid;
        // 调用 fork 函数，创建一个子进程
        pid = fork();
        // 检查 fork 是否成功
        if (pid < 0) 
        {
            // 如果失败，打印错误信息，并退出程序
            perror("fork");
            exit(1);
        } 
        else if (pid == 0) 
        {
            // 如果成功，并且是子进程，就调用 execvp 函数，执行外部命令
            if (execv(args[0], args) == -1) 
            {
                // 如果执行失败，打印错误信息，并退出程序
                printf("%s: no such command\n", buffer);
                exit(1);
            }
        } 
        else 
        {
            // 如果成功，并且是父进程，就等待子进程结束，并回收资源
            wait(NULL);
        }
    }
    // 返回一个非零值，表示继续循环
    
    //frearg(arg);
    return 1;
}

void list_log(log_t *log) 
{
  // 这个函数的作用是遍历log的链表，从栈底开始打印每个结点的cmd字符串，每个占一行
  // 我们可以使用一个临时指针来遍历链表，从头结点开始
  node *cur = log->head;
  // 如果链表为空，直接返回
  if (cur == NULL) 
  {
    return;
  }
  // 否则，我们可以使用递归的方法来打印链表
  // 首先递归打印后面的结点
  log->head = cur->next; // 将头结点后移一位
  list_log(log); // 递归打印剩余的链表
  log->head = cur; // 将头结点还原
  // 然后打印当前结点的cmd字符串
  printf("%s\n", cur->cmd);
}

int split(char *args[],char* str,const char* spl) 
{
  // 这个函数的作用是将str字符串按照spl分隔符分割成若干个子串，并存放在args数组中
  // 我们可以使用strtok()函数来实现这个功能，它可以将一个字符串分割成一系列的标记(token)
  // 我们需要一个变量来记录分割出来的子串的个数，初始为0
  int count = 0;
  // 我们首先调用strtok()函数，传入str和spl作为参数，它会返回第一个分割出来的子串
  char *token = strtok(str, spl);
  // 我们将这个子串存放在args数组中，并将计数器加一
  args[count++] = token;
  // 然后我们使用一个循环来继续分割剩余的字符串，直到没有更多的子串为止
  while (token != NULL) 
  {
    // 我们再次调用strtok()函数，但是这次传入NULL作为第一个参数，表示继续分割上次的字符串
    token = strtok(NULL, spl);
    // 我们将这个子串存放在args数组中，并将计数器加一
    args[count++] = token;
  }
  // 最后我们返回分割出来的子串的个数
  return count;
}
