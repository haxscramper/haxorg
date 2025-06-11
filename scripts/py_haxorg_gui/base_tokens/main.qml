import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15



ApplicationWindow {
    visible: true
    width: 1200
    height: 600
    title: "Token Visualizer"

    function replaceInvisibleChars(str) {
        const replacements = {
            '\x00': "␀",
            '\x01': "␁",
            '\x02': "␂",
            '\x03': "␃",
            '\x04': "␄",
            '\x05': "␅",
            '\x06': "␆",
            '\x07': "␇",
            '\x08': "␈",
            '\x09': "␉",
            '\x0A': "␤",
            '\x0B': "␋",
            '\x0C': "␌",
            '\x0D': "␍",
            '\x0E': "␎",
            '\x0F': "␏",
            '\x10': "␐",
            '\x11': "␑",
            '\x12': "␒",
            '\x13': "␓",
            '\x14': "␔",
            '\x15': "␕",
            '\x16': "␖",
            '\x17': "␗",
            '\x18': "␘",
            '\x19': "␙",
            '\x1A': "␚",
            '\x1B': "␛",
            '\x1C': "␜",
            '\x1D': "␝",
            '\x1E': "␞",
            '\x1F': "␟",
            '\x7f': "␡",
            ' ': "␣",
            '\t': "\\t",
            '\n': "\\n"
        };

        return str.split('').map((ch) => replacements[ch] || ch).join('');
    }

    ScrollView {
        width: parent.width;
        height: parent.height;
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn;
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn;

        ListView {
            model: tokenProvider.tokenRows;
            spacing: 2;
            delegate: Row {
                spacing: 2;
                RowLayout {
                    spacing: 1;
                    Rectangle {
                        width: 60;
                        height: 20;
                        border.width: 1;
                        radius: 2;
                        Text {
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            text: index;
                        }
                    }

                    Repeater {
                        model: modelData;
                        delegate: Rectangle {
                            border.width: 1;
                            radius: 4;
                            Layout.alignment: Qt.AlignCenter;
                            width: Math.max(tokenInfo.width, tokenText.width) + 10;
                            height: tokenInfo.height + tokenText.height + 10;
                            anchors.margins: 10 / 2;

                            color: {
                                if (modelData.kind === "Newline" || modelData.kind === "Whitespace") "cyan"
                                else if (modelData.kind === "SubtreeStars") "red"
                                else if (modelData.kind === "Word") "green"
                                else "white"
                            }

                            TextMetrics {
                                id: tokenText;
                                font.family: "Arial"
                                font.pixelSize: 14;
                                elide: Text.ElideMiddle
                                elideWidth: 100
                                text: replaceInvisibleChars(modelData.text);
                            }

                            TextMetrics {
                                id: tokenInfo;
                                text: modelData.kind;
                                font.pixelSize: 8;
                                font.italic: true;
                            }

                            ColumnLayout {
                                id: textItem;
                                spacing: 0;

                                Text {
                                    width: tokenText.width;
                                    text: tokenText.text;
                                    font.pixelSize: tokenText.font.pixelSize;
                                    Layout.topMargin: 5;
                                    Layout.leftMargin: 5;
                                    Layout.alignment: Qt.AlignHCenter;
                                }
                                Text {
                                    width: tokenInfo.width;
                                    text: tokenInfo.text;
                                    font.pixelSize: tokenInfo.font.pixelSize;
                                    font.italic: tokenInfo.font.italic;
                                    Layout.leftMargin: 5;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
