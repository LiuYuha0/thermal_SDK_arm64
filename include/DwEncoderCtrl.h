#pragma once
#include "BaseEncoderCtrl.h"
#include "InfEntity.h"
#ifdef MY_LINUX
#include <libusb-1.0/libusb.h>
#endif

#define FRAME_LT_START          (0xAA)
#define FRAME_LT_BACK           (0x55)
#define FRAME_TYPE              (0x00)
#define FRAME_TYPE01              (0x01)
#define FRAME_END_EB         (0xEB)
#define FRAME_END_AA         (0xAA)

#define MAX_WAIT_RESPONSE_TIME   100
#define MAX_LOCAL_BUF_LEN		512
static int mPaletteIndex = 0;//α�����
static int m_coreType = 5;//1: LT Temperature measurement type     2��MicroIII Temperature measurement type    3��MicroIII Imaging     4:ELF3


static unsigned char palettedata[40 * 1024] = {0};//α���ļ�
static void* outContext = NULL;
typedef enum IR_OPERATE_e  //������ö��
{
	IR_OPERATE_READ = 0x00,
	IR_OPERATE_WRITE = 0x01,
	IR_OPERATE_DO = 0x02,
	IR_OPERATE_READ_CK = 0x03,
	IR_OPERATE_WRITE_CK = 0x04,
} IR_OPERATE, *P_IR_OPERATE;

#define LT_OPERATE_COMMAND0             0x07
#define CMD_LT_TEMP_FRAME_MAX_MES       0x27 //��֡��������¶�/����(read only)
#define CMD_LT_TEMP_FRAME_MIN_MES       0x29 //��֡������С�¶�/����(read only)
#define CMD_LT_TEMP_FRAME_CEN_MES       0x2c //��֡���������¶�/����(read only)
#define CMD_LT_TEMP_FRAME_AVR           0x2a //��֡���¾�ֵ�¶�     (read only)
#define CMD_LT_TEMP_USER_REFLECT        0x0f //�����¶�
#define CMD_LT_TEMP_USER_AIRTEMP        0x10 //���������¶�
#define CMD_LT_TEMP_USER_HUMIDITY       0x11 //����ʪ��
#define CMD_LT_TEMP_USER_EMISS          0x12 //������
#define CMD_LT_TEMP_USER_DISTANCE       0x13 //����
#define CMD_LT_CALCULATE_ENV_PARAMS     0x18 //���������������¼���
#define CMD_LT_WTR_LOW_THRESHOLD        0x1d
#define CMD_LT_WTR_HIGH_THRESHOLD       0x1e
#define CMD_LT_TEMP_SWITCH              0x71 //�¶ȳ���Tֵ�л�ʹ��
#define CMD_LT_TEMP_WTR                 0xf0
#define CMD_LT_TEMP_DISPLAY_STYLE       0x02 //�¶���ʾ��ʽ��0x00-���϶� C��0x01-�����ģ�273.15K����0x02-���ϣ�F��

#define BULK_ENDPOINT_OUT               0x05
#define BULK_ENDPOINT_IN                0X85

