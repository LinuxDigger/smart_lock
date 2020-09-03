#ifndef __CAMERA_MOTO_H
#define __CAMERA_MOTO_H

#include <stdint.h>
/* 
 * @功能：			拍一张照片，保存到/目录下，文件名为capture.jpg
 * @返回值：		 0		正常
 * 					-1		打开/dev/video0失败
 */
int take_a_picture(void);

#endif // !__CAMERA_MOTO_H