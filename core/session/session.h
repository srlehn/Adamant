#ifndef SESSION_H
#define SESSION_H

#include <core_global.h>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QScopedPointer>
#include <QPointer>

class CoreService;

class CORE_EXTERN Session : public QObject
{
    Q_OBJECT
public:
    class Request;
    class ForumRequest;

    enum AttributeData {
        LoginSessionId = 0x01,
        Badge,
        UserData,
        League,
        Character,
        ForumSubmissionData
    };

    enum SessionLoginState {
        Idle,
        Success,
        Failed
    };

    static QUrl BaseUrl() {
        return QUrl("https://www.pathofexile.com");
    }

    static QUrl APIUrl() {
        return QUrl("https://www.pathofexile.com/api");
    }

    static QUrl LoginUrl() {
        return QUrl(BaseUrl().toString() + "/login");
    }

    static QUrl MainUrl() {
        return QUrl(BaseUrl().toString() + "/news");
    }

    static QUrl ProfileDataUrl() {
        return QUrl(APIUrl().toString() + "/account");
    }

    static QUrl AccountUrl() {
        return QUrl(BaseUrl().toString() + "/my-account");
    }

    static QUrl StashUrl() {
        return QUrl(BaseUrl().toString() + "/character-window/get-stash-items");
    }

    static QUrl CharacterItemsUrl() {
        return QUrl(BaseUrl().toString() + "/character-window/get-items");
    }

    static QUrl CharactersUrl() {
        return QUrl(BaseUrl().toString() + "/character-window/get-characters");
    }

    static QUrl LeaguesUrl() {
        return QUrl(BaseUrl().toString() + "/api/leagues?type=main");
    }

    static QString SessionIdCookie() {
        return "POESESSID";
    }

    Session(CoreService* parent);
    ~Session();

    void resetLoginState() {
        _loginState = SessionLoginState::Idle;
    }

    SessionLoginState loginState() const {
        return _loginState;
    }

    const QString accessToken() const {
        return _accessToken;
    }

    const QString sessionId() const {
        return _sessionId;
    }

    const QString accountName() const {
        return _accountName;
    }

    const QStringList leagues() const {
        return _leagues;
    }

    Request* request() const {
        return _request.data();
    }

    ForumRequest* forum() const {
        return _forumRequest.data();
    }

    void logError(const QString &error) const;

    static void SetCustomRequestAttribute(QNetworkRequest* request, AttributeData attr, const QVariant &data);
    static const QVariant GetCustomRequestAttribute(const QNetworkRequest *request, AttributeData attr);
    QNetworkRequest createRequest(const QUrl &url) const;
signals:
    void sessionChange();
private:
    CoreService* _core;
    SessionLoginState _loginState;
    QString _sessionId;
    QString _accessToken;
    QString _accountName;
    QStringList _leagues;

    QScopedPointer<QNetworkAccessManager> _manager;
    QScopedPointer<Request> _request;
    QScopedPointer<ForumRequest> _forumRequest;
};

#endif // SESSION_H
