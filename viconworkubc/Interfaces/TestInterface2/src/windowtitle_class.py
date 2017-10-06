from PyQt4.QtCore import *
from PyQt4.QtGui import *

import sys

class Windowtitle(QWidget):

    def __init__(self, label):
        super().__init__()

        self.title_label = QLabel(label)
        self.main_layout = QVBoxLayout()
        self.main_layout.addWidget(self.title_label)

        self.setLayout(self.main_layout)