/**
 * @brief
 * 文件描述：V1.0.0.2200806版本协议实现代码
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-08-06
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _PROTO_V1_0_0_220806_H_
#define _PROTO_V1_0_0_220806_H_

#include "string.h"
#include <cstdint>

#define FIRST_CODE 0x5A
#define END_CODE 0x5A
#define MAX_MOTOR_NUM 2

/**************************************公共定义结构体******************************************/

/**
 * @brief 数据ID定义
 *
 */
typedef enum
{
  DATA_ENCODER = 0x01, // 0x01-左右轮编码器
  DATA_IMU,            // 0x02-IMU传感器
  DATA_SPEED,          // 0x03-速度控制数据
  DATA_PID,            // 0x04-PID设置
  DATA_VER_INFO,       // 0x05-版本信息
  DATA_WIFI_CONFIG,    // 0x06-WIFI配置
  DATA_DEV_CONTROL,    // 0x07-设备控制
  DATA_PROTO_MODE,     // 0x08-通讯模式设置
} __attribute__((packed)) proto_data_id_t;

/**
 * @brief 数据传输方向定义
 *
 */
typedef enum
{
  DATA_TO_MASTER = 0x01, // 0x01,反馈数据（底盘向主控）
  DATA_TO_FBMC,          // 0x02,命令数据（主控向底盘）
} __attribute__((packed)) proto_data_direction_t;

/**
 * @brief 数据帧的目标地址
 *
 */
typedef enum
{
  DATA_TARGET_ADDR_PC = 0x01,   // 0x01 目标地址电脑
  DATA_TARGET_ADDR_FBMC = 0x02, // 0x02 目标地址FishBot运动控制板
} __attribute__((packed)) proto_data_target_addr_t;

/**
 * @brief 数据段头
 *
 */
typedef struct
{
  proto_data_id_t data_id;               // 数据编号ID
  uint16_t data_len;                     // 数据长度 2
  proto_data_direction_t data_direction; // 数据方向
} __attribute__((packed)) proto_data_header_t;

/**************************************电机控制相关结构体******************************************/

/**
 * @brief PID数据结构体
 *
 */
typedef struct
{
  float kp;
  float ki;
  float kd;
} proto_pid_data_t;

/**
 * @brief 电机编码器数据结构体
 *
 */
typedef struct
{
  int32_t motor_encoder[MAX_MOTOR_NUM]; // 电机的编码器数据
} __attribute__((packed)) proto_motor_encoder_data_t;

/**
 * @brief 电机速度控制结构体
 *
 */
typedef struct
{
  int16_t motor_speed[MAX_MOTOR_NUM]; // 单位mm/s
} __attribute__((packed)) proto_motor_speed_ctrl_data_t;

/**************************************IMU数据结构体******************************************/

/**
 * @brief IMU数据结构体
 *
 */
typedef struct
{
  float accel[3]; // 加速度
  float gyro[3];  // 重力加速度
  float euler[3]; // 欧拉角 RPY
} __attribute__((packed)) proto_imu_data_t;

/**************************************设备控制数据结构*******************************************/

typedef enum
{
  WIFI_MODE_NULL = 0, /**< null mode */
  WIFI_MODE_STA,      /**< WiFi station mode */
  WIFI_MODE_AP,       /**< WiFi soft-AP mode */
  WIFI_MODE_APSTA,    /**< WiFi station + soft-AP mode */
  WIFI_MODE_MAX
} wifi_mode_t;

/**
 * @brief WIFI配置结构体
 *
 */
typedef struct
{
  wifi_mode_t mode;
  char ssid[16];
  char password[24];
} __attribute__((packed)) proto_data_wifi_config_t;

/**************************************设备控制数据结构*******************************************/
/**
 * @brief 设备编号 0
 *
 */
typedef enum
{
  DEVICE_MOTION_CONTROL = 0x01, // 0x01 运动控制板
  DEVICE_LASER_CONTROL,         // 雷达转接控制板
  DEVICE_POWER_CONTROL,         // 电源管理板
} __attribute__((packed)) proto_device_id_t;

/**
 * @brief 对设备的操作
 *
 */
typedef enum
{
  DEIVCE_RESTART = 0x01, // 0x01 重启设备
  DEVICE_SHUTDOWN,       // 使得设备关机
  DEVICE_SLEEP,          // 使设备进入休眠状态
} __attribute__((packed)) proto_device_operation_t;

/**
 * @brief 设备控制结构体
 *
 */
typedef struct
{
  proto_device_id_t id;
  proto_device_operation_t operation;
} __attribute__((packed)) proto_device_control_t;

/*************************************数据域*通讯模式配置*******************************************/
/**
 * @brief 通讯模式定义
 *
 */
typedef enum
{
  PROTO_MODE_UART = 0x01,
  PROTO_MODE_WIFI_UDP_CLIENT,
  PROTO_MODE_WIFI_UDP_SERVER,
} __attribute__((packed)) proto_proto_mode_t;

/**
 * @brief 通讯模式配置结构体
 *
 */
typedef struct
{
  proto_proto_mode_t mode;
  uint32_t bautrate;
  uint16_t port;
  char ip[16];
} __attribute__((packed)) proto_proto_mode_config_t;

#endif // _PROTO_V1_0_0_220806_H_