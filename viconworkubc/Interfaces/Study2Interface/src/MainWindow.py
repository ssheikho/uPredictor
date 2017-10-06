from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import csv
import datetime
import sys
import time
import resources2

from application_control import *
from baskets import *
from create_warning_box import *
from create_windows_class import *
from IconDict import *
from Rack import *
from Ramp import *
from StudyTwoLogic import *
from WarningBox import *
from WindowContainer import *

#In this program, the main window serves only as a container for other widgets.
class Mainwindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Caris Lab - University of British Columbia")
        self.frame = QFrame()
        self.vbox = QHBoxLayout()
        self.vbox.setSpacing(0)
        self.vbox.setAlignment(Qt.AlignCenter)
        self.frame.setLayout(self.vbox)
        self.setCentralWidget(self.frame)

    def moveToWindow1(self):
        self.setGeometry(100, 100, 100, 100)
        self.showFullScreen()

    def moveToWindow2(self):
        self.setGeometry(2020, 100, 100, 100)
        self.showFullScreen()

    def setWindowContainer(self, windowContainer):
        self.windowContainer = windowContainer

    def keyPressEvent(self, event):
        self.windowContainer.keyPressEvent(event)

    def addWidget(self, widget):
        self.vbox.addWidget(widget)

def main():
    simulation = QApplication(sys.argv)

    windowContainer = WindowContainer()

    icon_dict = IconDict(0)
    icon_dict_small = IconDict(1)

    applicationControl = Application_Control()
    windowContainer.addKeyPressManager(applicationControl)
    applicationControl.addWindowContainer(windowContainer)

    rampWindow = Ramp(icon_dict)
    baskets = Baskets(icon_dict_small)
    rackWindowA = Rack(icon_dict)
    rackWindowB = Rack(icon_dict)
    warningA = WarningBox("Proceed to Round: 0?")
    warningB = WarningBox("Hit Enter")

    leftWindow = Mainwindow()
    rightWindow = Mainwindow()
    leftWindow.addWidget(rampWindow.ramp_window())
    leftWindow.addWidget(rackWindowA.rack_window())
    rightWindow.addWidget(baskets.baskets_window())
    rightWindow.addWidget(rackWindowB.rack_window())
    leftWindow.addWidget(warningA.warning_box())
    rightWindow.addWidget(warningB.warning_box())

    palette = QPalette()
    palette.setColor(QPalette.Background, Qt.white)

    windowContainer.addWindow(leftWindow)
    leftWindow.setPalette(palette)
    leftWindow.moveToWindow1()
    leftWindow.show()
    leftWindow.raise_()

    windowContainer.addWindow(rightWindow)
    rightWindow.setPalette(palette)
    rightWindow.moveToWindow2()
    rightWindow.show()
    rightWindow.raise_()

    logic = StudyTwoLogic(rampWindow, rackWindowA, rackWindowB, baskets, warningA, warningB, leftWindow, rightWindow
                          , windowContainer)
    applicationControl.addKeyController(logic)

    simulation.exec_()

if __name__ == "__main__":
    main()