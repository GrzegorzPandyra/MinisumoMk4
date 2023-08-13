#ifndef LOGGER_CFG_GUARD
#define LOGGER_CFG_GUARD
/*! @file logger_cfg.h
    @brief Configuration of logger
*/
/* Enable/disable logging */
#define LOGGING_ENABLED 1U

/*  When buffering is enabled, all logs shall be enqueued and transmitted based on task execution. 
    When buffering is disabled logs shall be sent directly to UDR */
#define BUFFERING_ENABLED 1U

/* Immediately push TX buffer when overflow is detected. Turning it off will cause data loss. */
#define TRANSMIT_WHEN_TX_OVFL 1U

/* Buffer sizes */
#define BUFFER_SIZE_SMALL   30U
#define BUFFER_SIZE_MEDIUM  100U
#define BUFFER_SIZE_LARGE   400U

/* Maximum number of digits for line number logging */
#define MAX_LINE_NUMBER_DIGITS 4u

#endif /* LOGGER_CFG_GUARD */
