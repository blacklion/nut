/*!
 * @file nut_libusb.h
 * @brief HID Library - Generic USB backend for Generic HID Access (using MGE HIDParser)
 *
 * @author Copyright (C)
 *	    2003 - 2016 Arnaud Quette <aquette.dev@gmail.com>
 *      2005 Peter Selinger <selinger@users.sourceforge.net>
 *
 * This program is sponsored by MGE UPS SYSTEMS - opensource.mgeups.com
 *
 *      The logic of this file is ripped from mge-shut driver (also from
 *      Arnaud Quette), which is a "HID over serial link" UPS driver for
 *      Network UPS Tools <http://www.networkupstools.org/>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * -------------------------------------------------------------------------- */

#ifndef NUT_LIBUSB_H
#define NUT_LIBUSB_H

#include "main.h"	/* for subdrv_info_t */
#include "usb-common.h"	/* for USBDevice_t and USBDeviceMatcher_t */

/* libusb header file */
#ifdef WITH_LIBUSB_1_0
#include <libusb.h>
#endif
#ifdef WITH_LIBUSB_0_1
#include <usb.h>
/* simple remap to avoid bloating structures */
typedef libusb_device_handle usb_dev_handle;
#endif

extern upsdrv_info_t comm_upsdrv_info; 

/*!
 * usb_communication_subdriver_s: structure to describe the communication routines
 * @name: can be either "shut" for Serial HID UPS Transfer (from MGE) or "usb"
 */
typedef struct usb_communication_subdriver_s {
	const char *name;                         /* name of this subdriver             */
	const char *version;                      /* version of this subdriver          */
	int (*open)(libusb_device_handle **sdevp, /* try to open the next available     */
		USBDevice_t *curDevice,               /* device matching USBDeviceMatcher_t */
		USBDeviceMatcher_t *matcher,
		int (*callback)(libusb_device_handle *udev, USBDevice_t *hd, unsigned char *rdbuf, int rdlen));
	void (*close)(libusb_device_handle *sdev);
	int (*get_report)(libusb_device_handle *sdev, int ReportId,
		unsigned char *raw_buf, int ReportSize );
	int (*set_report)(libusb_device_handle *sdev, int ReportId,
		unsigned char *raw_buf, int ReportSize );
	int (*get_string)(libusb_device_handle *sdev,
	int StringIdx, char *buf, size_t buflen);
	int (*get_interrupt)(libusb_device_handle *sdev,
		unsigned char *buf, int bufsize, int timeout);
} usb_communication_subdriver_t;

extern usb_communication_subdriver_t	usb_subdriver;

#endif /* NUT_LIBUSB_H */
