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

#endif /* LOGGER_CFG_GUARD */
