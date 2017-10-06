from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

class WindowContainer():
    def __init__(self):
        super().__init__()
        self.windows = []
        self.windowCount = 0

    def addWindow(self, window):
        self.windows.append(window)
        window.setWindowContainer(self)
        self.windowCount = self.windowCount + 1

    def addKeyPressManager(self, keyPressManager):
        self.keyPressManager = keyPressManager

    def closeAll(self):
        for i in range(0, self.windowCount):
            self.windows[i].close()

    def keyPressEvent(self, event):
        self.keyPressManager.keyPressEvent(event)