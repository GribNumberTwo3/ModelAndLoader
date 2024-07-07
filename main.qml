import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 340
    height: 480

    Rectangle {
        id: root
        anchors.fill: parent
        color: "green"

        QtObject {
            id: dataProvider
            function getData() {
                return [
                    {
                        name: "Param 1",
                        value: "STRING_VALUE"
                    },
                    {
                        name: "Param 2",
                        value: true
                    },
                    {
                        name: "Param 3",
                        value: 5
                    }
                ]
            }
        }

        Component.onCompleted: {
            mapModel.setData(dataProvider.getData());
        }

        ListView {
            id: myview
            anchors.fill: parent
            model: mapModel

            delegate: Item {
                width: parent.width
                height: 50

                Rectangle {
                    anchors.fill: parent
                    border.color: "yellow"

                    Text {
                        text: model.name
                        width: parent.width * 0.3
                        verticalAlignment: Text.AlignVCenter
                    }

                    Loader {
                        width: parent.width * 0.7
                        property var m_model: model.value
                        property int modelIndex: index
                        anchors.left: parent.left
                        anchors.leftMargin: 80
                        sourceComponent: {
                            switch (typeof model.value) {
                                case "string": return stringDelegateComponent;
                                case "boolean": return boolDelegateComponent;
                                case "number": return numberDelegateComponent;
                                default: return unknownDelegateComponent;
                            }
                        }

                        onLoaded: {
                            item.index = modelIndex
                        }
                    }
                }
            }
        }

        Component {
            id: stringDelegateComponent

            TextField {
                property int index
                text: m_model

                onEditingFinished: {
                    if(text !== m_model){
                        mapModel.updateData(index, text)
                        console.log(m_model)
                    }
                }
            }
        }

        Component {
            id: boolDelegateComponent

            CheckBox {
                property int index
                checked: m_model

                onCheckedChanged: {
                    if(checked !== m_model) {
                        mapModel.updateData(index, checked)
                        console.log(m_model)
                    }
                }
            }
        }

        Component {
            id: numberDelegateComponent
            SpinBox {
                property int index
                value: m_model

                onValueChanged: {
                    if(value !== m_model){
                        mapModel.updateData(index, value)
                        console.log(m_model)
                    }
                }
            }
        }

        Component {
            id: unknownDelegateComponent
            Text {
                text: "Unsupported type"
                color: "red"
            }
        }
    }
}