typedef enum IR_FEATURE_e	//����ָ�����
{
	//  ������                                      ֵ   ����  ����˵��    �����ֽ���                 ˵����Ĭ�Ϸ��� OK��
	IR_FEATURE_USER_INFO_SN = 0,		//0   WR,��о��SN�� ����Ŀǰʹ��6λ    ���غ��ϴ�ʱ ͨ������ĳ����ж�ʹ�ó���
	IR_FEATURE_USER_INFO_PN,        //1   WR,��о��PN�� ����Ŀǰʹ��14λ   ���غ��ϴ�ʱ ͨ������ĳ����ж�ʹ�ó���  ������LB6230CTT20001
	IR_FEATURE_USER_INFO_WIDTH,        //2   R, ̽����FPA�Ŀ��   0            ֻ�����������ز���2�ֽ�
	IR_FEATURE_USER_INFO_HEIGHT,        //3   R, ̽����FPA�ĸ��   0            ֻ�����������ز���2�ֽ�
	IR_FEATURE_USER_TMPR_FPA,        //4   R, FPA�¶�           0            ֻ�����������ز���2�ֽ�  �¶�=��������/100
	IR_FEATURE_USER_TMPR_ENV,        //5   R, ��о�¶�          0            ֻ�����������ز���2�ֽ�  ��������=�¶�*100
	IR_FEATURE_USER_TEMPSENSOR_TYPE,			//6   R�� ���ز���һ�� ��0x88��ʾ�ڲ��´���0x80��ʾ�ⲿ�´�
	IR_FEATURE_NUC_STATUS_EN = 14,//        			    //14   W, bit0 ͼ���ȶ����� 0 dis 1 en
	IR_FEATURE_USER_RESERVED_7_TO_15,		//7-15 Ԥ������

	IR_FEATURE_USER_SETT_UPLOAD = 16,        //16   Ԥ������
	IR_FEATURE_USER_SETT_SAVE,        //17  W, �������湦��      0            ���û����ò������浽flash����λ������ǰ���ñ���
	IR_FEATURE_USER_SETT_RESTORE_FACTORY,       //18  DO �ָ���������      0            ���������ò����ָ�����ǰ����
	IR_FEATURE_USER_SETT_RESTART,               //19  DO ��о����          0             ��о����
	IR_FEATURE_USER_SETT_BAUD,                  //20  DO �޸�ͨѶ������    1            ���� 0x01:�Զ�ʶ��(�ɿ�ȱ ����Ҫ����ʶ��ʧ��) 0x02:9600 0x04:19200 0x08 :38400 0x10:115200 0x20:921600

	IR_FEATURE_USER_NUC_AUTOSHUT,        //21 WR �����Զ�/�ֶ����� 1              ����1�ֽڣ�0���ֶ��� 1���Զ���
	IR_FEATURE_USER_NUC_SHUT_TYPE,        //22 WR �ֶ���������      1              ����1�ֽڣ�0/1������У�� 2������У��
	IR_FEATURE_USER_NUC_TIME_INTERVAL,        //23 WR �Զ�����ʱ����  1
	IR_FEATURE_USER_NUC_TEMP_CHANGE,        //24 WR �Զ������¶ȼ��  1

	IR_FEATURE_USER_TEC_CHANGE_EN = 25,        //25 WR TEC�Զ��л�����    1             ����1�ֽ�  0���� 1 ��
	IR_FEATURE_DRC_CLASS = 25,  		   					    //25   DO��  ����1����DRC����ѡ���ܹ�16��������dde��drc�в��ֲ��� 
																//���Ϊ0����ʹ���û��ɵ���������ֵ������ʹ��flash�е�1-16��Ԥ�趨ֵ��

	IR_FEATURE_USER_INFO_VERSION,        //26 R  ��ȡ��ǰ�豸�汾 
	IR_FEATURE_USER_DISCONNECT,        //27 DO  �Ͽ���������  �޷������� 
	R_FEATURE_USER_RESERVED_28_TO_32,          //29-41 Ԥ������	 //IR_FEATURE_USER_TEST_IMAGE         ,      
																										   //28 DO  ����ͼ�񿪹�      1             ����1�ֽ�  0���� 1 ��
	IR_FEATURE_DRC_DDE_DETAIL_GAIN = 30,        				//30  W,����1��������ϸ������ϵ����5λ������3λС��
	IR_FEATURE_DRC_AGC_HIGHTHROWPERCENT_SET = 33,			//33  W,����1����������ֱ��ͼ�ĸ��ױ���lowThrowPercent,��λ��1/1024.
	IR_FEATURE_DRC_AGC_HPLATEAUVALUE = 36,					//36  W,PE�ĸ�ƽֵ̨
	IR_FEATURE_DRC_AGC_LPLATEAUVALUE = 37,					//37  W,PE�ĵ�ƽֵ̨
	IR_FEATURE_DRC_AGC_ITTMEAN = 38,							//38  W,  1������ ITTMEAN
	IR_FEATURE_DRC_AGC_MAXGAIN_SET = 40,						//40  W,����AGC�в��ұ���������
	IR_FEATURE_USER_RESERVED_38_TO_41,          //38-41 Ԥ������

	IR_FEATURE_USER_VIDEO_ZOOM = 42,        //42  WR ���ӱ䱶          1             0:���䱶 1��2�� 2��4�� 3��8��
	IR_FEATURE_USER_VIDEO_CROSS_EN,        //43  WR ʮ�ֹ�꿪��      1             0����äԪ�� 1 ��äԪ�� 0x02���û����أ� 0x03���û���꿪
	IR_FEATURE_USER_VIDEO_CROSS_MOVE,        //44  DO ʮ�ֹ�궯��      1             äԪ�궨 0������ 1������ 2������ 3������ 4������ ���λBIT7 0 ��С���� 1 ��󲽷���  �û���� 5������ 6������ 7������ 8������ 9������ ���λBIT7 0 ��С���� 1 ��󲽷�
	IR_FEATURE_USER_VIDEO_COLORMAP,        //45  WR ��ɫ������        1             ��������COLORMAP_TYPE_e
	IR_FEATURE_USER_DIGITAL_SOURCE,        //46 WR ������ƵԴ        1               ��������DIGITAL_SOURCE_e
	IR_FEATURE_USER_DIGITAL_TYPE,        //47 WR ������Ƶ����ӿ�  1               ��������DIGITAL_TYPE_e 
	IR_FEATURE_USER_VIDEO_FLIP,		//48 WR ͼ��ת          1              8bit���� ���� bit0 = 1����ת��bit1=1���ҷ�ת��bit2=1���£�bit3=1��������
	IR_FEATURE_USER_BF_EN,        //49 WR �˲�����            1            ˫���˲����أ���λ����ʾ�˲����ع��ܣ� 0 �� 1��
	IR_FEATURE_USER_AGC_FROZEN,        //50  DO ����һ��00 ���� 01 ������� 
	IR_FEATURE_USER_OSD_VIDEO_EN,        //51 WR ģ����Ƶ���� just for LT
	IR_FEATURE_USER_DIGITAL_TYPE_LT,        //52 WR LT��Ƶ
	IR_FEATURE_USER_RESERVED_52_TO_57,        //53-57 Ԥ������

	IR_FEATURE_USER_AGC_MODE = 58,   	    //58 WR��AGCģʽ��        1               ��������AGC_ALGORITHM_e��0�ֶ���1�Զ�0��PE����2�Զ�1(LE)��
	IR_FEATURE_USER_AGC_CONTRAST,   	    //59 WR,���öԱȶ�        1               ��Χ0-255
	IR_FEATURE_USER_AGC_BRIGHT,	   	//60  WR, �������ȣ�       2               ��Χ0-511
	IR_FEATURE_USER_AGC_GAMMA = 61,		//61  WR, GAMMAУ��        1               ����gammaУ��ָ����������ָ������10������λ0.1 ���������ʾ 1.1 �·� 11
	IR_FEATURE_USER_AGC_ANALOG_ON_OFF = 61,		//61 ģ����Ƶ���� 
	IR_FEATURE_USER_DDE_EN,		//62  WR  DDE״̬          1               0���� 1����
	IR_FEATURE_USER_DDE_GRADE,        //63  WR  DDE��λ          1               Ŀǰ��Χ0-7 ������չ
	IR_FEATURE_USER_AGC_CONTRAST_STEP,        //64 �Աȶ�����ֵ
	IR_FEATURE_USER_AGC_BRIGHTNESS_STEP,        //65 ���Ȳ���ֵ
	IR_FEATURE_OSD_CURSOR_MOVE = 68,
	IR_FEATURE_USER_RESERVED_66_TO_80,        //66-80 Ԥ������

	IR_FEATURE_USER_BLIND_SCAN = 81,		//81  DO   äԪɨ��        0              
	IR_FEATURE_USER_BLIND_OP,        //82  DO   äԪ���ز���    1               0�����õ�ǰäԪ 1�������ϴ����� 2�� ����äԪ��FLASH

	IR_FEATURE_USER_K_IMAGE,       //83  DO  ��ȡ��ǰͼ������ 1               ������ΪDOʱ ��ȡ��ǰͼ��Ϊ 0������ 1���������� ����Kֵ
	IR_FEATURE_USER_K_CAL,       //84  DO  �Զ�����Kֵ
	IR_FEATURE_USER_K_OP,       //85  DO  �û�K����ز���  1               0�����浱ǰKֵ 1���ָ�����Kֵ ������ �ϴ�/���� Kֵ �ݲ�ʹ�� Ԥ����չ��

	IR_FEATURE_USER_FIRM_UPLOAD,       //86  W/D  �̼�����      W:128/D:2      �̼����´�С(KB)����=��С*8 ����ʵ�� ��λ������ ��ָ��DO ���سɹ�֮�󣬿�ʼʹ�ø�ָ���W ���� ÿ�η���128B���� ������8*��С ��

	IR_FEATURE_USER_FIRM_UPLOADK,       //87  W/R/D  ���ٹ̼�����   W/R/D          �̼����´�С(KB)����=��С ����ʵ�� ��λ������ ��ָ���W���� ���ʹ�����һ��1K�� ���سɹ�֮�󣬿�ʼ���ز��� ÿ�η���1KB���ݣ�ֻ�й̼����ݣ� �����ʹ�С �� 
	//������ɺ󣬷���ָ���Read������ȡ��λ������У��(4�ֽ�У��)��У��ʧ����ʾ�������أ��ɹ����棬�·�DO�������浽flash
	IR_FEATURE_USER_RESERVED_88_TO_99,       // 88-99 Ԥ������

	IR_FEATURE_USER_KEY = 100,       // 100 DO  ���ⰴ��        1               ���λbit7 ��Ϊ������� ����1 ���� 0  ��λ��Ӧ bit0:M�� bit1: +��  bit2:-�� bit3:C��
	IR_FEATURE_USER_BLACKFACE_SWITCH = 124,       // 100 DO  ���ⰴ��        1               ���λbit7 ��Ϊ������� ����1 ���� 0  ��λ��Ӧ bit0:M�� bit1: +��  bit2:-�� bit3:C��
	IR_FEATURE_USER_BLACKFACE_TEMP = 125,       // 100 DO  ���ⰴ��        1               ���λbit7 ��Ϊ������� ����1 ���� 0  ��λ��Ӧ bit0:M�� bit1: +��  bit2:-�� bit3:C��
	IR_FEATURE_USER_BLACKFACE_LOCATION = 126,       // 100 DO  ���ⰴ��        1               ���λbit7 ��Ϊ������� ����1 ���� 0  ��λ��Ӧ bit0:M�� bit1: +��  bit2:-�� bit3:C��
	IR_FEATURE_USER_RESERVED_101_TO_159, //101-159 ������������Ԥ��Ԥ������
	IR_FEATURE_NS_FLASH_COLORMAP = 140,        				//140 10��ɫ��
	IR_FEATURE_NS_FLASH_LOGO = 141,//LOGO����
	IR_FEATURE_TEMPER_ALARM_EN = 160,      // 160 wr  ���±���ʹ��     1               0�� 1��
	IR_FEATURE_NS_AUTO_CALC_GG,							//161	��ȡ���� W��0��ȡ�����㣬1���� 2���
	IR_FEATURE_MOTOR_MOVE = 162,     //162  DO  ��ͷ�������      4              ����1 1�ֽ� ֵ0��ֹͣ 1 ��ת 2 ��ת ������2 1���ֽ� ����PWMռ�ձ� ����3 2���ֽ� ���ò��� �����ת��������
	IR_FEATURE_NS_CALC_GG_PARA = 162,//162 д �� ����һ  1.����_ϵ��A  2.���� _ϵ��B  3.����_Range 4.�����²����� LimitMaxT 
								//���� ����һ 1. ��ȡ_A 2.��ȡ_B  3. ��ȡ_renge 4.��ȡ�¶�����MaxT

	IR_FEATURE_RTD323_FPA_AVERAGE = 196, 					 //196(ԭ176)	 R,��ȡ����ƽ��ֵ��count��	 2���ֽ�
	IR_FEATURE_RTD323_TEC_TEMP = 206,				 //206(ԭ222)		 WR,����TEC�¶�

	IR_FEATURE_RESERVED_163_TO_255,     //163 �ͻ����ƹ��� Ԥ������

} IR_FEATURE_USER, *P_IR_FEATURE_USER;

