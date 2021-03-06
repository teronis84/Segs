/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */

#pragma once

#include "Entity.h"

#include <QMutex>
#include <QtSql/QSqlQuery>
#include <string>

class IClient;
class QSqlQuery;
class CharacterClient;
class CharacterCostume;
class Character;
class AccountInfo;
class CharacterDatabase
{
        QSqlDatabase * m_db = nullptr;

        QSqlQuery m_prepared_account_select;
        QSqlQuery m_prepared_account_insert;
        QSqlQuery m_prepared_entity_select;
        QSqlQuery m_prepared_char_insert;
        QSqlQuery m_prepared_char_exists;
        QSqlQuery m_prepared_char_delete;
        QSqlQuery m_prepared_char_select;
        QSqlQuery m_prepared_char_update;
        QSqlQuery m_prepared_fill;
        QSqlQuery m_prepared_costume_insert;
        QSqlQuery m_prepared_costume_update;
        QSqlQuery m_prepared_options_update;
        QSqlQuery m_prepared_gui_update;

public:
virtual             ~CharacterDatabase();
        bool        CreateLinkedAccount(uint64_t auth_account_id,const std::string &username,int max_character_slots); // returns true on success
        bool        create(AccountInfo *);
        bool        create(uint64_t gid, uint8_t slot, Entity *e);
        bool        fill( AccountInfo *); //!x
        bool        fill( Entity *e ); //! Will call fill(CharacterCostume)
        bool        fill( Character *c ); //! Will call fill(CharacterCostume)
        bool        fill( CharacterCostume *);
        bool        update(Entity *);
        bool        updateClientOptions(Entity *);
        bool        updateGUISettings(Entity *);
        bool        update(CharacterCostume *);
        int         remove_account(uint64_t acc_serv_id); //will remove given account, TODO add logging feature
        bool        remove_character(AccountInfo *, int8_t slot_idx);
        bool        named_character_exists(const QString &name);
        void        setDb(QSqlDatabase *db) {m_db=db;}
        QSqlDatabase *getDb() {return m_db;}
        void        on_connected(QSqlDatabase *db); //prepare statements here
        CharacterFromDB *getCharacter(const QString &name);
        CharacterFromDB *getCharacter(int32_t db_id);
};
