/**
  ******************************************************************************
  *
  * @file    bsp_task.c
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
#include "bsp_task.h"
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
static uint32_t _bsp_task_get_time_interval(uint32_t act_time, uint32_t prev_time);

/**********************
 *  STATIC VARIABLES
 **********************/
static volatile uint8_t s_PriorityEnable;

static volatile uint32_t s_SysElapsTime;
static volatile uint32_t s_TasksUsageTime;

static bsp_task_t * s_pHeadTask;
static bsp_task_t * s_pTailTask;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void _ttywrch(int ch)
{
    ch = ch;
}

void bsp_task_tick_init( bsp_task_class_t * self,
                         void     (* pf_init)(void),
                         void     (* pf_deinit)(void),
                         uint32_t (* pf_get_beat)(void) )
{
    self->hearbeat_interface.init      = pf_init;
    self->hearbeat_interface.deinit    = pf_deinit;
    self->hearbeat_interface.get_beat  = pf_get_beat;
}


/**
  * @brief  初始化任务列表
  * @param  priorityEnable:设定是否开启优先级
  * @retval 无
  */
void bsp_task_init_list(void)
{
    s_pHeadTask = NULL;
    s_pTailTask = NULL;
}

/**
  * @brief  调度器析构，释放任务链表内存
  * @param  无
  * @retval 无
  */
void bsp_task_clear(void)
{
    /*!< 移动到链表头 */
    bsp_task_t * pTask = NULL;

    bsp_task_t * pTaskNext = s_pHeadTask;

    for(;;) {

        /*!< 当前节点是否为空 */
        if(pTaskNext == NULL) {
            break;
        }

        /*!< 将当前节点缓存，等待删除 */
        pTask = pTaskNext;

        /*!< 删除当前节点内存 */
        free(pTask);

        /*!< 移动到下一个节点 */
        pTaskNext = pTaskNext->pNextTask;
    }
}

/**
  * @brief  寻找任务,返回任务节点
  * @param  func:任务函数指针
  * @retval 任务节点地址
  */
bsp_task_t * bsp_task_find(bsp_task_cb_f pFunc)
{
    bsp_task_t * pTask = NULL;

    pTask = s_pHeadTask;

    for(;;) {

         /*!< 当前节点是否为空*/
        if(pTask == NULL) {
            return BSP_TASK_NONE;       
        }

        if(pTask->pCallback == pFunc) {     /**< 判断函数地址是否相等*/
            return pTask;
        }
        
        pTask = pTask->pNextTask;           /**< 移动到下一个节点*/
    }
}

/**
  * @brief  往任务链表添加一个任务，设定间隔执行时间
  * @param  func:任务函数指针
  * @param  timeMs:周期时间设定(毫秒)
  * @param  state:任务开关
  * @retval 任务节点地址
  */
bsp_task_t * bsp_task_register(bsp_task_cb_f pFunc, uint32_t period, uint8_t state)
{
    /*!< 寻找当前函数 */
    bsp_task_t * pTask = bsp_task_find(pFunc);

    /*!< 如果被注册 */
    if(pTask != NULL) {

        /*!< 更新信息 */
        pTask->time_period = period;
        pTask->state = state;
        return pTask;
    }

    /*!< 为新任务申请内存 */
    pTask = (bsp_task_t *)malloc(sizeof(bsp_task_t));

    /*!< 是否申请成功 */
    if(pTask == NULL) {
        return BSP_TASK_NONE;
    }

    pTask->state        = state;        /**< 任务状态*/
    pTask->time_period  = period;       /**< 任务执行周期*/
    pTask->time_prev    = 0;            /**< 上一次时间*/
    pTask->time_cost    = 0;            /**< 时间开销*/
    pTask->time_error   = 0;            /**< 误差时间*/
    pTask->pCallback    = pFunc;        /**< 任务回调函数*/
    pTask->pNextTask    = NULL;         /**< 下一个节点*/

    /*!< 如果任务链表为空 */
    if(s_pHeadTask == NULL) {

        /*!< 将当前任务作为链表的头 */
        s_pHeadTask = pTask;
    }
    else {
        
        /*!< 从任务链表尾部添加任务 */
        s_pTailTask->pNextTask = pTask;
    }

    /*!< 将当前任务作为链表的尾 */
    s_pTailTask = pTask;

    return pTask;
}

/**
  * @brief  获取当前节点的前一个节点
  * @param  task:当前任务节点地址
  * @retval 前一个任务节点地址
  */
bsp_task_t * bsp_task_get_prev(bsp_task_t * pHandle)
{
    /*!< 当前节点 */
    bsp_task_t * pTask = s_pHeadTask;

    /*!< 前一节点 */
    bsp_task_t * pTaskPrev = NULL;

    /*!< 开始遍历链表 */
    for(;;) {

        /*!< 如果当前节点为空 */
        if(pTask == NULL) {

            /*!< 遍历结束 */
            return BSP_TASK_NONE;
        }

        /*!< 如果当前节点与被搜索的节点匹配 */
        if(pTask == pHandle) {

            /*!< 返回任务句柄 */
            return pTaskPrev;
        }

        /*!< 当前节点保存为前一节点 */
        pTaskPrev = pTask;

        /*!< 节点后移 */
        pTask = pTask->pNextTask;
    }
}

/**
  * @brief  获取当前节点的后一个节点
  * @param  task:当前任务节点地址
  * @retval 后一个任务节点地址
  */
bsp_task_t * bsp_task_get_next(bsp_task_t * pHandle)
{
    return pHandle->pNextTask;
}

