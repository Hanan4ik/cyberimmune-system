/**
 * \file
 * \~English
 * \brief Implementation of methods for ATM server communication simulation.
 * \details The file contains implementation of methods, that simulate
 * requests to an ATM server send and received responses process.
 *
 * \~Russian
 * \brief Реализация методов для имитации общения с сервером ОРВД.
 * \details В файле реализованы методы, имитирующие отправку запросов на сервер ОРВД
 * и обработку полученных ответов.
 */

#include "../include/server_connector.h"

#include <stdio.h>
#include <string.h>

int flightStatusSend, missionSend, areasSend, armSend, newMissionSend, destinationRfid;

int initServerConnector() {
    if (strlen(BOARD_ID))
        setBoardName(BOARD_ID);
    else
        setBoardName("00:00:00:00:00:00");

    flightStatusSend = true;
    missionSend = true;
    areasSend = true;
    armSend= false;
    newMissionSend = false;
    destinationRfid = 0;

    return 1;
}

int requestServer(char* query, char* response, uint32_t responseSize) {
    if (strstr(query, "/api/auth?")) {
        if (responseSize < 10) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(response, "$Success#", 10);
    }
    else {
        if (responseSize < 3) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(response, "$#", 3);
    }

    return 1;
}

int publish(char* topic, char* publication) {
    if (strstr(topic, "api/arm/request"))
        armSend = true;
    else if (strstr(topic, "api/nmission/request"))
        newMissionSend = true;
    else if (strstr(topic, "api/rfid")) {
        if (strstr(publication, "tag=rfid2"))
            destinationRfid = 1;
        else
            destinationRfid = 2;
    }

    return 1;
}

int getSubscription(char* topic, char* message, uint32_t messageSize) {
    if (strstr(topic, "ping/")) {
        if (messageSize < 10) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$Delay 1#", 10);
    }
    else if (strstr(topic, "api/flight_status/") && flightStatusSend) {
        if (messageSize < 11) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$Flight 0#", 11);
        flightStatusSend = false;
    }
    else if (strstr(topic, "api/fmission_kos/") && missionSend) {
#ifdef IS_INSPECTOR
        if (messageSize < 420) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$FlightMission H60.0025741_27.8573723_0.0&T1.0&W60.0026011_27.8573723_1.0&W60.0026011_27.8574442_1.0&W60.0025652_27.8574442_1.0&W60.0025652_27.8574981_1.0&W60.002637_27.8574981_1.0&W60.002637_27.8576059_1.0&D3.0&W60.0026011_27.8576059_1.0&D3.0&W60.0026011_27.857552_1.0&W60.0026191_27.857552_1.0&D3.0&W60.0025921_27.857552_1.0&L0.0_0.0_0.0&I60.002637_27.8576059_0.0&I60.0026011_27.8576059_0.0&I60.0026191_27.857552_0.0#", 420);
#else
        if (messageSize < 308) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$FlightMission H60.002628_27.8573723_0.0&T1.0&W60.0026011_27.8573723_1.0&W60.0026011_27.8574442_1.0&W60.0025652_27.8574442_1.0&W60.0025652_27.8574981_1.0&W60.002637_27.8574981_1.0&W60.002637_27.8576059_1.0&W60.0026191_27.8576059_1.0&D3.0&S5.0_1200.0&D1.0&S5.0_1800.0&W60.0025741_27.8576059_1.0&L0.0_0.0_0.0#", 308);
#endif
        missionSend = false;
    }
    else if (strstr(topic, "api/forbidden_zones") && areasSend) {
        if (messageSize < 773) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$ForbiddenZones 2&outerOne&15&60.0025472_27.8573184&60.002655_27.8573184&60.002655_27.8576418&60.002646_27.8576418&60.002646_27.8574442&60.002628_27.8574442&60.002628_27.8574801&60.0025741_27.8574801&60.0025741_27.8574621&60.0026101_27.8574621&60.0026101_27.8574082&60.002646_27.8574082&60.002646_27.8573364&60.0025472_27.8573364&60.0025472_27.8573184&outerTwo&19&60.0025562_27.8573364&60.0025562_27.8574082&60.0025921_27.8574082&60.0025921_27.8574262&60.0025562_27.8574262&60.0025562_27.857516&60.002628_27.857516&60.002628_27.857534&60.0025831_27.857534&60.0025831_27.8575879&60.0025741_27.8575879&60.0025741_27.857534&60.0025562_27.857534&60.0025562_27.8576239&60.002646_27.8576239&60.002646_27.8576418&60.0025472_27.8576418&60.0025472_27.8573364&60.0025562_27.8573364#", 773);
        areasSend = false;
    }
    else if (strstr(topic, "api/arm/response/") && armSend) {
        if (messageSize < 16) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$Arm 0$Delay 1#", 16);
    }
    else if (strstr(topic, "api/nmission/response/") && newMissionSend) {
        if (messageSize < 13) {
            logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
            return 0;
        }
        strncpy(message, "$Approve 0#", 13);
    }
    else if (strstr(topic, "api/rfid/response/") && destinationRfid) {
        if (destinationRfid == 1) {
            if (messageSize < 7) {
                logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
                return 0;
            }
            strncpy(message, "$TRUE#", 7);
        }
        else {
            if (messageSize < 8) {
                logEntry("Size of response does not fit given buffer", ENTITY_NAME, LogLevel::LOG_WARNING);
                return 0;
            }
            strncpy(message, "$FALSE#", 8);
        }
        destinationRfid = 0;
    }
    else
        strcpy(message, "");

    return 1;
}