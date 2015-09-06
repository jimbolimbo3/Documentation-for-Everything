/*
 * nrf905.c
 *
 *  Created on: 2009-5-8
 *      Author: zhb
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "common.h"
#include "nrf905.h"
#include "key.h"

// The content of this struct is nRF905's initialize data.
// CH_NO=1;433MHZ;Normal Opration,No Retrans;RX,TX Address is 4 Bytes
// RX TX Payload Width is 32 Bytes;Disable Extern Clock;Fosc=16MHZ
// 8 Bits CRC And enable
u8_t RxTxConf[10] = {
 0x01, 0x0c, 0x44, 0x20, 0x20, 0xcc, 0xcc, 0xcc, 0xcc, 0x58
 //0x01, 0x0c, 0x44, 0x20, 0x20, 0xcc, 0xcc, 0xcc, 0xcc, 0x5c
};

packet_905_t tx_pkt_905;
packet_905_t rx_pkt_905;
u8_t rx_flag_905;

static void nrf_wait(u16_t cycles)
{
    while (cycles > 6)
        cycles -= 6;
}

// config NRF905 IOs
void nrf_setup(void)
{
 // CSN
 DDRB |= NRF905_CSN;
 PORTB |= NRF905_CSN;

 // other config
 DDRB |= NRF905_PWR_UP | NRF905_TRX_CE | NRF905_TX_EN;

 // config SPI protocol
 //SPSR |= (1<<SPI2X); // set SPI clock frequency doubling 
 SPCR |= (1<<SPE)|(1<<MSTR);  // enable SPI jack£¬master mode

 cli(); // clean all the interrupts
 MCUCR |= 0x0c; // INT1 trailing edge trigger
 GICR |= 0x80; // enable INT1

 rx_flag_905 = 0;
}

// Reset after power on
void nrf_powerup_reset(void)
{
 // switch to standby mode
 PORTB |= NRF905_PWR_UP;
 PORTB &= ~NRF905_TRX_CE;
 PORTB &= ~NRF905_TX_EN;
}

// Config parameters of NRF905
void nrf_write_settings(void)
{
 u8_t i;

 // enter standby mode
 PORTB |= NRF905_PWR_UP;
 PORTB &= ~NRF905_TRX_CE;
 PORTB &= ~NRF905_TX_EN;

 nrf_wait(20);

 PORTB &= ~NRF905_CSN;
 // Clear flag set during addr TX
 SPSR = 0x00;
 // Write config command
 SPDR = WC;
 // Wait for TX to finish
 while (!(SPSR & (1<<SPIF))) ;
 nrf_wait(20);
 // Write configration words
 for (i=0; i<10; i++) {
  // Clear flag
  SPSR = 0x00;
  // Write config word
  SPDR = RxTxConf[i];
  // Wait for TX to finish
  while (!(SPSR & (1<<SPIF))) ;
  nrf_wait(20);
 }
 // Clear flag
 SPSR = 0x00;
 PORTB |= NRF905_CSN;

 nrf_wait(20);

 // set RX mode
 PORTB &= ~NRF905_TX_EN;
 PORTB |= NRF905_TRX_CE;
 // ÑÓÊ±>=650us
 nrf_wait(30);
}

// Send a packet
void nrf_send_packet(u8_t *tx_buf, u8_t size)
{
 u8_t i;

 // check if collapse
 while (PIND&NRF905_CD) ;

 // switch to standby mode
 PORTB &= ~NRF905_TRX_CE;
 PORTB |= NRF905_TX_EN;
 nrf_wait(10);

 // write datas to transfer
 PORTB &= ~NRF905_CSN;
 // Clear flag set during addr TX
 SPSR = 0x00;
 SPDR = WTP;
 // Wait for TX to finish
 while (!(SPSR & (1<<SPIF))) ;
 nrf_wait(10);
 for (i=0; i<size; i++) {
  // Clear flag
  SPSR = 0x00;
  SPDR = tx_buf[i];
  // Wait for TX to finish
  while (!(SPSR & (1<<SPIF))) ;
  nrf_wait(10);
 }
 // Clear flag
 SPSR = 0x00;
 PORTB |= NRF905_CSN;
 nrf_wait(10);

 // write TX address
 PORTB &= ~NRF905_CSN;
 // Clear flag set during addr TX
 SPSR = 0x00;
 SPDR = WTA;
 // Wait for TX to finish
 while (!(SPSR & (1<<SPIF))) ;
 nrf_wait(10);
 for (i=0; i<4; i++) {
  // Clear flag
  SPSR = 0x00;
  SPDR = 0xcc;
  // Wait for TX to finish
  while (!(SPSR & (1<<SPIF))) ;
  nrf_wait(10);
 }
 // Clear flag
 SPSR = 0x00;
 PORTB |= NRF905_CSN;

 // start to TX
 PORTB |= NRF905_TRX_CE;
 // wait for tx complete...
 while ((PIND&NRF905_DR) == 0) ; // wait for DR hi
 nrf_wait(10);
 // switch to RX mode
 PORTB &= ~NRF905_TX_EN;
 nrf_wait(20);
}

// receive a packet
u8_t nrf_receive_packet(u8_t *rx_buf, u8_t *length)
{
 u8_t i;

 // Set nRF905 in standby mode
 PORTB &= ~NRF905_TRX_CE;

 PORTB &= ~NRF905_CSN;
 // Clear flag set during addr TX
 SPSR = 0x00;
 SPDR = RRP; // Read payload command
 // Wait for TX to finish
 while (!(SPSR & (1<<SPIF))) ;
 nrf_wait(10);
 for (i=0; i<*length; i++) {
  // clear flag
  SPSR = 0x00;
  SPDR = 0x55; // Read payload command
  // Wait for TX to finish
  while (!(SPSR & (1<<SPIF))) ;
  nrf_wait(10);
  rx_buf[i] = SPDR; // Read data and save to buffer
 }
 // clear flag
 SPSR = 0x00;
 PORTB |= NRF905_CSN;

 // switch to RX mode
 PORTB |= NRF905_TRX_CE;
 nrf_wait(20);

 return 0;
}

// receive interrupt function
SIGNAL(SIG_INTERRUPT1)
{
 rx_pkt_905.len = 32;
 nrf_receive_packet(rx_pkt_905.buf, &(rx_pkt_905.len));
 rx_flag_905 = 1;
}