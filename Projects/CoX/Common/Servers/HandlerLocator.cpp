#include "HandlerLocator.h"

#include "SEGSEvent.h"
#include "EventProcessor.h"

#include <QDebug>
EventProcessor * HandlerLocator::m_db_sync_handler = nullptr;
EventProcessor * HandlerLocator::m_auth_handler = nullptr;
std::deque<EventProcessor *> HandlerLocator::m_game_servers;
std::deque<EventProcessor *> HandlerLocator::m_game_db_servers;
std::deque<EventProcessor *> HandlerLocator::m_map_servers;
MessageBus * HandlerLocator::m_message_bus=nullptr;
void shutDownAllActiveHandlers()
{
    for(EventProcessor *game_handler : HandlerLocator::allGameHandlers())
    {
        if(!game_handler)
            continue;
        auto warn = qWarning();
        warn<<"Shutting down GameServer..";
        game_handler->putq(new SEGSEvent(SEGS_EventTypes::evFinish));
        game_handler->wait();
        delete game_handler;
        warn<<"Done";
    }
    for(EventProcessor *game_db_handler : HandlerLocator::allGameDBHandlers())
    {
        if(!game_db_handler)
            continue;
        auto warn = qWarning();
        warn<<"Shutting down GameDBSync..";
        game_db_handler->putq(new SEGSEvent(SEGS_EventTypes::evFinish));
        game_db_handler->wait();
        delete game_db_handler;
        warn<<"Done";
    }

    EventProcessor *authhandler = HandlerLocator::getAuth_Handler();
    if(authhandler)
    {
        auto warn = qWarning();
        warn<<"Shutting down AuthHandler..";
        authhandler->putq(new SEGSEvent(SEGS_EventTypes::evFinish));
        authhandler->wait();
        delete authhandler;
        warn<<"Done";
    }
    EventProcessor *dbsync=HandlerLocator::getAuthDB_Handler();
    if(dbsync)
    {
        auto warn = qWarning(); // no new line will be appended to ouput untill `warn` is alive
        warn<<"Shutting down DBSync..";
        dbsync->putq(new SEGSEvent(SEGS_EventTypes::evFinish));
        dbsync->wait();
        delete dbsync;
        warn<<"Done";
    }


}


