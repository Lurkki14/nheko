#pragma once

#include <string>
#include <vector>

#include <QMediaPlayer>
#include <QObject>
#include <QString>
#include <QTimer>

#include "mtx/events/collections.hpp"
#include "mtx/events/voip.hpp"

namespace mtx::responses {
struct TurnServer;
}

class WebRTCSession;

class CallManager : public QObject
{
        Q_OBJECT

public:
        CallManager(QObject *);

        void sendInvite(const QString &roomid, bool isVideo);
        void hangUp(
          mtx::events::msg::CallHangUp::Reason = mtx::events::msg::CallHangUp::Reason::User);
        bool onActiveCall() const;
        QString callPartyName() const { return callPartyName_; }
        QString callPartyAvatarUrl() const { return callPartyAvatarUrl_; }
        void refreshTurnServer();

public slots:
        void syncEvent(const mtx::events::collections::TimelineEvents &event);

signals:
        void newMessage(const QString &roomid, const mtx::events::msg::CallInvite &);
        void newMessage(const QString &roomid, const mtx::events::msg::CallCandidates &);
        void newMessage(const QString &roomid, const mtx::events::msg::CallAnswer &);
        void newMessage(const QString &roomid, const mtx::events::msg::CallHangUp &);
        void newCallParty();
        void newVideoCallState();
        void turnServerRetrieved(const mtx::responses::TurnServer &);

private slots:
        void retrieveTurnServer();

private:
        WebRTCSession &session_;
        QString roomid_;
        QString callPartyName_;
        QString callPartyAvatarUrl_;
        std::string callid_;
        const uint32_t timeoutms_ = 120000;
        std::vector<mtx::events::msg::CallCandidates::Candidate> remoteICECandidates_;
        std::vector<std::string> turnURIs_;
        QTimer turnServerTimer_;
        QMediaPlayer player_;

        template<typename T>
        bool handleEvent_(const mtx::events::collections::TimelineEvents &event);
        void handleEvent(const mtx::events::RoomEvent<mtx::events::msg::CallInvite> &);
        void handleEvent(const mtx::events::RoomEvent<mtx::events::msg::CallCandidates> &);
        void handleEvent(const mtx::events::RoomEvent<mtx::events::msg::CallAnswer> &);
        void handleEvent(const mtx::events::RoomEvent<mtx::events::msg::CallHangUp> &);
        void answerInvite(const mtx::events::msg::CallInvite &, bool isVideo);
        void generateCallID();
        void clear();
        void endCall();
        void playRingtone(const QString &ringtone, bool repeat);
        void stopRingtone();
};
