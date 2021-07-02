#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <QObject>
#include <QString>

class MenuOption : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString html READ html NOTIFY htmlChanged)

public:
    MenuOption(const std::string optionName, const std::vector<std::string> options);

    const QString html();
    Q_INVOKABLE void increment();
    Q_INVOKABLE void decrement();
    std::string getSelectedString();
    size_t getSelectedIndex();
    std::string getName();

signals:
    void htmlChanged();

private:
    std::vector<std::string> m_options;
    size_t m_selectedOption;
    std::string m_optionName;
};
#endif //BACKEND_H
