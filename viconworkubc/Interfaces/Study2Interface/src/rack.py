from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Rack(QWidget):
    def __init__(self, icon_dict):
        super().__init__()

        self.icon_dict = icon_dict

        self.clearBallColors()
        self.clearHighlights()

        self.fw_frame_rack = QFrame()

        self.fw_frame_rack.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.fw_frame_rack.setLineWidth(2)
        self.fw_frame_rack.setMidLineWidth(3)
        self.fw_frame_rack.setMinimumSize(600, 420)

        self.rack_col = QVBoxLayout()
        self.rack_col.setAlignment(Qt.AlignCenter)
        self.rack_rows = []

        self.rack_labels = []
        self.number_col_labels = []
        self.number_row_labels = []

        for row in range(0,3):
            rowbox = QHBoxLayout()
            self.rack_col.addLayout(rowbox)
            self.rack_rows.append(rowbox)
            for col in range(0,3):
                curRackLabel = QLabel()
                self.rack_labels.append(curRackLabel)
                rowbox.addWidget(curRackLabel)
            curNumLabel = QLabel()
            self.number_col_labels.append(curNumLabel)
            rowbox.addWidget(curNumLabel)
            curNumLabel.setPixmap(icon_dict.icon_dict[icon_dict.letters[row]])

        self.updateBallPixmaps()

        rowbox = QHBoxLayout()
        self.rack_col.addLayout(rowbox)
        self.rack_rows.append(rowbox)
        for col in range(0,3):
            curNumLabel = QLabel()
            self.number_row_labels.append(curNumLabel)
            rowbox.addWidget(curNumLabel)
            curNumLabel.setPixmap(icon_dict.icon_dict[icon_dict.numbers[col + 1]])

        curNumLabel = QLabel()
        self.number_row_labels.append(curNumLabel)
        rowbox.addWidget(curNumLabel)
        curNumLabel.setPixmap(icon_dict.icon_dict['box_white'])

        self.fw_frame_rack.setLayout(self.rack_col)  # Assign VLayout to the frame

    def rack_window(self):
        return self.fw_frame_rack

    def clearHighlights(self):
        self.ballHighlights = [False, False, False, False,False, False, False, False, False]

    def highlightBall(self, index):
        self.clearHighlights()
        self.ballHighlights[index] = True

    def clearBallColors(self):
        self.rack_icon_strings = []
        for i in range(0,9):
            self.rack_icon_strings.append("black")

    def getBallColor(self, index):
        # print("RACK_ICON_STRINGS %s" % self.rack_icon_strings[index])
        return self.rack_icon_strings[index]

    def setBallColor(self, index, color_index):
        # print("index:   %d" % index)
        # print("color_index:   %d" % color_index)
        self.rack_icon_strings[index] = self.icon_dict.ramp_pos[color_index]

    def updateBallPixmaps(self):
        for i in range(0,9):
            icon_dict = self.icon_dict.icon_dict
            if self.ballHighlights[i]:
                icon_dict = self.icon_dict.icon_dict_selected
            self.rack_labels[i].setPixmap(icon_dict[self.rack_icon_strings[i]])