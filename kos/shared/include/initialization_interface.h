/**
 * \file
 * \~English \brief Declaration of Initialization IDL-interface methods and methods
 * for wrappers over IPC message handlers.
 * \~Russian \brief Объявление методов IDL-интерфейса Initialization и методов, необходимых
 * оберткам над обработчиками IPC-сообщений.
 */

#pragma once

#include <coresrv/nk/transport-kos.h>

/**
 * \~English Initializes interface for IPC message send.
 * Used by all wrappers over IPC message send methods.
 * \param[in] connection Name of the connection used by IPC message receiver component.
 * \param[in] endpoint Full name of IDL method in "project.entity.endpoint" format.
 * \param[out] transport KasperskyOS transport structure.
 * \param[out] riid Interface realisation ID.
 * \~Russian Инициализирует интерфейс для отправки IPC-сообщений.
 * Используется всеми обертками над методами отправки IPC-сообщений.
 * \param[in] connection Имя соединения, используемого компонентом-получателем IPC-сообщения.
 * \param[in] endpoint Полное имя IDL-метода в формате "проект.сущность.конечная точка".
 * \param[out] transport Транспортная структура KasperskyOS.
 * \param[out] riid ID реализации интерфейса.
 */
void initSenderInterface(const char* connection, const char* endpoint, NkKosTransport &transport, nk_iid_t &riid);
/**
 * \~English Initializes interface for IPC message receive.
 * Used by all components with IPC-message handling main loops.
 * \param[in] connection Name of the connection used by IPC message receiver component.
 * \param[out] transport KasperskyOS transport structure.
 * \~Russian Инициализирует интерфейс для получения IPC-сообщений.
 * Используется всеми компонентами с основным циклом в виде обработки IPC-сообщений.
 * \param[in] connection Имя соединения, используемого компонентом-получателем IPC-сообщения.
 * \param[out] transport Транспортная структура KasperskyOS.
 */
void initReceiverInterface(const char* connection, NkKosTransport &transport);
