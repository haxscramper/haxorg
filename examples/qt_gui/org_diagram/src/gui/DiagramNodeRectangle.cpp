#include "DiagramNodeRectangle.hpp"

QWidget* DiagramNodeRectangle::createPropertiesWidget(QWidget* parent) {
    auto widget = new QWidget{parent};
    auto layout = new QVBoxLayout{widget};

    layout->addWidget(new QLabel{"Rectangle Properties"});

    auto nameEdit = new QLineEdit{name};
    layout->addWidget(new QLabel{"Name:"});
    layout->addWidget(nameEdit);

    auto colorButton = new QPushButton{"Change Color"};
    colorButton->setStyleSheet(
        std::format("background-color: {}", color.name().toStdString())
            .c_str());
    layout->addWidget(new QLabel{"Color:"});
    layout->addWidget(colorButton);

    auto widthSpin = new QSpinBox{};
    widthSpin->setRange(10, 500);
    widthSpin->setValue(static_cast<int>(bounds.width()));
    layout->addWidget(new QLabel{"Width:"});
    layout->addWidget(widthSpin);

    auto heightSpin = new QSpinBox{};
    heightSpin->setRange(10, 500);
    heightSpin->setValue(static_cast<int>(bounds.height()));
    layout->addWidget(new QLabel{"Height:"});
    layout->addWidget(heightSpin);

    QObject::connect(
        nameEdit,
        &QLineEdit::textChanged,
        widget,
        [this](const QString& text) {
            name = text;
            update();
        });

    QObject::connect(
        colorButton, &QPushButton::clicked, widget, [this, colorButton]() {
            QColor newColor = QColorDialog::getColor(color);
            if (newColor.isValid()) {
                color = newColor;
                colorButton->setStyleSheet(
                    std::format(
                        "background-color: {}", color.name().toStdString())
                        .c_str());
                update();
            }
        });

    QObject::connect(
        widthSpin,
        QOverload<int>::of(&QSpinBox::valueChanged),
        widget,
        [this](int value) {
            bounds.setWidth(value);
            update();
        });

    QObject::connect(
        heightSpin,
        QOverload<int>::of(&QSpinBox::valueChanged),
        widget,
        [this](int value) {
            bounds.setHeight(value);
            update();
        });

    layout->addStretch();
    return widget;
}