#ifdef MY_WIN32
class DwEncoderCtrl : public BaseEncoderCtrl, public ISampleGrabberCB
#elif defined MY_LINUX
class DwEncoderCtrl : public BaseEncoderCtrl
#endif
{
public:
	DwEncoderCtrl();
	~DwEncoderCtrl();

	virtual bool Init() override;
	virtual void Deinit() override;
	virtual unsigned int Login(HWND hWnd) override;
	virtual int SearchDev(DeviceLst &p) override;
    virtual int OpenDev(int type, int iGetCurSel, int portIndx, int usbIndx) override;
	virtual void CloseDev() override;
	virtual void Logout() override;
	virtual int ReadCoreType() override;
	
	virtual int ReadTempMeasureType() override;
	virtual int shutter_correction(int iCoreType, int type) override;
	virtual int set_color_plate(int iType, int color_plate) override;
	virtual int get_color_plate(int iType, int* color_plate) override;
	virtual int get_SN_PN(char *strSN, int *iLenSN, char* strPN, int *iLenPN) override;

	int __stdcall StartDeviceVideoCallBack(VideoCallBack pVideoCallBack, void *pContext) override;
	int __stdcall StartTempCallBack(TempCallBack pTempCallBack, void *pContext) override;

    virtual int ReadCMDHandle(char* buf, char* cmd, int* pLen, int cmdsize) override;
    virtual int WriteCMDHandle(char* buf, int len) override;

	int OpenCom(int port, DWORD baud, int parity);
	int PingPong();
#ifdef MY_WIN32
	void EnumCom();
	int GetComList_Reg();
	virtual int USBVersion(/*char* version*/) override;
	virtual bool ReadCommunicationType() override;
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
	HRESULT STDMETHODCALLTYPE SampleCB(double Time, IMediaSample *pSample);
	HRESULT STDMETHODCALLTYPE BufferCB(double Time, BYTE *pBuffer, long BufferLen);
#endif // MY_WIN32


	int get_FPA_temp(float *fTemp) override;
	int get_camera_temp(float *fTemp) override;
	int get_width(int *iValue) override;
	int get_height(int *iValue) override;
	int set_wtr_status(int iStatus) override;
	int get_wtr_status(int* iStatus) override;
	int set_wtr_low_threshold(int iThreshold) override;
	int get_wtr_low_threshold(int* iThreshold) override;
	int set_wtr_high_threshold(int iThreshold) override;
	int get_wtr_high_threshold(int* iThreshold) override;
	int set_reflect(signed int i32value) override;
	int get_reflect(signed int* p32value) override;
	int set_airTemp(signed int i32value) override;
	int get_airTemp(signed int* p32value) override;
	int set_humidity(signed int i32value) override;
	int get_humidity(signed int* p32value) override;
	int set_emiss(signed int i32value) override;
	int get_emiss(signed int* p32value) override;
	int set_distance(signed int i32value) override;
	int get_distance(signed int* p32value) override;
	int set_envir_param(envir_param envir_data) override;
	int get_envir_param(envir_param* envir_data) override;
	int envir_effect() override;
	int read_temp_unit(unsigned char* ucUnit) override;
	int set_temp_unit(unsigned char ucUnit) override;
	int get_temp_coefficient(int gain, short* param1, short* param2) override;
	int edge_detect(unsigned char* imageSrc, unsigned char* imageDst, int width, int height, int level) override;
	int edge_enhace(unsigned char* imageSrc, unsigned char* imageDst, int width, int height, int level) override;
	int get_video_interface() override;
    int get_formulatype(int gain, int* k, int* b) override;

public:
    VideoCallBack vcb = NULL;
    TempCallBack tcb = NULL;
	DeviceLst devList;

private:
    int iIfGetVideoSize = 0;
    int Width = 640;
    int Height = 512;
#ifdef MY_WIN32
	CaptureVideo g_CaptureVideo;
	bool bUSBNew;
	int DataReadLen;
	int comport;
	DWORD oldbaud;
	DCB dcb;
	HANDLE m_hComm = (HANDLE)INVALID_HANDLE_VALUE;

    unsigned char camera_data_out[2560 * 1024 * 2];
    unsigned char yuv_data_out[1280 * 1024 * 2];
    unsigned char temp_data_temp_out[1280 * 1024 * 2];

	int iIfTempCore = 0; //�Ƿ��ǲ����ͻ�о
	int m = 0;

	BOOL m_bGetPicture;  // is get a picture
	long m_lWidth;       //�洢ͼƬ�Ŀ��
	long m_lHeight;		 //�洢ͼƬ�ĳ���
	int  m_iBitCount;    //the number of bits per pixel (bpp)
	TCHAR m_chTempPath[MAX_PATH];
	TCHAR m_chSwapStr[MAX_PATH];
	TCHAR m_chDirName[MAX_PATH];
	bool bVideoTempFlag = false;
	vector<char*> name;
#elif defined MY_LINUX
	v4l2_dev_t *vd;
    serialport *sport;
	int fd;
    int m_connectType;
	pthread_t thread_read;
    libusb_device_handle *dev_handle;
    libusb_context *ctx = nullptr;
#endif
	
	bool bTempMeasureType;//��������  true���������  false�� ��ҵ����
	bool m_CDS3;
    int m_deviceType = TYPE_M3;
};

