/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _APPLENFORCEATAHARDWARE_H
#define _APPLENFORCEATAHARDWARE_H

#if     DEBUG
#define DEBUG_LOG(fmt, args...) IOLog(fmt, ## args)
#define ERROR_LOG(fmt, args...) IOLog(fmt, ## args)
#else
#define DEBUG_LOG(fmt, args...)
#define ERROR_LOG(fmt, args...) IOLog(fmt, ## args)
#endif

#define kMaxDriveCount      2
#define kMaxChannelCount    2

/*
 * I/O port addresses for primary and secondary channels.
 */
#define PRI_CMD_ADDR        0x1f0
#define PRI_CTR_ADDR        0x3f4
#define SEC_CMD_ADDR        0x170
#define SEC_CTR_ADDR        0x374

/*
 * IRQ assigned to primary and secondary channels.
 */
#define PRI_ISA_IRQ         14
#define SEC_ISA_IRQ         15

/*
 * Two ATA channels max.
 */
#define PRI_CHANNEL_ID      0
#define SEC_CHANNEL_ID      1

/*
 * PCI ATA config space registers.
 * Register size (bits) in parenthesis.
 */
#define PCI_CFID            0x00    // (32) PCI Device/Vendor ID
#define PCI_PCICMD          0x04    // (16) PCI command register
#define PCI_PCISTS          0x06    // (16) PCI device status register
#define PCI_RID             0x08    // (8)  Revision ID register
#define PCI_PI              0x09    // (8)  Programming interface
#define PCI_MLT             0x0d    // (8)  Master latency timer register
#define PCI_HEDT            0x0e    // (8)  Header type register
#define PCI_BMIBA           0x20    // (32) Bus-Master base address

#define PCI_BMIBA_RTE       0x01    // resource type indicator (I/O)
#define PCI_BMIBA_MASK      0xfff0  // base address mask

#define PCI_PCICMD_IOSE     0x01    // I/O space enable
#define PCI_PCICMD_BME      0x04    // bus-master enable

/*
 * nForce specific PCI config space registers.
 */
#define PCI_IDE_ENABLE      0x50
#define PCI_IDE_CONFIG      0x51
#define PCI_CABLE_DETECT	0x52
#define PCI_FIFO_CONFIG     0x53
#define PCI_DATA_TIMING     0x58
#define PCI_CMD_TIMING      0x5e
#define PCI_ADDRESS_SETUP   0x5c
#define PCI_ULTRA_TIMING    0x60

/*
 * Supported devices (ATA controller and PCI-ISA bridges).
 */

#define PCI_NVIDIA_ID       0x10de
#define PCI_NFORCE1         0x01bc10de
#define PCI_NFORCE2         0x006510de
#define PCI_NFORCE2_PRO     0x008510de
#define PCI_NFORCE3         0x00d510de
#define PCI_NFORCE3_PRO     0x00e510de
#define PCI_NFORCE_MCP04    0x003510de
#define PCI_NFORCE_CK804    0x005310de
#define PCI_NFORCE_MCP51    0x026510de
#define PCI_NFORCE_MCP55    0x036e10de
#define PCI_NFORCE_MCP61    0x03ec10de
#define PCI_NFORCE_MCP65    0x044810de
// sata
#define PCI_NFORCE2_PRO_S1  0x008e10de
#define PCI_NFORCE3_PRO_S1  0x00e310de
#define PCI_NFORCE3_PRO_S2  0x00ee10de
#define PCI_NFORCE_MCP04_S1 0x003610de
#define PCI_NFORCE_MCP04_S2 0x003e10de
#define PCI_NFORCE_CK804_S1 0x005410de
#define PCI_NFORCE_CK804_S2 0x005510de
#define PCI_NFORCE_MCP51_S1 0x026610de
#define PCI_NFORCE_MCP51_S2 0x026710de
#define PCI_NFORCE_MCP55_S1 0x037e10de
#define PCI_NFORCE_MCP55_S2 0x037f10de
#define PCI_NFORCE_MCP61_S1 0x03e710de
#define PCI_NFORCE_MCP61_S2 0x03f610de
#define PCI_NFORCE_MCP61_S3 0x03f710de
#define PCI_NFORCE_MCP65_S5 0x045c10de
#define PCI_NFORCE_MCP65_S6 0x045d10de
#define PCI_NFORCE_MCP65_S7 0x045e10de
#define PCI_NFORCE_MCP65_S8 0x045f10de

// AHCI
#define PCI_NFORCE_MCP65_S1	0x044c10de 
#define PCI_NFORCE_MCP65_S2	0x044d10de
#define PCI_NFORCE_MCP65_S3	0x044e10de
#define PCI_NFORCE_MCP65_S4	0x044f10de

 
/*
 * Bus master registers are located in I/O space.
 * Register size (bits) indicated in parenthesis.
 *
 * Note:
 * For the primary channel, the base address is stored in PCI_BMIBA.
 * For the secondary channel, an offset (BM_SEC_OFFSET) is added to
 * the value stored in PCI_BMIBA.
 */
#define BM_COMMAND          0x00    // (8) Bus master command register
#define BM_STATUS           0x02    // (8) Bus master status register
#define BM_PRD_TABLE        0x04    // (32) Descriptor table register

#define BM_SEC_OFFSET       0x08    // offset to channel 1 registers
#define BM_ADDR_MASK        0xfff0  // BMIBA mask to get I/O base address
#define BM_STATUS_INT       0x04    // IDE device asserted its interrupt

/*
 * Enumeration of NForce hardware types.
 */
enum {
    PCI_HW_UDMA_NONE = 0,
    PCI_HW_UDMA_33,
    PCI_HW_UDMA_66,
    PCI_HW_UDMA_100,
    PCI_HW_UDMA_133,
    PCI_HW_SATA,
    PCI_HW_COUNT
};

#define NV4 0x10
//0x0010
#define NVQ 0x20
//0x0020
#define NV_MCP_SATA_CFG_20					0x50
#define NV_MCP_SATA_CFG_20_SATA_SPACE_EN	0x04

/*
 * Property keys
 */
#define kChannelNumberKey         "Channel Number"
#define kCommandBlockAddressKey   "Command Block Address"
#define kControlBlockAddressKey   "Control Block Address"
#define kInterruptVectorKey       "Interrupt Vector"
#define kSerialATAKey             "Serial ATA"
#define kHardwareNameKey          "Hardware Name"
#define kSelectedPIOModeKey       "PIO Mode"
#define kSelectedDMAModeKey       "DMA Mode"
#define kSelectedUltraDMAModeKey  "Ultra DMA Mode"
#define kISABridgeMatchingKey     "ISA Bridge Matching"


#endif /* !_APPLENFORCEATAHARDWARE_H */
