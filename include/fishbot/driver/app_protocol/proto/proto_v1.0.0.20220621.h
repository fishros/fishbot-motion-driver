/**
 * @brief 文件描述：V1.0.0.220621版本协议实现代码，
 *        主要用于根据协议定义帧、进行数据帧的解析与合成。
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _PROTO_V1_0_0_220621_H_
#define _PROTO_V1_0_0_220621_H_

#include <cstdint>

#define FIRST_CODE 0x5A
#define END_CODE 0x5A

#define MAX_MOTOR_NUM 2

/**
 * @brief 数据ID定义
 *
 */
typedef enum {
  DATA_ENCODER = 0x01,  // 0x01-左右轮编码器
  DATA_IMU,             // 0x02-IMU传感器
  DATA_SPEED,           // 0x03-速度控制数据
  DATA_PID,             // 0x04-PID设置
  DATA_VER_INFO,        // 0x05-版本信息
} __attribute__((packed)) proto_data_id_t;

/**
 * @brief 数据传输方向定义
 *
 */
typedef enum {
  DATA_TO_MASTER = 0x01,  // 0x01,反馈数据（底盘向主控）
  DATA_TO_FBMC,           // 0x02,命令数据（主控向底盘）
} __attribute__((packed)) proto_data_direction_t;

/**
 * @brief 数据帧的目标地址
 *
 */
typedef enum {
  DATA_TARGET_ADDR_PC = 0x01,  // 0x01 目标地址电脑
  DATA_TARGET_ADDR_FBMC = 0x02,  // 0x02 目标地址FishBot运动控制板
} __attribute__((packed)) proto_data_target_addr_t;

/**
 * @brief PID数据结构体
 *
 */
typedef struct {
  float kp;
  float ki;
  float kd;
} proto_pid_data_t;

/**
 * @brief 电机编码器数据结构体
 *
 */
typedef struct {
  int32_t motor_encoder[MAX_MOTOR_NUM];  // 电机的编码器数据
} __attribute__((packed)) proto_motor_encoder_data_t;

/**
 * @brief 数据段头
 *
 */
typedef struct {
  proto_data_id_t data_id;                // 数据编号ID
  uint16_t data_len;                      // 数据长度 2
  proto_data_direction_t data_direction;  // 数据方向
} __attribute__((packed)) proto_data_header_t;

/**
 * @brief 电机速度控制结构体
 *
 */
typedef struct {
  int16_t motor_speed[MAX_MOTOR_NUM];  // 单位mm/s
} __attribute__((packed))  proto_motor_speed_ctrl_data_t;

/**
 * @brief IMU数据结构体
 *
 */
typedef struct
{
    float accel[3]; // 加速度
    float gyro[3];  // 重力加速度
    float euler[3]; // 欧拉角 RPY
} __attribute__((packed))  proto_imu_data_t;


#endif  // _PROTO_V1_0_0_220621_H_