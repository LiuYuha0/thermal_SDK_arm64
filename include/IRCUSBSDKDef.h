#ifndef IRCUSBSDKDEF_H
#define IRCUSBSDKDEF_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef IRCUSBSDK_EXPORTS
#define IRC_USB_API __declspec(dllexport)
#else
#define IRC_USB_API __declspec(dllimport)
#endif
#define IRC_USB_CALL _stdcall
#elif defined (__linux__)
#define IRC_USB_API     __attribute__((visibility("default")))
#define IRC_USB_CALL
#else defined (OS_POSIX) || defined (__APPLE__) || defined(ANDROID)
#define IRC_USB_API
#define IRC_USB_CALL
#endif

#include <stdint.h>

#define IRC_USB_NAME_LEN_MAX 256 ///< 名称长度最大值

/**
 * @brief 操作句柄
 *
 */
typedef uint64_t IRC_USB_HANDLE;

/**
 * @brief 异常类型
 *
 */
typedef enum
{
    IRC_USB_EXCEPTION_DEV_OFFLINE = 1001, ///< 设备离线
    IRC_USB_EXCEPTION_PREVIEW_OFFLINE = 1002, ///< 预览离线
    IRC_USB_EXCEPTION_TEMP_OFFLINE = 1003, ///< 温度离线
} IRC_USB_EXCEPTION_TYPE;

/**
 * @brief 异常回调
 *
 */
typedef void (* IRC_USB_EXCEPTION_CALLBACK)(IRC_USB_HANDLE handle, int exceptionType, void* userData);

/**
 * @brief 错误码
 *
 */
typedef enum
{
    IRC_USB_ERROR_OK = 0, ///< 成功
    IRC_USB_ERROR_FAILED = 1, ///< 失败
    IRC_USB_ERROR_NOT_SUPPORTED = 2, ///< 不支持
    IRC_USB_ERROR_PARAM_WRONG = 3, ///< 参数错误
    IRC_USB_ERROR_DEV_ERROR = 4, ///< 设备错误
} IRC_USB_ERROR;

/**
* @brief 增益模式类型
*
*/
typedef enum
{
    IRC_USB_TEMP_LEVEL_HG = 0, ///< 高增益
    IRC_USB_TEMP_LEVEL_LG, ///< 低增益
    IRC_USB_TEMP_LEVEL_AUTO ///< 自动
} IRC_USB_TEMP_LEVEL_TYPE;

/**
* @brief 色板类型
*
*/
typedef enum
{
    IRC_USB_PALETTE_WHITE_HOT = 0, ///< 白热
    IRC_USB_PALETTE_BLACK_HOT, ///< 黑热
    IRC_USB_PALETTE_RAINBOW, ///< 彩虹
    IRC_USB_PALETTE_RAINBOW_HC, ///< 高对比度彩虹
    IRC_USB_PALETTE_IRON, ///< 铁红
    IRC_USB_PALETTE_LAVA, ///< 熔岩
    IRC_USB_PALETTE_SKY, ///< 天空
    IRC_USB_PALETTE_MID_GREY, ///< 中灰
    IRC_USB_PALETTE_RDGY, ///< 灰红
    IRC_USB_PALETTE_PUOR, ///< 紫橙
    IRC_USB_PALETTE_SPECIAL, ///< 特殊
    IRC_USB_PALETTE_RED, ///< 警示红
    IRC_USB_PALETTE_ICE_FIRE, ///< 冰火
    IRC_USB_PALETTE_GREE_RED, ///< 青红
    IRC_USB_PALETTE_SPECIAL2, ///< 特殊2
    IRC_USB_PALETTE_RED_HOT, ///< 渐变红
    IRC_USB_PALETTE_GREEN_HOT, ///< 渐变绿
    IRC_USB_PALETTE_BLUE_HOT, ///< 渐变蓝
    IRC_USB_PALETTE_GREEN, ///< 警示绿
    IRC_USB_PALETTE_BLUE, ///警示蓝
} IRC_USB_PALETTE_TYPE;

/**
 * @brief 温度单位
 *
 */
typedef enum
{
    IRC_USB_TEMP_CENTIGRADE = 0, ///< 摄氏度
    IRC_USB_TEMP_KELVIN, ///< 开尔文
    IRC_USB_TEMP_FAHRENHEIT, ///< 华氏度
} IRC_USB_TEMP_UNIT;

/**
 * @brief 帧格式
 *
 */
typedef enum
{
    IRC_NET_FRAME_FMT_YUYV = 0, ///< 成像设备图像格式
    IRC_NET_FRAME_FMT_UYVY, ///< 测温设备图像格式
} IRC_USB_FRAME_FMT;

/**
 * @brief 图像参数设置类型
 *
 */
typedef enum
{
    IRC_USB_IMAGE_PARAM_TYPE_DETAIL = 0, ///< 细节增强
    IRC_USB_IMAGE_PARAM_TYPE_SPATIAL_DENOISING, ///< 空间域去噪
    IRC_USB_IMAGE_PARAM_TYPE_CONTRAST, ///< 对比度
    IRC_USB_IMAGE_PARAM_TYPE_BRIGHTNESS, ///< 亮度
    IRC_USB_IMAGE_PARAM_TYPE_TIME_DENOISING, ///< 时间域去噪
    IRC_USB_IMAGE_PARAM_TYPE_DYNAMIC_RANGE, ///< 动态范围
} IRC_USB_IMAGE_PARAM_TYPE;

/**
 * @brief 设备信息
 *
 */
typedef struct
{
    int id; ///< 设备ID
    char devName[IRC_USB_NAME_LEN_MAX]; ///< 设备名称
    char portName[IRC_USB_NAME_LEN_MAX]; ///< 串口名称
    char videoNode[IRC_USB_NAME_LEN_MAX]; ///<
} IRC_USB_DEV_INFO;

/**
 * @brief 设备搜索回调
 *
 */
typedef void (*IRC_USB_DEV_SEARCH_CALLBACK)(IRC_USB_DEV_INFO* searchInfo, void* userData);

/**
 * @brief 视频回调信息
 *
 */
typedef struct
{
    char* dataBuf; ///< 帧数据
    int width; ///< 宽度
    int height; ///< 高度
    int frameFmt; ///< 帧格式，参考IRC_USB_FRAME_FMT
} IRC_USB_VIDEO_INFO_CB;


/**
 * @brief 视频回调
 *
 */
typedef void (*IRC_USB_VIDEO_CALLBACK)(IRC_USB_HANDLE handle, IRC_USB_VIDEO_INFO_CB* videoInfo, void* userData);

/**
 * @brief 温度回调信息
 *
 */
typedef struct
{
    char* dataBuf; ///< 帧数据
    int width; ///< 宽度
    int height; ///< 高度
} IRC_USB_TEMP_INFO_CB;

/**
 * @brief 温度回调
 *
 */
typedef void (*IRC_USB_TEMP_CALLBACK)(IRC_USB_HANDLE handle, IRC_USB_TEMP_INFO_CB* tempInfo, void* userData);

/**
 * @brief 环境参数
 *
 */
typedef struct
{
    float atmosphereTemp; ///< 大气温度
    float distance; ///< 目标距离
    float emissivity; ///< 发射率 0.01-1
    float reflectedTemp; ///< 反射温度
    float transmittance; ///< 大气透过率 0.01-1
} IRC_USB_ENV_PARAM;

#endif // IRCUSBSDKDEF_H
