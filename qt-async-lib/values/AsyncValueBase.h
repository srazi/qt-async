/*
   Copyright (c) 2018 Alex Zhondin <lexxmark.dev@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef ASYNC_VALUE_BASE_H
#define ASYNC_VALUE_BASE_H

#include "../Config.h"
#include "../third_party/scope_exit.h"
#include <QObject>
#include <QMutex>
#include <QReadWriteLock>
#include <QWaitCondition>
#include <QThread>

enum class ASYNC_VALUE_STATE
{
    VALUE,
    ERROR,
    PROGRESS
};
Q_DECLARE_METATYPE(ASYNC_VALUE_STATE);

class AsyncValueBase : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AsyncValueBase)

signals:
    void stateChanged(ASYNC_VALUE_STATE state);

protected:
    explicit AsyncValueBase(ASYNC_VALUE_STATE state, QObject* parent = nullptr);

    QMutex m_writeLock;
    QReadWriteLock m_contentLock;
    ASYNC_VALUE_STATE m_state;

    struct Waiter
    {
        QWaitCondition waitValue;

        quint16 subWaiters = 0;
        QWaitCondition waitSubWaiters;
    };
    Waiter* m_waiter = nullptr;
};

#endif // ASYNC_VALUE_BASE_H
