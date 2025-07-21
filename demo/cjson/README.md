### cJSON的结构体
```c
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7)

typedef struct cJSON
{
  struct cJSON *next, *prev;
  struct cJSON *child;

  int type;

  char *valuestring;
  int valueint;
  double valuedouble;

  char *string;
} cJSON;
```
这里的type是用于区分 JSON 类型  
0 表示 false  
1 表示 true  
2 表示 null  
3 表示 number  
4 表示 string  
5 表示 array  
6 表示 object  