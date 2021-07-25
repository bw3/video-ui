#ifndef PROCESS_H
#define PROCESS_H

#include <QProcess>
#include <QVariant>

class Process : public QProcess
{
    Q_OBJECT
    Q_PROPERTY(bool isFinished READ isFinished NOTIFY isFinishedChanged)
public:
    Process(QObject *parent = 0) : QProcess(parent) {
        m_finished = false;
        QObject::connect(this, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Process::setFinished);
    }

    Q_INVOKABLE void start(const QString &program, const QVariantList &arguments) {
        QStringList args;

        // convert QVariantList from QML to QStringList for QProcess 

        for (int i = 0; i < arguments.length(); i++)
            args << arguments[i].toString();
        setWorkingDirectory(std::getenv("HOME"));
        QProcess::start(program, args);
    }

    bool isFinished() {
        return m_finished;
    }

    Q_INVOKABLE bool waitForFinished(int msecs = 30000) {
        return QProcess::waitForFinished(msecs);
    }
public slots:
    void setFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        m_finished = true;
        emit isFinishedChanged();
    }

signals:
    void isFinishedChanged();
private:
    bool m_finished;
};

#endif // PROCESS_H
