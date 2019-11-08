import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Percolation")

    Grid
    {
        id: board
        anchors.fill: parent
        anchors.margins: 10
        columns: Math.sqrt(Percolation.sitesNumber)
        rows: Math.sqrt(Percolation.sitesNumber)

        Repeater
        {
            model: Percolation.sitesNumber

            MouseArea
            {
                width: board.width / board.columns
                height: board.height / board.rows

                Rectangle
                {
                    id: background
                    anchors.fill: parent
                    color: 'black'
                    border.color: 'black'
                }

                onPressed:
                {
                    background.color = 'white'
                    Percolation.openSite(index)
                }
            }
        }
    }
}

