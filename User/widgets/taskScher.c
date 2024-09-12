/**
  ******************************************************************************
  *
  * @file    taskScher.c
  * @author  GarMing
  * @brief   
  *
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  **/
  
  
/*********************
 *      INCLUDES
 *********************/
#include "taskScher.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/
static uint32_t get_tick_elaps(uint32_t prev_tick);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t (* get_tick)(void) = NULL;

static volatile uint8_t s_PriorityEnable;

static volatile uint32_t s_TasksUsageTime;

static task_scher_ctx_t * s_HeadTaskHandle;
static task_scher_ctx_t * s_TailTaskHandle;
static task_scher_ctx_t s_TaskPool[MAX_TASK_ITEMS];

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void taskScher_init(uint32_t (* pf_get_tick)(void))
{
    s_HeadTaskHandle = NULL;
    s_TailTaskHandle = NULL;

    memset(s_TaskPool, 0, sizeof(s_TaskPool));

    get_tick = pf_get_tick;
}

task_scher_ctx_t * taskScher_find_task(task_scher_cb_t pf_task_cb)
{
    task_scher_ctx_t * task_handle = NULL;

    task_handle = s_HeadTaskHandle;

    for(;;) {

         /*!< 当前节点是否为空*/
        if(task_handle == NULL) {
            return NULL;       
        }

        if(task_handle->task_cb == pf_task_cb) {     /**< 判断函数地址是否相等*/
            return task_handle;
        }
        
        task_handle = task_handle->next_task_handle;           /**< 移动到下一个节点*/
    }
}

task_scher_ctx_t * taskScher_get_prev_task(task_scher_ctx_t * self)
{
    /*!< 当前节点 */
    task_scher_ctx_t * task_handle = s_HeadTaskHandle;

    /*!< 前一节点 */
    task_scher_ctx_t * prev_task_handle = NULL;

    /*!< 开始遍历链表 */
    for(;;) {

        /*!< 如果当前节点为空 */
        if(task_handle == NULL) {

            /*!< 遍历结束 */
            return NULL;
        }

        /*!< 如果当前节点与被搜索的节点匹配 */
        if(task_handle == self) {

            /*!< 返回任务句柄 */
            return prev_task_handle;
        }

        /*!< 当前节点保存为前一节点 */
        prev_task_handle = task_handle;

        /*!< 节点后移 */
        task_handle = task_handle->next_task_handle;
    }
}

task_scher_ctx_t * taskScher_get_next_task(task_scher_ctx_t * self)
{
    return (self->next_task_handle);
}

task_scher_ctx_t * taskScher_register_task(task_scher_cb_t pf_task_cb, uint32_t period, uint8_t state)
{
    uint32_t idx = 0;

    /*!< 寻找当前函数 */
    task_scher_ctx_t * task_handle = taskScher_find_task(pf_task_cb);

    /*!< 如果被注册 */
    if(task_handle != NULL) {

        /*!< 更新信息 */
        task_handle->time_period = period;
        task_handle->state = state;

        return task_handle;
    }

    for(idx = 0; idx < MAX_TASK_ITEMS - 1; idx++) {
        if(s_TaskPool[idx].task_cb == NULL) {
            break;
        }
    }

    /*!< 为新任务申请内存 */
    task_handle = &s_TaskPool[idx];

    task_handle->id_num             = idx;
    task_handle->state              = state;            /**< 任务状态*/
    task_handle->time_period        = period;           /**< 任务执行周期*/
    task_handle->time_prev          = 0;                /**< 上一次时间*/
    task_handle->time_cost          = 0;                /**< 时间开销*/
    task_handle->time_error         = 0;                /**< 误差时间*/
    task_handle->task_cb            = pf_task_cb;       /**< 任务回调函数*/
    task_handle->next_task_handle   = NULL;             /**< 下一个节点*/

    /*!< 如果任务链表为空 */
    if(s_HeadTaskHandle == NULL) {

        /*!< 将当前任务作为链表的头 */
        s_HeadTaskHandle = task_handle;
    }
    else {
        
        /*!< 从任务链表尾部添加任务 */
        s_TailTaskHandle->next_task_handle = task_handle;
    }

    /*!< 将当前任务作为链表的尾 */
    s_TailTaskHandle = task_handle;

    return task_handle;
}