/**
  * @brief  注销任务（谨慎使用，线程不安全）
  * @param  func:任务函数指针
  * @retval true:成功 ; false:失败
  */
int bsp_task_logout(bsp_task_cb_f pFunc)
{
    bsp_task_t * pCurrentTask = bsp_task_find(pFunc);

    if(pCurrentTask == NULL) {
        return BSP_TASK_FALSE;
    }

    bsp_task_t * pPrevTask = bsp_task_get_prev(pCurrentTask);   /**< 前一个节点*/
    bsp_task_t * pNextTask = bsp_task_get_next(pCurrentTask);   /**< 后一个节点*/

    /*!< 如果被删除节点在链表头 */
    if((pPrevTask == NULL) && (pNextTask != NULL)) {

        /*!< 将后一个节点作为链表头 */
        s_pHeadTask = pNextTask;
    }

    /*!< 如果被删除节点在链表尾 */
    else if((pPrevTask != NULL) && (pNextTask == NULL)) {

        /*!< 将前一个节点作为链表尾 */
        pPrevTask->pNextTask = NULL;
    }

    /*!< 如果被删除节点在链表中间 */
    else if((pPrevTask != NULL) && (pNextTask != NULL)) {

        /*!< 将前一个节点对接至后一个节点 */
        pPrevTask->pNextTask = pNextTask;
    }

    /*!< 删除当前节点 */
    free(pNextTask);

    return BSP_TASK_TRUE;

}

/**
  * @brief  任务状态控制
  * @param  func:任务函数指针
  * @param  state:任务状态
  * @retval 1:成功 ; 0:失败
  */
int bsp_task_set_state(bsp_task_cb_f pFunc, uint8_t state)
{
    bsp_task_t * pTask = bsp_task_find(pFunc);

    if(pTask == NULL) {
        return BSP_TASK_FALSE;
    }

    pTask->state = state;
    return BSP_TASK_TRUE;
}

/**
  * @brief  任务执行周期设置
  * @param  func:任务函数指针
  * @param  timeMs:任务执行周期
  * @retval 1:成功 ; 0:失败
  */
int bsp_task_set_period(bsp_task_cb_f pFunc, uint32_t period_ms)
{
    bsp_task_t * pTask = bsp_task_find(pFunc);

    if(pTask == NULL) {
        return BSP_TASK_FALSE;
    }

    pTask->time_period = period_ms;
    return BSP_TASK_TRUE;
}

/**
  * @brief  获取CPU占用率
  * @param  无
  * @retval CPU占用率，0~100%
  */
float bsp_task_get_cpu_usage(bsp_task_class_t * self)
{
    static uint32_t start_time;

    float usage = (float)s_TasksUsageTime / (self->hearbeat_interface.get_beat() - start_time) * 100.0f;
    
    if(usage > 100.0f) usage = 100.0f;

    start_time = self->hearbeat_interface.get_beat();
    
    s_TasksUsageTime = 0;

    return usage;
}

/**
  * @brief  获取任务单次耗费时间(ms)
  * @param  func:任务函数指针
  * @retval 任务单次耗费时间(ms)
  */
uint32_t bsp_task_get_time_cost(bsp_task_cb_f pFunc)
{
    bsp_task_t * pTask = bsp_task_find(pFunc);

    if(pTask == NULL) {
        return BSP_TASK_FALSE;
    }

    return pTask->time_cost;
}

/**
  * @brief  调度器(内核)
  * @param  tick:提供一个精确到毫秒的系统时钟变量
  * @retval 无
  */
void bsp_task_handler(bsp_task_class_t * self)
{
    uint32_t ticks = self->hearbeat_interface.get_beat();
    
    bsp_task_t * pTask = s_pHeadTask;
    
    for(;;) {

        /*!< 当前节点是否为空 */
        if(pTask == NULL) {

            /*!< 遍历结束 */
            break;
        }
        
        if((pTask->pCallback != NULL) && (pTask->state)) {
            
            uint32_t time_elaps = _bsp_task_get_time_interval(ticks, pTask->time_prev);

            if(time_elaps >= pTask->time_period) {
                
                /*!< 获取时间误差，误差越大实时性越差 */
                pTask->time_error = time_elaps - pTask->time_period;
                
                /*!< 记录时间点 */
                pTask->time_prev = ticks;
                
                /*!< 记录开始时间 */
                uint32_t start_time = self->hearbeat_interface.get_beat();
                
                /*!< 执行任务 */
                pTask->pCallback();
                
                /*!< 获取执行时间 */
                uint32_t time_cost = self->hearbeat_interface.get_beat() - start_time;
                
                /*!< 记录执行时间 */
                pTask->time_cost = time_cost;
                
                /*!< 总时间累加 */
                s_TasksUsageTime += time_cost;
                
                /*!< 判断是否开启优先级 */
                if(s_PriorityEnable) break;
            }
        }
        
        /*!< 移动到下一个节点 */
        pTask = pTask->pNextTask;
    }
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
  * @brief  时间差判定
  * @param  actTick:当前时间
  * @param  prevTick:上一个时间
  * @retval 时间差
  */
static uint32_t _bsp_task_get_time_interval(uint32_t act_time, uint32_t prev_time)
{
    if(act_time >= prev_time) {
        prev_time = act_time - prev_time;
    }
    else {
        prev_time = 0xFFFFFFFF - prev_time + 1;
        prev_time += act_time;
    }
    
    return prev_time;
}



/******************************* (END OF FILE) *********************************/
