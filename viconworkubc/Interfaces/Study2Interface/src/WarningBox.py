from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class WarningBox(QWidget):
    def __init__(self, warning_text):
        super().__init__()

        self.fw_frame_rack = QFrame()

        self.fw_frame_rack.setFrameStyle(QFrame.NoFrame)
        self.fw_frame_rack.setLineWidth(0)
        self.fw_frame_rack.setMidLineWidth(3)
        self.fw_frame_rack.setMinimumSize(600, 420)

        self.fw_rack = QHBoxLayout()
        self.fw_rack.setAlignment(Qt.AlignCenter)

        self.warningLabel = QLabel()
        self.fw_rack.addWidget(self.warningLabel)
        font = self.warningLabel.font()
        font.setPointSizeF(128)
        self.warningLabel.setFont(font)
        self.warningLabel.setText(warning_text)

        self.firstWindow2 = QVBoxLayout()  # Create a vertical Layout to contain both QLayouts
        self.firstWindow2.setAlignment(Qt.AlignCenter)
        self.firstWindow2.addLayout(self.fw_rack)

        self.fw_frame_rack.setLayout(self.firstWindow2)  # Assign VLayout to the frame

    def warning_box(self):
        return self.fw_frame_rack

    def setWarningText(self, warning_text):
        self.warningLabel.setText(warning_text)