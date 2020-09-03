
#include "camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

/* 
 * @功能：			拍一张照片，保存到/目录下，文件名为capture.jpg
 * @返回值：		 0		正常
 * 					-1		打开/dev/video0失败
 */
int take_a_picture(void)
{
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	int fd = 0;
	void *buff = NULL;
	int size = 0;
	int filefd;

	fd = open("/dev/video0", O_RDWR);
	if (fd < 0)
	{
		printf("open error\r\n");
		return -1;
	}

	ioctl(fd, VIDIOC_QUERYCAP, &cap);

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 640;
	fmt.fmt.pix.height = 480;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG; // 使用JPEG格式帧，用于静态图像采集
	ioctl(fd, VIDIOC_S_FMT, &fmt);

	buff = malloc(1024 * 1024); // 分配缓存足以容纳一帧图像
	size = read(fd, buff, 1024 * 1024);
	filefd = open("/capture.jpg", O_RDWR | O_CREAT);
	write(filefd, buff, size);
	close(fd);
	close(filefd);

	return 0;
}