int8_t taskScher_logout_task(task_scher_cb_t pf_task_cb)
{
    uint32_t idx = 0;
    task_scher_ctx_t * task_handle = taskScher_find_task(pf_task_cb);

    if(task_handle == NULL) {
        return -1;
    }

    task_scher_ctx_t * prev_task_handle = taskScher_get_prev_task(task_handle);   /**< 前一个节点*/
    task_scher_ctx_t * next_task_handle = taskScher_get_next_task(task_handle);   /**< 后一个节点*/

    /*!< 如果被删除节点在链表头 */
    if((prev_task_handle == NULL) && (next_task_handle != NULL)) {

        /*!< 将后一个节点作为链表头 */
        s_HeadTaskHandle = next_task_handle;
    }

    /*!< 如果被删除节点在链表尾 */
    else if((prev_task_handle != NULL) && (next_task_handle == NULL)) {

        /*!< 将前一个节点作为链表尾 */
        prev_task_handle->next_task_handle = NULL;
    }

    /*!< 如果被删除节点在链表中间 */
    else if((prev_task_handle != NULL) && (next_task_handle != NULL)) {

        /*!< 将前一个节点对接至后一个节点 */
        prev_task_handle->next_task_handle = next_task_handle;
    }

    for(idx = next_task_handle->id_num; idx < MAX_TASK_ITEMS - 1; idx++) {
        s_TaskPool[idx] = s_TaskPool[idx + 1];
        s_TaskPool[idx].id_num = idx;
    }

    /*!< 删除当前节点 */
    memset(next_task_handle, 0, sizeof(task_scher_ctx_t));

    return 0;
}

int8_t taskScher_set_state(task_scher_cb_t pf_task_cb, uint8_t state)
{
    task_scher_ctx_t * task_handle = taskScher_find_task(pf_task_cb);

    if(task_handle == NULL) {
        return -1;
    }

    task_handle->state = state;

    return 0;
}

int8_t taskScher_set_period(task_scher_cb_t pf_task_cb, uint32_t period_ms)
{
    task_scher_ctx_t * task_handle = taskScher_find_task(pf_task_cb);

    if(task_handle == NULL) {
        return -1;
    }

    task_handle->time_period = period_ms;

    return 0;
}

float taskScher_get_cpu_usage(void)
{
    static uint32_t start_time;

    float usage = (float)s_TasksUsageTime / (get_tick() - start_time) * 100.0f;
    
    if(usage > 100.0f) usage = 100.0f;

    start_time = get_tick();
    
    s_TasksUsageTime = 0;

    return usage;
}

uint32_t taskScher_get_time_cost(task_scher_cb_t pf_task_cb)
{
    task_scher_ctx_t * task_handle = taskScher_find_task(pf_task_cb);

    if(task_handle == NULL) {
        return 1;
    }

    return task_handle->time_cost;
}

void taskScher_handler(void)
{
    if(get_tick == NULL) {
        return;
    }

    uint32_t ticks = get_tick();
    
    task_scher_ctx_t * task_handle = s_HeadTaskHandle;
    
    for(;;) {

        /*!< 当前节点是否为空 */
        if(task_handle == NULL) {

            /*!< 遍历结束 */
            break;
        }
        
        if((task_handle->task_cb != NULL) && (task_handle->state)) {
            
            uint32_t time_elaps = get_tick_elaps(task_handle->time_prev);

            if(time_elaps >= task_handle->time_period) {
                
                /*!< 获取时间误差，误差越大实时性越差 */
                task_handle->time_error = time_elaps - task_handle->time_period;
                
                /*!< 记录时间点 */
                task_handle->time_prev = ticks;
                
                /*!< 记录开始时间 */
                uint32_t start_time = get_tick();
                
                /*!< 执行任务 */
                task_handle->task_cb();
                
                /*!< 获取执行时间 */
                uint32_t time_cost = get_tick() - start_time;
                
                /*!< 记录执行时间 */
                task_handle->time_cost = time_cost;
                
                /*!< 总时间累加 */
                s_TasksUsageTime += time_cost;
                
                /*!< 判断是否开启优先级 */
                if(s_PriorityEnable) break;
            }
        }
        
        /*!< 移动到下一个节点 */
        task_handle = task_handle->next_task_handle;
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static uint32_t get_tick_elaps(uint32_t prev_tick)
{
    uint32_t act_time = get_tick();

    /*If there is no overflow in sys_time simple subtract*/
    if(act_time >= prev_tick) {
        prev_tick = act_time - prev_tick;
    }
    else {
        prev_tick = UINT32_MAX - prev_tick + 1;
        prev_tick += act_time;
    }

    return prev_tick;
}

/******************************* (END OF FILE) *********************************/
