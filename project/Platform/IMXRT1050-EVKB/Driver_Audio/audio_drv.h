/*
 * Copyright (c) 2021 Arm Limited. All rights reserved.
 */

#ifndef __AUDIO_DRV_H
#define __AUDIO_DRV_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/* Audio Interface */
#define AUDIO_DRV_INTERFACE_TX              (1U)  ///< Transmitter
#define AUDIO_DRV_INTERFACE_RX              (2U)  ///< Receiver

/* Audio Control */
#define AUDIO_DRV_CONTROL_TX_ENABLE         (1UL << 0)  ///< Enable Transmitter
#define AUDIO_DRV_CONTROL_RX_ENABLE         (1UL << 1)  ///< Enable Receiver
#define AUDIO_DRV_CONTROL_TX_DISABLE        (1UL << 2)  ///< Disable Transmitter
#define AUDIO_DRV_CONTROL_RX_DISABLE        (1UL << 3)  ///< Disable Receiver

/* Audio Event */
#define AUDIO_DRV_EVENT_TX_DATA             (1UL << 0)  ///< Data block transmitted
#define AUDIO_DRV_EVENT_RX_DATA             (1UL << 1)  ///< Data block received

/* Return code */
#define AUDIO_DRV_OK                        (0)  ///< Operation succeeded
#define AUDIO_DRV_ERROR                     (-1) ///< Unspecified error
#define AUDIO_DRV_ERROR_BUSY                (-2) ///< Driver is busy
#define AUDIO_DRV_ERROR_TIMEOUT             (-3) ///< Timeout occurred
#define AUDIO_DRV_ERROR_UNSUPPORTED         (-4) ///< Operation not supported
#define AUDIO_DRV_ERROR_PARAMETER           (-5) ///< Parameter error

/**
\brief Audio Status
*/
typedef struct {
  uint32_t tx_active        :  1;       ///< Transmitter active
  uint32_t rx_active        :  1;       ///< Receiver active
  uint32_t reserved         : 30;
} AudioDrv_Status_t;

/**
  \fn          void AudioDrv_Event_t (uint32_t event)
  \brief       Audio Events callback.
  \param[in]   event Events notification mask
  \return      none
*/
typedef void (*AudioDrv_Event_t) (uint32_t event);

/**
  \fn          int32_t AudioDrv_Initialize (AudioDrv_Event_t cb_event)
  \brief       Initialize Audio Interface.
  \param[in]   cb_event Pointer to \ref AudioDrv_Event_t
  \return      return code
*/
int32_t AudioDrv_Initialize (AudioDrv_Event_t cb_event);

/**
  \fn          int32_t AudioDrv_Uninitialize (void)
  \brief       De-initialize Audio Interface.
  \return      return code
*/
int32_t AudioDrv_Uninitialize (void);

/**
  \fn          int32_t AudioDrv_Configure (uint32_t interface, uint32_t channels, uint32_t sample_bits, uint32_t sample_freq)
  \brief       Configure Audio Interface.
  \param[in]   interface   Audio Interface
  \param[in]   channels    Number of channels
  \param[in]   sample_bits Sample number of bits (8..32)
  \param[in]   sample_rate Sample rate (samples per second)
  \return      return code
*/
int32_t AudioDrv_Configure (uint32_t interface, uint32_t channels, uint32_t sample_bits, uint32_t sample_rate);

/**
  \fn          int32_t AudioDrv_SetBuf (uint32_t interface, void *buf, uint32_t block_count, uint32_t block_size)
  \brief       Set Audio Interface buffer.
  \param[in]   interface   Audio Interface
  \param[in]   buf         Pointer to buffer for audio data
  \param[in]   block_num   Number of blocks in buffer (must be 2^n)
  \param[in]   block_size  Block size in number of samples
  \return      return code
*/
int32_t AudioDrv_SetBuf (uint32_t interface, void *buf, uint32_t block_num, uint32_t block_size);

/**
  \fn          int32_t AudioDrv_Control (uint32_t control)
  \brief       Control Audio Interface.
  \param[in]   control Operation
  \return      return code
*/
int32_t AudioDrv_Control (uint32_t control);

/**
  \fn          uint32_t AudioDrv_GetTxCount (void)
  \brief       Get transmitted block count.
  \return      number of transmitted blocks
*/
uint32_t AudioDrv_GetTxCount (void);

/**
  \fn          uint32_t AudioDrv_GetRxCount (void)
  \brief       Get received block count.
  \return      number of received blocks
*/
uint32_t AudioDrv_GetRxCount (void);

/**
  \fn          AudioDrv_Status_t AudioDrv_GetStatus (void)
  \brief       Get Audio Interface status.
  \return      \ref AudioDrv_Status_t
*/
AudioDrv_Status_t AudioDrv_GetStatus (void);

#ifdef  __cplusplus
}
#endif

#endif /* __AUDIO_DRV_H */
