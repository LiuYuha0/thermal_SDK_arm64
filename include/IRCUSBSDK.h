#ifndef IRCUSBSDK_H
#define IRCUSBSDK_H

#include "IRCUSBSDKDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化
 *
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_Init();

/**
 * @brief 反初始化
 *
 * @return
 */
IRC_USB_API void IRC_USB_CALL IRC_USB_Deinit();

/**
 * @brief 搜索设备
 *
 * @param[in] searchCallback 搜索回调
 * @param[in] userData 用户自定义数据
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SearchDev(IRC_USB_DEV_SEARCH_CALLBACK searchCallback, void* userData);

/**
 * @brief 打开设备
 *
 * @param[in] id 设备ID，参考IRC_USB_DEV_INFO
 * @param[out] handle 操作句柄
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_OpenDev(int id, IRC_USB_HANDLE* handle);

/**
 * @brief 关闭设备
 *
 * @param[in] handle 操作句柄
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_CloseDev(IRC_USB_HANDLE handle);

 /**
* @brief 异常回调
*
* @param[in] handle 操作句柄
* @param[in] exceptionCb 异常回调函数
* @param[in] userData 用户自定义数据
* @return 错误码
*/
 IRC_USB_API int IRC_USB_CALL IRC_USB_SetExceptionCallback(IRC_USB_HANDLE handle, IRC_USB_EXCEPTION_CALLBACK exceptionCb, void* userData);

 /**
 * @brief 开启视频回调
 *
 * @param[in] handle 操作句柄
 * @param[in] videoCb 视频回调函数
 * @param[in] userData 用户自定义数据
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_StartPreview(IRC_USB_HANDLE handle, IRC_USB_VIDEO_CALLBACK videoCb, void* userData);

 /**
 * @brief 关闭视频回调
 *
 * @param[in] handle 操作句柄
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_StopPreview(IRC_USB_HANDLE handle);

 /**
 * @brief 开启温度回调
 *
 * @param[in] handle 操作句柄
 * @param[in] tempCb 视频回调函数
 * @param[in] userData 用户自定义数据
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_StartPullTemp(IRC_USB_HANDLE handle, IRC_USB_TEMP_CALLBACK tempCb, void* userData);

 /**
 * @brief 关闭温度回调
 *
 * @param[in] handle 操作句柄
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_StopPullTemp(IRC_USB_HANDLE handle);

 /**
 * @brief 读串口
 *
 * @param[in] handle 操作句柄
 * @param[out] buf 数据缓存区
 * @param[out] outSize 读取大小
 * @param[in] timeout 超时时间(ms),最小值为1ms
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_ReadPort(IRC_USB_HANDLE handle, char* buf, int inSize, int* outSize, int timeout);

  /**
 * @brief 写串口
 *
 * @param[in] handle 操作句柄
 * @param[in] buf 指令缓存区
 * @param[in] inSize 写入大小
 * @return 错误码
 */
 IRC_USB_API int IRC_USB_CALL IRC_USB_WritePort(IRC_USB_HANDLE handle, char* buf, int inSize);

/**
* @brief 快门校正
*
* @param[in] handle 操作句柄
* @return 错误码
*/
IRC_USB_API int IRC_USB_CALL IRC_USB_CorrectShutter(IRC_USB_HANDLE handle);

/**
 * @brief 获取图像色板序号
 *
 * @param[in] handle 操作句柄
 * @param[out] palleteType 色板类型，参考IRC_USB_PALETTE_TYPE
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetPalleteType(IRC_USB_HANDLE handle, int* palleteType);

/**
 * @brief 设置图像色板序号
 *
 * @param[in] handle 操作句柄
 * @param[in] palleteType 色板类型，参考IRC_USB_PALETTE_TYPE
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SetPalleteType(IRC_USB_HANDLE handle, int palleteType);

/**
 * @brief 获取增益模式
 *
 * @param[in] handle 操作句柄
 * @param[out] gainType 增益模式，参考IRC_USB_TEMP_LEVEL_TYPE
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetTempLevel(IRC_USB_HANDLE handle, int* gainType);

/**
 * @brief 设置增益模式
 *
 * @param[in] handle 操作句柄
 * @param[in] gainType 增益模式，参考IRC_USB_TEMP_LEVEL_TYPE
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SeTempLevel(IRC_USB_HANDLE handle, int gainType);

/**
 * @brief 获取FPA温度
 *
 * @param[in] handle 操作句柄
 * @param[out] fpaTemp FPA温度
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetFPATemp(IRC_USB_HANDLE handle, float* fpaTemp);

/**
 * @brief 获取相机温度
 *
 * @param[in] handle 操作句柄
 * @param[out] cameraTemp 相机温度
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetCameraTemp(IRC_USB_HANDLE handle, float* cameraTemp);

/**
 * @brief 获取面阵
 *
 * @param[in] handle 操作句柄
 * @param[out] width 面阵宽度
 * @param[out] height 面阵高度
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetFPASize(IRC_USB_HANDLE handle, int* width, int* height);

/**
 * @brief 获取环境参数
 *
 * @param[in] handle 操作句柄
 * @param[out] envParam 环境参数
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetEnvParam(IRC_USB_HANDLE handle, IRC_USB_ENV_PARAM* envParam);

/**
 * @brief 设置环境参数
 *
 * @param[in] handle 操作句柄
 * @param[in] envParam 环境参数
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SetEnvParam(IRC_USB_HANDLE handle, const IRC_USB_ENV_PARAM* envParam);

/**
 * @brief 获取温度单位
 *
 * @param[in] handle 操作句柄
 * @param[out] tempUnit 温度单位，参考IRC_USB_TEMP_UNIT
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetTempUnit(IRC_USB_HANDLE handle, int* tempUnit);

/**
 * @brief 设置增益模式
 *
 * @param[in] handle 操作句柄
 * @param[in] tempUnit 温度单位，参考IRC_NET_TEMP_UNIT
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SetTempUnit(IRC_USB_HANDLE handle, int tempUnit);

/**
 * @brief 获取图像增强等级
 *
 * @param[in] handle 操作句柄
 * @param[out] level 图像增强等级
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetImageLevel(IRC_USB_HANDLE handle, int* level);

/**
 * @brief 设置图像增强等级
 *
 * @param[in] handle 操作句柄
 * @param[in] level 图像增强等级, 0:手动,1-10:档位0-档位9
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SetImageLevel(IRC_USB_HANDLE handle, int level);

/**
 * @brief 获取图像参数
 *
 * @param[in] handle 操作句柄
 * @param[in] paramType 图像参数类型，参考IRC_USB_IMAGE_PARAM_TYPE
 * @param[out] value
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_GetImageParam(IRC_USB_HANDLE handle, int paramType, int* value);

/**
 * @brief 设置图像参数
 *
 * @param[in] handle 操作句柄
 * @param[in] paramType 图像参数类型，参考IRC_USB_IMAGE_PARAM_TYPE
 * @param[in] value
 * @return 错误码
 */
IRC_USB_API int IRC_USB_CALL IRC_USB_SetImageParam(IRC_USB_HANDLE handle, int paramType, int value);

#ifdef __cplusplus
}
#endif

#endif // IRCUSBSDK_H
