#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core_global.h>
#include <QMainWindow>
#include <QMap>
#include <QProgressBar>

namespace Ui {
class MainWindow;
}

class CoreService;
class QLabel;
class CommandButton;
class ScriptSandbox;

class CORE_EXTERN MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Mode {
        HomeMode,
        ElsewhereMode
    };

public:
    explicit MainWindow(CoreService *core, QWidget *parent = 0);
    ~MainWindow();

    void setPageIndex(int index);

    Q_INVOKABLE int RegisterPage(const QIcon &icon, const QString &title, const QString &description,
                                 QWidget* widget, bool lower = false);
    void SetCurrentPageButton(int index);
public slots:
    void OnProfileBadgeImage(const QString &badge, QImage image);
    void UpdateAccountMessagesCount(int messages);
    void AppendScriptOutput(const QString &output, const QString &type = "LOG");
private slots:
    void on_lineEdit_returnPressed();
    void on_messagesButton_clicked();
    void on_reloadScriptsButton_clicked();
    void on_homeButton_clicked();
signals:
    void Loaded();
private:
    Ui::MainWindow *ui;
    CoreService* _core;

    void setMode(Mode mode);

    Mode _mode;

    QMap<QString, QLabel*> _badgeMap;

    QMap<int, CommandButton*> _buttonForPage;

    ScriptSandbox* _script;

    QLabel* _statusBarLabel;
    QProgressBar* _statusBarProgress;
};
Q_DECLARE_METATYPE(MainWindow*)

#endif // MAINWINDOW_H