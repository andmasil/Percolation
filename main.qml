import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Percolation")

    Timer
    {
        interval: 1
        running: !Percolation.finished
        repeat: true

        onTriggered: Percolation.openNextRandomSite()
    }

    Connections
    {
        target: Percolation

        onStateChange: repeater.itemAt(id).backColor = color
    }

    Grid
    {
        id: board
        anchors.fill: parent
        columns: Math.sqrt(repeater.count)
        rows: Math.sqrt(repeater.count)

        Repeater
        {
            id: repeater
            model: Percolation.qmlModel

            MouseArea
            {
                property alias backColor: background.color
                id: mouseArea
                width: board.width / board.columns
                height: board.height / board.rows

                Rectangle
                {
                    id: background
                    anchors.fill: parent
                    color: modelData
                    border.color: 'black'
                }
            }
        }
    }
}

