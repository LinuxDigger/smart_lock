#ifndef __SERVER_MOTO_H
#define __SERVER_MOTO_H

#include <stdint.h>
/*
 * 关锁 开锁 关门 开门 函数
 * 方便调用
 *
 */
#define LOCK_DOOR()             lock_door_ctrl(0, -1)
#define UNLOCK_DOOR()           lock_door_ctrl(1, -1)
#define CLOSE_DOOR()            lock_door_ctrl(-1, 0)
#define OPEN_DOOR()             lock_door_ctrl(-1, 1)

/* 
 * @功能：		初始化内部电路以便控制舵机，
 *				初始化完成后要先配置角度，
 *				再启动舵机，然后在之后的操作中
 * 				直接调整角度即可，但不要超过限制值
 * @返回值：	 0		正常
 * 				-1		打开export文件失败
 * 				-2		写入export文件失败
 * 				-3		打开参数文件失败
 * 				-4		打开period文件失败
 * 				-5		写入period文件失败
 */
int server_moto_init(void);

/* 
 * @功能：		退出时关闭文件
 */
void server_moto_exit(void);

/*
 * @功能：			控制角度
 * @参数：			short lock, short door
 * 					分别对应锁和门
 *                  参数为0表示关闭，参数为不为0且大于0则表示打开
 * 					角度为负数即保持当前角度不变
 * @返回值：          0		正常
 * 					-1		写入duty_cycle失败
 * 					-2		写入enable失败
 */
int lock_door_ctrl(short lock, short door);

#endif // !__SERVER_MOTO_H
