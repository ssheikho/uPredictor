from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

class Application_Control():
    def __init__(self):
        super().__init__()
        self.key_controllers = []
        self.n_key_controllers = 0

    def addWindowContainer(self, windowContainer):
        self.windowContainer = windowContainer

    def addKeyController(self, key_controller):
        self.key_controllers.append(key_controller)
        self.n_key_controllers = self.n_key_controllers + 1

    def keyPressEvent(self, event):
        if (type(event) == QKeyEvent):
            key = event.key()
            for i in range(0, self.n_key_controllers):
                self.key_controllers[i].keyPressEvent(event)