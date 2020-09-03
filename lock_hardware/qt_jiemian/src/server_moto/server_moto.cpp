
#include "server_moto.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MOTO0_EXPORT_DIR "/sys/class/pwm/pwmchip0/export"
#define MOTO1_EXPORT_DIR "/sys/class/pwm/pwmchip1/export"

#define MOTO0_UNEXPORT_DIR "/sys/class/pwm/pwmchip0/unexport"
#define MOTO1_UNEXPORT_DIR "/sys/class/pwm/pwmchip1/unexport"

#define MOTO0_DUTY_CYCLE_DIR "/sys/class/pwm/pwmchip0/pwm0/duty_cycle" //占空比
#define MOTO1_DUTY_CYCLE_DIR "/sys/class/pwm/pwmchip1/pwm0/duty_cycle"

#define MOTO0_PERIOD_DIR "/sys/class/pwm/pwmchip0/pwm0/period" //周期
#define MOTO1_PERIOD_DIR "/sys/class/pwm/pwmchip1/pwm0/period"

#define MOTO0_ENABLE_DIR "/sys/class/pwm/pwmchip0/pwm0/enable" //使能开关
#define MOTO1_ENABLE_DIR "/sys/class/pwm/pwmchip1/pwm0/enable"

static int fd_duty_cycle[2];
static int fd_enable[2];
static int64_t duty_cycle;

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
 * duty_cycle文件写入值大于perid
 */
int server_moto_init(void)
{
	int ret = 0;
	int fd_export = 0, fd_period = 0;
    char duty_cycle_str[10];

	/* 导出设备 */
	{
		fd_export = open(MOTO0_EXPORT_DIR, O_WRONLY); //舵机1
		if (fd_export < 0)
		{
			return -1;
		}
		ret = write(fd_export, "0", strlen("0"));
		if (ret < 0)
		{
			return -2;
		}
		close(fd_export);

		fd_export = open(MOTO1_EXPORT_DIR, O_WRONLY); //舵机2
		if (fd_export < 0)
		{
			return -1;
		}
		ret = write(fd_export, "0", strlen("0"));
		if (ret < 0)
		{
			return -2;
		}
		close(fd_export);
	}

	/* 写入周期 */
	{
		fd_period = open(MOTO0_PERIOD_DIR, O_WRONLY); //舵机1
		if (fd_period < 0)
		{
			return -4;
		}
		ret = write(fd_period, "20000000", strlen("20000000")); // 20ms周期
		if (ret < 0)
		{
			return -5;
		}
		close(fd_period);

		fd_period = open(MOTO1_PERIOD_DIR, O_WRONLY); //舵机2
		if (fd_period < 0)
		{
			return -4;
		}
		ret = write(fd_period, "20000000", strlen("20000000")); // 20ms周期
		if (ret < 0)
		{
			return -5;
		}
		close(fd_period);
	}

	/* 打开参数文件 */
	{
        fd_duty_cycle[0] = open(MOTO0_DUTY_CYCLE_DIR, O_RDWR);
        fd_duty_cycle[1] = open(MOTO1_DUTY_CYCLE_DIR, O_RDWR);

		fd_enable[0] = open(MOTO0_ENABLE_DIR, O_WRONLY);
		fd_enable[1] = open(MOTO1_ENABLE_DIR, O_WRONLY);

        if (fd_duty_cycle[0] == 0 || fd_duty_cycle[1] == 0 || fd_enable[0] == 0 || fd_enable[1] == 0)
		{
			return -3;
		}
    }

    duty_cycle = 2480000;
    sprintf(duty_cycle_str, "%d", duty_cycle);
    printf ("\r\n%s\r\n", duty_cycle_str);
    write(fd_duty_cycle[1], duty_cycle_str, strlen(duty_cycle_str));
    if (ret < 0)
    {
        printf ("\r\n-6!!!\r\n");
        return -6;
    }

	return 0;
}

/* 
 * @功能：		退出时关闭文件
 */
void server_moto_exit(void)
{
	int fd_unexport;

	close(fd_duty_cycle[0]);
	close(fd_duty_cycle[1]);

	close(fd_enable[0]);
	close(fd_enable[1]);

	fd_unexport = open(MOTO0_UNEXPORT_DIR, O_WRONLY); //舵机1
	write(fd_unexport, "0", strlen("0"));
	close(fd_unexport);

	fd_unexport = open(MOTO1_UNEXPORT_DIR, O_WRONLY); //舵机2
	write(fd_unexport, "0", strlen("0"));
	close(fd_unexport);
}

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
int lock_door_ctrl(short lock, short door)
{
    int ret = 0;

    if (lock >= 0)
    {
        int64_t duty_cycle_temp = duty_cycle;

        char duty_cycle_str[10];
        if (lock)
        {
            duty_cycle = 1500000;
        }
        else
        {
            duty_cycle = 500000;
        }

        sprintf(duty_cycle_str, "%d", duty_cycle);
        write(fd_duty_cycle[0], duty_cycle_str, strlen(duty_cycle_str));
        if (ret < 0)
        {
            return -1;
        }

        write(fd_enable[0], "1", strlen("1"));
        if (ret < 0)
        {
            return -2;
        }

        duty_cycle = duty_cycle_temp;
    }

    if (door >= 0)
    {
        sleep(2);

        char duty_cycle_str[10];

        while (1)
        {
            if (door)         //open
            {
                if (duty_cycle <= 1800000)
                {
                    break;
                }
                else
                {
                    duty_cycle -= 1000;
                }
            }
            else            //close
            {
                if (duty_cycle >= 2480000)
                {
                    break;
                }
                else
                {
                    duty_cycle += 1000;
                }
            }

            sprintf(duty_cycle_str, "%d", duty_cycle);

            write(fd_duty_cycle[1], duty_cycle_str, strlen(duty_cycle_str));
            if (ret < 0)
            {
                return -1;
            }

            usleep(3000);
        }

        write(fd_enable[1], "1", strlen("1"));
        if (ret < 0)
        {
            return -2;
        }
    }

	return 0;
}
