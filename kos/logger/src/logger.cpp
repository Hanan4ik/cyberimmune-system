/**
 * \file
 * \~English
 * \brief Implementation of methods for work with a log.
 * \details The file contains implementation of methods, that are required to log messages.
 *
 * \~Russian
 * \brief Реализация методов для работы с логом.
 * \details В файле реализованы методы, необходимые для логирования сообщений.
 */

#include "../include/logger.h"
#include "../../shared/include/ipc_messages_server_connector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createLog() {
    return 1;
}

int addLogEntry(char* entry, int level) {
    char logHeader[32] = {0};
    switch (level) {
    case 0:
        strcpy(logHeader, "[TRACE]");
        break;
    case 1:
        strcpy(logHeader, "[DEBUG]");
        break;
    case 2:
        strcpy(logHeader, "[INFO]");
        break;
    case 3:
        strcpy(logHeader, "[WARNING]");
        break;
    case 4:
        strcpy(logHeader, "[ERROR]");
        break;
    case 5:
        strcpy(logHeader, "[CRITICAL]");
        break;
    }
    fprintf(stderr, "%s %s\n", logHeader, entry);

    return 1;
}