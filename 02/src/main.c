#define NVIC_INT_CTRL		0xE000ED04
#define NVIC_PENDSVSET		0x10000000
#define NVIC_SYSPRI2		0xE000ED22
#define NVIC_PENDSV_PRI		0x000000FF

#define MEM32(addr)		*(volatile unsigned long*)(addr)
#define MEM8(addr)		*(volatile unsigned char*)(addr)
	

//Cortex-M 的栈单元类型：堆栈单元的大小为32位
typedef unsigned long tTaskStack;

//任务结构：包含了把一任务的所有信息
typedef struct _tTask{
	
	unsigned long * stack;
}tTask;

tTask tTask1;
tTask tTask2;

tTaskStack task1Env[1024];
tTaskStack tsak2Env[1024];



void triggerPendSVC(void)
{
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

typedef struct _BlockType_t
{
	unsigned long *stackPtr;
}BlockType_t;


BlockType_t * blockPtr;

void delay(int count)
{
	while(--count > 0);
}
int flag;
unsigned long stackBuffer[1024];
BlockType_t block;
int main()
{

	block.stackPtr = &stackBuffer[1024];
	blockPtr = &block;
	while(1)
	{
		delay(200);
		triggerPendSVC();
	}
	return 0;
}
