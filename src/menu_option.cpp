#include "menu_option.h"

MenuOption::MenuOption(const std::string optionName, const std::vector<std::string> options) {
    m_options=options;
    m_selectedOption = 0;
    m_optionName = optionName;
}

const QString MenuOption::html() {
    std::string html = m_optionName + ": ";
    for(size_t i=0;i<m_options.size();i++) {
        if(i == m_selectedOption) {
            html += "<u>" + m_options[i] + "</u>";
        } else {
            html += "" + m_options[i] + "";
        }
        if( i + 1 < m_options.size() ) {
            html += " | ";
        }
    }

    html+="";
    return html.c_str();
}

Q_INVOKABLE void MenuOption::increment() {
    m_selectedOption++;
    if(m_selectedOption == m_options.size()) {
        m_selectedOption = 0;
    }
    emit htmlChanged();
}

Q_INVOKABLE void MenuOption::decrement() {
    if(m_selectedOption == 0 ) {
        m_selectedOption = m_options.size();
    }
    m_selectedOption--;
    emit htmlChanged();
}

std::string MenuOption::getSelectedString() {
    return m_options[m_selectedOption];
}

size_t MenuOption::getSelectedIndex() {
    return m_selectedOption;
}

std::string MenuOption::getName() {
    return m_optionName;
}
