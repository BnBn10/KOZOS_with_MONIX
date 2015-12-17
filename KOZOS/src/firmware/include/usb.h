/*****************************************************************************
	�I�[�_�[	: USB�h���C�o �w�b�_
	CPU			: H8 3069F
	�R���p�C��	: h8300-elf-gcc version 3.4.6
	�t�@�C����	: usb.h
	�ړ���		: usb
	�쐬����	: 2014-06-26
*****************************************************************************/
/*
	��������
*/
#ifndef _USB_H_
#define _USB_H_

/*****************************************************************************
	�C���N���[�h
*****************************************************************************/
#include	"defines.h"

/*****************************************************************************
	��`
*****************************************************************************/
#define	ATTR_PACK	(__attribute__((packed)))
#define	bswap16(x)	((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))
#define	htole16(x)	bswap16((x))
#define	le16toh(x)	bswap16((x))

#define	TRANS_TO_DEV	(0x00)
#define	TRANS_TO_HOST	(0x80)
#define	TRANS_TO_IF		(0x01)
#define	TRANS_TO_EP		(0x02)

#define	GET_STATUS		(0x00)
#define	CLEAR_FEATURE	(0x01)
#define	SET_FEATURE		(0x03)
#define	SET_ADDRESS		(0x05)
#define	GET_DESCRIPTOR	(0x06)
#define	SET_DESCRIPTOR	(0x07)
#define	GET_CONFIG		(0x08)
#define	SET_CONFIG		(0x09)
#define	GET_INTERFACE	(0x0a)
#define	SET_INTERFACE	(0x0b)
#define	SYNCH_FRAME		(0x0c)

#define	DEVICE_TYPE		(0x01)
#define	CONFIG_TYPE		(0x02)
#define	STRING_TYPE		(0x03)
#define	INTERFACE_TYPE	(0x04)
#define	ENDPOINT_TYPE	(0x05)

#define	STDCLASS		(0x00)
#define	HIDCLASS		(0x03)
#define	HUBCLASS		(0x09)	// bDeviceClass, bInterfaceClass

#define	MAX_EP			(8)


#define USB_RESET	46
#define USB_SETUP	47
#define USB_GETSPEED	48
 #define USB_LOW	1
 #define USB_FULL	2

#define USB_EP		1
#define USB_TOGGLE	2
#define USB_HDRSIZ	2

#define SL_NUM	1

#define USB_ACK		1
#define USB_NAK		2
#define USB_STALL	4

/*****************************************************************************
	�^��`�A�\���̒�`
*****************************************************************************/
/*
	_attribute__((packed))�́A�R���p�C��������ɍ\���̂Ƀp�b�h(�A���C�����g)
	�����Ȃ��悤�ɂ���錾
*/


typedef struct {
	uint16	wVID, wPID;			// Vendor ID and Product ID
	uint08	bClass;				// 
	uint08	bNumOfEPs;			// actual number endpoint from slave
	uint08	iMfg;				// Manufacturer ID
	uint08	iPdt;				// Product ID
	uint08	bId1;
	uint08	bId2;
	uint08	bEPAddr[MAX_EP];	// bit 7 = 1 = use PID_IN, 
	uint08	bAttr[MAX_EP];		// ISO | Bulk | Interrupt | Control
	uint16	wPayLoad[MAX_EP];	// ISO range: 1-1023, Bulk: 1-64, etc
	uint16	bInterval[MAX_EP];	// polling interval (for LS)
	uint08	bData1[MAX_EP];		// DataToggle value
	uint16	usDummy[62];
	/* byte count
	uint16	wVID, wPID;			// 2*2=4
	uint08	bClass;				// 1
	uint08	bNumOfEPs;			// 1
	uint08	iMfg;				// 1
	uint08	iPdt;				// 1
	uint08	bId1;				// 1
	uint08	bId2;				// 1
	uint08	bEPAddr[MAX_EP];	// 8
	uint08	bAttr[MAX_EP];		// 8
	uint16	wPayLoad[MAX_EP];	// 16
	uint16	bInterval[MAX_EP];	// 16
	uint08	bData1[MAX_EP];		// 8
								// 4+ 1*6 + 8*3 + 16*2 = 66
	*/
	
} USBDEV;

typedef struct {
	uint08	bmRequest	__attribute__((packed));
	uint08	bRequest	__attribute__((packed));
	uint16	wValue		__attribute__((packed));
	uint16	wIndex		__attribute__((packed));
	uint16	wLength		__attribute__((packed));
} SetupPKG;

typedef struct {
	uint08	bLength				__attribute__((packed));
	uint08	bDescriptorType		__attribute__((packed));
	uint16	bcdUSB				__attribute__((packed));
	uint08	bDeviceClass		__attribute__((packed));
	uint08	bDeviceSubClass		__attribute__((packed));
	uint08	bDeviceProtocol		__attribute__((packed));
	uint08	bMaxPacketSize0		__attribute__((packed));
	uint16	idVendor			__attribute__((packed));
	uint16	idProduct			__attribute__((packed));
	uint16	bcdDevice			__attribute__((packed));
	uint08	iManufacturer		__attribute__((packed));
	uint08	iProduct			__attribute__((packed));
	uint08	iSerialNumber		__attribute__((packed));
	uint08	bNumConfigurations	__attribute__((packed));
	uint08	usDummy[14]			__attribute__((packed));
} DevDesc;

// Standard Configuration Descriptor
typedef struct {
	uint08	bLength		__attribute__((packed));	// Size of descriptor in uint08
	uint08	bType		__attribute__((packed));	// Configuration
	uint16	wLength		__attribute__((packed));	// Total length
	uint08	bNumIntf	__attribute__((packed));	// Number of interface
	uint08	bCV			__attribute__((packed));	// bConfigurationValue
	uint08	bIndex		__attribute__((packed));	// iConfiguration
	uint08	bAttr		__attribute__((packed));	// Configuration Characteristic
	uint08	bMaxPower	__attribute__((packed));	// Power config
	uint08	ucDummy[7]	__attribute__((packed));
} CfgDesc;

// Standard Interface Descriptor
typedef struct {
	uint08	bLength		__attribute__((packed));
	uint08	bType		__attribute__((packed));
	uint08	iNum		__attribute__((packed));
	uint08	iAltString	__attribute__((packed));
	uint08	bEndPoints	__attribute__((packed));
	uint08	iClass		__attribute__((packed));
	uint08	iSub		__attribute__((packed)); 
	uint08	iProto		__attribute__((packed));
	uint08	iIndex		__attribute__((packed)); 
	uint08	ucDummy[7]	__attribute__((packed));
} IntfDesc;

// Standard EndPoint Descriptor
typedef struct{
	uint08	bLength		__attribute__((packed));
	uint08	bType		__attribute__((packed));
	uint08	bEPAdd		__attribute__((packed));
	uint08	bAttr		__attribute__((packed));
	uint16	wPayLoad	__attribute__((packed));	// low-speed this must be 0x08
	uint08	bInterval	__attribute__((packed));
	uint08	ucDummy		__attribute__((packed));
} EPDesc;

// Standard String Descriptor
typedef struct {
	uint08	bLength;
	uint08	bType;
	uint16	wLang;
} StrDesc;


/*****************************************************************************
	�v���g�^�C�v�錾
*****************************************************************************/
int usb_main(int argc, char** argv);

/*****************************************************************************
	�O���ϐ� 
*****************************************************************************/

#endif	/* _USB_H_ */
/***** End Of File *****/
