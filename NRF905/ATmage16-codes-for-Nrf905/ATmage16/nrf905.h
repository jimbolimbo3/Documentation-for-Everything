/*
 * nrf905.h
 *
 *  Created on: 2009-5-8
 *      Author: Administrator
 */

#ifndef NRF905_H_
#define NRF905_H_

// regs
#define WC  0x00    // Write configuration register command
#define RC  0x10  // Read  configuration register command
#define WTP  0x20  // Write TX Payload  command
#define RTP  0x21 // Read  TX Payload  command
#define WTA  0x22 // Write TX Address  command
#define RTA  0x23 // Read  TX Address  command
#define RRP  0x24 // Read  RX Payload  command

// Control IOs
#define NRF905_TX_EN   RF_IO4 // PB3
#define NRF905_TRX_CE  RF_IO5 // PB2
#define NRF905_PWR_UP  RF_IO6 // PB1
#define NRF905_CD      RF_IO3
#define NRF905_AM      RF_IO1
#define NRF905_DR      RF_IO2
#define NRF905_CSN     RF_IO0

// Define data packet
#define NRF905_PKT_LEN   32
typedef struct {
 u8_t buf[NRF905_PKT_LEN];
 u8_t len;
} packet_905_t;
extern packet_905_t tx_pkt_905;
extern packet_905_t rx_pkt_905;
extern u8_t rx_flag_905;

void nrf_setup(void);
void nrf_powerup_reset(void);
void nrf_write_settings(void);

void nrf_send_packet(u8_t *tx_buf, u8_t size);
u8_t nrf_receive_packet(u8_t *rx_buf, u8_t *length);

void nrf_test(void);

#endif /* NRF905_H_ */